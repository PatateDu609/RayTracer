//
// Created by bouce on 3/24/2021.
//

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "SceneObject.hpp"

class Sphere : public SceneObject
{
public:
	Sphere() = default;

	Sphere(const Vector3lf &pos, double r, const Color &color);

	Sphere(const Sphere &other) = default;

	~Sphere() override = default;

	Sphere &operator=(const Sphere &other) = default;

	bool intersect(const Ray &ray, Hit &local) const override;

private:
	double _r;
};


#endif //RAYTRACER_SPHERE_HPP
