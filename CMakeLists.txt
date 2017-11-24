cmake_minimum_required(VERSION 3.8)
project(ex2)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Board.cpp Board.h Player.cpp Player.h Cell.cpp Cell.h GameFlow.cpp GameFlow.h)
add_executable(ex2 ${SOURCE_FILES} Board.cpp Board.h)