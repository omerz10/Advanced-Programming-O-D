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
    /*
     * returns player's type
     */
    char getType() const;

    /*
     * returns the cell of the last move of last player
     */
    Cell getLastMove() const;
    /*
     * set cell of last move by receiving it's index
     * initialize it with an empty cell
     */
    void setLastMove(int i, int j);
    /*
     * sort the possible moves of the player according to their size and prints it on gui
     */
    void printMoves();

    /*
     *
     *
     */
    bool checkInput(string input);

    void playTurn();
    /*
     *
     */
    void getPlayerMoves();

    /*
     *
     */
    bool getPossibleMoveStatus();


};


#endif //EX2_PLAYER_H
