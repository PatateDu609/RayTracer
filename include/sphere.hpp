#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include "scene_block_object.hpp"
#include "material.hpp"
#include "vector.hpp"
#include <variant>

class Sphere : public SceneBlockObject {
public:
	[[nodiscard]] const Vector &getPosition() const;
	[[nodiscard]] std::variant<Material, std::string> getMaterial() const;
	[[nodiscard]] double getRadius() const;

	void setPosition(const Vector& p);
	void setMaterial(const Material& m);
	void setMaterial(const std::string& material_id);
	void resetMaterial();
	void setRadius(double r);

private:
	static const Material default_material;

	Vector position;
	bool   position_set;

	std::optional<std::variant<Material, std::string>> mat;

	double radius;
	bool   radius_set;

	friend class yy::parser;
	friend std::ostream &operator<<(std::ostream& os, const Sphere& s);
};

#endif //RAY_TRACER_SPHERE_HPP
