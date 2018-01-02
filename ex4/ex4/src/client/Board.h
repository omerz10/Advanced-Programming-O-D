/*
 * Board.h
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#ifndef EX2_BOARD_H
#define EX2_BOARD_H


#include <vector>
#include "Cell.h"

using namespace std;

/*
 * Board Class which comprise of Cell's class
 */
class Board {

private:
    /*
     * square size of board
     */
    int size;
    /*
     * board comprise of bunch of cells
     */
    Cell** cells;

public:
    /*
     * constructor
     */
    Board(int size);

    // copy constructor
    
    Board(Board *b);

    /*
     * deconstructor
     */
    ~Board();
    
    
    /**
     returns size of board

     @return size of board
     */
    int getSize() const;
    /*
     * returns the value of the Cell at indexes (x,y)
     */
    
    /**
     Get value of board Cell in indexes x,y.

     @param x location
     @param y location
     @return value
     */
    char getValueAtIndexes(int x, int y);
    /*
     *
     */
    
    /**
     set a cell by its index and content (value)

     @param i x location
     @param j y location
     @param c value
     */
    void setCell(int i, int j, char c);
    /*
     * creates pointers of the board's cells including
     * thier index and value and keep them in cells member.
     */
    void create() const;
    /*
     * prints board on screen including discription of row and columns.
     * initializing 4 cells in the middle of the board with values
     */
    void show() const;

    /**
     copy board from this to destination.

     @param dest dest reference.
     */
    void copyBoardTo(Board* dest);
};


#endif //EX2_BOARD_H
