//
// Created by David Nakash on 28/11/2017.
//

#ifndef PROJECT_UPDATED_AIPLAYER_H
#define PROJECT_UPDATED_AIPLAYER_H

class Logic;

#include "Player.h"


class AIPlayer : public Player {
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

    
    
    AIPlayer(char type, Board *board, Logic *gLogic);
    
    
    /**
     returns player's type

     @return <#return value description#>
     */
    char getType() const;

    /**
     returns the cell of the last move of last player.
     
     @return Cell   cell
     */
    Cell getLastMove() const;
    
    /**
     set cell of last move by receiving it's index,
    initialize it with an empty cell.

     @param i x location
     @param j y location
     */
    void setLastMove(int i, int j);
    
    
    /**
     sort the possible moves of the player according to their size and prints it on gui.
     */
    void printMoves();


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

    
    /**
     Calculates the possible moves of the player, takes the best possible outcome (using maxmin) scenario and returns
     a cell of that location...

     @return Cell   best move to play
     */
    Cell calculateBestPossibleMove();

    
    /**
     Gets the enemy's player ID - if curr player is 'X' returns 'O' and vice versa..

     @return char   type
     */
    char getEnemyPlayerID();
};


#endif //PROJECT_UPDATED_AIPLAYER_H
