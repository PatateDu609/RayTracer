#ifndef RAYTRACER_AMBIENTLIGHT_HPP
#define RAYTRACER_AMBIENTLIGHT_HPP

/**
 * 
 * \author Teyber.
 * \file AmbientLight.hpp.
 * \date 3/27/2021.
 */

#include "Light.hpp"

class AmbientLight : public Light
{
public:
	AmbientLight() = default;
	AmbientLight(const AmbientLight& other) = default;
	AmbientLight(const Color& color, double intensity);

	~AmbientLight() = default;

	AmbientLight& operator=(const AmbientLight& other) = default;

	uint32_t shade(const Hit &hit) const override;
};


#endif //RAYTRACER_AMBIENTLIGHT_HPP
