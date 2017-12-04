cmake_minimum_required(VERSION 3.8)
project(Advanced_Programming_O_D)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

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
        src/Player.h
        src/Structs.h)

set(SERVER_FILES server/Server.cpp server/Server.h)

set(TEST_FILES Tests/test_main.cpp Tests/test_board.cpp Tests/test_cell.cpp Tests/test_game.cpp
        Tests/test_genericLogic.cpp Tests/test_AIPlayer.cpp Tests/test_humanPlayer.cpp)

add_executable(Advanced_Programming_O_D ${SOURCE_FILES} src/main.cpp)
add_executable(SERVER ${SERVER_FILES} server/main.cpp)
add_executable(RunTests ${TEST_FILES} ${SOURCE_FILES} Tests/test_main.cpp)


target_link_libraries(RunTests gtest gtest_main pthread)

add_test(Advanced_Programming_O_D Advanced_Programming_O_D)