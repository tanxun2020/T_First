cmake_minimum_required(VERSION 3.5)

project(Ray_Tracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Ray_Tracing main.cpp
                BitmapPlusPlus.hpp
                vec3.h
                ray.h
                TriangleMesh.h
                LoadObject.h
                Hit_Result.h)
