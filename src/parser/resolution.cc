#include "resolution.hpp"

Resolution::Resolution(uint32_t w, uint32_t h) : tuple{w, h} {

}


uint32_t Resolution::width() const {
	return tuple[0];
}


uint32_t Resolution::height() const {
	return tuple[1];
}


std::pair<uint32_t, uint32_t> Resolution::size() const {
	return std::make_pair(width(), height());
}


void Resolution::width(uint32_t val) {
	tuple[0] = val;
}


void Resolution::height(uint32_t val) {
	tuple[1] = val;
}

std::ostream& operator<<(std::ostream& os, const Resolution& r) {
	os << "Resolution" << r.tuple;
	return os;
}