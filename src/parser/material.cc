#include "parser/material.hpp"
#include "syntax_highlighting.hpp"


Material::Material() : diffuse(0, 0, 0), diffuse_set(false) {

}


Material::Material(const Color &diff) : diffuse(diff), diffuse_set(true) {

}


const Color &Material::getDiffuse() const {
	return diffuse;
}


void Material::setDiffuse(const Color &d) {
	diffuse     = d;
	diffuse_set = true;
}


SyntaxHighlighter& operator<<(SyntaxHighlighter& sh, const Material& mat) {
	sh << "Material";
	if (mat.identifier)
		sh << *mat.identifier;
	sh << "{";

	if (mat.diffuse_set)
		sh << "diffuse" << "=" << mat.diffuse;

	return sh << "}";
}