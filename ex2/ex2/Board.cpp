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

Cell** Board::getCells() const {
    return cells;
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
        string line = "----------------------------------";
        cout << "\nCurrent Board:\n" << endl;
        cout << " |";
        for (int k = 1; k < size+1; k++) {
            cout << ' ' << k << " |";
        }
        cout << endl << line << endl;
        for (int i = 0; i < size; i++) {
            cout << i + 1 << "|";
            for (int j = 0; j < size; j++) {
                cout << ' ' << cells[i][j].getVal() << " |";
            }
            cout << endl << line << endl;
        }
    }
