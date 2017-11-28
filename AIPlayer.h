//
// Created by David Nakash on 28/11/2017.
//

#ifndef PROJECT_UPDATED_AIPLAYER_H
#define PROJECT_UPDATED_AIPLAYER_H

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

    /*
     * constructor.
     * construct Player with his type and reference of board
     */
    AIPlayer(char type, Board *board, Logic *gLogic);
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
    bool checkInputAndPlayTurn(string input);

    /*
     *
     */
    void getPlayerMoves();


    /*
     *
     */
    bool getPossibleMoveStatus();


    void playSelection(PossibleMove pMove);

    /*
     *
     */
    void CalculatePossibleMoves();
};


#endif //PROJECT_UPDATED_AIPLAYER_H
