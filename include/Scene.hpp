//
// Created by bouce on 3/22/2021.
//

#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include "Displayer.hpp"
#include "Camera.hpp"
#include "SphericalLight.hpp"
#include "AmbientLight.hpp"
#include "Object.hpp"
#include <vector>
#include <stdexcept>
#include <string>

class Scene
{
private:
	Scene(Displayer *target, int w, int h);

public:
	enum GetterMode
	{
		CAMERA,
		LIGHT,
		SCENE
	};

	Scene() = delete;

	Scene(const Scene &other) = delete;

	static Scene *getInstance(Displayer *displayer, int w, int h);

	static Scene *getInstance();

	static void resetInstance();

	~Scene();

	void draw() const;

	void add_object(SceneObject *obj);

	void add_camera(Camera *obj);

	void add_light(Light *obj);

	Object *get_object(size_t index);

	Object *get_camera(size_t index);

	Object *get_light(size_t index);

	const Object *get_object(size_t index) const;

	const Object *get_camera(size_t index) const;

	const Object *get_light(size_t index) const;

	Object *operator[](size_t index);

	const Object *operator[](size_t index) const;

	void setGetterMode(GetterMode getterMode);

	void setBounces(uint16_t bounces);

	Hit intersect(const Ray &ray) const;

	void setAmbient(AmbientLight *ambient);

private:
	static Scene *instance;

	Displayer *_target;
	int _width;
	int _height;

	GetterMode _getterMode{CAMERA};
	std::vector<Camera *> _cameras;
	std::vector<Light *> _lights;
	std::vector<SceneObject *> _objects;
	uint16_t _bounces;
	AmbientLight *_ambient;


	uint32_t pixel_color(const Light *light, const Ray &ray, uint16_t bounces) const;

	uint32_t lighting(Hit &hit) const;
};


#endif //RAYTRACER_SCENE_HPP
