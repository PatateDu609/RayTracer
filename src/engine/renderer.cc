#include "engine/renderer.hpp"
#include "parser/scene.hpp"
#include "parser/utils.hpp"


Tuple<double, 2> make_pixel_tuple(double x, double y) {
	return Tuple<double, 2>{x, y};
}


std::shared_ptr<IntersectionMetadata> intersection(const Ray &ray) {
	const auto &spheres = Scene::spheres();

	std::shared_ptr<IntersectionMetadata> intersection_metadata;
	for (size_t                           i = 0; i < spheres.size(); i++) {
		const auto &current_intersection_metadata = spheres[i]->intersect(ray);
		if (!current_intersection_metadata)
			continue;

		if (!intersection_metadata)
			intersection_metadata = current_intersection_metadata;
		else if (intersection_metadata->t < current_intersection_metadata->t) {
			intersection_metadata = current_intersection_metadata;
		}
	}

	return intersection_metadata;
}


std::vector<Color> render() {
	uint32_t           w = Scene::resolution().width();
	uint32_t           h = Scene::resolution().height();
	std::vector<Color> res;
	res.reserve(w * h);

	const Camera &cam = Scene::camera();
	const std::vector<std::unique_ptr<PointLight>> &lights = Scene::point_lights();

	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			Ray ray = cam.cast_ray(make_pixel_tuple(x, y));

			if (lights.empty())
			{
				res.push_back(Color(0, 0, 0));
				continue;
			}

			const auto &intersection_metadata = intersection(ray);
			if (!intersection_metadata) {
				res.push_back(Color(0, 0, 0));
				continue;
			}

			const auto& light = lights[0];
			res.push_back(light->compute_lighting(intersection_metadata));
		}
	}

	return res;
}