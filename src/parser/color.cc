#include "parser/color.hpp"


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


std::ostream &operator<<(std::ostream &os, const Color &c) {
	return os << "Color(" << +c.r() << ", " << +c.g() << ", " << +c.b() << ")";
}

