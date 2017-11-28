cmake_minimum_required(VERSION 3.8)
project(Advanced_Programming_O_D)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

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

add_executable(Advanced_Programming_O_D ${SOURCE_FILES} Tests/Testclass.h Tests/test.cpp)
target_link_libraries(Advanced_Programming_O_D gtest gtest_main)