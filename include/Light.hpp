#ifndef RAYTRACER_LIGHT_HPP
#define RAYTRACER_LIGHT_HPP

/**
 * 
 * \author Teyber.
 * \file Light.hpp.
 * \date 3/27/2021.
 */

#include "Object.hpp"
#include "Color.hpp"
#include "Camera.hpp"

class Light : public Object
{
public:
	Light() = default;

	Light(const Color &color, double intensity);

	Light(const Light &other) = default;

	~Light() override = default;

	Light &operator=(const Light &other) = default;

	virtual uint32_t shade(const Hit &hit) const = 0;

protected:
	Color _color{0, 0, 0};
	double _intensity;
};



#endif //RAYTRACER_LIGHT_HPP
