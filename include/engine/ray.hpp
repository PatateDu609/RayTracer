#ifndef RAYTRACER_INCLUDE_ENGINE_RAY_HPP
#define RAYTRACER_INCLUDE_ENGINE_RAY_HPP

#include "maths/vector.hpp"

struct Ray {
	Ray(const Vector3 &o, const Vector3 &d);

	Vector3 operator() (double t) const;

	Vector3 origin;
	Vector3 direction;
};

#endif //RAYTRACER_INCLUDE_ENGINE_RAY_HPP
