//
// Created by bouce on 3/24/2021.
//

#ifndef RAYTRACER_SPHERICALLIGHT_HPP
#define RAYTRACER_SPHERICALLIGHT_HPP

#include "Object.hpp"
#include "Color.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class SphericalLight : public Light
{
public:
	SphericalLight() = default;

	SphericalLight(const Vector3lf &coord, const Color &diffuse, double intensity);

	SphericalLight(const SphericalLight &other) = default;

	~SphericalLight() override = default;

	SphericalLight &operator=(const SphericalLight &other) = default;

	uint32_t shade(const Hit &hit) const final;

	static long real_intensity;

private:
	uint32_t diffuse(const Hit &hit) const;
};

#endif //RAYTRACER_SPHERICALLIGHT_HPP
