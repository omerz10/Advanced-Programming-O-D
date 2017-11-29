//
// Created by omerz on 29/11/17.
//

/**
 * Board test
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Board.h"

using namespace std;




// Test correct size of board
TEST(boradTest, HandalesBoardSize) {
    Board board(4);
    EXPECT_EQ(board.getSize(), 4);
}

// Tests board creation
TEST(boardTest, HandlesGettingCell) {
    Board board(8);
    board.create();
    EXPECT_EQ(board.getValueAtIndexes(3, 4), 'X');
    EXPECT_EQ(board.getValueAtIndexes(3, 3), 'O');
}

// Tests incorrect indexes of cells
TEST(boardTest, HandlesInvalidIndex) {
    Board board(8);
    EXPECT_THROW(board.getValueAtIndexes(-2, -7), invalid_argument);

    Board board2(4);
    EXPECT_THROW(board.getValueAtIndexes(6,-9), invalid_argument);
}


// Test setting values to wrong cells
TEST(boardTest, HandlesCellSeting) {
    Board board(8);
    EXPECT_THROW(board.setCell(10, 1, 'X'), invalid_argument);
    EXPECT_THROW(board.setCell(-5, 7, 'X'), invalid_argument);
}



