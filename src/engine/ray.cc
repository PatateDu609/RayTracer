#include "engine/ray.hpp"

Ray::Ray(const Vector &o, const Vector &d) : origin(o), direction(d) {
	direction.normalize();
}


Vector Ray::operator()(double t) const {
	return origin + t * direction;
}