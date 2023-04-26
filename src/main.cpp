#include <iostream>
#include "parser.hpp"

int main() {
	yyscan_t scanner;
	yylex_init(&scanner);

	yy::parser parser(scanner);
	parser.parse();

	yylex_destroy(scanner);
	return 0;
}
