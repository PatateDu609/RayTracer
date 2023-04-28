#include "parser/resolution.hpp"


Resolution::Resolution(uint32_t w, uint32_t h) : tuple{w, h} {
	update_ratio();
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


double Resolution::aspect_ratio() const {
	return ratio;
}


void Resolution::width(uint32_t val) {
	tuple[0] = val;
	update_ratio();
}


void Resolution::height(uint32_t val) {
	tuple[1] = val;
	update_ratio();
}


void Resolution::update_ratio() {
	if (tuple[0] && tuple[1])
		ratio = static_cast<double>(tuple[0]) / static_cast<double>(tuple[1]);
	else
		ratio = 0;
}


#include "syntax_highlighting.hpp"


SyntaxHighlighter &operator<<(SyntaxHighlighter &os, const Resolution &r) {
	os << "Resolution" << "=" << "(" << static_cast<long>(r.tuple[0]) << "," << static_cast<long>(r.tuple[1]) << ")";
	return os;
}