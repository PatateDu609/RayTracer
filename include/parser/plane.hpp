#ifndef RAY_TRACER_INCLUDE_PARSER_PLANE_HPP
#define RAY_TRACER_INCLUDE_PARSER_PLANE_HPP

#include "object.hpp"

class Plane : public Object {
public:
	const Vector3& getPoint() const;
	void setPoint(const Vector3& pt);


	const Vector3& getNormal() const;
	void setNormal(const Vector3& N);

	virtual std::shared_ptr<IntersectionMetadata> intersect(const Ray &r) const final;

	virtual SyntaxHighlighter& dump(SyntaxHighlighter& sh) const final;

private:
	Vector3 point;
	bool point_set{false};

	Vector3 normal;
	bool normal_set{false};

	friend class yy::parser;
};

#endif  //RAY_TRACER_INCLUDE_PARSER_PLANE_HPP
