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
	static void set_ambient_light(const AmbientLight &ambient_light);
	static void set_camera(const Camera &camera);

	static void append_point_light(const PointLight &point_light);
	static void append_sphere(const Sphere &sphere);
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
	[[nodiscard]] static const AmbientLight &ambient_light();
	[[nodiscard]] static const Camera &camera();

	[[nodiscard]] static const std::vector<std::unique_ptr<PointLight>> &point_lights();
	[[nodiscard]] static const std::vector<std::unique_ptr<Sphere>> &spheres();
	[[nodiscard]] static std::shared_ptr<Material> material(const std::string &id);

private:
	static std::unique_ptr<Scene> scene_instance;

	// Mandatory fields
	std::unique_ptr<Resolution>   res;
	std::unique_ptr<AmbientLight> ambient_lighting;
	std::unique_ptr<Camera>       cam;

	// Optional fields
	std::vector<std::unique_ptr<PointLight>>         pt_lights;
	std::vector<std::unique_ptr<Sphere>>             sps;
	std::map<std::string, std::shared_ptr<Material>> mats;

	friend SceneParserProxy;

	friend void dump_scene();
};

#endif //RAYTRACER_INCLUDE_SCENE_HPP
