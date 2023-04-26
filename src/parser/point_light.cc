#include "point_light.hpp"


PointLight::PointLight(const std::string &id) : Light(id) {

}


const Vector &PointLight::getPosition() const {
	return position;
}


void PointLight::setPosition(const Vector &pos) {
	position_set = true;
	position     = pos;
}


std::string PointLight::get_type_name() const {
	return "PointLight";
}


void PointLight::print_specific(std::ostream &os, bool need_comma) const {
	if (need_comma && position_set)
		os << ", ";
	if (position_set)
		os << "position = " << position;
}