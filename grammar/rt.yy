%require "3.8"
%language "c++"

%code requires {
	//  /!\ DON'T REMOVE THESE LINES, IT IS ABSOLUTELY CRUCIAL TO THE LEXER.
	// / ! \ It will do really strange stuff with its definitions...

	#ifndef DONT_NEED_LEXER
	#include "lexer.hpp"
	#endif

	#include "maths/vector.hpp"

	#include "parser/color.hpp"
	#include "parser/resolution.hpp"
	#include "parser/point_light.hpp"
	#include "parser/ambient_light.hpp"
	#include "parser/camera.hpp"
	#include "parser/material.hpp"
	#include "parser/sphere.hpp"
	#include "parser/scene.hpp"
	#include "parser/plane.hpp"
	#include "parser/triangle.hpp"
}

%code top {
	#include <iostream>
	#include <string>
	#include <sstream>
}

%code provides {
	int yyerror(const char *s);

	#define YY_DECL \
        int yylex(yy::parser::semantic_type *yylval, yyscan_t yyscanner)
    YY_DECL;
}

%code {
}

%define api.value.type variant
%define parse.error detailed
%define parse.lac full
%define parse.trace

%param {yyscan_t scanner}

%start file_description

%token <std::string> ID
%token <double> FLOAT
%token <long> INT

%token OPEN_BLOCK "{"
%token CLOSE_BLOCK "}"
%token OPEN_TUPLE "("
%token CLOSE_TUPLE ")"
%token COMMA ","
%token EQUAL "="

%token RESOLUTION "resolution"
%token POINT_LIGHT "point_light"
%token AMBIENT_LIGHT "ambient_light"
%token CAMERA "camera"
%token SPHERE "sphere"
%token POSITION "position"
%token COLOR "color"
%token INTENSITY "intensity"
%token VIEW_DIRECTION "view_direction"
%token FOV "fov"
%token MATERIAL "material"
%token RADIUS "radius"
%token DIFFUSE "diffuse"
%token PLANE "plane"
%token TRIANGLE "triangle"
%token POINT "point"
%token POINTS "points"
%token NORMAL "normal"

%type <Resolution> resolution_line resolution_tuple
%type <Color> color_tuple color_line diffuse_line
%type <Vector3> vector position_line view_direction_line point_line normal_line vector_tuple_content
%type <std::vector<Vector3>> points_line vector_tuple_content_list
%type <PointLight> point_light_block_content point_light_block_content_list point_light_block
%type <AmbientLight> ambient_light_block_content ambient_light_block_content_list ambient_light_block
%type <Camera> camera_block_content camera_block_content_list camera_block
%type <Material> material_block_content material_block_content_list material_block material_block_object material_line_obj
%type <std::string> identifier material_line_id
%type <double> number intensity_line fov_line radius_line

%type <Sphere> sphere_block_content sphere_block_content_list sphere_block
%type <Plane> plane_block_content plane_block_content_list plane_block
/* %type <Triangle> triangle_block_content triangle_block_content_list triangle_block */

%%

epsilon: /* empty rule */

// Creating the actual file description
file_object_description:
	resolution_line { SceneParserProxy::set_resolution($1); }
	| ambient_light_block { SceneParserProxy::set_ambient_light($1); }
	| camera_block { SceneParserProxy::set_camera($1); }
	| point_light_block { SceneParserProxy::append_point_light($1); }
	| material_block { SceneParserProxy::append_material($1); }
	| sphere_block { SceneParserProxy::append_object(std::shared_ptr<Object>(new Sphere($1))); }
	| plane_block { SceneParserProxy::append_object(std::shared_ptr<Object>(new Plane($1))); }
	/* | triangle_block { SceneParserProxy::append_object(std::shared_ptr<Object>(new Triangle($1))); } */

file_description: epsilon | file_object_description file_description


identifier:
	epsilon { $$ = ""; }
	| ID { $$ = $1; }

number:
	INT { $$ = $1; }
	| FLOAT { $$ = $1; }

 // Defining resolution line
resolution_tuple: OPEN_TUPLE INT COMMA INT CLOSE_TUPLE { $$ = Resolution($2, $4); }
resolution_line: RESOLUTION EQUAL resolution_tuple { $$ = $3; }

 // Defining utils lines
color_tuple: OPEN_TUPLE INT COMMA INT COMMA INT CLOSE_TUPLE { $$ = Color($2, $4, $6); }
color_line: COLOR EQUAL color_tuple { $$ = $3; }
vector: OPEN_TUPLE number COMMA number COMMA number CLOSE_TUPLE { $$ = Vector3($2, $4, $6); }
position_line: POSITION EQUAL vector { $$ = $3; }
point_line: POINT EQUAL vector { $$ = $3; }
normal_line: NORMAL EQUAL vector { $$ = $3; }
intensity_line: INTENSITY EQUAL number { $$ = $3; }

vector_tuple_content: COMMA vector { $$ = $2; }
vector_tuple_content_list:
	vector_tuple_content { $$ = $1; }
	| vector_tuple_content_list vector_tuple_content { $$ = $1; $$.push_back(2); }
points_line: POINTS EQUAL OPEN_TUPLE vector vector_tuple_content_list CLOSE_TUPLE { $$ = $5; $$.insert($$.begin(), $4); }

material_line_id: MATERIAL EQUAL ID { $$ = $3; }
material_line_obj: MATERIAL EQUAL material_block_object { $$ = $3; }

 // Adding the point_light block definition
point_light_block_content:
	color_line { PointLight pt; pt.setColor($1); $$ = pt; }
	| position_line { PointLight pt; pt.setPosition($1); $$ = pt; }
	| intensity_line { PointLight pt; pt.setIntensity($1); $$ = pt; }

point_light_block_content_list:
	point_light_block_content { $$ = $1; }
	| point_light_block_content_list point_light_block_content {
		$$ = $1;
		if ($2.color.has_value())
			$$.setColor(*$2.color);
		if ($2.position_set)
			$$.setPosition($2.position);
		if ($2.intensity.has_value())
			$$.setIntensity(*$2.intensity);
	}

point_light_block: POINT_LIGHT identifier OPEN_BLOCK point_light_block_content_list CLOSE_BLOCK {
	$$ = $4;
	if (!$2.empty())
		$$.identifier = $2;
}

 // Adding the ambient_light block definition
ambient_light_block_content:
	color_line { AmbientLight pt; pt.setColor($1); $$ = pt; }
	| intensity_line { AmbientLight pt; pt.setIntensity($1); $$ = pt; }

ambient_light_block_content_list:
	ambient_light_block_content { $$ = $1; }
	| ambient_light_block_content_list ambient_light_block_content {
		$$ = $1;
		if ($2.color.has_value())
			$$.setColor(*$2.color);
		if ($2.intensity.has_value())
			$$.setIntensity(*$2.intensity);
	}

ambient_light_block: AMBIENT_LIGHT identifier OPEN_BLOCK ambient_light_block_content_list CLOSE_BLOCK {
	$$ = $4;
	if (!$2.empty())
		$$.identifier = $2;
}

 // Adding the camera block definition
view_direction_line: VIEW_DIRECTION EQUAL vector { $$ = $3; }
fov_line: FOV EQUAL number { $$ = $3; }

camera_block_content:
	position_line { Camera cam; cam.position($1); $$ = cam; }
	| view_direction_line { Camera cam; cam.view($1); $$ = cam; }
	| fov_line { Camera cam; cam.fov($1); $$ = cam; }

camera_block_content_list:
	camera_block_content { $$ = $1; }
	| camera_block_content_list camera_block_content {
		$$ = $1;

		if ($2.pos_set)
			$$.position($2.pos);
		if ($2.view_dir_set)
			$$.view($2.view_dir);
		if ($2.fov_rad.has_value()) {
			$$.fov_rad = $2.fov_rad;
			$$.tan_fov = $2.tan_fov;
		}
	}

camera_block: CAMERA identifier OPEN_BLOCK camera_block_content_list CLOSE_BLOCK {
	$$ = $4;
	if (!$2.empty())
		$$.identifier = $2;
}

 // Adding the material block object definition
diffuse_line: DIFFUSE EQUAL color_tuple { $$ = $3; }
material_block_content: diffuse_line { Material mat; mat.setDiffuse($1); $$ = mat; }
material_block_content_list:
	material_block_content { $$ = $1; }
	| material_block_content_list material_block_content {
		$$ = $1;

		if ($2.diffuse_set)
			$$.setDiffuse($2.diffuse);
	}

material_block_object: OPEN_BLOCK material_block_content_list CLOSE_BLOCK {	$$ = $2; }
material_block: MATERIAL ID material_block_object {
	$$ = $3;
	if (!$2.empty())
		$$.identifier = $2;
}

 // Adding the sphere block object definition
radius_line: RADIUS EQUAL number { $$ = $3; }
sphere_block_content:
	position_line { Sphere s; s.setPosition($1); $$ = s; }
	| material_line_id { Sphere s; s.setMaterial($1); $$ = s; }
	| material_line_obj { Sphere s; s.setMaterial($1); $$ = s; }
	| radius_line { Sphere s;
		s.setRadius($1);
		$$ = s;
		}

sphere_block_content_list:
	sphere_block_content { $$ = $1; }
	| sphere_block_content_list sphere_block_content {
		$$ = $1;

		if ($2.position_set)
			$$.setPosition($2.position);
		if ($2.mat.has_value())
			$$.mat = $2.mat;
		if ($2.radius_set)
			$$.setRadius($2.radius);
	}

sphere_block: SPHERE identifier OPEN_BLOCK sphere_block_content_list CLOSE_BLOCK {
	$$ = $4;
	if (!$2.empty())
		$$.identifier = $2;
}

 // Adding the plane block object definition
plane_block_content:
	point_line { Plane s; s.setPoint($1); $$ = s; }
	| material_line_id { Plane s; s.setMaterial($1); $$ = s; }
	| material_line_obj { Plane s; s.setMaterial($1); $$ = s; }
	| normal_line { Plane s; s.setNormal($1); $$ = s; }

plane_block_content_list:
	plane_block_content { $$ = $1; }
	| plane_block_content_list plane_block_content {
		$$ = $1;

		if ($2.point_set)
			$$.setPoint($2.getPoint());
		if ($2.mat.has_value())
			$$.mat = $2.mat;
		if ($2.normal_set)
			$$.setNormal($2.getNormal());
	}

plane_block: PLANE identifier OPEN_BLOCK plane_block_content_list CLOSE_BLOCK {
	$$ = $4;
	if (!$2.empty())
		$$.identifier = $2;
}

 // Adding the box block object definition
/* triangle_block_content:
	points_line { Triangle s; s.setBounds($1); $$ = b; }
	| material_line_id { Triangle s; s.setMaterial($1); $$ = s; }
	| material_line_obj { Triangle s; s.setMaterial($1); $$ = s; }

triangle_block_content_list:
	triangle_block_content { $$ = $1; }
	| triangle_block_content_list triangle_block_content {
		$$ = $1;

		if (!$2.points.empty())
			$$.setBounds($2.getBounds());
		if ($2.mat.has_value())
			$$.mat = $2.mat;
	}

triangle_block: TRIANGLE identifier OPEN_BLOCK triangle_block_content_list CLOSE_BLOCK {
	$$ = $4;
	if (!$2.empty())
		$$.identifier = $2;
} */

%%

void yy::parser::error(const std::string& msg) {
	yyerror(msg.c_str());
}

/* void yy::parser::report_syntax_error (const context& ctx) const {
	std::ostringstream oss;

	oss << "syntax error: ";
	// Report the tokens expected at this point.
	{
		enum { TOKENMAX = 5 };
		std::array<symbol_kind_type, TOKENMAX> expected;
		int n = ctx.expected_tokens(expected.data(), expected.size());
		for (int i = 0; i < n; ++i)
			oss << (i == 0 ? "expected " : " or") << symbol_name(expected[i]);
	}
	// Report the unexpected token.
	{
		auto lookahead = ctx.token();
		if (lookahead != symbol_kind_type::S_YYEMPTY)
		 oss << " before " <<  symbol_name(lookahead);
	}

	oss << std::endl;
	std::cerr << oss.str();
} */
