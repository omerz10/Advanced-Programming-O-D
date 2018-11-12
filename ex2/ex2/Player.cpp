/*
 * Player.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */


#include <algorithm>
#include "Player.h"

Player::Player(char type, Board *board): type(type), board(board) {
    VectorOfCells initVectorOfCells;
    changeableCells.push_back(initVectorOfCells);
    lastMove = Cell();
}

char Player::getType() const {
    return type;
}

vector<Cell> Player::getMoves() const {
    return moves;
}

Cell Player::getLastMove() const {
    return lastMove;
}

void Player::setLastMove(int i, int j) {
    lastMove.setX(i);
    lastMove.setY(j);
}

void Player::printMoves() {
    sort(moves.begin(), moves.end());
    moves.erase(unique(moves.begin(), moves.end()), moves.end());
    for(int k = 0; k < (int)moves.size(); k++) {
        cout << "(" << moves[k].getX() + 1 << "," << moves[k].getY() + 1 << ")";
    }
    cout <<"\n";
}

bool Player::getPossibleMoves() {
    int k, n;
    vector<Cell> pCells;
    Cell** c = board->getCells();
    for (int i = 0; i < board->getSize(); i++) {
        for (int j = 0; j < board->getSize(); j++) {
            k = i, n = j;

            //upper left
            if (i > 1 and  j > 1) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (c[i][j].isValue(' ') and !c[k-1][n-1].isValue(type) and !c[k-1][n-1].isValue(' ') and k > 1
                       and n > 1) {
                    Cell newCell(k-1,n-1);
                    pCells.push_back(newCell);
                    k--, n--;
                    if (c[k-1][n-1].isValue(type)) {
                        getEmptyCell(i, j, k-1, n-1);
                        changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // up
            if (i > 1) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (c[i][j].isValue(' ') and !c[k-1][n].isValue(type) and !c[k-1][n].isValue(' ') and k > 1) {
                    Cell newCell(k-1,n);
                    pCells.push_back(newCell);
                    k--;
                    if (c[k-1][n].isValue(type)) {
                        getEmptyCell(i, j, k-1, n);
                        changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // upper right
            if (i > 1 and j < board->getSize() - 2 ) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (c[i][j].isValue(' ') and !c[k-1][n+1].isValue(type) and !c[k-1][n+1].isValue(' ') and k > 1
                       and n < board->getSize() - 2) {
                    Cell newCell(k-1,n+1);
                    pCells.push_back(newCell);
                    k--, n++;
                    if (c[k-1][n+1].isValue(type)) {
                        getEmptyCell(i, j, k-1, n+1);
                        changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // left
            if (j > 1) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (c[i][j].isValue(' ') and !c[k][n-1].isValue(type) and !c[k][n-1].isValue(' ') and n > 1) {
                    Cell newCell(k,n-1);
                    pCells.push_back(newCell);
                    n--;
                    if (c[k][n-1].isValue(type)) {
                        getEmptyCell(i, j, k, n-1);
                        changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // right
            if (j < board->getSize() - 2) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (c[i][j].isValue(' ') and !c[k][n+1].isValue(type) and !c[k][n+1].isValue(' ')
                       and n < board->getSize() - 2) {
                    Cell newCell(k,n+1);
                    pCells.push_back(newCell);
                    n++;
                    if (c[k][n+1].isValue(type)) {
                        getEmptyCell(i, j, k, n+1);
                        changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // lower left
            if (i < board->getSize() - 2 and j > 1) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (c[i][j].isValue(' ') and !c[k+1][n-1].isValue(type) and !c[k+1][n-1].isValue(' ')
                       and k < board->getSize() - 2 and n > 1) {
                    Cell newCell(k+1,n-1);
                    pCells.push_back(newCell);
                    k++, n--;
                    if (c[k+1][n-1].isValue(type)) {
                        getEmptyCell(i, j, k+1, n-1);
                        changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // down
            if (i < board->getSize() - 2) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (c[i][j].isValue(' ') and !c[k+1][n].isValue(type) and !c[k+1][n].isValue(' ')
                       and k < board->getSize() - 2) {
                    Cell newCell(k+1,n);
                    pCells.push_back(newCell);
                    k++;
                    if (c[k+1][n].isValue(type)) {
                        getEmptyCell(i, j, k+1, n);
                        changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
                k = i, n = j;
            }
            // lower right
            if (i < board->getSize() - 2 and j < board->getSize() - 2) {
                Cell thisCell(k, n);
                pCells.push_back(thisCell);
                while (c[i][j].isValue(' ') and !c[k+1][n+1].isValue(type) and !c[k+1][n+1].isValue(' ')
                       and k < board->getSize() - 2 and n < board->getSize() - 2) {
                    Cell newCell(k+1,n+1);
                    pCells.push_back(newCell);
                    k++, n++;
                    if (c[k+1][n+1].isValue(type)) {
                        getEmptyCell(i, j, k+1, n+1);
                        changeableCells.push_back(pCells);
                    }
                }
                pCells.clear();
            }
        }
    }
    // no possible moves
    if(moves.empty()) {
        return false;
    }
    return true;
}

void Player::getEmptyCell(int i, int j, int k, int n) {
    // possible move for 'X'
    if (type == 'X' and board->getCells()[k][n].isValue('X')) {
        Cell cell(i,j);
        moves.push_back(cell);
    }
    // possible move for 'O'
    if (type == 'O' and board->getCells()[k][n].isValue('O')) {
        Cell cell(i,j);
        moves.push_back(cell);
    }

}

void Player::switchCells(int i, int j) {
    int x, y, u, w, z;
    Cell cell(i, j);
    // run through all vectors of changeable cells
    for (int s = 0; s < (int) changeableCells.size(); s++) {
        if (!changeableCells[s].empty() and cell == changeableCells[s][0]) {
            Cell firstCell = board->getCells()[changeableCells[s][0].getX()][changeableCells[s][0].getY()];
            Cell secondCell = board->getCells()[changeableCells[s][1].getX()][changeableCells[s][1].getY()];
            // if chosen move by user is in a specific vector
            if (firstCell.isValue(' ') and !secondCell.isValue(type)) {
                // change all cells in the a specific vector
                for (int n = 1; n < (int) changeableCells[s].size(); n++) {
                    z = s;
                    x = changeableCells[s][n].getX();
                    y = changeableCells[s][n].getY();
                    board->setCell(x, y, type);
                }
            }
        }
    }
     u = changeableCells[z][0].getX();
     w = changeableCells[z][0].getY();
    board->setCell(u, w, type);
}

void Player:: switchPlayer(char player) {
    if (player == 'X') {
        type = 'O';
    }
    else {
        type= 'X';
    }
    moves.clear();
    for (int i = 0; i < changeableCells.size(); i++) {
        changeableCells[i].clear();
    }
}





