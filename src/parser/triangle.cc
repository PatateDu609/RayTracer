#include "parser/triangle.hpp"
#include "syntax_highlighting.hpp"

const std::vector<Vector3> &Triangle::vertices() const {
	return _vertices;
}


void Triangle::vertices(const std::vector<Vector3> &v) {
	_vertices = v;
}

SyntaxHighlighter &Triangle::dump(SyntaxHighlighter &sh) const {
	sh << "Triangle";

	if (identifier)
		sh << *identifier;
	sh << "{";

	sh << "material" << "=";
	dump_material(sh);

	sh << "points" << "=" << "(" << _vertices[0];
	for (size_t i = 1; i < _vertices.size(); i++)
		sh << "," << _vertices[i];
	sh << ")";

	return sh << "}";
}


std::shared_ptr<Object::IntersectionMetadata> Triangle::intersect(const Ray &r) const {
	return nullptr;
}
