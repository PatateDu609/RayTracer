#include <iostream>
#include <sstream>
#include "parser/scene.hpp"
#include "parser.hpp"
#include "engine/renderer.hpp"

#include <stb_image_write.h>

#define DEFAULT_IMG_COMP 3


static FILE *open_file(int ac, char **av) {
	if (ac == 1) {
		std::cout << "No argument was provided, please provide a scene input in the terminal." << std::endl;
		return stdin;
	}

	FILE *file = fopen(av[1], "r");
	if (file)
		return file;

	std::ostringstream oss;
	oss << "couldn't open " << av[1] << ": " << strerror(errno);
	yyerror(oss.str().c_str());

	exit(EXIT_FAILURE);
}


static void parse_scene(int ac, char **av) {
	yyscan_t scanner;
	yylex_init(&scanner);
	yyset_in(open_file(ac, av), scanner);

	yy::parser parser(scanner);
	parser.parse();

	yylex_destroy(scanner);
}


static void output_png(const std::string &path, const std::vector<uint8_t> &image) {
	uint32_t w = Scene::resolution().width();
	uint32_t h = Scene::resolution().height();

	stbi_write_png(path.c_str(), w, h, DEFAULT_IMG_COMP, image.data(), w * DEFAULT_IMG_COMP);
}


int main(int ac, char **av) {
	parse_scene(ac, av);

	dump_scene();

	const std::vector<Color> &colors = render();

	std::vector<uint8_t> res;
	res.reserve(colors.size() * DEFAULT_IMG_COMP);

	for (const Color& c : colors) {
		res.push_back(c.r());
		res.push_back(c.g());
		res.push_back(c.b());
	}

	output_png("result.png", res);
	return 0;
}
