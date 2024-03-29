#ifndef RAY_TRACER_INCLUDE_MATERIAL_HPP
#define RAY_TRACER_INCLUDE_MATERIAL_HPP

#include "scene_block_object.hpp"
#include "color.hpp"

class Material : public SceneBlockObject {
public:
	Material();
	explicit Material(const Color& diffuse);

	[[nodiscard]] const Color& getDiffuse() const;
	void setDiffuse(const Color& d);

private:
	Color diffuse;
	bool diffuse_set{false};

	friend yy::parser;
	friend SyntaxHighlighter& operator<<(SyntaxHighlighter& sh, const Material& mat);
};

#endif //RAY_TRACER_INCLUDE_MATERIAL_HPP
