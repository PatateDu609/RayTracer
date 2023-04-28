#include "parser/sphere.hpp"
#include "parser/scene.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

const Material Sphere::default_material(Color(255, 255, 255));


IntersectionMetadata::IntersectionMetadata(const Ray &ray, double param) : t(param), r(ray) {
	hit = r(t);
}


const Vector &Sphere::getPosition() const {
	return position;
}


std::variant<Material, std::string> Sphere::getMaterial() const {
	if (mat)
		return *mat;

	std::variant<Material, std::string> res(default_material);
	return res;
}


double Sphere::getRadius() const {
	return radius;
}


void Sphere::setPosition(const Vector &p) {
	position     = p;
	position_set = true;
}


void Sphere::setMaterial(const Material &m) {
	mat = m;
}


void Sphere::setMaterial(const std::string &material_id) {
	mat = material_id;
}


void Sphere::resetMaterial() {
	mat.reset();
}


void Sphere::setRadius(double r) {
	radius     = r;
	radius_2   = r * r;
	radius_set = true;
}


std::ostream &operator<<(std::ostream &os, const Sphere &s) {
	os << "Sphere";
	if (s.identifier)
		os << "(" << *s.identifier << ")";
	os << "{";

	std::vector<std::string> parts;
	std::ostringstream       oss;

	if (s.position_set) {
		oss << "position = " << s.position;
		parts.push_back(oss.str());
		oss.str("");
		oss.clear();
	}

	if (s.mat.has_value()) {
		oss << "material = ";
		const auto variant = *s.mat;

		if (std::holds_alternative<std::string>(variant))
			oss << "Material(" << std::get<std::string>(variant) << ")";
		else
			oss << std::get<Material>(variant);

		parts.push_back(oss.str());
		oss.str("");
		oss.clear();
	}

	if (s.radius_set) {
		oss << "radius = " << s.radius;
		parts.push_back(oss.str());
		oss.str("");
		oss.clear();
	}

	if (parts.empty())
		return os << "}";

	os << parts[0];
	for (size_t i = 1; i < parts.size(); i++)
		os << ", " << parts[i];

	return os << "}";
}


std::shared_ptr<IntersectionMetadata> Sphere::intersect(const Ray &r) const {
	auto ro_center = r.origin - position; // ray origin -> sphere center

	double a = r.direction.dot(r.direction);
	double b = 2 * r.direction.dot(ro_center);
	double c = ro_center.dot(ro_center) - radius_2;

	double discriminant = std::pow(b, 2) - 4 * a * c;
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


std::shared_ptr<IntersectionMetadata> Sphere::make_metadata(const Ray &r, double t) const {
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