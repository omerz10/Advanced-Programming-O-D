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


    /**
     * returns true if the player has actual possible cells and keep the in 'moves' member,
     * returns false if player does not have any possible moves..
     
     @param board board reference
     @param playerID type
     @return PossibleMove struct
     */
    PossibleMove getPossibleMoves(Board *board, char playerID);
    
    /**
     * according to the player's type the function inserts the right possible moves to 'moves' member,
     * while get index of cells on input...
     
     @param board board reference
     @param i x value of empty cell
     @param j y value of empty cell
     @param k x value of next cell
     @param n y value of next cell
     @param playerID type
     @param pMove PossibleMove reference
     */
    void getEmptyCell(Board *board, int i, int j, int k, int n, char playerID, PossibleMove *pMove);


    /**
     * gets player's index of last move and change the relevant cells according to player's type,
     * by pushing new content to these cells.
     
     @param board reference
     @param i x location of cell to switch from
     @param j y location of cell to switch from
     @param pMove PossibleMove struct including everything...
     @param playerID type
     @return counter of how many cells were switched.
     */
    int switchCells(Board *board, int i, int j, PossibleMove *pMove, char playerID);


};


#endif //PROJECT_UPDATED_GENERICLOGIC_H
