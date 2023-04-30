#include "parser/scene.hpp"
#include "syntax_highlighting.hpp"
#include "parser/object.hpp"
#include <sstream>
#include <complex>

std::unique_ptr<Scene> Scene::scene_instance{};


const char *NoSceneLoadedException::what() const noexcept {
	return "Scene accessed but never initialized";
}


Scene::MissingRequiredPropertyOrBlock::MissingRequiredPropertyOrBlock(const std::string &name) : message() {
	std::ostringstream oss;

	oss << "missing required property or block: " << name << std::endl;
}


const char *Scene::MissingRequiredPropertyOrBlock::what() const noexcept {
	return message.c_str();
}


void SceneParserProxy::set_resolution(const Resolution &resolution) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>();
	Scene::scene_instance->res = std::make_unique<Resolution>(resolution);
}


void SceneParserProxy::set_ambient_light(const AmbientLight &ambient_light) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>();
	Scene::scene_instance->ambient_lighting = std::make_unique<AmbientLight>(ambient_light);
}


void SceneParserProxy::set_camera(const Camera &camera) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>();
	Scene::scene_instance->cam = std::make_unique<Camera>(camera);
}


void SceneParserProxy::append_point_light(const PointLight &point_light) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>();
	Scene::scene_instance->pt_lights.emplace_back(new PointLight(point_light));
}


void SceneParserProxy::append_object(const std::shared_ptr<Object> &obj) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>();
	Scene::scene_instance->objs.emplace_back(obj);
}


void SceneParserProxy::append_material(const Material &material) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>();
	Scene::scene_instance->mats[material.getIdentifier().value()] = std::make_shared<Material>(material);
}


const Resolution &Scene::resolution() {
	if (!Scene::scene_instance)
		throw NoSceneLoadedException();
	return *Scene::scene_instance->res;
}


Camera &Scene::camera() {
	if (!Scene::scene_instance)
		throw NoSceneLoadedException();
	return *Scene::scene_instance->cam;
}


std::vector<std::shared_ptr<Light>> Scene::lights() {
	if (!Scene::scene_instance)
		throw NoSceneLoadedException();
	std::vector<std::shared_ptr<Light>> lts;
	auto                                &i = scene_instance;

	lts.push_back(i->ambient_lighting);

	for (const auto &pt_lts: i->pt_lights) {
		lts.push_back(pt_lts);
	}

	return lts;
}


const std::vector<std::shared_ptr<Object>> &Scene::objects() {
	if (!Scene::scene_instance)
		throw NoSceneLoadedException();
	return Scene::scene_instance->objs;
}


std::shared_ptr<Material> Scene::material(const std::string &id) {
	if (!Scene::scene_instance)
		throw NoSceneLoadedException();

	try {
		return Scene::scene_instance->mats.at(id);
	} catch (const std::out_of_range &e) {
		return std::shared_ptr<Material>(nullptr);
	}
}


bool Scene::cast_shadow_ray(const PointLight &pt, const std::shared_ptr<Object::IntersectionMetadata> &metadata) {
	const auto &objs = Scene::objects();

	Vector3 L    = pt.getPosition() - metadata->hit;
	double  norm = L.norm();
	Vector3 dir = L.normalize();

	Ray             ray(metadata->hit + metadata->normal * 1e-4, dir);
	for (const auto &obj: objs) {
		std::shared_ptr<Object::IntersectionMetadata> local_metadata = obj->intersect(ray);
		if (!local_metadata)
			continue;

		if (local_metadata->t < norm) // if distance of t is less than distance hit->light, there is an intersection.
			return false;
	}
	return true;
}


void dump_scene() {
	SyntaxHighlighter sh(std::cout);

	const std::unique_ptr<Scene> &s = Scene::scene_instance;

	sh << *s->res << SyntaxHighlighter::endl;

	if (s->ambient_lighting)
		sh << *s->ambient_lighting << SyntaxHighlighter::endl;
	if (s->cam)
		sh << *s->cam << SyntaxHighlighter::endl;
	sh << SyntaxHighlighter::endl;
	for (const auto &mat: s->mats) {
		sh << *mat.second << SyntaxHighlighter::endl;
	}

	for (const auto &l: s->pt_lights) {
		sh << *l << SyntaxHighlighter::endl;
	}
	for (const auto &obj: s->objs) {
		sh << obj << SyntaxHighlighter::endl;
	}
}
