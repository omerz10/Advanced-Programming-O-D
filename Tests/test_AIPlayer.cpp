//
// Created by omerz on 29/11/17.
//

/**
 * AIPlayer test
 */
#include "gtest/gtest.h"
#include "../AIPlayer.h"
#include "../GenericLogic.h"

using namespace std;

// Tests wrong args for move
TEST(AIPlayerTest1, HandlesWrongArgs) {
    Board board(4);
    GenericLogic logic(&board);
    AIPlayer player('X', &board, &logic);
    EXPECT_THROW(player.setLastMove(-1, 3), invalid_argument);
}

// Tests player ID allocate
TEST(AIPlayerTest2, HandlesWrongArgs) {
    Board board(4);
    GenericLogic logic(&board);
    AIPlayer player('X', &board, &logic);
    EXPECT_EQ(player.getType(), 'X');
}