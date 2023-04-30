#include "maths/utils.hpp"
#include <cmath>

double angle_deg_to_rad(double deg) {
	static double ratio = M_PI / 180.0;

	return ratio * deg;
}


double angle_rad_to_deg(double rad) {
	static double ratio = 180.0 / M_PI;

	return ratio * rad;
}