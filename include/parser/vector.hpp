#ifndef RAY_TRACER_INCLUDE_VECTOR_H
#define RAY_TRACER_INCLUDE_VECTOR_H

#include "utils.hpp"

class Vector {
public:
	Vector();
	Vector(double x, double y, double z);
	Vector(const Vector& c);
	Vector& operator=(const Vector& c) = default;

	[[nodiscard]] double x() const;
	[[nodiscard]] double y() const;
	[[nodiscard]] double z() const;

	void x(double val);
	void y(double val);
	void z(double val);

	[[nodiscard]] double norm() const;
	Vector & normalize();

	Vector operator+(const Vector& other) const;
	Vector& operator+=(const Vector& other);
	Vector operator-(const Vector& other) const;
	Vector& operator-=(const Vector& other);
	Vector operator*(double lambda) const;
	Vector& operator*=(double lambda);

	[[nodiscard]] double dot(const Vector& other) const;
	[[nodiscard]] Vector cross(const Vector& other) const;

private:
	Tuple<double, 3> _internal;
	double _norm;

	void compute_norm();

	friend std::ostream &operator<<(std::ostream& os, const Vector& v);
};
Vector operator*(double lambda, const Vector& a);

#endif
