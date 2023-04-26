#ifndef RAY_TRACER_INCLUDE_STRUCTS_H
#define RAY_TRACER_INCLUDE_STRUCTS_H

#include <cstdlib>
#include <cinttypes>
#include <array>
#include <iostream>

template <typename T, size_t size>
struct Tuple : public std::array<T, size> {
};

template<typename T, size_t size>
std::ostream &operator<<(std::ostream &os, const Tuple<T, size> &t) {
	os << "(";
	if (!t.empty()) {
		os << t[0];
		for (size_t i = 1; i < t.size(); i++)
			os << ", " << t[i];
	}

	return os << ")";
}


#endif
