#ifndef RAYTRACER_INCLUDE_AMBIENT_LIGHT_HPP
#define RAYTRACER_INCLUDE_AMBIENT_LIGHT_HPP

#include "light.hpp"

class AmbientLight final : public Light {
public:
	explicit AmbientLight(const std::string& identifier = "");

	[[nodiscard]] Color compute_lighting(const std::shared_ptr<IntersectionMetadata> &metadata) const final;

	friend class yy::parser;
	friend SyntaxHighlighter& operator<<(SyntaxHighlighter& sh, const AmbientLight &lt);
};

#endif //RAYTRACER_INCLUDE_AMBIENT_LIGHT_HPP
