#include "maths/matrix.hpp"
#include <sstream>
#include <cstring>


Matrix4x4::Matrix4x4() {
	for (size_t i = 0; i < 4; i++)
		std::memset(_data[i], 0, 4 * sizeof(_data[i][0]));
}


Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &other) const {
	Matrix4x4 res = *this;

	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res._data[j][i] = _data[j][i] + other._data[j][i];

	return res;
}


Matrix4x4 &Matrix4x4::operator+=(const Matrix4x4 &other) {
	return *this = *this + other;
}


Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &other) const {
	Matrix4x4 res = *this;

	const auto &other_data = other._data;

	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res._data[j][i] = _data[j][i] - other_data[j][i];

	return res;
}


Matrix4x4 &Matrix4x4::operator-=(const Matrix4x4 &other) {
	return *this = *this - other;
}


Matrix4x4 Matrix4x4::operator*(double lambda) const {
	Matrix4x4 res = *this;

	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res._data[j][i] = _data[j][i] * lambda;

	return res;
}


Matrix4x4 &Matrix4x4::operator*=(double lambda) {
	return *this = *this * lambda;
}


const double *Matrix4x4::operator[](size_t i) const {
	if (i >= 4) {
		std::ostringstream oss;
		oss << "trying to access element " << i << " in array of size 4";
		throw std::out_of_range(oss.str());
	}
	return _data[i];
}


double *Matrix4x4::operator[](size_t i) {
	if (i >= 4) {
		std::ostringstream oss;
		oss << "trying to access element " << i << " in array of size 4";
		throw std::out_of_range(oss.str());
	}
	return _data[i];
}


void Matrix4x4::set_row(size_t i, const Vector3 &vec3, double w) {
	if (i >= 4) {
		std::ostringstream oss;
		oss << "trying to access element " << i << " in array of size 4";
		throw std::out_of_range(oss.str());
	}

	_data[i][0] = vec3.x();
	_data[i][1] = vec3.y();
	_data[i][2] = vec3.z();
	_data[i][3] = w;
}


Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &other) const {
	// We're expanding the computing to avoid useless branching and useless checks.
	// Also, all the needed information will be cached in the CPU.

	double a00 = _data[0][0];
	double a01 = _data[0][1];
	double a02 = _data[0][2];
	double a03 = _data[0][3];

	double a10 = _data[1][0];
	double a11 = _data[1][1];
	double a12 = _data[1][2];
	double a13 = _data[1][3];

	double a20 = _data[2][0];
	double a21 = _data[2][1];
	double a22 = _data[2][2];
	double a23 = _data[2][3];

	double a30 = _data[3][0];
	double a31 = _data[3][1];
	double a32 = _data[3][2];
	double a33 = _data[3][3];

	const auto b_data = other._data;

	double b00 = b_data[0][0];
	double b01 = b_data[0][1];
	double b02 = b_data[0][2];
	double b03 = b_data[0][3];

	double b10 = b_data[1][0];
	double b11 = b_data[1][1];
	double b12 = b_data[1][2];
	double b13 = b_data[1][3];

	double b20 = b_data[2][0];
	double b21 = b_data[2][1];
	double b22 = b_data[2][2];
	double b23 = b_data[2][3];

	double b30 = b_data[3][0];
	double b31 = b_data[3][1];
	double b32 = b_data[3][2];
	double b33 = b_data[3][3];

	Matrix4x4 mat_res;
	auto      &res = mat_res._data;

	res[0][0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
	res[0][1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
	res[0][2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
	res[0][3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;

	res[1][0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
	res[1][1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
	res[1][2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
	res[1][3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;

	res[2][0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
	res[2][1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
	res[2][2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
	res[2][3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;

	res[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
	res[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
	res[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
	res[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;

	return mat_res;
}


Matrix4x4 &Matrix4x4::operator*=(const Matrix4x4 &other) {
	return *this = *this * other;
}


Vector3 Matrix4x4::transform_point(const Vector3 &vec) const {
	double a00 = _data[0][0];
	double a01 = _data[0][1];
	double a02 = _data[0][2];
	double a03 = _data[0][3];

	double a10 = _data[1][0];
	double a11 = _data[1][1];
	double a12 = _data[1][2];
	double a13 = _data[1][3];

	double a20 = _data[2][0];
	double a21 = _data[2][1];
	double a22 = _data[2][2];
	double a23 = _data[2][3];

	double a30 = _data[3][0];
	double a31 = _data[3][1];
	double a32 = _data[3][2];
	double a33 = _data[3][3];

	double vx = vec.x();
	double vy = vec.y();
	double vz = vec.z();

	double x = vx * a00 + vy * a10 + vz * a20 + a30;
	double y = vx * a01 + vy * a11 + vz * a21 + a31;
	double z = vx * a02 + vy * a12 + vz * a22 + a32;
	double w = vx * a03 + vy * a13 + vz * a23 + a33;

	return Vector3(x / w, y / w, z / w);
}

Vector3 Matrix4x4::transform_point(double x, double y, double z) const {
	return transform_point(Vector3(x, y, z));
}

Vector3 Matrix4x4::transform_direction(const Vector3 &vec) const {
	double a00 = _data[0][0];
	double a01 = _data[0][1];
	double a02 = _data[0][2];

	double a10 = _data[1][0];
	double a11 = _data[1][1];
	double a12 = _data[1][2];

	double a20 = _data[2][0];
	double a21 = _data[2][1];
	double a22 = _data[2][2];

	double vx = vec.x();
	double vy = vec.y();
	double vz = vec.z();

	double x = vx * a00 + vy * a10 + vz * a20;
	double y = vx * a01 + vy * a11 + vz * a21;
	double z = vx * a02 + vy * a12 + vz * a22;

	return Vector3(x, y, z);
}

Vector3 Matrix4x4::transform_direction(double x, double y, double z) const {
	return transform_direction(Vector3(x, y, z));
}


Matrix4x4 operator*(double lambda, const Matrix4x4 &other) {
	return other * lambda;
}