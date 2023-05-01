#include <chrono>
#include <valarray>
#include "engine/renderer.hpp"
#include "parser/scene.hpp"
#include "parser/utils.hpp"


Tuple<double, 2> make_pixel_tuple(double x, double y) {
	return Tuple<double, 2>{x, y};
}


std::shared_ptr<Object::IntersectionMetadata> intersection(const Ray &ray) {
	const auto &objs = Scene::objects();

	std::shared_ptr<Object::IntersectionMetadata> intersection_metadata;
	for (const auto& obj : objs) {
		const auto &current_intersection_metadata = obj->intersect(ray);
		if (!current_intersection_metadata)
			continue;

		if (!intersection_metadata)
			intersection_metadata = current_intersection_metadata;
		else if (current_intersection_metadata->t < intersection_metadata->t) {
			intersection_metadata = current_intersection_metadata;
		}
	}

	return intersection_metadata;
}

Color compute_single_anti_aliased_pixel(const Camera& cam, const std::vector<std::shared_ptr<Light>>& lts, size_t x, size_t y) {
	const auto &anti_aliasing = *Scene::antiAliasing();

	double ray_inc = anti_aliasing.rays_increment();
	double nb_rays_per_axis = anti_aliasing.nb_rays_per_axis();

	Color final;

	for (int i = 0; i < nb_rays_per_axis; i++)
	{
		for (int j = 0; j  < nb_rays_per_axis; j++) {
			Ray ray = cam.cast_ray(make_pixel_tuple(x + j * ray_inc, y + i * ray_inc));

			const auto &intersection_metadata = intersection(ray);
			if (!intersection_metadata) {
				final.r(final.r() / 2.);
				final.g(final.g() / 2.);
				final.b(final.b() / 2.);
				continue;
			}

			Color sub_final = compute_lighting(lts, intersection_metadata);
			if (i == 0 && j == 0)
			{
				final = sub_final;
				continue;
			}
			final.r((final.r() + sub_final.r()) / 2.);
			final.g((final.g() + sub_final.g()) / 2.);
			final.b((final.b() + sub_final.b()) / 2.);
		}
	}

	return final;
}

Color compute_single_pixel(const Camera& cam, const std::vector<std::shared_ptr<Light>>& lts, size_t x, size_t y) {
	const auto &anti_aliasing = Scene::antiAliasing();
	if (anti_aliasing)
		return compute_single_anti_aliased_pixel(cam, lts, x, y);

	Ray ray = cam.cast_ray(make_pixel_tuple(x, y));

	const auto &intersection_metadata = intersection(ray);
	if (!intersection_metadata) {
		return Color(0, 0, 0);
	}

	return compute_lighting(lts, intersection_metadata);
}


std::vector<uint8_t> render() {
	uint32_t           w = Scene::resolution().width();
	uint32_t           h = Scene::resolution().height();
	std::vector<uint8_t> res;
	res.reserve(w * h * DEFAULT_IMG_COMP);

	Camera &cam = Scene::camera();
	const auto &lts = Scene::lights();

	cam.look_at();

	auto start = std::chrono::high_resolution_clock::now();
	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			if (lts.empty())
			{
				res.push_back(0);
				res.push_back(0);
				res.push_back(0);
				continue;
			}

			Color final = compute_single_pixel(cam, lts, x, y);
			res.push_back(final.r());
			res.push_back(final.g());
			res.push_back(final.b());
		}
	}
	auto end = std::chrono::high_resolution_clock::now();

	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Rendering lasted for " << seconds.count() << "s" << std::endl;

	return res;
}