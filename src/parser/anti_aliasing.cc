#include <valarray>
#include "parser/anti_aliasing.hpp"


AntiAliasing::AntiAliasing(int nb_rays) : _nb_rays(nb_rays), _nb_rays_per_axis(sqrt(nb_rays)),
                                          _rays_increment(1.0 / _nb_rays_per_axis) {

}


int AntiAliasing::nb_rays_per_axis() const {
	return _nb_rays_per_axis;
}


double AntiAliasing::rays_increment() const {
	return _rays_increment;
}