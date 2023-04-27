#include "sphere.hpp"
#include <string>
#include <sstream>
#include <vector>

const Material Sphere::default_material(Color(255,255,255));


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
