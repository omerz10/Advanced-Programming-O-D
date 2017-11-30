/*
 * Player.h
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#ifndef EX2_PLAYER_H
#define EX2_PLAYER_H

using namespace std;

#include "Player.h"


/*
 * Class Player contains the player properties and status
 */
class HumanPlayer : public Player {

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
     * constructor.
     * construct Player with his type and reference of board
     */
    HumanPlayer(char type, Board *board, Logic *gLogic);
    
    
    /**
     returns player's type.
     
     @return type
     */
    char getType() const;

    /**
     returns the cell of the last move of last player.
     
     @return Cell lastmove
     */
    Cell getLastMove() const;
    
    
    /**
     * set cell of last move by receiving it's index,
     * initialize it with an empty cell.
     
     @param i y location
     @param j x location
     */
    void setLastMove(int i, int j);
    
    /**
     sort the possible moves of the player according to their size and prints it on gui.
     */
    void printMoves();
    
    /**
     Checks the user's input and returns true/false if correct/not..

     @param input string
     @return bool   true/false
     */
    bool checkInput(string input);
    
    /**
     Plays one turn of the player, runs the CalculateBestPossibleMove function and flips the corresponding cells.
     */
    void playTurn();
    
    /**
     Gets the player's possible moves, and inserts them to the member PossibleMove...
     */
    void getPlayerMoves();

    /**
     Gets the possible move status (the boolean value inside of PossibleMove struct members)...
     
     @return bool   true/false
     */
    bool getPossibleMoveStatus();

    /*
     * this function determines whether the game should print a gui for the player or not (if AI then it won't..)
     * @return bool     true/false
     */
    bool printGUI();
};


#endif //EX2_PLAYER_H
