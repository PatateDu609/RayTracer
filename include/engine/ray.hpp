#ifndef RAYTRACER_INCLUDE_ENGINE_RAY_HPP
#define RAYTRACER_INCLUDE_ENGINE_RAY_HPP

#include "parser/vector.hpp"

struct Ray {
	Ray(const Vector &o, const Vector &d);

	Vector operator() (double t) const;

	Vector origin;
	Vector direction;
};

#endif //RAYTRACER_INCLUDE_ENGINE_RAY_HPP
