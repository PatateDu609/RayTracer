#include "light.hpp"

const Color  Light::default_color{255, 255, 255};
const double Light::default_intensity{1.0};


Light::Light(const std::string &identifier, const Color &c, double i) :
		SceneBlockObject(identifier),
		color(c), intensity(i) {
}


const Color &Light::getColor() const {
	if (color.has_value())
		return *color;
	return default_color;
}


double Light::getIntensity() const {
	if (intensity.has_value())
		return *intensity;
	return default_intensity;
}


void Light::setColor(const Color &c) {
	color = c;
}


void Light::resetColor() {
	color.reset();
}


void Light::setIntensity(double i) {
	*intensity = i;
}


void Light::resetIntensity() {
	intensity.reset();
}

std::ostream &operator<<(std::ostream& os, const Light& l) {
	os << l.get_type_name();
	if (l.identifier.has_value()) {
		os << "(" << *l.identifier << ")";
	}
	os << "{";

	if (l.color.has_value())
		os << "color = " << *l.color;
	if (l.color.has_value() && l.intensity.has_value())
		os << ", ";
	if (l.intensity.has_value())
		os << *l.intensity;

	l.print_specific(os, l.intensity.has_value());
	return os << "}";
}