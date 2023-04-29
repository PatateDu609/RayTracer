#ifndef RAY_TRACER_INCLUDE_PARSER_BOX_HPP
#define RAY_TRACER_INCLUDE_PARSER_BOX_HPP

#include "object.hpp"

class Box : public Object {
public:
	std::array<Vector3, 2> getBounds() const;
	void setBounds(const Vector3 &min, const Vector3 &max);

private:
	Vector3 bounds[2];
	bool bounds_set{false};

	friend class yy::parser;
};

#endif  //RAY_TRACER_INCLUDE_PARSER_BOX_HPP
