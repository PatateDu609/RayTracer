//
// Created by bouce on 3/24/2021.
//

#include "Object.hpp"

Object::Object() : _coord{0.f, 0.f, 0.f}
{}

Object::Object(const Vector3lf &coord) : _coord(coord)
{}

Object::Object(const Object &other)
{
	*this = other;
}

Object::~Object()
{}

Object &Object::operator=(const Object &other)
{
	_coord = other._coord;
	return *this;
}

void Object::setCoord(const Vector3lf &vec)
{
	_coord = vec;
}

void Object::translate(const Vector3lf &vec)
{
	_coord += vec;
}
