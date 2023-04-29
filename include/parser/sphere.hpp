#ifndef RAY_TRACER_SPHERE_HPP
#define RAY_TRACER_SPHERE_HPP

#include "material.hpp"
#include "maths/vector.hpp"
#include "engine/ray.hpp"
#include "object.hpp"
#include <variant>
#include <memory>

class Sphere : public Object {
public:
	Sphere() = default;
	Sphere(const Sphere&) = default;
	Sphere &operator=(const Sphere &other) = default;

	[[nodiscard]] const Vector3 &getPosition() const;
	[[nodiscard]] double getRadius() const;

	void setPosition(const Vector3 &p);
	void setRadius(double r);

	virtual std::shared_ptr<Object::IntersectionMetadata> intersect(const Ray &r) const final;

protected:
	virtual SyntaxHighlighter &dump(SyntaxHighlighter &sh) const final;

private:

	Vector3 position;
	bool    position_set{false};

	double radius;
	double radius_2;
	bool   radius_set{false};

	std::shared_ptr<IntersectionMetadata> make_metadata(const Ray &r, double t) const;

	friend class yy::parser;
};

#endif //RAY_TRACER_SPHERE_HPP
