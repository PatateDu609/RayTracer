#include "camera.hpp"
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>

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
	view_dir     = v;
	view_dir_set = true;
}


void Camera::up(const Vector &u) {
	up_dir = u;
}


void Camera::reset_up() {
	up_dir.reset();
}


void Camera::fov(double deg) {
	fov_rad = angle_deg_to_rad(deg);
}


void Camera::reset_fov() {
	fov_rad.reset();
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