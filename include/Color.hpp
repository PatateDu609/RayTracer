//
// Created by bouce on 3/22/2021.
//

#ifndef RAYTRACER_COLOR_HPP
#define RAYTRACER_COLOR_HPP

#include <cstdint>
#include <iostream>

struct Color
{
	Color(uint32_t color, bool bgr = false);

	Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255);

	Color(const Color &other) = default;

	[[nodiscard]] uint32_t abgr() const;

	operator uint32_t() const;

	void setRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

	Color operator+(const Color& b) const;
	Color &operator+=(const Color& b);

	uint8_t r{};
	uint8_t g{};
	uint8_t b{};
	uint8_t a{255};
};

std::ostream& operator<<(std::ostream& os, const Color& c);

#endif //RAYTRACER_COLOR_HPP
