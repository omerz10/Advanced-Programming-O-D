
/**
 * AIPlayer test
 */
#include "gtest/gtest.h"
#include "../src/HumanPlayer.h"
#include "../src/GenericLogic.h"

using namespace std;


// Tests Human input
TEST(humanPlayer1, HandlesHumanInput) {
    Board board(4);
    board.create();
    GenericLogic logic(&board);
    HumanPlayer player('X', &board, &logic);
    player.getPlayerMoves();
    EXPECT_TRUE(player.checkInput("3 4"));
}

// Tests wrong args for move
TEST(humanPlayer2, HandlesWrongArgs) {
    Board board(4);
    GenericLogic logic(&board);
    HumanPlayer player('X', &board, &logic);
    EXPECT_THROW(player.setLastMove(-1, 3), invalid_argument);
}

// Tests player ID allocate
TEST(humanPlayer3, HandlesIDAllocate) {
    Board board(4);
    GenericLogic logic(&board);
    HumanPlayer player('X', &board, &logic);
    EXPECT_EQ(player.getType(), 'X');
}

// Tests last move
TEST(humanPlayer4, HandlesLastMove) {
    Board board(4);
    GenericLogic logic(&board);
    HumanPlayer player('X', &board, &logic);
    player.setLastMove(2,3);
    Cell cell(2,3);
    EXPECT_EQ(player.getLastMove(), cell);
}