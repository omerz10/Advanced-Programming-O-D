
/**
 * Game test
 */
#include "gtest/gtest.h"
#include "../Game.h"
#include "../GenericLogic.h"
#include "../AIPlayer.h"

using namespace std;

// Test if player played one move
TEST(gameTest, HandlesOneMove) {
    Board board(8);
    board.create();
    GenericLogic logic(&board);
    AIPlayer p1('X', &board, &logic);
    AIPlayer p2('O', &board, &logic);
    Player *lastPlayerPtr;
    Game game(&p1, &p2, &board);
    // the function also prints turn and last moves
    // this check is just on the boolean
    EXPECT_TRUE(game.playOneMove(&p1, &lastPlayerPtr));
}