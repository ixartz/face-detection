cmake_minimum_required(VERSION 2.8.11)
# On Mac(10.9 - Mavericks), OpenCV need libc++ instead of libstdc++.
# The project cannot compile with g++.
set(CMAKE_CXX_COMPILER "clang++")

project(face-detection)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
add_subdirectory(src)