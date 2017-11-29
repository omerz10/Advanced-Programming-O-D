//
// Created by omerz on 29/11/17.
//

/**
 * GenericLogic test
 */
#include "gtest/gtest.h"
#include "../GenericLogic.h"

using namespace std;

// Tests if there are possible moves
TEST(logicTest1, HandlesPossibleMoves) {
    Board board(8);
    board.create();
    char c = 'X';
    GenericLogic logic(&board);
    PossibleMove pMoves = logic.getPossibleMoves(&board, c);
    // there are posibble moves
    EXPECT_TRUE(pMoves.moves.size() > 0);
}


// Tests if cells were flliped
TEST(logicTest2, HandlesPossibleMoves) {
    Board board(8);
    board.create();
    char c = 'X';
    GenericLogic logic(&board);
    PossibleMove pMoves = logic.getPossibleMoves(&board, c);
    // 1 cell flliped
    EXPECT_EQ(logic.switchCells(&board, 2, 2, &pMoves, c), 1);
}


