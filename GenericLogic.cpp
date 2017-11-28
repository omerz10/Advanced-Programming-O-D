//
// Created by David Nakash on 28/11/2017.
//

#include "GenericLogic.h"

GenericLogic :: GenericLogic (Board *board): board(board) {

}

PossibleMove GenericLogic::getPossibleMoves(Player *currPlayer) {

    int k, n; // indexes
    vector<Cell> pCells; // temp vector

    PossibleMove pMove; // possible move struct

    for (int i = 0; i < board->getSize(); i++) {
        for (int j = 0; j < board->getSize(); j++) {
            k = i, n = j;

            //upper left
            if (i > 1 and  j > 1) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);

                while (this->board->getValueAtIndexes(i, j) == ' '
                       and this->board->getValueAtIndexes(k - 1, n - 1) != currPlayer->getType()
                       and this->board->getValueAtIndexes(k - 1, n - 1) != ' ' and k > 1 and n > 1) {
                    Cell newCell(k - 1,n - 1);
                    pCells.push_back(newCell);
                    k--, n--;
                    if (this->board->getValueAtIndexes(k - 1, n - 1) == currPlayer->getType()) {
                        //if (c[k-1][n-1].isValue(type)) {
                        getEmptyCell(i, j, k - 1, n - 1, currPlayer, &pMove);
                        pMove.changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // up
            if (i > 1) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (this->board->getValueAtIndexes(i, j) == ' '
                       and this->board->getValueAtIndexes(k - 1, n) != currPlayer->getType()
                       and this->board->getValueAtIndexes(k - 1, n) != ' ' and k > 1) {

                    Cell newCell(k-1,n);
                    pCells.push_back(newCell);
                    k--;
                    if (this->board->getValueAtIndexes(k - 1, n) == currPlayer->getType()) {
                        //if (c[k-1][n].isValue(type)) {
                        getEmptyCell(i, j, k - 1, n, currPlayer, &pMove);
                        pMove.changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // upper right
            if (i > 1 and j < board->getSize() - 2 ) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (this->board->getValueAtIndexes(i, j) == ' '
                       and this->board->getValueAtIndexes(k - 1, n + 1) != currPlayer->getType()
                       and this->board->getValueAtIndexes(k - 1, n + 1) != ' ' and k > 1
                       and n < (this->board->getSize() - 2)) {
                    Cell newCell(k-1,n+1);
                    pCells.push_back(newCell);
                    k--, n++;
                    if (this->board->getValueAtIndexes(k - 1, n + 1) == currPlayer->getType()) {
                        //if (c[k-1][n+1].isValue(type)) {
                        getEmptyCell(i, j, k-1, n+1, currPlayer, &pMove);
                        pMove.changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // left
            if (j > 1) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (this->board->getValueAtIndexes(i, j) == ' '
                       and this->board->getValueAtIndexes(k, n - 1) != currPlayer->getType()
                       and this->board->getValueAtIndexes(k, n - 1) != ' ' and n > 1) {

                    Cell newCell(k,n-1);
                    pCells.push_back(newCell);
                    n--;
                    if (this->board->getValueAtIndexes(k, n - 1) == currPlayer->getType()) {
                        //if (c[k][n-1].isValue(type)) {
                        getEmptyCell(i, j, k, n-1, currPlayer, &pMove);
                        pMove.changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // right
            if (j < board->getSize() - 2) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (this->board->getValueAtIndexes(i, j) == ' '
                       and this->board->getValueAtIndexes(k, n + 1) != currPlayer->getType()
                       and this->board->getValueAtIndexes(k, n + 1) != ' ' and n < (board->getSize() - 2)) {

                    Cell newCell(k,n+1);
                    pCells.push_back(newCell);
                    n++;
                    if (this->board->getValueAtIndexes(k, n + 1) == currPlayer->getType()) {
                        //if (c[k][n+1].isValue(type)) {
                        getEmptyCell(i, j, k, n+1, currPlayer, &pMove);
                        pMove.changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // lower left
            if (i < board->getSize() - 2 and j > 1) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);

                while (this->board->getValueAtIndexes(i, j) == ' '
                       and this->board->getValueAtIndexes(k + 1, n - 1) != currPlayer->getType()
                       and this->board->getValueAtIndexes(k + 1, n - 1) != ' '
                       and k < (this->board->getSize() -2) and n > 1) {
                    Cell newCell(k+1,n-1);
                    pCells.push_back(newCell);
                    k++, n--;
                    if (this->board->getValueAtIndexes(k + 1, n - 1) == currPlayer->getType()) {
                        getEmptyCell(i, j, k+1, n-1, currPlayer, &pMove);
                        pMove.changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // down
            if (i < board->getSize() - 2) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (this->board->getValueAtIndexes(i, j) == ' '
                       and this->board->getValueAtIndexes(k + 1, n) != currPlayer->getType()
                       and this->board->getValueAtIndexes(k + 1, n) != ' '
                       and k < (this->board->getSize() - 2)) {
                    Cell newCell(k+1,n);
                    pCells.push_back(newCell);
                    k++;
                    if (this->board->getValueAtIndexes(k + 1, n) == currPlayer->getType()) {
                        //if (c[k+1][n].isValue(type)) {
                        getEmptyCell(i, j, k+1, n, currPlayer, &pMove);
                        pMove.changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // lower right
            if (i < board->getSize() - 2 and j < board->getSize() - 2) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (this->board->getValueAtIndexes(i, j) == ' '
                       and this->board->getValueAtIndexes(k + 1, n + 1) != currPlayer->getType()
                       and this->board->getValueAtIndexes(k + 1, n + 1) != ' '
                       and k < (this->board->getSize() - 2) and n < (this->board->getSize() - 2)) {
                    //while (c[i][j].isValue(' ') and !c[k+1][n+1].isValue(type) and !c[k+1][n+1].isValue(' ')
                    //       and k < board->getSize() - 2 and n < board->getSize() - 2) {
                    Cell newCell(k + 1,n + 1);
                    pCells.push_back(newCell);
                    k++, n++;
                    if (this->board->getValueAtIndexes(k + 1, n + 1) == currPlayer->getType()) {
                        //if (c[k+1][n+1].isValue(type)) {
                        getEmptyCell(i, j, k + 1, n + 1, currPlayer, &pMove);
                        pMove.changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
            }
        }
    }

    // any possible moves?
    if (!pMove.moves.empty()) {
        pMove.possible = true;
    } else {
        pMove.possible = false;
    }

    return (pMove);
}

void GenericLogic::getEmptyCell(int i, int j, int k, int n, Player *currPlayer, PossibleMove *pMove) {
    // possible move for 'X'
    if (currPlayer->getType() == 'X' and this->board->getValueAtIndexes(k, n) == 'X') {
        //if (type == 'X' and board->getCells()[k][n].isValue('X')) {
        Cell cell(i,j);
        pMove->moves.push_back(cell);
    }
    // possible move for 'O'
    if (currPlayer->getType() == 'O' and this->board->getValueAtIndexes(k, n) == 'O') {
        //if (type == 'O' and board->getCells()[k][n].isValue('O')) {
        Cell cell(i,j);
        pMove->moves.push_back(cell);
    }

}

void GenericLogic::switchCells(int i, int j, PossibleMove *pMove, Player *currPlayer) {

    int x, y, u, w, z = 0;
    Cell cell(i, j);

    // run through all vectors of changeable cells
    for (int s = 0; s < (int) pMove->changeableCells.size(); s++) {
        if (!pMove->changeableCells[s].empty() and cell == pMove->changeableCells[s][0]) {

            //Cell firstCell = board->getCells()[changeableCells[s][0].getX()][changeableCells[s][0].getY()];
            char firstCell = this->board->getValueAtIndexes(pMove->changeableCells[s][0].getX()
                    , pMove->changeableCells[s][0].getY());
            //Cell secondCell = board->getCells()[changeableCells[s][1].getX()][changeableCells[s][1].getY()];
            char secondCell = this->board->getValueAtIndexes(pMove->changeableCells[s][1].getX()
                    , pMove->changeableCells[s][1].getY());
            // if chosen move by user is in a specific vector
            if (firstCell == ' ' and secondCell != currPlayer->getType()) {
                // change all cells in the a specific vector
                for (int n = 1; n < (int) pMove->changeableCells[s].size(); n++) {
                    z = s;
                    x = pMove->changeableCells[s][n].getX();
                    y = pMove->changeableCells[s][n].getY();
                    board->setCell(x, y, currPlayer->getType());
                }
            }
        }
    }

    u = pMove->changeableCells[z][0].getX();
    w = pMove->changeableCells[z][0].getY();
    board->setCell(u, w, currPlayer->getType());
}