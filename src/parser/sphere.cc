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


SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, const Sphere &s) {
	sh << "Sphere";
	if (s.identifier)
		sh << *s.identifier;
	sh << "{";

	if (s.position_set)
		sh << "position" << "=" << s.position;

	if (s.mat.has_value()) {
		sh << "material" << "=";
		const auto variant = *s.mat;

		if (std::holds_alternative<std::string>(variant))
			sh << std::get<std::string>(variant);
		else
			sh << std::get<Material>(variant);
	}

	if (s.radius_set) {
		sh << "radius" << "=" << s.radius << SyntaxHighlighter::endl;
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
	if (t2 >= t)
		t = t2;

	if (t1 < 0 && t2 < 0)
		return nullptr;

	return make_metadata(r, t);
}


std::shared_ptr<Object::IntersectionMetadata> Sphere::make_metadata(const Ray &r, double t) const {
	IntersectionMetadata metadata(r, t);

	metadata.normal = (metadata.hit - position).normalize();

	const auto &material = getMaterial();
	if (std::holds_alternative<std::string>(material)) {
		std::string mat_name = std::get<std::string>(material);
		const auto  mat_ptr  = Scene::material(mat_name);
		if (!mat_ptr)
			throw std::runtime_error("Material " + mat_name + " specified not found");
		metadata.mat = *mat_ptr;
	} else
		metadata.mat = std::get<Material>(material);
	return std::make_shared<IntersectionMetadata>(metadata);
}