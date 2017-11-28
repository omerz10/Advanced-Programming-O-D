cmake_minimum_required(VERSION 3.8)
project(Project_updated)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Board.cpp
        Board.h
        Cell.cpp
        Cell.h
        GameFlow.cpp
        GameFlow.h
        main.cpp
        Player.cpp
        Player.h Game.cpp Game.h Logic.cpp Logic.h GenericLogic.cpp GenericLogic.h Structs.h)


add_executable(Project_updated ${SOURCE_FILES})