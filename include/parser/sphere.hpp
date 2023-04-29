#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include "scene_block_object.hpp"
#include "material.hpp"
#include "maths/vector.hpp"
#include "engine/ray.hpp"
#include <variant>
#include <memory>

struct IntersectionMetadata {
	IntersectionMetadata(const Ray& r, double t);

	Vector3  normal;
	Vector3  hit;
	Material mat;
	double t;
	const Ray& r;
};

class Sphere : public SceneBlockObject {
public:
	Sphere& operator=(const Sphere& other) = default;

	[[nodiscard]] const Vector3 &getPosition() const;
	[[nodiscard]] std::variant<Material, std::string> getMaterial() const;
	[[nodiscard]] double getRadius() const;

	void setPosition(const Vector3& p);
	void setMaterial(const Material& m);
	void setMaterial(const std::string& material_id);
	void resetMaterial();
	void setRadius(double r);

	std::shared_ptr<IntersectionMetadata> intersect(const Ray& r) const;

private:
	static const Material default_material;

	Vector3 position;
	bool    position_set{false};

	std::optional<std::variant<Material, std::string>> mat;

	double radius;
	double radius_2;
	bool   radius_set{false};

	std::shared_ptr<IntersectionMetadata> make_metadata(const Ray& r, double t) const;

	friend class yy::parser;
	friend SyntaxHighlighter& operator<<(SyntaxHighlighter& sh, const Sphere& s);
};

#endif //RAY_TRACER_SPHERE_HPP
