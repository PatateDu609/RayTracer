//
// Created by bouce on 3/24/2021.
//

#include "SceneObject.hpp"

SceneObject::SceneObject() : Object(), _color{0, 0, 0}, _reflexion(0.f)
{

}

SceneObject::SceneObject(const Vector3lf &pos, const Color &color, double reflexion) : Object(pos), _color(color),
                                                                                       _reflexion(0)
{
	setReflexion(reflexion);
}

const Color &SceneObject::getColor() const
{
	return _color;
}

double SceneObject::getReflexion() const
{
	return _reflexion;
}

void SceneObject::setReflexion(double reflexion)
{
	_reflexion = std::min(1., std::max(reflexion, .0));
}

SceneObject::~SceneObject() = default;

SceneObject &SceneObject::operator=(const SceneObject &other) = default;
