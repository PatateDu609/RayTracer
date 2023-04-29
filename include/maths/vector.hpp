#ifndef RAY_TRACER_INCLUDE_VECTOR_H
#define RAY_TRACER_INCLUDE_VECTOR_H

#include "parser/tuple.hpp"
#include <iostream>

class SyntaxHighlighter;

class Vector3 {
public:
	Vector3();
	Vector3(double x, double y, double z);
	Vector3(const Vector3& c) = default;
	Vector3& operator=(const Vector3& c) = default;

	[[nodiscard]] double x() const;
	[[nodiscard]] double y() const;
	[[nodiscard]] double z() const;

	void x(double val);
	void y(double val);
	void z(double val);

	[[nodiscard]] double norm() const;
	Vector3 & normalize();

	Vector3 operator+(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-();
	Vector3 operator-(const Vector3& other) const;
	Vector3& operator-=(const Vector3& other);
	Vector3 operator*(double lambda) const;
	Vector3& operator*=(double lambda);

	[[nodiscard]] double dot(const Vector3& other) const;
	[[nodiscard]] Vector3 cross(const Vector3& other) const;

private:
	Tuple<double, 3> _internal;
	double _norm;

	void compute_norm();

	friend std::ostream &operator<<(std::ostream& os, const Vector3& v);
	friend SyntaxHighlighter &operator<<(SyntaxHighlighter& sh, const Vector3& v);
};
Vector3 operator*(double lambda, const Vector3& a);

class Vector4 {
public:
	Vector4();
	Vector4(double x, double y, double z, double w);
	Vector4(const Vector4& c);
	Vector4& operator=(const Vector4& c) = default;

	[[nodiscard]] double x() const;
	[[nodiscard]] double y() const;
	[[nodiscard]] double z() const;
	[[nodiscard]] double w() const;

	void x(double val);
	void y(double val);
	void z(double val);
	void w(double val);

	[[nodiscard]] double norm() const;
	Vector4 & normalize();

	Vector4 operator+(const Vector4& other) const;
	Vector4& operator+=(const Vector4& other);
	Vector4& operator-();
	Vector4 operator-(const Vector4& other) const;
	Vector4& operator-=(const Vector4& other);
	Vector4 operator*(double lambda) const;
	Vector4& operator*=(double lambda);

private:
	Tuple<double, 4> _internal;
	double _norm;

	void compute_norm();

	friend std::ostream &operator<<(std::ostream& os, const Vector4& v);
	friend SyntaxHighlighter &operator<<(SyntaxHighlighter& sh, const Vector4& v);
};
Vector4 operator*(double lambda, const Vector4& a);

#endif
