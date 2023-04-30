#ifndef RAY_TRACER_INCLUDE_CAMERA_HPP
#define RAY_TRACER_INCLUDE_CAMERA_HPP

#include "scene_block_object.hpp"
#include "maths/vector.hpp"
#include "engine/ray.hpp"
#include "maths/matrix.hpp"

class Camera : public SceneBlockObject {
public:
	Camera();
	Camera(const Camera &other) = default;
	Camera &operator=(const Camera &other) = default;
	~Camera() override = default;

	[[nodiscard]] const Vector3 &position() const;
	[[nodiscard]] const Vector3 &view() const;
	[[nodiscard]] double fov() const;

	void position(const Vector3 &p);
	void view(const Vector3 &v);
	void fov(double deg);
	void reset_fov();

	Ray cast_ray(const Tuple<double, 2>& pixel_coord) const;

	void look_at();

private:
	static const Vector3 default_up;
	static const double  default_fov;

	Vector3 pos;
	bool    pos_set;

	Vector3 view_dir;
	bool    view_dir_set;

	std::optional<double> fov_rad;
	double tan_fov;

	Matrix4x4 c2w;
	Vector3 ray_origin;

	friend SyntaxHighlighter &operator<<(SyntaxHighlighter& os, const Camera& cam);
	friend class yy::parser;
};

#endif //RAY_TRACER_INCLUDE_CAMERA_HPP
