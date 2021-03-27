/**
 * 
 * \author Teyber.
 * \file AmbientLight.cpp.cc.
 * \date 3/27/2021.
 */

#include "AmbientLight.hpp"

AmbientLight::AmbientLight(const Color &color, double intensity) : Light(color, intensity)
{

}

uint32_t AmbientLight::shade(const Hit &hit) const
{
	Color res;

	res.r = _intensity * (_color.r / 255.) * hit.obj->getColor().r;
	res.g = _intensity * (_color.g / 255.) * hit.obj->getColor().g;
	res.b = _intensity * (_color.b / 255.) * hit.obj->getColor().b;
	return res;
}
