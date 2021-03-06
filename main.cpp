#include <vector>
#include <Color.hpp>
#include <ImageDisplayer.hpp>
#include <ctime>

#include "stb_image_write.h"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "SphericalLight.hpp"

long SphericalLight::real_intensity = 700000000;

int main()
{
	clock_t start = clock();
	int w = 1024, h = 1024;
	ImageDisplayer img(ImageDisplayer::PNG, "../save");

	Scene *scene = Scene::getInstance(&img, w, h);
	scene->setGetterMode(Scene::SCENE);
	scene->setAmbient(false);
	scene->setBounces(5);
	scene->setSamples(32);

	scene->add_camera(new Camera({0, 0, 0}, {w, h}, 60));

	scene->add_object(new Sphere({0, 0, -55}, 20, Color(255, 255, 255)));
	scene->add_object(new Sphere({0, -2000 - 20, 0}, 2000, Color(255, 255, 255)));
	scene->add_object(new Sphere({0, 2000 + 100, 0}, 2000, Color(255, 255, 255)));
	scene->add_object(new Sphere({-2000 - 50, 0, 0}, 2000, Color(0, 255, 0)));
	scene->add_object(new Sphere({2000 + 50, 0, 0}, 2000, Color(0, 0, 255)));
	scene->add_object(new Sphere({0, 0, -2000 - 100}, 2000, Color(0, 255, 255)));

//	auto obj = dynamic_cast<SceneObject *>((*scene)[0]);
//	obj->setReflexion(1);
//	obj->setTransparency(1, 1.3);
//	obj = dynamic_cast<SceneObject *>((*scene)[1]);
//	obj->setReflexion(1);

	scene->add_light(new SphericalLight({15, 70, -30}, Color(255, 255, 255), 0.65));

	img.setSize(w, h);
	img.setComp(4);

	scene->draw();

	Scene::resetInstance();

	std::cout << "Elapsed time: " << (clock() - start) / (double) CLOCKS_PER_SEC << "s" << std::endl;
	return 0;
}