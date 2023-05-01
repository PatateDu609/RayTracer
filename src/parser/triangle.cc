#include "parser/triangle.hpp"
#include "syntax_highlighting.hpp"


const std::vector<Vector3> &Triangle::vertices() const {
	return _vertices;
}


void Triangle::vertices(const std::vector<Vector3> &v) {
	_vertices = v;
	_normal.reset();
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


constexpr double EPSILON = 1e-7;


std::shared_ptr<Object::IntersectionMetadata> Triangle::intersect(const Ray &r) const {
	Vector3 v0 = _vertices[0];
	Vector3 v1 = _vertices[1];
	Vector3 v2 = _vertices[2];

	Vector3 e1 = v1 - v0;
	Vector3 e2 = v2 - v0;
	Vector3 h, s, q;
	double  a, f, u, v;

	h = r.direction.cross(e2);
	a = e1.dot(h);

	if (abs(a) < EPSILON)
		return nullptr;

	f = 1. / a;
	s = r.origin - v0;
	u = f * s.dot(h);

	if (u < 0 || u > 1)
		return nullptr;

	q = s.cross(e1);
	v = f * r.direction.dot(q);

	if (v < 0 || v + u > 1.)
		return nullptr;

	float t = f * e2.dot(q);

	if (t <= EPSILON)
		return nullptr;

	Vector3 n = *_normal;
	if (_normal->dot(-r.direction) < 0)
		n = -*_normal;

	auto metadata = std::make_shared<IntersectionMetadata>(r, t);
	metadata->mat    = retrieveMaterialData();
	metadata->normal = n;

	return metadata;
}


void Triangle::compute_normal() {
	_normal = _vertices[0].cross(_vertices[1]);
}