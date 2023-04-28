#ifndef RAYTRACER_INCLUDE_PARSER_TUPLE_HPP
#define RAYTRACER_INCLUDE_PARSER_TUPLE_HPP

#include <cinttypes>
#include <array>
#include <cstdlib>

template<typename T, size_t size>
struct Tuple : public std::array<T, size> {
};

#endif //RAYTRACER_INCLUDE_PARSER_TUPLE_HPP
