#include "parser/object.hpp"

const Material Object::default_material(Color(255, 255, 255));


Object::IntersectionMetadata::IntersectionMetadata(const Ray &ray, double param) : t(param), r(ray) {
	hit = r(t);
}


void Object::setMaterial(const Material &m) {
	mat = m;
}


void Object::setMaterial(const std::string &material_id) {
	mat = material_id;
}


void Object::resetMaterial() {
	mat.reset();
}


std::variant<Material, std::string> Object::getMaterial() const {
	if (mat)
		return *mat;

	std::variant<Material, std::string> res(default_material);
	return res;
}
