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

set(LEXER_PARSER_OUT_DIR ${PROJECT_SOURCE_DIR}/generated)

set(LEXER_OUT ${LEXER_PARSER_OUT_DIR}/lexer.cc)
set(PARSER_OUT ${LEXER_PARSER_OUT_DIR}/parser.cc)
set(LEXER_HEADER_OUT ${LEXER_PARSER_OUT_DIR}/lexer.hpp)
set(PARSER_HEADER_OUT ${LEXER_PARSER_OUT_DIR}/parser.hpp)

flex_target(LEXER "${GRAMMAR_PATH}/rt.lex" ${LEXER_OUT} DEFINES_FILE ${LEXER_HEADER_OUT})
bison_target(PARSER "${GRAMMAR_PATH}/rt.yy" ${PARSER_OUT} DEFINES_FILE ${PARSER_HEADER_OUT})
if (${BISON_PARSER_DEFINED})
	message(STATUS "Successfully built bison target")
endif ()
add_flex_bison_dependency(LEXER PARSER)

set(SRCS
		${LEXER_OUT} ${PARSER_OUT}
		${SRC_PATH}/parser/color.cc
		${SRC_PATH}/parser/vector.cc
		${SRC_PATH}/main.cc
		${SRC_PATH}/parser/point_light.cc
		${SRC_PATH}/parser/scene.cc
		${SRC_PATH}/parser/scene_block_object.cc
		${SRC_PATH}/parser/resolution.cc
		${SRC_PATH}/parser/utils.cc
		${SRC_PATH}/parser/ambient_light.cc
		${SRC_PATH}/parser/light.cc
		${SRC_PATH}/parser/material.cc
		${SRC_PATH}/parser/camera.cc
		${SRC_PATH}/parser/sphere.cc
		)
set(INCLUDE_FILES
		${LEXER_HEADER_OUT} ${PARSER_HEADER_OUT}
		${INCLUDE_PATH}/color.hpp
		${INCLUDE_PATH}/utils.hpp
		${INCLUDE_PATH}/vector.hpp
		${INCLUDE_PATH}/point_light.hpp
		${INCLUDE_PATH}/scene.hpp
		${INCLUDE_PATH}/scene_block_object.hpp
		${INCLUDE_PATH}/resolution.hpp
		${INCLUDE_PATH}/ambient_light.hpp
		${INCLUDE_PATH}/light.hpp
		${INCLUDE_PATH}/material.hpp
		${INCLUDE_PATH}/camera.hpp
		${INCLUDE_PATH}/sphere.hpp
		)

add_executable(${PROJECT_NAME} ${SRCS} ${INCLUDE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME rt)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_PATH} PRIVATE ${LEXER_PARSER_OUT_DIR})
target_link_libraries(${PROJECT_NAME} ${FLEX_LIBRARIES})
