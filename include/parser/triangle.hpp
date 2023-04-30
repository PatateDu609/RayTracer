#ifndef RAY_TRACER_INCLUDE_PARSER_TRIANGLE_HPP
#define RAY_TRACER_INCLUDE_PARSER_TRIANGLE_HPP

#include <vector>
#include "object.hpp"

class Triangle : public Object {
public:
	const std::vector<Vector3> &vertices() const;
	void vertices(const std::vector<Vector3> &v);

	std::shared_ptr<IntersectionMetadata> intersect(const Ray &r) const final;

protected:
	SyntaxHighlighter &dump(SyntaxHighlighter &sh) const final;

private:
	std::vector<Vector3> _vertices;

	friend class yy::parser;
};

#endif //RAY_TRACER_INCLUDE_PARSER_TRIANGLE_HPP