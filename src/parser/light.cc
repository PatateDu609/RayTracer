#include "parser/light.hpp"

const Color  Light::default_color{255, 255, 255};
const double Light::default_intensity{1.0};


Light::Light(const std::string &identifier) :
		SceneBlockObject(identifier), color(), intensity() {
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
	intensity = i;
}


void Light::resetIntensity() {
	intensity.reset();
}


Color compute_lighting(const std::vector<std::shared_ptr<Light>> &lts,
                       const std::shared_ptr<Object::IntersectionMetadata> &metadata) {
	Color c(0, 0, 0);

	for (const auto &lt: lts) {
		c += lt->compute_lighting(metadata);
	}

	return c;
}