/**
 * Defining all functions for the Scene class.
 * \author Teyber
 * \file Scene.cpp
 * \date 3/27/2021
 */

#include <Sphere.hpp>
#include "Scene.hpp"

Scene *Scene::instance = nullptr;

/**
 * Constructs a scene.
 * @param target Display target.
 * @param w Image's width.
 * @param h Image's height.
 */
Scene::Scene(Displayer *target, int w, int h) : _target(target), _width(w), _height(h), _bounces(0)
{}

/**
 * Get (or construct) the unique instance of Scene.
 *
 * @see Scene::Scene()
 *
 * @param displayer
 * @param w
 * @param h
 * @return The instance of Scene.
 */
Scene *Scene::getInstance(Displayer *displayer, int w, int h)
{
	return instance ? instance : (instance = new Scene(displayer, w, h));
}

/**
 * Get an existent instance of Scene (or returns nullptr).
 * @return
 */
Scene *Scene::getInstance()
{
	return instance;
}

/**
 * Deletes the current instance of Scene.
 */
void Scene::resetInstance()
{
	delete instance;
	instance = nullptr;
}

/**
 * Destructs all the stored objects.
 */
Scene::~Scene()
{
	for (Object * cam : _cameras)
		delete cam;
	for (Object * light : _lights)
		delete light;
	for (Object *obj : _objects)
		delete obj;
}

/**
 * Draw the current scene targeting the displayer.
 */
void Scene::draw() const
{
	Camera *cam;
	Light *light;
	std::vector<uint32_t> _frame(_width * _height, 0);

	cam = _cameras[0];
	light = _lights[0];

	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			Ray ray = cam->castRay({x, y});
			_frame[y * _width + x] = pixel_color(light, ray, _bounces);
		}
	}

	_target->display(_frame);
}

/**
 * Adding a displayable object to the scene.
 * @param obj
 */
void Scene::add_object(SceneObject *obj)
{
	_objects.push_back(obj);
}

/**
 * Adding a camera.
 * @param obj
 */
void Scene::add_camera(Camera *obj)
{
	_cameras.push_back(obj);
}

/**
 * Adding a light.
 * @param obj
 */
void Scene::add_light(Light *obj)
{
	_lights.push_back(obj);
}

/**
 * Getting a scene object.
 * @param Index Index of the object.
 * @return
 */
Object *Scene::get_object(size_t index)
{
	if (index > _objects.size())
		throw std::out_of_range(std::to_string(index) + " is out of range");
	return _objects[index];
}

/**
 * Getting a camera.
 * @param Index Index of the object.
 * @return
 */
Object *Scene::get_camera(size_t index)
{
	if (index > _cameras.size())
		throw std::out_of_range(std::to_string(index) + " is out of range");
	return _cameras[index];
}

/**
 * Getting a light.
 * @param Index Index of the object.
 * @return
 */
Object *Scene::get_light(size_t index)
{
	if (index > _lights.size())
		throw std::out_of_range(std::to_string(index) + " is out of range");
	return _lights[index];
}

const Object *Scene::get_object(size_t index) const
{
	if (index > _objects.size())
		throw std::out_of_range(std::to_string(index) + " is out of range");
	return _objects[index];
}

const Object *Scene::get_camera(size_t index) const
{
	if (index > _cameras.size())
		throw std::out_of_range(std::to_string(index) + " is out of range");
	return _cameras[index];
}

const Object *Scene::get_light(size_t index) const
{
	if (index > _cameras.size())
		throw std::out_of_range(std::to_string(index) + " is out of range");
	return _cameras[index];
}

void Scene::setGetterMode(Scene::GetterMode getterMode)
{
	_getterMode = getterMode;
}

Object *Scene::operator[](size_t index)
{
	return _getterMode == SCENE ? get_object(index) : (_getterMode == CAMERA ? get_camera(index) : get_light(index));
}

const Object *Scene::operator[](size_t index) const
{
	return _getterMode == SCENE ? get_object(index) : (_getterMode == CAMERA ? get_camera(index) : get_light(index));
}

/**
 * Intersection routine with the current scene.
 * @param Ray The ray that needs to be intersected.
 * @return Returns a hit (with the intersected object).
 */
Hit Scene::intersect(const Ray &ray) const
{
	Hit local;
	Hit hit;
	hit.obj = nullptr;

	for (Object *obj : _objects) {
		auto *tobj = dynamic_cast<SceneObject *>(obj);

		if (tobj == nullptr)
			continue;

		if (tobj->intersect(ray, local))
			hit = (hit.obj == nullptr) ? local : Hit::nearest(hit, local);
	}

	return hit;
}

/**
 * Recursive routine that computes the current pixel color (and recurse if bounces is not 0, and if the surface has reflexion/refraction).
 * @param light The current light (TODO: needs to be modified to take care of multiple lighting).
 * @param ray The ray to intersect with the scene, can be from the camera or from a mirror/transparent surface.
 * @param bounces Remaining bounces.
 * @return Final pixel color.
 */
uint32_t Scene::pixel_color(const Light *light, const Ray &ray, uint16_t bounces) const
{
	Hit hit = intersect(ray);

	if (hit.obj && (hit.obj->getReflexion() == 0.0f || !bounces))
		return light->shade(hit);
	else if (hit.obj) {
		Vector3lf dir = (ray.dir - 2 * ray.dir.dot(hit.normal) * hit.normal).normalize();
		return pixel_color(light, Ray{.origin = hit.pos + 0.001 * hit.normal, .dir = dir}, bounces - 1);
	}
	return Color();
}

/**
 * Set the scene bounces to enable the recursive ray casting.
 * @param bounces Max number of bounces.
 */
void Scene::setBounces(uint16_t bounces)
{
	_bounces = bounces;
}
