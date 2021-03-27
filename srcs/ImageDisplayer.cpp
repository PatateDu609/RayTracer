//
// Created by bouce on 3/22/2021.
//

#include "ImageDisplayer.hpp"

#include <utility>
#include <Color.hpp>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image_write.h>
#include <iostream>

ImageDisplayer::ImageDisplayer(ImageDisplayer::Mode m, std::string name) : _name(std::move(name)), _mode(m)
{
	switch (m)
	{
		case PNG:
			_name += ".png";
			break;
		case JPG:
			_name += ".jpg";
			break;
		case BMP:
			_name += ".bmp";
			break;
		default:
			std::cerr << "Unknown format." << std::endl;
	}
}

[[maybe_unused]] ImageDisplayer::ImageDisplayer(const ImageDisplayer &other)
{
	*this = other;
}

ImageDisplayer &ImageDisplayer::operator=(const ImageDisplayer &other)
{
	_name = other._name;
	_mode = other._mode;
	return *this;
}

void ImageDisplayer::display(const std::vector<uint32_t> &data)
{
	switch (_mode)
	{
		case JPG:
		{
			std::vector<uint32_t> reversed = data;
			for (size_t i = 0; i < data.size(); i++)
				reversed[i] = Color(reversed[i], true);
			stbi_write_jpg(_name.c_str(), _width, _height, _comp, reversed.data(), 0);
			break;
		}
		case PNG:
			stbi_write_png(_name.c_str(), _width, _height, _comp, data.data(), _width * _comp);
			break;
		case BMP:
			stbi_write_bmp(_name.c_str(), _width, _height, _comp, data.data());
			break;
		default:
			std::cerr << "Unknown format." << std::endl;
	}
}
