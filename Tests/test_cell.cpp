//
// Created by omerz on 29/11/17.
//

/**
 * Cell test
 */
#include "gtest/gtest.h"
#include "../Cell.h"

using namespace std;

// Tests default value of cell
TEST(cellTest, HandlesDefaultValue) {
    Cell cell(1,1);
    EXPECT_EQ(cell.getVal(), ' ');
}

// Tests X and Y allocation
TEST(cellTest, HandlesValuesAllocate) {
    Cell cell(3,4);
    EXPECT_EQ(cell.getX(), 3);
    EXPECT_EQ(cell.getY(), 4);
}

// Tests setting wrong val to a cell
TEST(cellTest, HandlesWrongValue) {
    Cell cell(2,2);
    EXPECT_THROW(cell.setVal('G'), invalid_argument);
}

// Tests setting wrong X & Y
TEST(cellTest, HandlesWrongArgs) {
    Cell cell(4,4);
    EXPECT_THROW(cell.setX(-7), invalid_argument);
    EXPECT_THROW(cell.setY(-2), invalid_argument);
}



