#include <iostream>
#include <sstream>
#include "parser/scene.hpp"
#include "parser.hpp"
#include "engine/renderer.hpp"

#include <stb_image_write.h>

std::string scene_filename;

static FILE *open_file(int ac, char **av) {
	if (ac == 1) {
		std::cout << "No argument was provided, please provide a scene input in the terminal." << std::endl;
		return stdin;
	}

	scene_filename = av[1];

	FILE *file = fopen(av[1], "r");
	if (file)
		return file;

	std::ostringstream oss;
	oss << "couldn't open " << av[1] << ": " << strerror(errno);
	yyerror(oss.str().c_str());

	exit(EXIT_FAILURE);
}


static int parse_scene(int ac, char **av) {
	yyscan_t scanner;
	yylex_init(&scanner);
	yyset_in(open_file(ac, av), scanner);

	yy::parser parser(scanner);
	int res = parser.parse();

	yylex_destroy(scanner);

	return res;
}


static void output_png(const std::string &path, const std::vector<uint8_t> &image) {
	uint32_t w = Scene::resolution().width();
	uint32_t h = Scene::resolution().height();

	stbi_write_png(path.c_str(), w, h, DEFAULT_IMG_COMP, image.data(), w * DEFAULT_IMG_COMP);
}


int main(int ac, char **av) {
	if (parse_scene(ac, av))
		return 1;

	dump_scene();

	output_png("result.png", render());
	return 0;
}
