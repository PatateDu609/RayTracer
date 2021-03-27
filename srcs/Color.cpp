//
// Created by bouce on 3/22/2021.
//

#include <algorithm>
#include "Color.hpp"

Color::Color(uint32_t color, bool bgr)
{
	if (bgr)
	{
		a = (color & 0xff000000) >> 24;
		b = (color & 0x00ff0000) >> 16;
		g = (color & 0x0000ff00) >> 8;
		r = (color & 0x000000ff);
	}
	else
	{
		r = (color & 0xff000000) >> 24;
		g = (color & 0x00ff0000) >> 16;
		b = (color & 0x0000ff00) >> 8;
		a = (color & 0x000000ff);
	}
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	setRGBA(r, g, b, a);
}

uint32_t Color::abgr() const
{
	return a << 24 | b << 16 | g << 8 | r;
}

Color::operator uint32_t() const
{
	return abgr();
}

void Color::setRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color Color::operator+(const Color &color) const
{
	Color res;

	res.r = std::min(255, (int)r + (int)color.r);
	res.g = std::min(255, (int)g + (int)color.g);
	res.b = std::min(255, (int)b + (int)color.b);
	res.a = 255;
	return res;
}

Color &Color::operator+=(const Color &b)
{
	*this = *this + b;
	return *this;
}