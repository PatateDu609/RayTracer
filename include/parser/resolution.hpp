#ifndef RAYTRACER_SRC_PARSER_RESOLUTION_HPP
#define RAYTRACER_SRC_PARSER_RESOLUTION_HPP

#include "utils.hpp"
#include <iostream>
#include "tuple.hpp"

class SyntaxHighlighter;

class Resolution {
public:
	Resolution() = default;
	Resolution(const Resolution &other) = default;
	Resolution &operator=(const Resolution &other) = default;
	~Resolution() = default;

	Resolution(uint32_t w, uint32_t h);

	[[nodiscard]] uint32_t width() const;
	[[nodiscard]] uint32_t height() const;
	[[nodiscard]] double aspect_ratio() const;
	[[nodiscard]] std::pair<uint32_t, uint32_t> size() const;

	void width(uint32_t val);
	void height(uint32_t val);

private:
	Tuple<uint32_t, 2> tuple;
	double ratio;

	void update_ratio();

	friend SyntaxHighlighter &operator<<(SyntaxHighlighter &os, const Resolution &r);
};


#endif //RAYTRACER_SRC_PARSER_RESOLUTION_HPP
