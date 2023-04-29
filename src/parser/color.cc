#include "parser/color.hpp"
#include "syntax_highlighting.hpp"


Color::Color() : Color(0, 0, 0) {
}


Color::Color(uint8_t r, uint8_t g, uint8_t b) : _internal{r, g, b}, _albedo{} {
	compute_albedo_rgb();
}


Color::Color(const Color &c) : Color() {
	*this = c;
}


uint8_t Color::r() const {
	return _internal[0];
}


uint8_t Color::g() const {
	return _internal[1];
}


uint8_t Color::b() const {
	return _internal[2];
}


double Color::albedo_r() const {
	return _albedo[0];
}


double Color::albedo_g() const {
	return _albedo[1];
}


double Color::albedo_b() const {
	return _albedo[2];
}


void Color::r(uint8_t val) {
	_internal[0] = val;
	compute_albedo_r();
}


void Color::g(uint8_t val) {
	_internal[1] = val;
	compute_albedo_g();
}


void Color::b(uint8_t val) {
	_internal[2] = val;
	compute_albedo_b();
}


void Color::compute_albedo_rgb() {
	compute_albedo_r();
	compute_albedo_g();
	compute_albedo_b();
}


void Color::compute_albedo_r() {
	_albedo[0] = r() / 255.;
}


void Color::compute_albedo_g() {
	_albedo[1] = g() / 255.;
}


void Color::compute_albedo_b() {
	_albedo[2] = b() / 255.;
}


void Color::albedo_r(double val) {
	_albedo[0]   = std::max(std::min(val, 1.), 0.);
	_internal[0] = _albedo[0] * 255.;
}


void Color::albedo_g(double val) {
	_albedo[1]   = std::max(std::min(val, 1.), 0.);
	_internal[1] = _albedo[1] * 255.;
}


void Color::albedo_b(double val) {
	_albedo[2]   = std::max(std::min(val, 1.), 0.);
	_internal[2] = _albedo[2] * 255.;
}


Color Color::operator+(const Color &other) const {
	Color c(
			std::max(0, std::min(255, r() + other.r())),
			std::max(0, std::min(255, g() + other.g())),
			std::max(0, std::min(255, b() + other.b()))
	);

	return c;
}


Color &Color::operator+=(const Color &c) {
	return *this = *this + c;
}


Color Color::operator*(double lambda) const {
	Color c;

	c.albedo_r(std::max(0., std::min(1., albedo_r() * lambda)));
	c.albedo_g(std::max(0., std::min(1., albedo_g() * lambda)));
	c.albedo_b(std::max(0., std::min(1., albedo_b() * lambda)));

	return c;
}


Color &Color::operator*=(double lambda) {
	return *this = *this * lambda;
}


Color operator*(double lambda, const Color &c) {
	return c * lambda;
}


Color Color::operator*(const Color &other) const {
	Color c;

	c.albedo_r(std::max(0., std::min(1., albedo_r() * other.albedo_r())));
	c.albedo_g(std::max(0., std::min(1., albedo_g() * other.albedo_g())));
	c.albedo_b(std::max(0., std::min(1., albedo_b() * other.albedo_b())));

	return c;
}


Color &Color::operator*=(const Color &other) {
	return *this = *this * other;
}

Color Color::operator/(double lambda) const
{
	Color c;

	c.albedo_r(std::max(0., std::min(1., albedo_r() / lambda)));
	c.albedo_g(std::max(0., std::min(1., albedo_g() / lambda)));
	c.albedo_b(std::max(0., std::min(1., albedo_b() / lambda)));

	return c;
}

std::ostream &operator<<(std::ostream &os, const Color &c) {
	return os << "Color(" << +c.r() << ", " << +c.g() << ", " << +c.b() << ")";
}


SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, const Color &c) {
	return sh << "(" << c.r() << "," << c.g() << "," << c.b() << ")";
}

