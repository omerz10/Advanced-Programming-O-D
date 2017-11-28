//
// Created by David Nakash on 28/11/2017.
//

#ifndef PROJECT_UPDATED_GENERICLOGIC_H
#define PROJECT_UPDATED_GENERICLOGIC_H


#include "Board.h"
#include "Logic.h"


/*
 * Class Logic contains the player properties and status
 */

class GenericLogic : public Logic {

private:

    /*
     * holds reference of the board
     */
    Board* board;

public:
    /*
     * constructor.
     * construct Player with his type and reference of board
     */
    GenericLogic(Board *board);


    /*
     * returns true if the player has actual possible cells and keep the in 'moves' member
     * returns false if player does not have any possible moves
     */
    PossibleMove getPossibleMoves(Player *currPlayer);
    /*
     * according to the player's type the function inserts the right possible moves to 'moves' member
     * while get index of cells on input
     */
    void getEmptyCell(int i, int j, int k, int n, Player *currPlayer, PossibleMove *pMove);


    /*
     * gets player's index of last move and change the relevant cells according to player's type
     * by pushing new content to these cells.
     */
    void switchCells(int i, int j, PossibleMove *pMove, Player *currPlayer);


};


#endif //PROJECT_UPDATED_GENERICLOGIC_H
