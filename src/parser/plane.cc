#include "parser/plane.hpp"
#include "syntax_highlighting.hpp"


const Vector3 &Plane::getPoint() const {
	return point;
}


void Plane::setPoint(const Vector3 &pt) {
	point     = pt;
	point_set = true;
}


const Vector3 &Plane::getNormal() const {
	return normal;
}


void Plane::setNormal(const Vector3 &N) {
	normal = N;
	normal.normalize();
	normal_set = true;
}


std::shared_ptr<Object::IntersectionMetadata> Plane::intersect(const Ray &r) const {
	double d = normal.dot(r.direction);

	if (abs(d) <= 1e-6)
		return nullptr;

	double t = (point - r.origin).dot(normal) / d;
	if (t <= 1e-6)
		return nullptr;

	const auto res = std::make_shared<IntersectionMetadata>(r, t);

	res->normal = normal;
	res->mat = retrieveMaterialData();

	return res;
}


SyntaxHighlighter &Plane::dump(SyntaxHighlighter &sh) const {
	sh << "Plane";

	if (identifier)
		sh << *identifier;
	sh << "{";

	sh << "material" << "=";
	dump_material(sh);

	if (point_set)
		sh << "point" << "=" << point;
	if (normal_set)
		sh << "normal" << "=" << normal;


	return sh << "}";
}