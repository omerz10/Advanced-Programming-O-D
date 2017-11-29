//
// Created by David Nakash on 27/11/2017.
//

#ifndef EX2_GAME_H
#define EX2_GAME_H

#include "Board.h"
#include "HumanPlayer.h"

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
     *
     */
    

    /**
     * returns of the input is correct.
     * if so, it calls function for switching cells values (flipping to the other player).

     @param p player reference
     @param lastPlayer last player pointer's reference
     @return true if moves exist
     */
    bool playOneMove(Player *p, Player **lastPlayer);

    
    /**
     Gets the first player's reference, for use of functions inside of player - wasn't used much if at all...

     @return Player reference
     */
    Player *getP1();

    /**
     Gets the first player's reference, for use of functions inside of player - wasn't used much if at all...

     @return Player reference
     */
    Player *getP2();

    /**
     Prints the board to the console.
     */
    void showBoard();

    /**
     Updates the player scores in the end of the game - for displaying reasons...
     */
    void updatePlayerScores();

    /**
     Get player 1's score

     @return value
     */
    int getP1Score();

    /**
     Get player 2's score

     @return value
     */
    int getP2Score();
};


#endif //EX2_GAME_H
