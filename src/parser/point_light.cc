#include <complex>
#include "parser/point_light.hpp"


PointLight::PointLight(const std::string &id) : Light(id) {

}


const Vector &PointLight::getPosition() const {
	return position;
}


void PointLight::setPosition(const Vector &pos) {
	position_set = true;
	position     = pos;
}


Color PointLight::compute_lighting(const std::shared_ptr<IntersectionMetadata> &metadata) const {
	Vector i_l            = (position - metadata->hit).normalize(); // Intersection hit point ----> Light position
	double dot            = std::max(0., (-i_l).dot(metadata->normal));
	Color  d_object_color = metadata->mat.getDiffuse();
	Color  d_light_color  = getColor();

	Color res;

	double common = (getIntensity() * dot * DEFAULT_LIGHT_INTENSITY) / std::pow(i_l.norm(), 2);

	res.r(std::max(0., std::min(255., d_object_color.albedo_r() * d_light_color.albedo_r() * common)));
	res.g(std::max(0., std::min(255., d_object_color.albedo_g() * d_light_color.albedo_g() * common)));
	res.b(std::max(0., std::min(255., d_object_color.albedo_b() * d_light_color.albedo_b() * common)));

	return res;
}


#include "syntax_highlighting.hpp"


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