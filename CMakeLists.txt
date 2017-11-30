cmake_minimum_required(VERSION 3.8)
project(Advanced_Programming_O_D)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES

        src/AIPlayer.cpp
        src/AIPlayer.h
        src/Board.cpp
        src/Board.h
        src/Cell.cpp
        src/Cell.h
        src/Game.cpp
        src/Game.h
        src/GameFlow.cpp
        src/GameFlow.h
        src/GenericLogic.cpp
        src/GenericLogic.h
        src/HumanPlayer.cpp
        src/HumanPlayer.h
        src/Logic.h
        src/main.cpp
        src/Player.h
        src/Structs.h
        Tests/test_AIPlayer.cpp
        Tests/test_board.cpp
        Tests/test_cell.cpp
        Tests/test_game.cpp
        Tests/test_genericLogic.cpp
        Tests/test_humanPlayer.cpp
        Tests/test_main.cpp)

add_executable(Advanced_Programming_O_D ${SOURCE_FILES})