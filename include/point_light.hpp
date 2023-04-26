#ifndef RAYTRACER_INCLUDE_POINT_LIGHT_HPP
#define RAYTRACER_INCLUDE_POINT_LIGHT_HPP

#include <optional>
#include "color.hpp"
#include "vector.hpp"
#include "light.hpp"

class PointLight final : public Light {
public:
	explicit PointLight(const std::string &identifier = "");

	void setPosition(const Vector &pos);
	[[nodiscard]] const Vector &getPosition() const;

protected:
	[[nodiscard]] std::string get_type_name() const override;
	void print_specific(std::ostream &os, bool need_comma) const override;

private:
	bool position_set{};

	Vector position;

	friend class yy::parser;
};

#endif //RAYTRACER_INCLUDE_POINT_LIGHT_HPP
