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


    
    
    /**
     returns player's type.

     @return type
     */
    virtual char getType() const = 0;
    
    /**
     returns the cell of the last move of last player.

     @return Cell lastmove
     */
    virtual Cell getLastMove() const = 0;
    
    /**
     * set cell of last move by receiving it's index,
     * initialize it with an empty cell.

     @param i y location
     @param j x location
     */
    virtual void setLastMove(int i, int j) = 0;

    
    /**
     sort the possible moves of the player according to their size and prints it on gui.
     */
    virtual void printMoves() = 0;

    /**
     Plays one turn of the player, runs the CalculateBestPossibleMove function and flips the corresponding cells.
     */
    virtual void playTurn() = 0;
    
    /**
     Gets the player's possible moves, and inserts them to the member PossibleMove...
     */
    virtual void getPlayerMoves() = 0;

    
    /**
     Gets the possible move status (the boolean value inside of PossibleMove struct members)...
     
     @return bool   true/false
     */
    virtual bool getPossibleMoveStatus() = 0;


    /**
     Checks the user's input and returns true/false if correct/not..

     @param input string
     @return bool   true/false
     */
    virtual bool checkInput(string input) = 0;

    virtual int getBoardSize() = 0;

    virtual char getBoardValueAtIndexes(int i, int j) = 0;

    virtual void showBoard() = 0;
    /*
     * this function determines whether the game should print a gui for the player or not (if AI then it won't..)
     * @return bool     true/false
     */
    virtual bool printGUI() = 0;

};


#endif //PROJECT_UPDATED_PLAYER_H
