#include "parser/object.hpp"
#include "syntax_highlighting.hpp"

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


SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, const std::shared_ptr<Object> &obj) {
	obj->dump(sh);
	return sh;
}


void Object::dump_material(SyntaxHighlighter &sh) const {
	const auto variant = getMaterial();

	if (std::holds_alternative<std::string>(variant))
		sh << std::get<std::string>(variant) << SyntaxHighlighter::endl;
	else
		sh << std::get<Material>(variant);
}


Material Object::retrieveMaterialData() const {
	const auto &material = getMaterial();

	if (std::holds_alternative<std::string>(material)) {
		std::string mat_name = std::get<std::string>(material);
		const auto  mat_ptr  = Scene::material(mat_name);
		if (!mat_ptr)
			throw std::runtime_error("Material " + mat_name + " specified not found");
		return *mat_ptr;
	}

	return std::get<Material>(material);
}