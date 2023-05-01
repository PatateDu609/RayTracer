#ifndef RAYTRACER_INCLUDE_SCENE_HPP
#define RAYTRACER_INCLUDE_SCENE_HPP

#include <vector>
#include <memory>
#include <map>

#include "resolution.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "ambient_light.hpp"
#include "point_light.hpp"
#include "anti_aliasing.hpp"


void dump_scene();


class NoSceneLoadedException : public std::exception {
public:
	const char *what() const noexcept override;
};

class SceneParserProxy {
public:
	SceneParserProxy() = delete;
	SceneParserProxy(const SceneParserProxy &other) = delete;
	SceneParserProxy &operator=(const SceneParserProxy &other) = delete;

private:
	static void set_resolution(const Resolution &resolution);
	static void set_anti_aliasing(const AntiAliasing &anti_aliasing);
	static void set_ambient_light(const AmbientLight &ambient_light);
	static void set_camera(const Camera &camera);

	static void append_point_light(const PointLight &point_light);
	static void append_object(const std::shared_ptr<Object> &obj);
	static void append_material(const Material &material);

	friend class yy::parser;
};

class Scene {
public:
	class MissingRequiredPropertyOrBlock : public std::exception {
	public:
		explicit MissingRequiredPropertyOrBlock(const std::string &name);
		const char *what() const noexcept override;

	private:
		std::string message;
	};

	[[nodiscard]] static const Resolution &resolution();
	[[nodiscard]] static const std::optional<AntiAliasing> &antiAliasing();
	[[nodiscard]] static Camera &camera();

	[[nodiscard]] static std::vector<std::shared_ptr<Light>> lights();
	[[nodiscard]] static const std::vector<std::shared_ptr<Object>> &objects();
	[[nodiscard]] static std::shared_ptr<Material> material(const std::string &id);

	static bool cast_shadow_ray(const PointLight &pt, const std::shared_ptr<Object::IntersectionMetadata> &metadata);

private:
	static std::unique_ptr<Scene> scene_instance;

	// Mandatory fields
	std::shared_ptr<Resolution>   res;
	std::optional<AntiAliasing>   anti_aliasing;
	std::shared_ptr<AmbientLight> ambient_lighting;
	std::shared_ptr<Camera>       cam;

	// Optional fields
	std::vector<std::shared_ptr<PointLight>>         pt_lights;
	std::vector<std::shared_ptr<Object>>             objs;
	std::map<std::string, std::shared_ptr<Material>> mats;

	friend SceneParserProxy;

	friend void dump_scene();
};

#endif //RAYTRACER_INCLUDE_SCENE_HPP
