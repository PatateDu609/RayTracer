#ifndef RAYTRACER_INCLUDE_LIGHT_HPP
#define RAYTRACER_INCLUDE_LIGHT_HPP

#include <vector>
#include "scene_block_object.hpp"
#include "color.hpp"
#include "object.hpp"

class Light : public SceneBlockObject {
public:
	Light() = default;
	explicit Light(const std::string &identifier);

	Light(const Light &other) = default;
	Light &operator=(const Light &other) = default;

	[[nodiscard]] const Color &getColor() const;
	[[nodiscard]] double getIntensity() const;

	void setColor(const Color &c);
	void resetColor();

	void setIntensity(double i);
	void resetIntensity();

	[[nodiscard]]
	virtual Color compute_lighting(const std::shared_ptr<Object::IntersectionMetadata> &metadata) const = 0;

private:
	static const Color  default_color;
	static const double default_intensity;

protected:
	std::optional<Color>  color;
	std::optional<double> intensity;

	friend class yy::parser;
};

Color compute_lighting(const std::vector<std::shared_ptr<Light>> &lts,
                       const std::shared_ptr<Object::IntersectionMetadata> &metadata);

#endif //RAYTRACER_INCLUDE_LIGHT_HPP
