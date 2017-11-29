/*
 * Cell.h
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#ifndef EX2_CELL_H
#define EX2_CELL_H

#include <iostream>
#include <string>

using namespace std;

/*
 * Class Cell which build the Board class
 */
class Cell {

private:
    /*
     * the content of the cell
     */
    char value;
    /*
     * index of row
     */
    int x;
    /*
     * index of column
     */
    int y;

public:
    /*
     * defaut constructor
     */
    Cell();
    /*
     * constructor initialized by external index
     */
    Cell(int x, int y);
    /*
     * returns content of the cell
     */
    char getVal() const;
    /*
     * returns row index
     */
    int getX() const;
    /*
     * returns column index
     */
    int getY() const;
    /*
     * set the content of the cell by inserting a char
     */
    void setVal(char c);
    /*
     * set row index
     */
    void setX(int x);
    /*
     * set column index
     */
    void setY(int y);


    /*
     * overloading of the operator '<'.
     * comparing row index & column index of different cells
     */
    bool operator < (const Cell &cell) const {
        if (x < cell.getX()) {
            return true;
        }
        if (x == cell.getX()) {
            if (y < cell.getY()) {
                return true;
            }
        }
        return false;
    }

    /*
     * overloading of the operator '='.
     * comparing row index & column index of different cells
     */
    bool operator == (const Cell &cell) const {
        return x == cell.getX() and y == cell.getY();
    }
};


#endif //EX2_CELL_H
