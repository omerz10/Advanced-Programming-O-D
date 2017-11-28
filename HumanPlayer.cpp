/*
 * Player.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */


#include <algorithm>
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(char type, Board *board, Logic *gLogic): type(type), board(board), gameLogic(gLogic) {
    lastMove = Cell();
}

char HumanPlayer::getType() const {
    return this->type;
}

Cell HumanPlayer::getLastMove() const {
    return lastMove;
}

void HumanPlayer::setLastMove(int i, int j) {
    lastMove.setX(i);
    lastMove.setY(j);
}

void HumanPlayer::printMoves() {
    sort(this->possibleMove.moves.begin(), this->possibleMove.moves.end());
    this->possibleMove.moves.erase(unique(this->possibleMove.moves.begin(), this->possibleMove.moves.end())
            , this->possibleMove.moves.end());
    for(int k = 0; k < (int)this->possibleMove.moves.size(); k++) {
    //for (int k : moves) {
        cout << "(" << this->possibleMove.moves[k].getX() + 1 << "," << this->possibleMove.moves[k].getY() + 1 << ")";
    }
    cout <<"\n";
}

// checks input AND plays the turn
bool HumanPlayer :: checkInputAndPlayTurn(string input) {

    if (input.length() == 3 and isdigit(input.at(0)) and input.at(1) == ' ' and isdigit(input.at(2))) {
        //currPlayer->setLastMove(input[0] - '0' - 1, input[2] - '0' - 1);
        this->setLastMove(input[0] - '0' - 1, input[2] - '0' - 1);

    }

    for (int i = 0; i < (int)this->possibleMove.moves.size(); i++) {
        if (this->lastMove.getX() == this->possibleMove.moves[i].getX()
            and this->lastMove.getY() == this->possibleMove.moves[i].getY()) {
            this->gameLogic->switchCells(this->lastMove.getX(), this->lastMove.getY()
            , &this->possibleMove, this);
            return true;
        }
    }

    return false;
}

void HumanPlayer::getPlayerMoves() {
    this->possibleMove = this->gameLogic->getPossibleMoves(this);
}

bool HumanPlayer::getPossibleMoveStatus() {
    return this->possibleMove.possible;
}







