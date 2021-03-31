//
// Created by bouce on 3/24/2021.
//

#include "Camera.hpp"

/**
 * Construct a default camera.
 */
Camera::Camera() : Object(), _fov(0), _size{0, 0}
{}

/**
 * Construct a camera by copying another.
 * @param other The other camera to copy.
 */
Camera::Camera(const Camera &other) : Object(other)
{
	*this = other;
}

/**
 * Construct a camera with parameters.
 * @param coord Coordinates of its origin.
 * @param size Size of the render frame.
 * @param fov Field Of View of the camera.
 */
Camera::Camera(const Vector3lf &coord, const Vector2i &size, double fov) : Object(coord), _fov(fov), _size(size)
{
	_fov *= M_PI / 180.;
}

/**
 * Assignation operator of the Camera.
 * @param other The other camera to copy.
 * @return A reference to the current object (to permit operations chaining).
 */
Camera &Camera::operator=(const Camera &other)
{
	Object::operator=(*this);
	_fov = other._fov;
	_size = other._size;
	return *this;
}

/**
 * Edit the FOV of the Camera.
 * @param fov
 */
void Camera::setFOV(double fov)
{
	_fov = fov;
}

/**
 * Cast a ray in the scene.
 * @param pos Position of the current rendered pixel.
 * @return Returns the casted ray.
 */
Ray Camera::castRay(const Vector2i &pos, const Vector2lf &offset)
{
	double ratio = _size.x / (double) _size.y;
	double angle = tan(_fov / 2.);

	Vector2lf NDC((pos.x + 0.5f + offset.x) / (double) _size.x, (pos.y + 0.5 + offset.y) / (double) _size.y);

	Vector2lf camera((2 * NDC.x - 1) * ratio * angle, (1 - 2 * NDC.y) * angle);

	Ray ray;
	ray.origin = _coord;
	ray.dir = Vector3lf(camera.x, camera.y, -1).normalize();

	return ray;
}

/**
 * Get the nearest hit.
 * @param a First hit.
 * @param b Second hit.
 * @return Returns the nearest hit.
 */
Hit Camera::Hit::nearest(const Hit &a, const Hit &b)
{
	return a.t < b.t ? a : b;
}
