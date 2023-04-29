#include "maths/vector.hpp"
#include <cmath>
#include "syntax_highlighting.hpp"


// Implementation of Vector3
Vector3::Vector3() : Vector3(0, 0, 0) {
}


Vector3::Vector3(double x, double y, double z) : _internal{x, y, z}, _norm(0) {
	compute_norm();
}


double Vector3::x() const {
	return _internal[0];
}


double Vector3::y() const {
	return _internal[1];
}


double Vector3::z() const {
	return _internal[2];
}


void Vector3::x(double val) {
	_internal[0] = val;
	compute_norm();
}


void Vector3::y(double val) {
	_internal[1] = val;
	compute_norm();
}


void Vector3::z(double val) {
	_internal[2] = val;
	compute_norm();
}


double Vector3::norm() const {
	return _norm;
}


Vector3 &Vector3::normalize() {
	_internal[0] /= _norm;
	_internal[1] /= _norm;
	_internal[2] /= _norm;
	_norm = 1;
	return *this;
}


Vector3 Vector3::operator+(const Vector3 &other) const {
	Vector3 res(x() + other.x(), y() + other.y(), z() + other.z());

	return res;
}


Vector3 &Vector3::operator+=(const Vector3 &other) {
	*this = *this + other;

	return *this;
}


Vector3 &Vector3::operator-() {
	x(-x());
	y(-y());
	z(-z());
	return *this;
}


Vector3 Vector3::operator-(const Vector3 &other) const {
	Vector3 res(x() - other.x(), y() - other.y(), z() - other.z());

	return res;
}


Vector3 &Vector3::operator-=(const Vector3 &other) {
	*this = *this - other;

	return *this;
}


Vector3 Vector3::operator*(double lambda) const {
	Vector3 res(x() * lambda, y() * lambda, z() * lambda);

	return res;
}


Vector3 operator*(double lambda, const Vector3 &a) {
	return a * lambda;
}


Vector3 &Vector3::operator*=(double lambda) {
	*this = *this * lambda;

	return *this;
}


double Vector3::dot(const Vector3 &other) const {
	double res =
			       x() * other.x() +
			       y() * other.y() +
			       z() * other.z();
	return res;
}


Vector3 Vector3::cross(const Vector3 &other) const {
	Vector3 res(
			y() * other.z() - z() * other.y(),
			z() * other.x() - x() * other.z(),
			x() * other.y() - y() * other.x()
	);

	return res;
}


void Vector3::compute_norm() {
	double sum = pow(x(), 2) + pow(y(), 2) + pow(z(), 2);
	_norm = sqrt(sum);
}


std::ostream &operator<<(std::ostream &os, const Vector3 &v) {
	return os << "Vector" << v._internal;
}


SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, const Vector3 &v) {
	sh << v._internal;
	return sh;
}

// Implementation of Vector4

Vector4::Vector4() : Vector4(0, 0, 0, 0) {

}


Vector4::Vector4(double x, double y, double z, double w) : _internal{x, y, z, w} {
	compute_norm();
}


Vector4::Vector4(const Vector4 &c) {
	*this = c;
}


double Vector4::x() const {
	return _internal[0];
}


double Vector4::y() const {
	return _internal[1];
}


double Vector4::z() const {
	return _internal[2];
}


double Vector4::w() const {
	return _internal[3];
}


void Vector4::x(double val) {
	_internal[0] = val;
}


void Vector4::y(double val) {
	_internal[1] = val;

}


void Vector4::z(double val) {
	_internal[2] = val;

}


void Vector4::w(double val) {
	_internal[3] = val;
}


double Vector4::norm() const {
	return _norm;
}


Vector4 &Vector4::normalize() {
	_internal[0] /= _norm;
	_internal[1] /= _norm;
	_internal[2] /= _norm;
	_internal[3] /= _norm;
	_norm = 1;
	return *this;
}


Vector4 Vector4::operator+(const Vector4 &other) const {
	return Vector4(
			x() + other.x(),
			y() + other.y(),
			z() + other.z(),
			w() + other.w()
	);
}


Vector4 &Vector4::operator+=(const Vector4 &other) {
	return *this = *this + other;
}


Vector4 &Vector4::operator-() {
	return *this = Vector4(-x(), -y(), -z(), -w());
}


Vector4 Vector4::operator-(const Vector4 &other) const {
	return Vector4(
			x() - other.x(),
			y() - other.y(),
			z() - other.z(),
			w() - other.w()
	);
}


Vector4 &Vector4::operator-=(const Vector4 &other) {
	return *this = *this - other;
}


Vector4 Vector4::operator*(double lambda) const {
	return Vector4(
			lambda * x(),
			lambda * y(),
			lambda * z(),
			lambda * w()
	);
}


Vector4 &Vector4::operator*=(double lambda) {
	return *this = *this * lambda;
}


void Vector4::compute_norm() {
	double sum = std::pow(x(), 2) + std::pow(y(), 2) + std::pow(z(), 2) + std::pow(w(), 2);
	_norm = std::sqrt(sum);
}


Vector4 operator*(double lambda, const Vector4 &a) {
	return a * lambda;
}

std::ostream &operator<<(std::ostream& os, const Vector4& v) {
	return os << "Vector" << v._internal;
}

SyntaxHighlighter &operator<<(SyntaxHighlighter& sh, const Vector4& v) {
	return sh << v._internal;
}