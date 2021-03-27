//
// Created by bouce on 3/24/2021.
//

#ifndef RAYTRACER_SCENEOBJECT_HPP
#define RAYTRACER_SCENEOBJECT_HPP

#include "Object.hpp"
#include "Camera.hpp"
#include "Color.hpp"

class SceneObject : public Object
{
public:
	SceneObject();

	SceneObject(const Vector3lf &pos, const Color &color, double reflexion = 0.0f);

	SceneObject(const SceneObject &other) = default;

	virtual ~SceneObject();

	SceneObject &operator=(const SceneObject &other);

	virtual bool intersect(const Ray &ray, Hit &local) const = 0;

	const Color &getColor() const;

	double getReflexion() const;

	void setReflexion(double reflexion);

private:
	Color _color;
	double _reflexion;
};

#endif //RAYTRACER_SCENEOBJECT_HPP
