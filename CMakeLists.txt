cmake_minimum_required(VERSION 2.8.11)
# On Mac(10.9 - Mavericks), OpenCV need libc++ instead of libstdc++.
# The project cannot compile with g++.
set(CMAKE_CXX_COMPILER "clang++")

project(face-detection)

set(PROJECT_SRC_DIR ${PROJECT_SOURCE_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h")

include_directories("${PROJECT_BINARY_DIR}")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
add_subdirectory(src)