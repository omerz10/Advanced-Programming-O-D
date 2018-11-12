/*
 * Player.h
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#ifndef EX2_PLAYER_H
#define EX2_PLAYER_H

#include <iostream>

#include "Board.h"

using namespace std;

/*
 * Class Player contains the player properties and status
 */
class Player {

public:
    /*
     * announcing new typedef VectorOfCells
     */
    typedef vector<Cell> VectorOfCells;

private:
    /*
     * type of player- 'X' or 'Y'
     */
    char type;
    /*
     * holds reference of the board
     */
    Board* board;
    /*
     * possible cells which the player can fill in his turn
     */
    VectorOfCells moves;
    /*
     * cells which are a potential for flip in the future according to player's choice of moves
     */
    vector <VectorOfCells> changeableCells;
    /*
     * last empty cell filled by the last player
     */
    Cell lastMove;


public:
    /*
     * constructor.
     * construct Player with his type and reference of board
     */
    Player(char type, Board *board);
    /*
     * returns player's type
     */
    char getType() const;
    /*
     * returns possible cells which the player can fill in his turn
     */
    VectorOfCells getMoves() const;
    /*
     * returns true if the player has actual possible cells and keep the in 'moves' member
     * returns false if player does not have any possible moves
     */
    bool getPossibleMoves();
    /*
     * according to the player's type the function inserts the right possible moves to 'moves' member
     * while get index of cells on input
     */
    void getEmptyCell(int k, int n, int i, int j);
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
     * gets player's index of last move and change the relevant cells according to player's type
     * by pushing new content to these cells.
     */
    void switchCells(int i, int j);
    /*
     * change type of player from 'X' to 'O' and vice versa
     */
    void switchPlayer(char player);
};


#endif //EX2_PLAYER_H
