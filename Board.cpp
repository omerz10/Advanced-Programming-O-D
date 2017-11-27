/*
 * Board.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#include "Board.h"


Board::Board(int size): size(size) {
    cells = new Cell *[size];
}

Board::~Board()
{
    for (int i = 0; i < size; i++)
    {
        delete [] cells[i];
    }

    delete [] cells;
}

int Board::getSize() const {
    return size;
}

char Board :: getValueAtIndexes(int x, int y) {
    return this->cells[x][y].getVal();
}


void Board::setCell(int i, int j, char c) {
    cells[i][j].setVal(c);
}

void Board::create() const {
    for (int i = 0; i < size; i++) {
        cells[i] = new Cell[size];
    }
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                if ((j == size / 2 - 1 and k == size / 2 - 1) or (j == size / 2 and k == size / 2)) {
                    cells[j][k].setVal('O');
                } else if ((j == size / 2 - 1 and k == size / 2) or (j == size / 2 and k == size / 2 - 1)) {
                    cells[j][k].setVal('X');
                } else {
                    cells[j][k].setVal(' ');
                }
            }
        }
    }

void Board::show() const {

    // first line..
    cout << " |";
    for (int i = 1; i <= this->size; i++) {
        cout << " " << i << " |";
    }

    cout << endl << string((unsigned long)(4 * size + 2), '-') << endl;

    // rest of the board..
    for (int i = 0; i < this->size; i++) {
        cout << i + 1 << "|";
        for (int j = 0; j  < this->size; j++) {
            cout << " " << this->cells[i][j].getVal() << " |";
        }
        cout << endl << string((unsigned long)(4 * size + 2), '-') << endl;
    }
}
