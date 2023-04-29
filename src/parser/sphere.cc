#include "parser/sphere.hpp"
#include "parser/scene.hpp"
#include "syntax_highlighting.hpp"
#include <string>
#include <sstream>
#include <cmath>



const Vector3 &Sphere::getPosition() const {
	return position;
}




double Sphere::getRadius() const {
	return radius;
}


void Sphere::setPosition(const Vector3 &p) {
	position     = p;
	position_set = true;
}


void Sphere::setRadius(double r) {
	radius     = r;
	radius_2   = std::pow(r, 2);
	radius_set = true;
}


SyntaxHighlighter &Sphere::dump(SyntaxHighlighter &sh) const {
	sh << "Sphere";
	if (identifier)
		sh << *identifier;
	sh << "{";

	if (position_set)
		sh << "position" << "=" << position;

	if (mat.has_value()) {
		sh << "material" << "=";
		dump_material(sh);
	}

	if (radius_set) {
		sh << "radius" << "=" << radius << SyntaxHighlighter::endl;
	}

	return sh << "}";
}


std::shared_ptr<Object::IntersectionMetadata> Sphere::intersect(const Ray &r) const {
	auto ro_center = r.origin - position; // ray origin -> sphere center

	double a = 1;
	double b = 2 * r.direction.dot(ro_center);
	double c = ro_center.dot(ro_center) - radius_2;

	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return nullptr;

	double minus_b_2a = -b / (2 * a);
	if (discriminant == 0)
		return make_metadata(r, minus_b_2a);

	double delta = std::sqrt(discriminant);
	double t1    = minus_b_2a + delta;
	double t     = 0;
	if (t1 >= 0)
		t = t1;

	double t2 = minus_b_2a - delta;
	if (t2 <= t)
		t = t2;

	if (t1 < 0 && t2 < 0)
		return nullptr;

	return make_metadata(r, t);
}


std::shared_ptr<Object::IntersectionMetadata> Sphere::make_metadata(const Ray &r, double t) const {
	IntersectionMetadata metadata(r, t);

	metadata.normal = (-metadata.hit + position).normalize();
	metadata.mat = retrieveMaterialData();
	return std::make_shared<IntersectionMetadata>(metadata);
}