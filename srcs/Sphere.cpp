//
// Created by bouce on 3/24/2021.
//

#include "Sphere.hpp"

Sphere::Sphere(const Vector3lf &pos, double r, const Color &color) : SceneObject(pos, color, 0.f), _r(r)
{
}

bool Sphere::intersect(const Ray &ray, Hit &local) const
{
	double a, b, c, delta;

	a = 1;
	b = 2 * ray.dir.dot(ray.origin - _coord);
	c = (ray.origin - _coord).getNorm2() - _r * _r;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return false;
	double t1 = (-b - sqrt(delta)) / (2 * a);
	double t2 = (-b + sqrt(delta)) / (2 * a);
	if (t2 < 0)
		return false;
	local.t = (t1 > 0) ? t1 : t2;
	local.obj = this;
	local.pos = ray.origin + ray.dir * local.t;
	local.normal = (local.pos - _coord).normalize();
	return true;
}
