%{
	#include <sstream>
	#include <string>

	//  /!\ DON'T REMOVE THIS LINE, IT IS ABSOLUTELY CRUCIAL TO THE LEXER.
	// / ! \ It will do really strange stuff with its definitions...
	#define DONT_NEED_LEXER
	#include "parser.hpp"

	int col = 1;
	int row = 1;

	typedef yy::parser::token_kind_type token_kind_type;
%}

DIGIT [0-9]
ID [a-z][a-z0-9A-Z_]*

%option noinput nounput noyywrap reentrant

%%

"resolution" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::RESOLUTION;
}
"point_light" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::POINT_LIGHT;
}
"ambient_light" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::AMBIENT_LIGHT;
}
"camera" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::CAMERA;
}
"sphere" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::SPHERE;
}
"position" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::POSITION;
}
"color" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::COLOR;
}
"intensity" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::INTENSITY;
}
"view_direction" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::VIEW_DIRECTION;
}
"fov" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::FOV;
}
"material" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::MATERIAL;
}
"radius" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::RADIUS;
}
"diffuse" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::DIFFUSE;
}
"plane" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::PLANE;
}
"triangle" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::TRIANGLE;
}
"point" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::POINT;
}
"normal" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::NORMAL;
}
"points" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::POINTS;
}
"nb_rays" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::NB_RAYS;
}

[+-]?{DIGIT}+ {
	std::string yystr(yytext);
	long val = std::stol(yystr);

	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += yystr.length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;

	yylval->emplace<long>(val);
	return token_kind_type::INT;
}

[+-]?{DIGIT}+"."{DIGIT}+ {
	std::string yystr(yytext);
	double val = std::stod(yystr);

		yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += yystr.length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;

	yylval->emplace<double>(val);
	return token_kind_type::FLOAT;
}

"{" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::OPEN_BLOCK;
}
"}" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::CLOSE_BLOCK;
}

"(" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::OPEN_TUPLE;
}
")" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::CLOSE_TUPLE;
}
"," {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::COMMA;
}
"=" {
	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += std::string(yytext).length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;
	return token_kind_type::EQUAL;
}

{ID} {
	std::string yystr(yytext);

	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col += yystr.length();

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;

	yylval->emplace<std::string>(yystr);
	return token_kind_type::ID;
}

[ ] {
	col++;
}

[\t] {
	col += 4;
}

\n|\r\n {
	col = 1;
	row++;
}

. {
	std::ostringstream oss;

	yy::position begin;
	begin.initialize(&scene_filename, row, col);

	col++;

	yy::position end;
	end.initialize(&scene_filename, row, col);

	yylloc->begin = begin;
	yylloc->end = end;

	oss << "bad character encountred: " << row << ":" << col << ": " << yytext;
	yyerror(oss.str().c_str());

	return token_kind_type::YYUNDEF;
}

%%

int yyerror(const char *s) {
	std::cerr << "error: " << s << std::endl;
	return 1;
}
