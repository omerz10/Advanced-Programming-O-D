//
// Created by David Nakash on 28/11/2017.
//

#include "GenericLogic.h"

GenericLogic::GenericLogic (Board *board): board(board) {

}

PossibleMove GenericLogic::getPossibleMoves(Board *board, char playerID) {

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

                while (board->getValueAtIndexes(i, j) == ' '
                       and board->getValueAtIndexes(k - 1, n - 1) != playerID
                       and board->getValueAtIndexes(k - 1, n - 1) != ' ' and k > 1 and n > 1) {
                    Cell newCell(k - 1,n - 1);
                    pCells.push_back(newCell);
                    k--, n--;
                    if (board->getValueAtIndexes(k - 1, n - 1) == playerID) {
                        //if (c[k-1][n-1].isValue(type)) {
                        getEmptyCell(board, i, j, k - 1, n - 1, playerID, &pMove);
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
                while (board->getValueAtIndexes(i, j) == ' '
                       and board->getValueAtIndexes(k - 1, n) != playerID
                       and board->getValueAtIndexes(k - 1, n) != ' ' and k > 1) {

                    Cell newCell(k-1,n);
                    pCells.push_back(newCell);
                    k--;
                    if (board->getValueAtIndexes(k - 1, n) == playerID) {
                        //if (c[k-1][n].isValue(type)) {
                        getEmptyCell(board, i, j, k - 1, n, playerID, &pMove);
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
                while (board->getValueAtIndexes(i, j) == ' '
                       and board->getValueAtIndexes(k - 1, n + 1) != playerID
                       and board->getValueAtIndexes(k - 1, n + 1) != ' ' and k > 1
                       and n < (board->getSize() - 2)) {
                    Cell newCell(k-1,n+1);
                    pCells.push_back(newCell);
                    k--, n++;
                    if (board->getValueAtIndexes(k - 1, n + 1) == playerID) {
                        //if (c[k-1][n+1].isValue(type)) {
                        getEmptyCell(board, i, j, k-1, n+1, playerID, &pMove);
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
                while (board->getValueAtIndexes(i, j) == ' '
                       and board->getValueAtIndexes(k, n - 1) != playerID
                       and board->getValueAtIndexes(k, n - 1) != ' ' and n > 1) {

                    Cell newCell(k,n-1);
                    pCells.push_back(newCell);
                    n--;
                    if (board->getValueAtIndexes(k, n - 1) == playerID) {
                        //if (c[k][n-1].isValue(type)) {
                        getEmptyCell(board, i, j, k, n-1, playerID, &pMove);
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
                while (board->getValueAtIndexes(i, j) == ' '
                       and board->getValueAtIndexes(k, n + 1) != playerID
                       and board->getValueAtIndexes(k, n + 1) != ' ' and n < (board->getSize() - 2)) {

                    Cell newCell(k,n+1);
                    pCells.push_back(newCell);
                    n++;
                    if (board->getValueAtIndexes(k, n + 1) == playerID) {
                        //if (c[k][n+1].isValue(type)) {
                        getEmptyCell(board, i, j, k, n+1, playerID, &pMove);
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

                while (board->getValueAtIndexes(i, j) == ' '
                       and board->getValueAtIndexes(k + 1, n - 1) != playerID
                       and board->getValueAtIndexes(k + 1, n - 1) != ' '
                       and k < (board->getSize() -2) and n > 1) {
                    Cell newCell(k+1,n-1);
                    pCells.push_back(newCell);
                    k++, n--;
                    if (board->getValueAtIndexes(k + 1, n - 1) == playerID) {
                        getEmptyCell(board, i, j, k+1, n-1, playerID, &pMove);
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
                while (board->getValueAtIndexes(i, j) == ' '
                       and board->getValueAtIndexes(k + 1, n) != playerID
                       and board->getValueAtIndexes(k + 1, n) != ' '
                       and k < (board->getSize() - 2)) {
                    Cell newCell(k+1,n);
                    pCells.push_back(newCell);
                    k++;
                    if (board->getValueAtIndexes(k + 1, n) == playerID) {
                        //if (c[k+1][n].isValue(type)) {
                        getEmptyCell(board, i, j, k+1, n, playerID, &pMove);
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
                while (board->getValueAtIndexes(i, j) == ' '
                       and board->getValueAtIndexes(k + 1, n + 1) != playerID
                       and board->getValueAtIndexes(k + 1, n + 1) != ' '
                       and k < (board->getSize() - 2) and n < (board->getSize() - 2)) {
                    Cell newCell(k + 1,n + 1);
                    pCells.push_back(newCell);
                    k++, n++;
                    if (board->getValueAtIndexes(k + 1, n + 1) == playerID) {
                        //if (c[k+1][n+1].isValue(type)) {
                        getEmptyCell(board, i, j, k + 1, n + 1, playerID, &pMove);
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

void GenericLogic::getEmptyCell(Board *board, int i, int j, int k, int n, char playerID, PossibleMove *pMove) {
    // possible move for 'X'
    if (playerID == 'X' and board->getValueAtIndexes(k, n) == 'X') {
        //if (type == 'X' and board->getCells()[k][n].isValue('X')) {
        Cell cell(i,j);
        pMove->moves.push_back(cell);
    }
    // possible move for 'O'
    if (playerID == 'O' and board->getValueAtIndexes(k, n) == 'O') {
        //if (type == 'O' and board->getCells()[k][n].isValue('O')) {
        Cell cell(i,j);
        pMove->moves.push_back(cell);
    }

}

int GenericLogic :: switchCells(Board *board, int i, int j, PossibleMove *pMove, char playerID) {

    int x, y, u, w, z = 0;
    Cell cell(i, j);
    int count = 0;

    // run through all vectors of changeable cells
    for (int s = 0; s < (int) pMove->changeableCells.size(); s++) {
        if (!pMove->changeableCells[s].empty() and cell == pMove->changeableCells[s][0]) {

            char firstCell = board->getValueAtIndexes(pMove->changeableCells[s][0].getX()
                    , pMove->changeableCells[s][0].getY());

            char secondCell = board->getValueAtIndexes(pMove->changeableCells[s][1].getX()
                    , pMove->changeableCells[s][1].getY());

            // if chosen move by user is in a specific vector
            if (firstCell == ' ' and secondCell != playerID) {
                count += pMove->changeableCells[s].size() - 1;
                // change all cells in the a specific vector
                for (int n = 1; n < (int) pMove->changeableCells[s].size(); n++) {
                    z = s;
                    x = pMove->changeableCells[s][n].getX();
                    y = pMove->changeableCells[s][n].getY();
                    board->setCell(x, y, playerID);
                }
            }
        }
    }

    u = pMove->changeableCells[z][0].getX();
    w = pMove->changeableCells[z][0].getY();
    board->setCell(u, w, playerID);
    return count + 1;
}