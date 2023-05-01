#ifndef RAYTRACER_INCLUDE_PARSER_ANTI_ALIASING_HPP
#define RAYTRACER_INCLUDE_PARSER_ANTI_ALIASING_HPP

class AntiAliasing {
public:
	AntiAliasing() = default;
	AntiAliasing(int nb_rays);

	int nb_rays_per_axis() const;
	double rays_increment() const;

private:
	int _nb_rays;
	int _nb_rays_per_axis;
	double _rays_increment;
};

#endif //RAYTRACER_INCLUDE_PARSER_ANTI_ALIASING_HPP
