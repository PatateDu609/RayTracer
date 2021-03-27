//
// Created by bouce on 3/22/2021.
//

#ifndef RAYTRACER_VECTOR_HPP
#define RAYTRACER_VECTOR_HPP

#include <array>
#include <initializer_list>
#include <exception>
#include <stdexcept>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iostream>

template<class T, size_t m, size_t n>
class Matrix;

template<class T, size_t dim>
struct Vector
{
	Vector() = default;

	Vector(std::initializer_list<T> initializerList) : data(initializerList)
	{}

	Vector(const Vector &other)
	{
		*this = other;
	}

	Vector &operator=(const Vector &other)
	{
		data = other.data;
		return *this;
	}

	T &operator[](size_t index)
	{
		if (index >= dim)
			throw std::out_of_range((std::to_string(index) + " is out of range.").c_str());
		return data[index];
	}

	explicit operator Matrix<T, 1, dim>() const
	{
		Matrix<T, 1, dim> res;

		for (int i = 0; i < dim; i++)
			res[0][i] = data[i];
		return res;
	}

	explicit operator Matrix<T, dim, 1>() const
	{
		Matrix<T, dim, 1> res;

		for (int i = 0; i < dim; i++)
			res[i][0] = data[i];
		return res;
	}

	double getNorm2() const
	{
		auto sq = [](const T &left, const T &right) {
			return left + right * right;
		};

		return std::accumulate(data.begin(), data.end(), 0., sq);
	}

	double getNorm() const
	{
		return std::sqrt(getNorm2());
	}

	Vector & normalize()
	{
		double norm = getNorm();
		std::for_each(data.begin(), data.end(), [norm](T &x) {
			x /= norm;
		});
		return *this;
	}

private:
	std::array<T, dim> data;
};

template<class T>
struct Vector<T, 2>
{
	T &x;
	T &y;

	Vector() : Vector(0, 0)
	{}

	Vector(T _x, T _y) : x(data[0]), y(data[1])
	{
		x = _x;
		y = _y;
	}

	Vector(std::initializer_list<T> list) : Vector(0, 0)
	{
		int i = 0;
		for (T e : list)
			data[i++] = e;
	}

	Vector(const Vector &other) : Vector()
	{
		*this = other;
	}

	Vector &operator=(const Vector &other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	T &operator[](size_t index)
	{
		if (index >= 2)
			throw std::out_of_range((std::to_string(index) + " is out of range.").c_str());
		return data[index];
	}

	const T &operator[](size_t index) const
	{
		if (index >= 2)
			throw std::out_of_range((std::to_string(index) + " is out of range.").c_str());
		return data[index];
	}

	explicit operator Matrix<T, 1, 2>() const
	{
		Matrix<T, 1, 2> res;

		for (int i = 0; i < 2; i++)
			res[0][i] = data[i];
		return res;
	}

	explicit operator Matrix<T, 2, 1>() const
	{
		Matrix<T, 2, 1> res;

		for (int i = 0; i < 2; i++)
			res[i][0] = data[i];
		return res;
	}

	double getNorm2() const
	{
		auto sq = [](const T &left, const T &right) {
			return left + right * right;
		};

		return std::accumulate(data.begin(), data.end(), 0., sq);
	}

	double getNorm() const
	{
		return std::sqrt(getNorm2());
	}

	Vector<T, 3> & normalize()
	{
		double norm = getNorm();
		std::for_each(data.begin(), data.end(), [norm](T &e) {
			e /= norm;
		});
		return *this;
	}

private:
	std::array<T, 2> data;
};


template<class T>
struct Vector<T, 3>
{
	T &x;
	T &y;
	T &z;

	Vector() : Vector(0, 0, 0)
	{}

	Vector(T _x, T _y, T _z) : x(data[0]), y(data[1]), z(data[2])
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector(std::initializer_list<T> list) : Vector(0, 0, 0)
	{
		int i = 0;
		for (T e : list)
			data[i++] = e;
	}

	Vector(const Vector &other) : Vector()
	{
		*this = other;
	}

	Vector &operator=(const Vector &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	T &operator[](size_t index)
	{
		if (index >= 3)
			throw std::out_of_range((std::to_string(index) + " is out of range.").c_str());
		return data[index];
	}

	const T &operator[](size_t index) const
	{
		if (index >= 3)
			throw std::out_of_range((std::to_string(index) + " is out of range.").c_str());
		return data[index];
	}

	explicit operator Matrix<T, 1, 3>() const
	{
		Matrix<T, 1, 3> res;

		for (int i = 0; i < 3; i++)
			res[0][i] = data[i];
		return res;
	}

	explicit operator Matrix<T, 3, 1>() const
	{
		Matrix<T, 3, 1> res;

		for (int i = 0; i < 3; i++)
			res[i][0] = data[i];
		return res;
	}

	double getNorm2() const
	{
		auto sq = [](const T &left, const T &right) {
			return left + right * right;
		};

		return std::accumulate(data.begin(), data.end(), 0., sq);
	}

	double getNorm() const
	{
		return std::sqrt(getNorm2());
	}

	Vector<T, 3> & normalize()
	{
		double norm = getNorm();
		std::for_each(data.begin(), data.end(), [norm](T &e) {
			e /= norm;
		});
		return *this;
	}

	double dot(const Vector &b) const
	{
		return x * b.x + y * b.y + z * b.z;
	}

private:
	std::array<T, 3> data;
};

template<class T>
struct Vector<T, 4>
{
	T &x;
	T &y;
	T &z;
	T &w;

	Vector() : Vector(0, 0, 0, 0)
	{}

	Vector(T _x, T _y, T _z, T _w) : x(data[0]), y(data[1]), z(data[2]), w(data[3])
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	Vector(std::initializer_list<T> list) : Vector(0, 0, 0, 0)
	{
		int i = 0;
		for (T e : list)
			data[i++] = e;
	}

	Vector(const Vector &other) : Vector()
	{
		*this = other;
	}

	Vector &operator=(const Vector &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	T &operator[](size_t index)
	{
		if (index >= 4)
			throw std::out_of_range((std::to_string(index) + " is out of range.").c_str());
		return data[index];
	}

	const T &operator[](size_t index) const
	{
		if (index >= 4)
			throw std::out_of_range((std::to_string(index) + " is out of range.").c_str());
		return data[index];
	}

	explicit operator Matrix<T, 1, 4>() const
	{
		Matrix<T, 1, 4> res;

		for (int i = 0; i < 4; i++)
			res[0][i] = data[i];
		return res;
	}

	explicit operator Matrix<T, 4, 1>() const
	{
		Matrix<T, 4, 1> res;

		for (int i = 0; i < 4; i++)
			res[i][0] = data[i];
		return res;
	}

private:
	std::array<T, 4> data;
};

template<typename T, size_t dim>
Vector<T, dim> operator+(const Vector<T, dim> &a, const Vector<T, dim> &b)
{
	Vector<T, dim> res;

	for (size_t i = 0; i < dim; i++)
		res[i] = a[i] + b[i];
	return res;
}

template<typename T, size_t dim>
Vector<T, dim> &operator+=(Vector<T, dim> &a, const Vector<T, dim> &b)
{
	for (size_t i = 0; i < dim; i++)
		a[i] += b[i];
	return a;
}

template<typename T, size_t dim>
Vector<T, dim> operator-(const Vector<T, dim> &a, const Vector<T, dim> &b)
{
	Vector<T, dim> res;

	for (size_t i = 0; i < dim; i++)
		res[i] = a[i] - b[i];
	return res;
}

template<typename T, size_t dim>
Vector<T, dim> &operator-=(Vector<T, dim> &a, const Vector<T, dim> &b)
{
	for (size_t i = 0; i < dim; i++)
		a[i] -= b[i];
	return a;
}

template<typename T, size_t dim>
Vector<T, dim> operator*(const Vector<T, dim> &v, double lambda)
{
	Vector<T, dim> res = v;
	for (size_t i = 0; i < dim; i++)
		res[i] = v[i] * lambda;
	return res;
}

template<typename T, size_t dim>
Vector<T, dim> &operator*=(Vector<T, dim> &v, double lambda)
{
	for (size_t i = 0; i < dim; i++)
		v[i] *= lambda;
	return v;
}

template<typename T, size_t dim>
Vector<T, dim> operator*(double lambda, const Vector<T, dim> &v)
{
	return v * lambda;
}

template<typename T, size_t dim>
bool operator==(const Vector<T, dim> &lhs, const Vector<T, dim> &rhs)
{
	for (int i = 0; i < dim; i++)
		if (lhs[i] != rhs[i])
			return false;
	return true;
}

template<typename T, size_t dim>
bool operator!=(const Vector<T, dim> &lhs, const Vector<T, dim> &rhs)
{
	return !(rhs == lhs);
}

typedef Vector<int, 1> Vector1i;
typedef Vector<int, 2> Vector2i;
typedef Vector<int, 3> Vector3i;
typedef Vector<int, 4> Vector4i;

typedef Vector<double, 1> Vector1lf;
typedef Vector<double, 2> Vector2lf;
typedef Vector<double, 3> Vector3lf;
typedef Vector<double, 4> Vector4lf;

template<class T, size_t dim>
std::ostream &operator<<(std::ostream &os, const Vector<T, dim> &vec)
{
	os << "(" << vec[0];
	for (size_t i = 1; i < dim; i++)
		os << ", " << vec[i];
	os << ")";
	return os;
}

#endif //RAYTRACER_VECTOR_HPP
