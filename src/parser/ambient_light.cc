#include "parser/ambient_light.hpp"
#include "syntax_highlighting.hpp"


AmbientLight::AmbientLight(const std::string &identifier) : Light(identifier) {

}


Color AmbientLight::compute_lighting(const std::shared_ptr<IntersectionMetadata> &metadata) const {
	Color d_object_color = metadata->mat.getDiffuse();
	Color d_light_color  = getColor();

	Color res;

	res.albedo_r(d_object_color.albedo_r() * d_light_color.albedo_r() * getIntensity());
	res.albedo_g(d_object_color.albedo_g() * d_light_color.albedo_g() * getIntensity());
	res.albedo_b(d_object_color.albedo_b() * d_light_color.albedo_b() * getIntensity());

	return res;
}


SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, const AmbientLight &lt) {
	sh << "ambient_light";

	if (lt.identifier)
		sh << *lt.identifier;
	sh << "{";

	sh << "color" << "=" << lt.getColor();
	sh << "intensity" << "=" << lt.getIntensity() << SyntaxHighlighter::endl;

	return sh << "}";
}