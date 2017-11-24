/*
 * GameFlow.h
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckerod
 */

#ifndef EX2_GAMEFLOW_H
#define EX2_GAMEFLOW_H

#include "Board.h"
#include "Player.h"

/*
 * Class GameFlow managed an end to end flow of the game
 */
class GameFlow {

private:
    /*
     * reference to player.
     * the player could be chnged by the user or thr computer.
     */
    Player* player;
    /*
     * reference the a board which is created once
     */
    Board* board;

public:
    /*
     * constructor
     * construct GameFlow by the first player and the board
     */
    GameFlow(Player* defaultPlayer, Board *board);
    /*
     * the function responsible for running the game from A to Z, including printing gui's notifications and
     * inputs requests from the user.
     * the function update the gameFlow by boards status and player switches
     */
    void play();
    /*
     * returns of the input is correct.
     * if so, it calls function for switching cells values (flipping to the other player)
     */
    bool checkInput(string input);
};


#endif //EX2_GAMEFLOW_H
