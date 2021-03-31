//
// Created by bouce on 3/24/2021.
//

#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#define _USE_MATH_DEFINES

#include <cmath>
#include "Object.hpp"
#include "Matrix.hpp"

struct Ray;

class SceneObject;

class Camera : public Object
{
public:
	struct Hit
	{
		double t;
		Vector3lf pos;
		Vector3lf normal;
		const SceneObject *obj;

		static Hit nearest(const Hit &a, const Hit &b);
	};

	Camera();

	Camera(const Camera &other);

	Camera(const Vector3lf &coord, const Vector2i &size, double fov);

	Camera &operator=(const Camera &other);

	void setFOV(double fov);

	Ray castRay(const Vector2i &pos, const Vector2lf &offset = Vector2lf());

private:
	double _fov;
	Vector2i _size;
};

using Hit = Camera::Hit;

struct Ray
{
	Vector3lf origin;
	Vector3lf dir;
};

#include "SceneObject.hpp"

#endif //RAYTRACER_CAMERA_HPP
