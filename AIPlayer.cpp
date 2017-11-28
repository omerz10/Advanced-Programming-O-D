//
// Created by David Nakash on 28/11/2017.
//

#include "AIPlayer.h"


AIPlayer::AIPlayer(char type, Board *board, Logic *gLogic) {
    this->type = type;
    this->board = board;
    this->gameLogic = gLogic;
}

void AIPlayer::CalculatePossibleMoves() {

}

bool AIPlayer::getPossibleMoveStatus() {
    return this->possibleMove.possible;
}

void AIPlayer::getPlayerMoves() {
    this->possibleMove = this->gameLogic->getPossibleMoves(this);
}

bool AIPlayer::checkInputAndPlayTurn(string input) {
    return false;
}

void AIPlayer::printMoves() {

}

void AIPlayer::setLastMove(int i, int j) {
    lastMove.setX(i);
    lastMove.setY(j);
}

Cell AIPlayer::getLastMove() const {
    return this->lastMove;
}

char AIPlayer::getType() const {
    return 0;
}

void AIPlayer::playSelection(PossibleMove pMove) {

}


