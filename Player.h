//
// Created by David Nakash on 28/11/2017.
//

#ifndef PROJECT_UPDATED_PLAYER_H
#define PROJECT_UPDATED_PLAYER_H

#include <iostream>
#include "Board.h"
#include "Logic.h"
#include "Structs.h"

class Logic;

class Player {

private:
    /*
     * type of player- 'X' or 'Y'
     */
    char type;
    /*
     * holds reference of the board
     */
    Board* board;

    Logic *gameLogic;

    PossibleMove possibleMove;

    /*
     * last empty cell filled by the last player
     */
    Cell lastMove;


public:

    /*
     * returns player's type
     */
    virtual char getType() const = 0;

    /*
     * returns the cell of the last move of last player
     */
    virtual Cell getLastMove() const = 0;
    /*
     * set cell of last move by receiving it's index
     * initialize it with an empty cell
     */
    virtual void setLastMove(int i, int j) = 0;
    /*
     * sort the possible moves of the player according to their size and prints it on gui
     */
    virtual void printMoves() = 0;

    /*
     *
     */
    virtual bool checkInputAndPlayTurn(string input) = 0;

    /*
     *
     */
    virtual void getPlayerMoves() = 0;

    /*
     *
     */
    virtual bool getPossibleMoveStatus() = 0;
};


#endif //PROJECT_UPDATED_PLAYER_H
