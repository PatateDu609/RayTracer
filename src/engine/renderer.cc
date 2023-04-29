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


std::vector<Color> render() {
	uint32_t           w = Scene::resolution().width();
	uint32_t           h = Scene::resolution().height();
	std::vector<Color> res;
	res.reserve(w * h);

	Camera &cam = Scene::camera();
	const auto &lts = Scene::lights();

	cam.look_at();

	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			Ray ray = cam.cast_ray(make_pixel_tuple(x, y));

			if (lts.empty())
			{
				res.push_back(Color(0, 0, 0));
				continue;
			}

			const auto &intersection_metadata = intersection(ray);
			if (!intersection_metadata) {
				res.push_back(Color(0, 0, 0));
				continue;
			}

			Color final = compute_lighting(lts, intersection_metadata);
			res.push_back(final);
		}
	}

	return res;
}