//
// Created by David Nakash on 28/11/2017.
//

#ifndef PROJECT_UPDATED_LOGIC_H
#define PROJECT_UPDATED_LOGIC_H


class Player;

#include "Board.h"
#include "Player.h"
#include "Structs.h"

/*
 * Class Logic contains the player properties and status
 */

class Logic {

private:

    /*
     * holds reference of the board
     */
    Board* board;

public:

    /*
     * returns true if the player has actual possible cells and keep the in 'moves' member
     * returns false if player does not have any possible moves
     */
    virtual PossibleMove getPossibleMoves(Player *currPlayer) = 0;
    /*
     * according to the player's type the function inserts the right possible moves to 'moves' member
     * while get index of cells on input
     */
    virtual void getEmptyCell(int i, int j, int k, int n, Player *currPlayer, PossibleMove *pMove) = 0;


    /*
     * gets player's index of last move and change the relevant cells according to player's type
     * by pushing new content to these cells.
     */
    virtual void switchCells(int i, int j, PossibleMove *pMove, Player *currPlayer) = 0;


};


#endif //PROJECT_UPDATED_LOGIC_H
