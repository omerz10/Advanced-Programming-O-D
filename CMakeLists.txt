cmake_minimum_required(VERSION 3.8)
project(Advanced_Programming_O_D)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(tests/lib/googletest-master)
include_directories(tests/lib/googletest-master/googletest/include)
include_directories(tests/lib/googletest-master/googlemock/include)

set(SOURCE_FILES
        src/client/AIPlayer.cpp
        src/client/AIPlayer.h
        src/client/Board.cpp
        src/client/Board.h
        src/client/Cell.cpp
        src/client/Cell.h
        src/client/Game.cpp
        src/client/Game.h
        src/client/GameFlow.cpp
        src/client/GameFlow.h
        src/client/GenericLogic.cpp
        src/client/GenericLogic.h
        src/client/HumanPlayer.cpp
        src/client/HumanPlayer.h
        src/client/Logic.h
        src/client/Player.h
        src/client/Structs.h src/client/Client.cpp src/client/Client.h)

set(SERVER_FILES src/server/Server.cpp src/server/Server.h)

set(TEST_FILES tests/test_main.cpp tests/test_board.cpp tests/test_cell.cpp tests/test_game.cpp
        tests/test_genericLogic.cpp tests/test_AIPlayer.cpp tests/test_humanPlayer.cpp)

add_executable(Advanced_Programming_O_D ${SOURCE_FILES} src/client/main.cpp src/client/Client.cpp src/client/Client.h)
add_executable(SERVER ${SERVER_FILES} src/server/main.cpp)
add_executable(RunTests ${TEST_FILES} ${SOURCE_FILES} tests/test_main.cpp)


target_link_libraries(RunTests gtest gtest_main pthread)

add_test(Advanced_Programming_O_D Advanced_Programming_O_D)