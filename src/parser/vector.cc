#include "parser/vector.hpp"
#include <cmath>


Vector::Vector() : Vector(0, 0, 0) {
}


Vector::Vector(double x, double y, double z) : _internal{x, y, z}, _norm(0) {
	compute_norm();
}


Vector::Vector(const Vector &c) : Vector() {
	*this = c;
}


double Vector::x() const {
	return _internal[0];
}


double Vector::y() const {
	return _internal[1];
}


double Vector::z() const {
	return _internal[2];
}


void Vector::x(double val) {
	_internal[0] = val;
	compute_norm();
}


void Vector::y(double val) {
	_internal[1] = val;
	compute_norm();
}


void Vector::z(double val) {
	_internal[2] = val;
	compute_norm();
}


double Vector::norm() const {
	return _norm;
}


Vector & Vector::normalize() {
	_internal[0] /= _norm;
	_internal[1] /= _norm;
	_internal[2] /= _norm;
	_norm = 1;
	return *this;
}


Vector Vector::operator+(const Vector &other) const {
	Vector res(x() + other.x(), y() + other.y(), z() + other.z());

	return res;
}


Vector &Vector::operator+=(const Vector &other) {
	*this = *this + other;

	return *this;
}


Vector Vector::operator-(const Vector &other) const {
	Vector res(x() - other.x(), y() - other.y(), z() - other.z());

	return res;
}


Vector &Vector::operator-=(const Vector &other) {
	*this = *this - other;

	return *this;
}


Vector Vector::operator*(double lambda) const {
	Vector res(x() * lambda, y() * lambda, z() * lambda);

	return res;
}


Vector operator*(double lambda, const Vector &a) {
	return a * lambda;
}


Vector &Vector::operator*=(double lambda) {
	*this = *this * lambda;

	return *this;
}


double Vector::dot(const Vector &other) const {
	double res =
			       x() * other.x() +
			       y() * other.y() +
			       z() * other.z();
	return res;
}


Vector Vector::cross(const Vector &other) const {
	Vector res(
			y() * other.z() - z() * other.y(),
			z() * other.x() - x() * other.z(),
			x() * other.y() - y() * other.x()
	);

	return res;
}


void Vector::compute_norm() {
	double sum = pow(x(), 2) + pow(y(), 2) + pow(z(), 2);
	_norm = sqrt(sum);
}


std::ostream &operator<<(std::ostream &os, const Vector &v) {
	return os << "Vector" << v._internal;
}
