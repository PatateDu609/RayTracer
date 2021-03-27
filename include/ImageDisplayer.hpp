//
// Created by bouce on 3/22/2021.
//

#ifndef RAYTRACER_IMAGEDISPLAYER_HPP
#define RAYTRACER_IMAGEDISPLAYER_HPP


#include "Displayer.hpp"
#include <string>
#include <vector>

class ImageDisplayer : public Displayer
{
public:
	enum Mode
	{
		JPG,
		PNG,
		BMP
	};

	ImageDisplayer() = delete;

	ImageDisplayer(Mode m, std::string name);

	[[maybe_unused]] ImageDisplayer(const ImageDisplayer &other);

	ImageDisplayer &operator=(const ImageDisplayer &other);

	void display(const std::vector<uint32_t> &data) override;

private:
	std::string _name;
	Mode _mode;
};


#endif //RAYTRACER_IMAGEDISPLAYER_HPP
