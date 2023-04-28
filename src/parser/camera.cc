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
	pos = p;
	pos.normalize();
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


std::ostream &operator<<(std::ostream &os, const Camera &cam) {
	os << "Camera";
	if (cam.identifier)
		os << "(" << *cam.identifier << ")";
	os << "{";

	std::vector<std::string> parts;
	std::ostringstream       oss;

	if (cam.pos_set) {
		oss << "position = " << cam.pos;
		parts.push_back(oss.str());
		oss.str("");
		oss.clear();
	}

	if (cam.view_dir_set) {
		oss << "view_dir = " << cam.view_dir;
		parts.push_back(oss.str());
		oss.str("");
		oss.clear();
	}

	if (cam.up_dir.has_value()) {
		oss << "up_dir = " << *cam.up_dir;
		parts.push_back(oss.str());
		oss.str("");
		oss.clear();
	}

	if (cam.fov_rad.has_value()) {
		auto default_precision = oss.precision();
		oss << "fov = " << std::setprecision(1) << *cam.fov_rad
		    << std::setprecision(static_cast<int>(default_precision));
		oss.str("");
		oss.clear();
	}

	if (parts.empty())
		return os << "}";

	os << parts[0];
	for (size_t i = 1; i < parts.size(); i++)
		os << ", " << parts[i];

	return os << "}";
}


Ray Camera::cast_ray(const Tuple<double, 2> &pixel_coord) const {
	uint32_t w           = Scene::resolution().width();
	uint32_t h           = Scene::resolution().height();
	double   aspectRatio = Scene::resolution().aspect_ratio();

	double x = pixel_coord[0] - w  / 2;
	double y = pixel_coord[1] - h / 2;
	double z = - w / 2 * tan_fov * aspectRatio;

	return Ray(Vector(0, 0, 0), Vector(x, y, z));
}
