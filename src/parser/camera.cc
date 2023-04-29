#include "parser/camera.hpp"
#include "parser/scene.hpp"
#include "syntax_highlighting.hpp"
#include <cmath>

const Vector3 Camera::default_up{0, 1, 0};
const double  Camera::default_fov = M_PI_2;


double angle_deg_to_rad(double deg) {
	static double ratio = M_PI / 180.0;

	return ratio * deg;
}


double angle_rad_to_deg(double rad) {
	static double ratio = 180.0 / M_PI;

	return ratio * rad;
}


Camera::Camera() : SceneBlockObject(""), pos(), pos_set(false), view_dir(), view_dir_set(false), fov_rad() {
	tan_fov = tan(default_fov / 2);
}


const Vector3 &Camera::position() const {
	return pos;
}


const Vector3 &Camera::view() const {
	return view_dir;
}


double Camera::fov() const {
	if (fov_rad.has_value())
		return *fov_rad;
	return default_fov;
}


void Camera::position(const Vector3 &p) {
	pos     = p;
	pos_set = true;
}


void Camera::view(const Vector3 &v) {
	view_dir = v;
	view_dir.normalize();
	view_dir_set = true;
}


void Camera::fov(double deg) {
	fov_rad = angle_deg_to_rad(deg);
	tan_fov = std::tan(*fov_rad / 2);
}


void Camera::reset_fov() {
	fov_rad.reset();
	tan_fov = std::tan(default_fov / 2);
}


SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, const Camera &cam) {
	sh << "Camera";
	if (cam.identifier)
		sh << *cam.identifier;
	sh << "{";

	if (cam.pos_set)
		sh << "position" << "=" << cam.pos;

	if (cam.view_dir_set)
		sh << "view_dir" << "=" << cam.view();

	sh << "fov" << "=" << angle_rad_to_deg(cam.fov()) << SyntaxHighlighter::endl;

	return sh << "}";
}


void Camera::look_at() {
	Vector3 forward = view();

	Vector3 arbitrary(0, 1, 0);
	arbitrary.normalize();

	Vector3 right = arbitrary.cross(forward);

	Vector3 up = forward.cross(right);

	c2w.set_row(0, right, 0);
	c2w.set_row(1, up, 0);
	c2w.set_row(2, forward, 0);
	c2w.set_row(3, position(), 1);

	ray_origin = c2w.transform_point(Vector3(0, 0, 0));
}


Ray Camera::cast_ray(const Tuple<double, 2> &pixel_coord) const {
	uint32_t w = Scene::resolution().width();
	uint32_t h = Scene::resolution().height();
	double   aspectRatio = Scene::resolution().aspect_ratio();

	double x = pixel_coord[0];
	double y = pixel_coord[1];

	double fx = (2 * (x + .5) / static_cast<double>(w) - 1) * aspectRatio * tan_fov;
	double fy = (1 - 2 * (y + .5) / static_cast<double>(h)) * tan_fov;


	return Ray(ray_origin, c2w.transform_direction(fx, fy, -1));
}
