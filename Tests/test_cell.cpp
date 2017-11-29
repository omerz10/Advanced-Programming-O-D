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
TEST(cellTest, HandlesPositiveInput) {
    Cell cell(1,1);
    EXPECT_EQ(cell.getVal(), ' ');
    EXPECT_EQ(cell.getVal(), 'X');
}

// Tests arguments allocation
TEST(cellTest, HandlesValuesAllocate) {
    Cell cell(3,4);
    EXPECT_EQ(cell.getX(), 3);
    EXPECT_EQ(cell.getY(), 4);
}


TEST(cellTest, HandlesWronginput) {
    Cell cell(2,2);
    EXPECT_THROW(cell.setVal(3), invalid_argument);
    EXPECT_THROW(cell.setX(5.5), invalid_argument);
}

