/**
 * Defining all functions for the Scene class.
 * \author Teyber
 * \file Scene.cpp
 * \date 3/27/2021
 */

#define _USE_MATH_DEFINES

#include "Sphere.hpp"
#include "Scene.hpp"

#include <random>
#include <cmath>
#include <future>
#include <atomic>
#include <thread>

std::default_random_engine g_engine;
std::uniform_real_distribution<double> g_uniform(0, 1);

Scene *Scene::instance = nullptr;

double random(double min, double  max)
{
	return min + (max - min) * g_uniform(g_engine);
}

/**
 * Returns the square of the number in parameter.
 * \param n
 * \return n * n
 */
double sqr(double n)
{
	return n * n;
}

/**
 * Constructs a scene.
 * @param target Display target.
 * @param w Image's width.
 * @param h Image's height.
 */
Scene::Scene(Displayer *target, int w, int h) : _target(target), _width(w), _height(h), _bounces(0), _samples(1),
                                                _ambient(false)
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
	for (Object *cam : _cameras)
		delete cam;
	for (Object *light : _lights)
		delete light;
	for (Object *obj : _objects)
		delete obj;
}

/**
 * Traces a ray into the scene and saves its color in the frame.
 * @param coord Current coordinates where we want to draw.
 * @param pixel The frame array.
 */
void Scene::trace(const Vector2i &coord, uint32_t &pixel, Camera *cam) const
{
//	Color c;
	Vector3lf c;
	for (int k = 0; k < _samples; k++)
	{
		double r1 = g_uniform(g_engine);
		double r2 = g_uniform(g_engine);
		double R = sqrt(- 2 * log(r1));
		double dx = R * cos(2 * M_PI * r2);
		double dy = R * sin(2 * M_PI * r2);

		Ray ray = cam->castRay(coord, {dx, dy});

		Color tmp(pixel_color(ray, _bounces), true);
		c += Vector3lf(tmp.r, tmp.g, tmp.b);
	}
	c *= 1. / _samples;
	pixel = Color(c.x, c.y, c.z);
}

/**
 * Draw the current scene targeting the displayer.
 */
void Scene::draw() const
{
	Camera *cam;
	std::vector<uint32_t> frame(_width * _height, 0);
	std::vector<std::future<void>> futures;

	cam = _cameras[0];

	std::size_t max = _width * _height;
	std::size_t cores = std::thread::hardware_concurrency();

	for (std::size_t i(0); i < cores; i++)
	{
		futures.emplace_back(
			std::async([&frame, i, max, cores, cam, this]() {
				for (std::size_t index(i); index < max; index += cores)
				{
					std::size_t x = index % _width;
					std::size_t y = index / _width;

					trace({(int) x, (int) y}, frame[index], cam);
				}
			})
		);
	}

	for (std::size_t i = 0; i < cores; i++)
		futures[i].wait();

	_target->display(frame);
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

	for (Object *obj : _objects)
	{
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
uint32_t Scene::pixel_color(const Ray &ray, uint16_t bounces) const
{
	Hit hit = intersect(ray);

	if (!hit.obj)
		return Color();
	else if (hit.obj->getReflexion() != 0.f && bounces)
	{
		Vector3lf dir = (ray.dir - 2 * ray.dir.dot(hit.normal) * hit.normal).normalize();
		return pixel_color(Ray{.origin = hit.pos + 0.001 * hit.normal, .dir = dir}, bounces - 1);
	}
	else if (hit.obj->getTransparency() != 0.f && bounces)
	{
		double n1 = 1;
		double n2 = hit.obj->getIOR();
		Vector3lf N = hit.normal;

		if (ray.dir.dot(hit.normal) > 0)
		{
			std::swap(n1, n2);
			N = -hit.normal;
		}

		double radical = 1. - sqr(n1 / n2) * (1. - sqr(N.dot(ray.dir)));
		if (radical > 0)
		{
			Vector3lf dir = (n1 / n2) * (ray.dir - ray.dir.dot(N) * N) - N * sqrt(radical);
			return pixel_color(Ray{.origin = hit.pos - 0.001 * N, .dir = dir.normalize()}, bounces - 1);
		}
		return Color();
	}
	else
		return lighting(ray, hit, bounces - 1);
}

/**
 * Set the scene bounces to enable the recursive ray casting.
 * @param bounces Max number of bounces.
 */
void Scene::setBounces(uint16_t bounces)
{
	_bounces = bounces;
}

/**
 * Computes the Ambient lighting.
 *
 * \param hit The target point.
 */
uint32_t Scene::ambient(const Ray &ray, const Hit &hit, uint16_t bounces) const
{
	double r1 = g_uniform(g_engine);
	double r2 = g_uniform(g_engine);
	Vector3lf local(
		cos(2 * M_PI * r1) * sqrt(1 - r2),
		sin(2 * M_PI * r1) * sqrt(1 - r2),
		sqrt(r2)
	);
	Vector3lf random(g_uniform(g_engine) - 0.5, g_uniform(g_engine) - 0.5, g_uniform(g_engine) - 0.5);
	Vector3lf tangent1 = hit.normal.cross(random).normalize();
	Vector3lf tangent2 = tangent1.cross(hit.normal);

	Vector3lf dir = local[2] * hit.normal + local[0] * tangent1 + local[1] * tangent2;
	Ray randomRay{.origin = hit.pos + 0.001 * hit.normal, .dir = dir};
	Color c = Color(pixel_color(randomRay, bounces - 1), true);
	c.r *= hit.obj->getColor().r / 255.;
	c.g *= hit.obj->getColor().g / 255.;
	c.b *= hit.obj->getColor().b / 255.;
	return c;
}

/**
 * Computes the lighting of the scene.
 * @param hit The point where we need to compute the lighting.
 * @return The final color.
 */
uint32_t Scene::lighting(const Ray &ray, const Hit &hit, uint16_t bounces) const
{
	Color res;

	for (Light *light : _lights)
		res += Color(light->shade(hit), true);
	if (_ambient)
		res += Color(ambient(ray, hit, bounces), true);
	return res;
}

/**
 * Set the number of required samples.
 * @param samples
 */
void Scene::setSamples(uint16_t samples)
{
	_samples = std::max(static_cast<uint16_t>(1), samples);
}

/**
 * Set if we need to bother rendering ambient lighting or not.
 * @param ambient
 */
void Scene::setAmbient(bool ambient)
{
	_ambient = ambient;
}
