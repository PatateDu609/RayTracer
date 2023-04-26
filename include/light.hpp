#ifndef RAYTRACER_INCLUDE_LIGHT_HPP
#define RAYTRACER_INCLUDE_LIGHT_HPP

#include "scene.hpp"
#include "color.hpp"

class Light : public SceneBlockObject {
public:
	explicit Light(const std::string &identifier = "", const Color &color = default_color,
	               double intensity = default_intensity);

	[[nodiscard]] const Color &getColor() const;
	[[nodiscard]] double getIntensity() const;

	void setColor(const Color &c);
	void resetColor();

	void setIntensity(double i);
	void resetIntensity();

protected:
	[[nodiscard]] virtual std::string get_type_name() const = 0;
	virtual void print_specific(std::ostream &os, bool need_comma) const = 0;

private:
	static const Color  default_color;
	static const double default_intensity;

	std::optional<Color>  color;
	std::optional<double> intensity;

	friend std::ostream &operator<<(std::ostream &os, const Light &l);

	friend class yy::parser;
};

#endif //RAYTRACER_INCLUDE_LIGHT_HPP
