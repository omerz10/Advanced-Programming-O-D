/*
 * Cell.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#include "Cell.h"
#include <stdexcept>

Cell::Cell(): x(0), y(0), value(' ') { }

Cell::Cell(int x, int y): x(x), y(y) {
    value = ' ';
}

char Cell::getVal() const {
    return value;
}

int Cell::getX() const {
    return x;
}

int Cell::getY() const {
    return y;
}

void Cell::setVal(char c) {

    if (c != ' ' and c != 'O' and c != 'X') {
        throw invalid_argument("Value does not exit");
    }
    this->value = c;
}


void Cell::setX(int x) {
    if (x < 0) {
        throw invalid_argument("Negative number");
    }
    this->x = x;
}

void Cell::setY(int y) {
    if (y < 0) {
        throw invalid_argument("Negative number");
    }
    this->y = y;
}

