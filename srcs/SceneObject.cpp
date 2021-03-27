//
// Created by bouce on 3/24/2021.
//

#include "SceneObject.hpp"

SceneObject::SceneObject() : Object(), _color(), _reflexion(0.), _transparency(0.), _ior(1.)
{

}

SceneObject::SceneObject(const Vector3lf &pos, const Color &color, double reflexion) : Object(pos), _color(color),
                                                                                       _reflexion(0.), _transparency(0.),
                                                                                       _ior(1.)
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

double SceneObject::getTransparency() const
{
	return _transparency;
}

void SceneObject::setTransparency(double transparency, double ior)
{
	_transparency = std::min(1., std::max(transparency, .0));
	_ior = ior;
}

double SceneObject::getIOR() const
{
	return _ior;
}

SceneObject::~SceneObject() = default;

SceneObject &SceneObject::operator=(const SceneObject &other) = default;
