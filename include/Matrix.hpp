//
// Created by bouce on 3/24/2021.
//

#ifndef RAYTRACER_MATRIX_HPP
#define RAYTRACER_MATRIX_HPP

#include "Vector.hpp"
#include <iostream>

template<typename T, size_t m, size_t n>
class Matrix
{
public:
	Matrix()
	{
		for (size_t i = 0; i < m; i++)
			for (size_t j = 0; j < n; j++)
				data[i][j] = 0;
	}

	Matrix(const Matrix &other) = default;

	std::array<T, n> &operator[](size_t index)
	{
		if (index >= m)
			throw std::out_of_range(std::to_string(index) + "is out of range (m = " + std::to_string(m) + ")");
		return data[index];
	}

	const std::array<T, n> &operator[](size_t index) const
	{
		if (index >= m)
			throw std::out_of_range(std::to_string(index) + "is out of range (m = " + std::to_string(m) + ")");
		return data[index];
	}

	Matrix operator+(const Matrix &b) const
	{
		Matrix res = *this;
		for (size_t i = 0; i < m; i++)
			for (size_t j = 0; j < n; j++)
				res[i][j] += b[i][j];
		return res;
	}

	Matrix &operator+=(const Matrix &b)
	{
		*this = *this + b;
		return *this;
	}

	Matrix operator-(const Matrix &b) const
	{
		Matrix res = *this;
		for (size_t i = 0; i < m; i++)
			for (size_t j = 0; j < n; j++)
				res[i][j] -= b[i][j];
		return res;
	}

	Matrix &operator-=(const Matrix &b)
	{
		*this = *this - b;
		return *this;
	}

	Matrix operator*(double lambda) const
	{
		Matrix res = *this;
		for (size_t i = 0; i < m; i++)
			for (size_t j = 0; j < n; j++)
				res[i][j] *= lambda;
		return res;
	}

	Matrix &operator*=(double lambda)
	{
		*this = *this * lambda;
		return *this;
	}

	template<size_t k>
	Matrix<T, m, k> operator*(const Matrix<T, n, k> &b)
	{
		Matrix<T, m, k> res;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < k; j++)
				for (int l = 0; l < n; l++)
					res[i][j] += data[i][l] * b[l][j];
		return res;
	}

	Matrix<T, n, m> transpose() const
	{
		Matrix<T, n, m> result;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				result[i][j] = data[j][i];
		return result;
	}

	friend std::ostream &operator<<(std::ostream &os, const Matrix mat)
	{
		os << "[";

		for (size_t i = 0; i < m; i++) {
			if (i == 0)
				os << "  ";
			else
				os << "   ";
			os << mat[i][0];
			for (size_t j = 1; j < n; j++)
				os << ", " << mat[i][j];
			if (i != m - 1)
				os << "\n";
			else
				os << "  ";
		}

		os << "]" << std::endl;
		return os;
	}

private:
	std::array<std::array<T, n>, m> data;
};

typedef Matrix<int, 1, 1> Matrix1i;
typedef Matrix<int, 2, 2> Matrix2i;
typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<int, 4, 4> Matrix4i;

typedef Matrix<double, 1, 1> Matrix1f;
typedef Matrix<double, 2, 2> Matrix2f;
typedef Matrix<double, 3, 3> Matrix3f;
typedef Matrix<double, 4, 4> Matrix4f;

typedef Matrix<int, 1, 2> Matrixl2i;
typedef Matrix<int, 1, 3> Matrixl3i;
typedef Matrix<int, 1, 4> Matrixl4i;

typedef Matrix<double, 1, 2> Matrixl2f;
typedef Matrix<double, 1, 3> Matrixl3f;
typedef Matrix<double, 1, 4> Matrixl4f;

typedef Matrix<int, 2, 1> Matrixc2i;
typedef Matrix<int, 3, 1> Matrixc3i;
typedef Matrix<int, 4, 1> Matrixc4i;

typedef Matrix<double, 2, 1> Matrixc2f;
typedef Matrix<double, 3, 1> Matrixc3f;
typedef Matrix<double, 4, 1> Matrixc4f;

#endif //RAYTRACER_MATRIX_HPP
