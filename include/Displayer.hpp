//
// Created by bouce on 3/22/2021.
//

#ifndef RAYTRACER_DISPLAYER_HPP
#define RAYTRACER_DISPLAYER_HPP

#include <vector>

class Displayer
{
public:
	virtual void display(const std::vector<uint32_t> &data) = 0;

	void setSize(int width, int height);

	void setComp(int comp);

protected:
	int _width;
	int _height;
	int _comp;
};


#endif //RAYTRACER_DISPLAYER_HPP
