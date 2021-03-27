//
// Created by bouce on 3/24/2021.
//

#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>
#include "SphericalLight.hpp"
#include "Scene.hpp"

SphericalLight::SphericalLight(const Vector3lf &coord, const Color &diffuse, double intensity) : Light(diffuse, intensity)
{
	_coord = coord;
}

uint32_t SphericalLight::shade(const Hit &hit) const
{
	Scene *scene = Scene::getInstance();
	Ray shadow;

	shadow.origin = hit.pos + hit.normal * 0.001f;
	(shadow.dir = _coord - hit.pos).normalize();

	Hit shadowHit = scene->intersect(shadow);
	if (!shadowHit.obj || shadowHit.t * shadowHit.t > (_coord - hit.pos).getNorm2())
		return diffuse(hit);
	return Color();
}

uint32_t SphericalLight::diffuse(const Hit &hit) const
{
	Color c;
	Vector3lf L = _coord - hit.pos;
	double ratio = L.getNorm2() * M_PI;
	L.normalize();

	Vector3lf normalizedColor{
			(double) hit.obj->getColor().r / 255.,
			(double) hit.obj->getColor().g / 255.,
			(double) hit.obj->getColor().b / 255.,
	};

	Vector3lf normalizedDiffuse{
			(double) _color.r / 255.,
			(double) _color.g / 255.,
			(double) _color.b / 255.,
	};

	double dot = std::max(0., L.dot(hit.normal));

	Vector3lf intensity;

	intensity.x = _intensity * real_intensity * normalizedDiffuse.x * normalizedColor.x * dot / ratio;
	intensity.y = _intensity * real_intensity * normalizedDiffuse.y * normalizedColor.y * dot / ratio;
	intensity.z = _intensity * real_intensity * normalizedDiffuse.z * normalizedColor.z * dot / ratio;

	c.r = std::max(0., std::min(255., std::pow(intensity.x, 1 / 2.2)));
	c.g = std::max(0., std::min(255., std::pow(intensity.y, 1 / 2.2)));
	c.b = std::max(0., std::min(255., std::pow(intensity.z, 1 / 2.2)));
	return c;
}
