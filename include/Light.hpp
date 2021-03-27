//
// Created by bouce on 3/24/2021.
//

#ifndef RAYTRACER_LIGHT_HPP
#define RAYTRACER_LIGHT_HPP

#include "Object.hpp"
#include "Color.hpp"
#include "Camera.hpp"

class Light : public Object
{
public:
	Light() = default;

	Light(const Vector3lf &coord, const Color &diffuse, double intensity);

	Light(const Light &other) = default;

	~Light() override = default;

	Light &operator=(const Light &other) = default;

	uint32_t shade(const Hit &hit) const;

private:
	Color _diffuse{0, 0, 0};
	double _intensity;

	uint32_t diffuse(const Hit &hit) const;
};

#endif //RAYTRACER_LIGHT_HPP
