#ifndef RAY_TRACER_INCLUDE_CAMERA_HPP
#define RAY_TRACER_INCLUDE_CAMERA_HPP

#include "scene_block_object.hpp"
#include "vector.hpp"
#include "engine/ray.hpp"

double angle_deg_to_rad(double deg);
double angle_rad_to_deg(double rad);

class Camera : public SceneBlockObject {
public:
	Camera();
	Camera(const Camera &other) = default;
	Camera &operator=(const Camera &other) = default;
	~Camera() override = default;

	[[nodiscard]] const Vector &position() const;
	[[nodiscard]] const Vector &view() const;
	[[nodiscard]] const Vector &up() const;
	[[nodiscard]] double fov() const;

	void position(const Vector &p);
	void view(const Vector &v);
	void up(const Vector &u);
	void reset_up();
	void fov(double deg);
	void reset_fov();

	Ray cast_ray(const Tuple<double, 2>& pixel_coord) const;

private:
	static const Vector default_up;
	static const double default_fov;

	Vector pos;
	bool   pos_set;

	Vector view_dir;
	bool   view_dir_set;

	std::optional<Vector> up_dir;

	std::optional<double> fov_rad;
	double tan_fov;

	friend SyntaxHighlighter &operator<<(SyntaxHighlighter& os, const Camera& cam);
	friend class yy::parser;
};

#endif //RAY_TRACER_INCLUDE_CAMERA_HPP
