//
// Created by David Nakash on 27/11/2017.
//

#ifndef EX2_GAME_H
#define EX2_GAME_H

#include "Board.h"
#include "HumanPlayer.h"

// last player should be member of gameFlow - its important to know who played last..
// endMovesForP1/P2 should also be members of gameFlow to mark "game over"/"tie"/etc..
// Game function - bool(endMoveForPlayer) playOneMove(Player *p, Player **lastPlayer-UPDATE)


class Game {
private:
    /*
     * reference to player.
     * the player could be chnged by the user or thr computer.
     */
    Player* P1, *P2;

    /*
     * reference the a board which is created once
     */
    Board* board;


    /*
     * keeps players' scores
     */
    int scoreP1, scoreP2;

public:

    /*
     * constructor
     * construct Game by the first player and the board
     */
    Game(Player* P1, Player *P2, Board *board);

    /*
     * returns of the input is correct.
     * if so, it calls function for switching cells values (flipping to the other player)
     */
    //bool checkInput(string input, Player *currPlayer);

    bool playOneMove(Player *p, Player **lastPlayer);

    Player *getP1();

    Player *getP2();

    void showBoard();

    void updatePlayerScores();

    int getP1Score();

    int getP2Score();
};


#endif //EX2_GAME_H
