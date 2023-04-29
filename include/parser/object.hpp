#ifndef RAYTRACER_INCLUDE_PARSER_OBJECT_HPP
#define RAYTRACER_INCLUDE_PARSER_OBJECT_HPP

#include <variant>
#include <memory>
#include "scene_block_object.hpp"
#include "material.hpp"
#include "engine/ray.hpp"

class Object : public SceneBlockObject {
public:
	struct IntersectionMetadata {
		IntersectionMetadata(const Ray &r, double t);

		Vector3  normal;
		Vector3  hit;
		Material mat;
		double   t;
		const Ray &r;
	};

	virtual std::shared_ptr<IntersectionMetadata> intersect(const Ray &r) const = 0;

	[[nodiscard]] std::variant<Material, std::string> getMaterial() const;

	void setMaterial(const Material& m);
	void setMaterial(const std::string& material_id);
	void resetMaterial();

protected:
	virtual SyntaxHighlighter& dump(SyntaxHighlighter& sh) const = 0;
	void dump_material(SyntaxHighlighter& sh) const;

	Material retrieveMaterialData() const;

	std::optional<std::variant<Material, std::string>> mat;

private:
	static const Material default_material;

	friend SyntaxHighlighter& operator<<(SyntaxHighlighter& sh, const std::shared_ptr<Object>& obj);
};

#endif //RAYTRACER_INCLUDE_PARSER_OBJECT_HPP
