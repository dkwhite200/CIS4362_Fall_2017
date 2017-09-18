cmake_minimum_required(VERSION 3.8)
project(Practice)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Pad.cpp Pad.h pFlag.cpp pFlag.h)
add_executable(Practice ${SOURCE_FILES})