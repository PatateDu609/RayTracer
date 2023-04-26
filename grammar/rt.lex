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
	col += std::string(yytext).length();
	return token_kind_type::RESOLUTION;
}
"point_light" {
	col += std::string(yytext).length();
	return token_kind_type::POINT_LIGHT;
}
"ambient_light" {
	col += std::string(yytext).length();
	return token_kind_type::AMBIENT_LIGHT;
}
"camera" {
	col += std::string(yytext).length();
	return token_kind_type::CAMERA;
}
"sphere" {
	col += std::string(yytext).length();
	return token_kind_type::SPHERE;
}
"position" {
	col += std::string(yytext).length();
	return token_kind_type::POSITION;
}
"color" {
	col += std::string(yytext).length();
	return token_kind_type::COLOR;
}
"intensity" {
	col += std::string(yytext).length();
	return token_kind_type::INTENSITY;
}
"view_direction" {
	col += std::string(yytext).length();
	return token_kind_type::VIEW_DIRECTION;
}
"up_direction" {
	col += std::string(yytext).length();
	return token_kind_type::UP_DIRECTION;
}
"fov" {
	col += std::string(yytext).length();
	return token_kind_type::FOV;
}
"material" {
	col += std::string(yytext).length();
	return token_kind_type::MATERIAL;
}
"radius" {
	col += std::string(yytext).length();
	return token_kind_type::RADIUS;
}
"diffuse" {
	col += std::string(yytext).length();
	return token_kind_type::DIFFUSE;
}

[+-]?{DIGIT}+ {
	std::string yystr(yytext);
	long val = std::stol(yystr);

	col += yystr.length();
	yylval->emplace<long>(val);
	return token_kind_type::INT;
}

[+-]?{DIGIT}+"."{DIGIT}+ {
	std::string yystr(yytext);
	double val = std::stod(yystr);

	col += yystr.length();
	yylval->emplace<double>(val);
	return token_kind_type::FLOAT;
}

"{" {
	col += std::string(yytext).length();
	return token_kind_type::OPEN_BLOCK;
}
"}" {
	col += std::string(yytext).length();
	return token_kind_type::CLOSE_BLOCK;
}

"(" {
	col += std::string(yytext).length();
	return token_kind_type::OPEN_TUPLE;
}
")" {
	col += std::string(yytext).length();
	return token_kind_type::CLOSE_TUPLE;
}
"," {
	col += std::string(yytext).length();
	return token_kind_type::COMMA;
}
"=" {
	col += std::string(yytext).length();
	return token_kind_type::EQUAL;
}

{ID} {
	std::string yystr(yytext);

	col += yystr.length();

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

	oss << "bad character encountred: " << row << ":" << col << ": " << yytext;
	yyerror(oss.str().c_str());

	return -1;
}

%%

int yyerror(const char *s) {
	std::cerr << "error: " << s << std::endl;
	return 1;
}
