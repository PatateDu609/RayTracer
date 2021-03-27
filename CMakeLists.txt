cmake_minimum_required(VERSION 3.17)
project(RayTracer)

include_directories(include)

set(CMAKE_CXX_STANDARD 20)
add_executable(RayTracer main.cpp srcs/Color.cpp include/Color.hpp srcs/Displayer.cpp include/Displayer.hpp srcs/Scene.cpp include/Scene.hpp srcs/ImageDisplayer.cpp include/ImageDisplayer.hpp include/Vector.hpp include/Matrix.hpp srcs/Object.cpp include/Object.hpp srcs/Camera.cpp include/Camera.hpp srcs/SceneObject.cpp include/SceneObject.hpp srcs/Sphere.cpp include/Sphere.hpp srcs/Light.cpp include/Light.hpp)