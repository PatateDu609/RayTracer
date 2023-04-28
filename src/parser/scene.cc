#include "parser/scene.hpp"
#include <sstream>

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
		Scene::scene_instance = std::make_unique<Scene>(Scene());
	Scene::scene_instance->res = std::make_unique<Resolution>(resolution);
}


void SceneParserProxy::set_ambient_light(const AmbientLight &ambient_light) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>(Scene());
	Scene::scene_instance->ambient_lighting = std::make_unique<AmbientLight>(ambient_light);
}


void SceneParserProxy::set_camera(const Camera &camera) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>(Scene());
	Scene::scene_instance->cam = std::make_unique<Camera>(camera);
}


void SceneParserProxy::append_point_light(const PointLight &point_light) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>(Scene());
	Scene::scene_instance->pt_lights.emplace_back(new PointLight(point_light));
}


void SceneParserProxy::append_sphere(const Sphere &sphere) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>(Scene());
	Scene::scene_instance->sps.emplace_back(new Sphere(sphere));
}


void SceneParserProxy::append_material(const Material &material) {
	if (!Scene::scene_instance)
		Scene::scene_instance = std::make_unique<Scene>(Scene());
	Scene::scene_instance->mats[material.getIdentifier().value()] = std::make_shared<Material>(material);
}


const Resolution &Scene::resolution() {
	if (!Scene::scene_instance)
		throw NoSceneLoadedException();
	return *Scene::scene_instance->res;
}


const AmbientLight &Scene::ambient_light() {
	if (!Scene::scene_instance)
		throw NoSceneLoadedException();
	return *Scene::scene_instance->ambient_lighting;
}


const Camera &Scene::camera() {
	if (!Scene::scene_instance)
		throw NoSceneLoadedException();
	return *Scene::scene_instance->cam;
}


const std::vector<std::unique_ptr<PointLight>> &Scene::point_lights() {
	if (!Scene::scene_instance)
		throw NoSceneLoadedException();
	return Scene::scene_instance->pt_lights;
}


const std::vector<std::unique_ptr<Sphere>> &Scene::spheres() {
	if (!Scene::scene_instance)
		throw NoSceneLoadedException();
	return Scene::scene_instance->sps;
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
