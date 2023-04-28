#include "parser/ambient_light.hpp"


AmbientLight::AmbientLight(const std::string &identifier) : Light(identifier) {

}


std::string AmbientLight::get_type_name() const {
	return "AmbientLight";
}


void AmbientLight::print_specific(std::ostream &os, bool need_comma) const {
	(void) os;
	(void) need_comma;
}
