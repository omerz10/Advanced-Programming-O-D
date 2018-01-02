
/**
 * AIPlayer test
 */
#include "gtest/gtest.h"
#include "../src/AIPlayer.h"
#include "../src/GenericLogic.h"

using namespace std;

// Tests wrong args for move
TEST(AIPlayerTest1, HandlesWrongArgs) {
    Board board(4);
    GenericLogic logic(&board);
    AIPlayer player('X', &board, &logic);
    EXPECT_THROW(player.setLastMove(-1, 3), invalid_argument);
}

// Tests player ID allocate
TEST(AIPlayerTest2, HandlesIdAllocate) {
    Board board(4);
    GenericLogic logic(&board);
    AIPlayer player('X', &board, &logic);
    EXPECT_EQ(player.getType(), 'X');
}

// Tests last move
TEST(AIPlayerTest2, HandlesLastMove) {
    Board board(4);
    GenericLogic logic(&board);
    AIPlayer player('X', &board, &logic);
    player.setLastMove(2,3);
    Cell cell(2,3);
    EXPECT_EQ(player.getLastMove(), cell);
}