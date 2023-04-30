#include "maths/transform.hpp"
#include <cmath>

static Matrix4x4 get_identity();

const Matrix4x4 identity = get_identity();

static Matrix4x4 get_identity() {
	Matrix4x4 res;

	res[0][0] = 1;
	res[0][1] = 0;
	res[0][2] = 0;
	res[0][3] = 0;

	res[1][0] = 0;
	res[1][1] = 1;
	res[1][2] = 0;
	res[1][3] = 0;

	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = 1;
	res[2][3] = 0;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;

	return res;
}


Matrix4x4 rotate_x(double theta) {
	double sin_theta = sin(theta);
	double cos_theta = cos(theta);

	Matrix4x4 res;

	res[0][0] = 1;
	res[0][1] = 0;
	res[0][2] = 0;
	res[0][3] = 0;

	res[1][0] = 0;
	res[1][1] = cos_theta;
	res[1][2] = -sin_theta;
	res[1][3] = 0;

	res[2][0] = 0;
	res[2][1] = sin_theta;
	res[2][2] = cos_theta;
	res[2][3] = 0;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;

	return res;
}


Matrix4x4 rotate_y(double theta) {
	double sin_theta = sin(theta);
	double cos_theta = cos(theta);

	Matrix4x4 res;

	res[0][0] = cos_theta;
	res[0][1] = 0;
	res[0][2] = sin_theta;
	res[0][3] = 0;

	res[1][0] = 0;
	res[1][1] = 1;
	res[1][2] = 0;
	res[0][3] = 0;

	res[2][0] = -sin_theta;
	res[2][1] = 0;
	res[2][2] = cos_theta;
	res[2][3] = 0;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;

	return res;
}


Matrix4x4 rotate_z(double theta) {
	double sin_theta = sin(theta);
	double cos_theta = cos(theta);

	Matrix4x4 res;

	res[0][0] = cos_theta;
	res[0][1] = -sin_theta;
	res[0][2] = 0;
	res[0][3] = 0;

	res[1][0] = sin_theta;
	res[1][1] = cos_theta;
	res[1][2] = 0;
	res[1][3] = 0;

	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = 1;
	res[2][3] = 0;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;

	return res;
}

// Each angle represent a rotation around one of the axis x, y or z:
//					|	z axis   |    y axis  |     x axis
Matrix4x4 rotate_xyz(double alpha, double beta, double gamma) {
	double cos_alpha = cos(alpha);
	double sin_alpha = sin(alpha);

	double cos_beta = cos(beta);
	double sin_beta = sin(beta);

	double cos_gamma = cos(gamma);
	double sin_gamma = sin(gamma);

	Matrix4x4 res;

	res[0][0] = cos_alpha * cos_beta;
	res[0][1] = cos_alpha * sin_beta * sin_gamma - sin_alpha * cos_gamma;
	res[0][2] = cos_alpha * sin_beta * cos_gamma + sin_alpha * sin_gamma;
	res[0][3] = 0;

	res[1][0] = sin_alpha * cos_beta;
	res[1][1] = sin_alpha * sin_beta * sin_gamma + cos_alpha * cos_gamma;
	res[1][2] = sin_alpha * sin_beta * cos_gamma - cos_alpha * sin_gamma;
	res[1][3] = 0;

	res[2][0] = -sin_beta;
	res[2][1] = cos_beta * sin_gamma;
	res[2][2] = cos_beta * sin_gamma;
	res[2][3] = 0;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;

	return res;
}


Matrix4x4 scale(const Vector3 &factors) {
	return scale(factors.x(), factors.y(), factors.z());
}


Matrix4x4 scale(double xf, double yf, double zf) {
	Matrix4x4 res;

	res[0][0] = xf;
	res[0][1] = 0;
	res[0][2] = 0;
	res[0][3] = 0;

	res[1][0] = 0;
	res[1][1] = yf;
	res[1][2] = 0;
	res[1][3] = 0;

	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = zf;
	res[2][3] = 0;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;

	return res;
}


Matrix4x4 translate(const Vector3 &factors) {
	return translate(factors.x(), factors.y(), factors.z());
}


Matrix4x4 translate(double xf, double yf, double zf) {
	Matrix4x4 res;

	res[0][0] = 1;
	res[0][1] = 0;
	res[0][2] = 0;
	res[0][3] = xf;

	res[1][0] = 0;
	res[1][1] = 1;
	res[1][2] = 0;
	res[1][3] = yf;

	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = 1;
	res[2][3] = zf;

	res[3][0] = 0;
	res[3][1] = 0;
	res[3][2] = 0;
	res[3][3] = 1;

	return res;
}

Matrix4x4 transform(const Matrix4x4& translate, const Matrix4x4& rotate, const Matrix4x4& scale) {
	return translate * rotate * scale;
}