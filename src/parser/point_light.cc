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


Color PointLight::compute_lighting(const std::shared_ptr<IntersectionMetadata> &metadata) const {
	Vector3 i_l            = (position - metadata->hit).normalize(); // Intersection hit point ----> Light position
	double  dot            = std::max(0., (-i_l).dot(metadata->normal));
	Color   d_object_color = metadata->mat.getDiffuse();
	Color   d_light_color  = getColor();

	Color res;

	double common = (getIntensity() * dot) / std::pow(i_l.norm(), 2);

	res.albedo_r(std::max(0., std::min(1., d_object_color.albedo_r() * d_light_color.albedo_r() * common)));
	res.albedo_g(std::max(0., std::min(1., d_object_color.albedo_g() * d_light_color.albedo_g() * common)));
	res.albedo_b(std::max(0., std::min(1., d_object_color.albedo_b() * d_light_color.albedo_b() * common)));

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