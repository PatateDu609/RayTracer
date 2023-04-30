cmake_minimum_required(VERSION 3.20)

project(RayTracer)

#set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra")

find_package(FLEX 2.6 REQUIRED)
find_package(BISON 3.8 REQUIRED)

set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
set(GRAMMAR_PATH ${PROJECT_SOURCE_DIR}/grammar)
set(LIBS_PATH libs)

set(LEXER_PARSER_OUT_DIR ${PROJECT_SOURCE_DIR}/generated)

set(LEXER_OUT ${LEXER_PARSER_OUT_DIR}/lexer.cc)
set(PARSER_OUT ${LEXER_PARSER_OUT_DIR}/parser.cc)
set(LEXER_HEADER_OUT ${LEXER_PARSER_OUT_DIR}/lexer.hpp)
set(PARSER_HEADER_OUT ${LEXER_PARSER_OUT_DIR}/parser.hpp)

set(PARSER_COMPILE_FLAGS "")
if (DEFINED CACHE{PARSER_COMPILE_FLAGS} AND NOT CACHE{PARSER_COMPILE_FLAGS} STREQUAL "")
	message(STATUS "Using \"$CACHE{PARSER_COMPILE_FLAGS}\" as bison parameters")
	set(PARSER_COMPILE_FLAGS $CACHE{PARSER_COMPILE_FLAGS})
endif ()

flex_target(LEXER "${GRAMMAR_PATH}/rt.lex" ${LEXER_OUT} DEFINES_FILE ${LEXER_HEADER_OUT})
bison_target(PARSER "${GRAMMAR_PATH}/rt.yy" ${PARSER_OUT} COMPILE_FLAGS ${PARSER_COMPILE_FLAGS} DEFINES_FILE ${PARSER_HEADER_OUT})
if (${BISON_PARSER_DEFINED})
	message(STATUS "Successfully built bison target")
endif ()
add_flex_bison_dependency(LEXER PARSER)

set(SRCS
		${SRC_PATH}/main.cc
		${SRC_PATH}/stb_implementation.c
		${SRC_PATH}/syntax_highlighting.cc

		${LEXER_OUT} ${PARSER_OUT}

		${SRC_PATH}/parser/color.cc
		${SRC_PATH}/parser/object.cc
		${SRC_PATH}/parser/point_light.cc
		${SRC_PATH}/parser/scene.cc
		${SRC_PATH}/parser/scene_block_object.cc
		${SRC_PATH}/parser/resolution.cc
		${SRC_PATH}/parser/ambient_light.cc
		${SRC_PATH}/parser/light.cc
		${SRC_PATH}/parser/material.cc
		${SRC_PATH}/parser/camera.cc
		${SRC_PATH}/parser/sphere.cc
		${SRC_PATH}/parser/plane.cc
		${SRC_PATH}/parser/triangle.cc

		${SRC_PATH}/maths/vector.cc
		${SRC_PATH}/maths/matrix.cc
		${SRC_PATH}/maths/utils.cc
		${SRC_PATH}/maths/transform.cc

		${SRC_PATH}/engine/renderer.cc
		${SRC_PATH}/engine/ray.cc
		)
set(INCLUDE_FILES
		${LEXER_HEADER_OUT} ${PARSER_HEADER_OUT}
		${INCLUDE_PATH}/syntax_highlighting.hpp

		${INCLUDE_PATH}/parser/color.hpp
		${INCLUDE_PATH}/parser/object.hpp
		${INCLUDE_PATH}/parser/point_light.hpp
		${INCLUDE_PATH}/parser/scene.hpp
		${INCLUDE_PATH}/parser/scene_block_object.hpp
		${INCLUDE_PATH}/parser/resolution.hpp
		${INCLUDE_PATH}/parser/ambient_light.hpp
		${INCLUDE_PATH}/parser/light.hpp
		${INCLUDE_PATH}/parser/material.hpp
		${INCLUDE_PATH}/parser/camera.hpp
		${INCLUDE_PATH}/parser/sphere.hpp
		${INCLUDE_PATH}/parser/plane.hpp
		${INCLUDE_PATH}/parser/triangle.hpp

		${INCLUDE_PATH}/maths/vector.hpp
		${INCLUDE_PATH}/maths/matrix.hpp
		${INCLUDE_PATH}/maths/utils.hpp
		${INCLUDE_PATH}/maths/transform.hpp

		${INCLUDE_PATH}/engine/renderer.hpp
		${INCLUDE_PATH}/engine/ray.hpp
		)

add_executable(${PROJECT_NAME} ${SRCS} ${INCLUDE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME rt)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_PATH} PRIVATE ${LEXER_PARSER_OUT_DIR} PUBLIC ${LIBS_PATH}/include)
target_link_libraries(${PROJECT_NAME} ${FLEX_LIBRARIES})
