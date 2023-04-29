#ifndef RAYTRACER_INCLUDE_POINT_LIGHT_HPP
#define RAYTRACER_INCLUDE_POINT_LIGHT_HPP

#include "light.hpp"
#include <optional>
#include "color.hpp"
#include "maths/vector.hpp"

class PointLight final : public Light {
public:
	explicit PointLight(const std::string &identifier = "");

	void setPosition(const Vector3 &pos);
	[[nodiscard]] const Vector3 &getPosition() const;

	[[nodiscard]] Color compute_lighting(const std::shared_ptr<Object::IntersectionMetadata> &metadata) const final;

private:
	bool position_set{};

	Vector3 position;

	friend class yy::parser;

	friend SyntaxHighlighter &operator<<(SyntaxHighlighter& sh, const PointLight& pt);
};

#endif //RAYTRACER_INCLUDE_POINT_LIGHT_HPP
