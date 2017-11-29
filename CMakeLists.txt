cmake_minimum_required(VERSION 3.8)
project(Advanced_Programming_O_D)

set(CMAKE_CXX_STANDARD 98)

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
        Player.h
        Structs.h)

set(TEST_FILES Tests/test_main.cpp Tests/test_board.cpp Tests/test_cell.cpp Tests/test_game.cpp
        Tests/test_genericLogic.cpp Tests/test_AIPlayer.cpp Tests/test_humanPlayer.cpp)

add_executable(Advanced_Programming_O_D ${SOURCE_FILES} main.cpp)
add_executable(RunTests ${TEST_FILES} ${SOURCE_FILES} Tests/test_main.cpp)


target_link_libraries(RunTests gtest gtest_main pthread)

add_test(Advanced_Programming_O_D Advanced_Programming_O_D)