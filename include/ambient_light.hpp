#ifndef RAYTRACER_INCLUDE_AMBIENT_LIGHT_HPP
#define RAYTRACER_INCLUDE_AMBIENT_LIGHT_HPP

#include "light.hpp"

class AmbientLight final : public Light {
public:
	explicit AmbientLight(const std::string& identifier = "");

protected:
	[[nodiscard]] std::string get_type_name() const override;
	void print_specific(std::ostream &os, bool need_comma) const override;

	friend class yy::parser;
};

#endif //RAYTRACER_INCLUDE_AMBIENT_LIGHT_HPP
