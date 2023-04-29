#ifndef RAY_TRACER_INCLUDE_COLOR_H
#define RAY_TRACER_INCLUDE_COLOR_H

#include "tuple.hpp"
#include <iostream>

class SyntaxHighlighter;

class Color {
public:
	Color();
	Color(uint8_t r, uint8_t g, uint8_t b);
	Color(const Color& c);
	Color& operator=(const Color& c) = default;

	[[nodiscard]] uint8_t r() const;
	[[nodiscard]] uint8_t g() const;
	[[nodiscard]] uint8_t b() const;

	void r(uint8_t val);
	void g(uint8_t val);
	void b(uint8_t val);

	[[nodiscard]] double albedo_r() const;
	[[nodiscard]] double albedo_g() const;
	[[nodiscard]] double albedo_b() const;

	void albedo_r(double val);
	void albedo_g(double val);
	void albedo_b(double val);

	Color operator+(const Color& other) const;
	Color& operator+=(const Color& c);

private:
	Tuple<uint8_t, 3> _internal;
	Tuple<double, 3> _albedo;

	void compute_albedo_rgb();
	void compute_albedo_r();
	void compute_albedo_g();
	void compute_albedo_b();

	friend std::ostream &operator<<(std::ostream& os, const Color& c);
	friend SyntaxHighlighter &operator<<(SyntaxHighlighter& os, const Color& c);
};

#endif
