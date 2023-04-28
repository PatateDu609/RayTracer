#include "parser/camera.hpp"
#include "parser/scene.hpp"
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>

const Vector Camera::default_up{0, 1, 0};
const double Camera::default_fov = M_PI_2;


double angle_deg_to_rad(double deg) {
	static double ratio = M_PI / 180.0;

	return ratio * deg;
}


double angle_rad_to_deg(double rad) {
	static double ratio = 180.0 / M_PI;

	return ratio * rad;
}


Camera::Camera() : SceneBlockObject(""), pos(), pos_set(false), view_dir(), view_dir_set(false), up_dir(), fov_rad() {

}


const Vector &Camera::position() const {
	return pos;
}


const Vector &Camera::view() const {
	return view_dir;
}


const Vector &Camera::up() const {
	if (up_dir.has_value())
		return *up_dir;
	return default_up;
}


double Camera::fov() const {
	if (fov_rad.has_value())
		return *fov_rad;
	return default_fov;
}


void Camera::position(const Vector &p) {
	pos     = p;
	pos_set = true;
}


void Camera::view(const Vector &v) {
	view_dir = v;
	view_dir.normalize();
	view_dir_set = true;
}


void Camera::up(const Vector &u) {
	up_dir = u;
	up_dir->normalize();
}


void Camera::reset_up() {
	up_dir.reset();
}


void Camera::fov(double deg) {
	fov_rad = angle_deg_to_rad(deg);
	tan_fov = std::tan(*fov_rad / 2);
}


void Camera::reset_fov() {
	fov_rad.reset();
	tan_fov = std::tan(default_fov / 2);
}


#include "syntax_highlighting.hpp"


SyntaxHighlighter &operator<<(SyntaxHighlighter &sh, const Camera &cam) {
	sh << "Camera";
	if (cam.identifier)
		sh << *cam.identifier;
	sh << "{";

	if (cam.pos_set)
		sh << "position" << "=" << cam.pos;

	if (cam.view_dir_set)
		sh << "view_dir" << "=" << cam.view_dir;

	sh << "up_dir" << "=" << cam.up();
	sh << "fov" << "=" << angle_rad_to_deg(cam.fov()) << SyntaxHighlighter::endl;

	return sh << "}";
}


Ray Camera::cast_ray(const Tuple<double, 2> &pixel_coord) const {
	uint32_t w           = Scene::resolution().width();
	uint32_t h           = Scene::resolution().height();
	double   aspectRatio = Scene::resolution().aspect_ratio();

	Vector d{
			pixel_coord[0] - w / 2.,
			h / 2. - pixel_coord[1],
			-(h / 2.) / (tan_fov),
	};
	d.normalize();

	return Ray(Vector(0, 0, 0), d);
}
