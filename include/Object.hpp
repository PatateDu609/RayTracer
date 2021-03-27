//
// Created by bouce on 3/24/2021.
//

#ifndef RAYTRACER_OBJECT_HPP
#define RAYTRACER_OBJECT_HPP

#include "Vector.hpp"

class Object
{
public:
	Object();

	Object(const Vector3lf &coord);

	Object(const Object &other);

	virtual ~Object();

	Object &operator=(const Object &other);

	void setCoord(const Vector3lf &vec);

	void translate(const Vector3lf &vec);

protected:
	Vector3lf _coord;
};


#endif //RAYTRACER_OBJECT_HPP
