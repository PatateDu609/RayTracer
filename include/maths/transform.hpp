#ifndef RAYTRACER_INCLUDE_MATHS_TRANSFORM_HPP
#define RAYTRACER_INCLUDE_MATHS_TRANSFORM_HPP

#include "matrix.hpp"

const extern Matrix4x4 identity;

Matrix4x4 rotate_x(double rad);
Matrix4x4 rotate_y(double rad);
Matrix4x4 rotate_z(double rad);
Matrix4x4 rotate_xyz(double xr, double yr, double zr);

Matrix4x4 scale(const Vector3 &factors);
Matrix4x4 scale(double xf, double yf, double zf);

Matrix4x4 translate(const Vector3 &factors);
Matrix4x4 translate(double xf, double yf, double zf);

Matrix4x4 transform(const Matrix4x4 &translate, const Matrix4x4 &rotate, const Matrix4x4 &scale);

#endif //RAYTRACER_INCLUDE_MATHS_TRANSFORM_HPP
