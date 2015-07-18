cmake_minimum_required(VERSION 3.2)
project(UI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(UI_Test ${SOURCE_FILES} ui/Menu.cpp ui/Menu.h ui/parser.cpp ui/parser.h)