#include <complex>
#include "parser/point_light.hpp"
#include "syntax_highlighting.hpp"


PointLight::PointLight(const std::string &id) : Light(id) {

}


const Vector3 &PointLight::getPosition() const {
	return position;
}


void PointLight::setPosition(const Vector3 &pos) {
	position_set = true;
	position     = pos;
}


Color PointLight::compute_lighting(const std::shared_ptr<Object::IntersectionMetadata> &metadata) const {
	Vector3 L       = position - metadata->hit; // Intersection hit point ----> Light position
	double  L_norm2 = std::pow(L.norm(), 2);
	double  L_dot_N = std::max(L.normalize().dot(metadata->normal.normalize()), 0.);

	Color res = 5000 * ((metadata->mat.getDiffuse() / M_PI) * getIntensity() * getColor() * (L_dot_N / L_norm2));

	return res;
}


SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, const PointLight &pt) {
	sh << "point_light";

	if (pt.identifier)
		sh << *pt.identifier;
	sh << "{";

	if (pt.position_set)
		sh << "position" << "=" << pt.position;

	sh << "color" << "=" << pt.getColor();
	sh << "intensity" << "=" << pt.getIntensity() << SyntaxHighlighter::endl;

	return sh << "}";
}