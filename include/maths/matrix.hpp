#ifndef RAYTRACER_INCLUDE_MATRIX_HPP
#define RAYTRACER_INCLUDE_MATRIX_HPP

#include <array>
#include <cstdlib>
#include "vector.hpp"

class Matrix4x4 {
public:
	Matrix4x4();
	Matrix4x4(const Matrix4x4& other) = default;
	Matrix4x4& operator=(const Matrix4x4& other) = default;
	~Matrix4x4() = default;

	Matrix4x4 operator+(const Matrix4x4& other) const;
	Matrix4x4 &operator+=(const Matrix4x4& other);
	Matrix4x4 operator-(const Matrix4x4& other) const;
	Matrix4x4 &operator-=(const Matrix4x4& other);
	Matrix4x4 operator*(double lambda) const;
	Matrix4x4 &operator*=(double lambda);

	Matrix4x4 operator*(const Matrix4x4& other) const;
	Matrix4x4 &operator*=(const Matrix4x4& other);

	Vector3 transform_point(const Vector3& pt) const;
	Vector3 transform_point(double x, double y, double z) const;
	Vector3 transform_direction(const Vector3& vec) const;
	Vector3 transform_direction(double x, double y, double z) const;

	const double *operator[](size_t i) const;
	double *operator[](size_t i);

	void set_row(size_t i, const Vector3& vec3, double w);

private:
	double _data[4][4];
};
Matrix4x4 operator*(double lambda, const Matrix4x4& other);

#endif //RAYTRACER_INCLUDE_MATRIX_HPP
