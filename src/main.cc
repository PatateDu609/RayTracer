#include <iostream>
#include <sstream>
#include "parser.hpp"
#include "scene.hpp"

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

int main(int ac, char **av) {
	yyscan_t scanner;
	yylex_init(&scanner);
	yyset_in(open_file(ac, av), scanner);

	yy::parser parser(scanner);
	parser.parse();

	yylex_destroy(scanner);
	return 0;
}
