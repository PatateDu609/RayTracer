#include "engine/ray.hpp"

Ray::Ray(const Vector3 &o, const Vector3 &d) : origin(o), direction(d) {
	direction.normalize();
}


Vector3 Ray::operator()(double t) const {
	return origin + t * direction;
}