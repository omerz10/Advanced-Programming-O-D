cmake_minimum_required(VERSION 3.8)
project(Advanced_Programming_O_D)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        AIPlayer.cpp
        AIPlayer.h
        Board.cpp
        Board.h
        Cell.cpp
        Cell.h
        Game.cpp
        Game.h
        GameFlow.cpp
        GameFlow.h
        GenericLogic.cpp
        GenericLogic.h
        HumanPlayer.cpp
        HumanPlayer.h
        Logic.h
        main.cpp
        Player.h
        Structs.h)

add_executable(Advanced_Programming_O_D ${SOURCE_FILES})