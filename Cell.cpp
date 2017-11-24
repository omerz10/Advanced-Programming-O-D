/*
 * Cell.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#include "Cell.h"
Cell::Cell(): x(0), y(0), value(' '){ }
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
    this->value = c;
}


void Cell::setX(int x) {
    this->x = x;
}

void Cell::setY(int y) {
    this->y = y;
}

bool Cell::isValue(char c) {
    return value == c;
}
