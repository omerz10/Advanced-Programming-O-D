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
        cout << "(" << this->possibleMove.moves[k].getX() + 1 << "," << this->possibleMove.moves[k].getY() + 1 << ")";
    }
    cout <<"\n";
}

// checks input AND plays the turn
bool HumanPlayer::checkInput(string input) {

    if (input.length() == 3 and isdigit(input.at(0)) and input.at(1) == ' ' and isdigit(input.at(2))) {
        for (int i = 0; i < this->possibleMove.moves.size(); i++) {
            Cell tempCell = Cell(input[0] - '0' - 1, input[2] - '0' - 1);
            if (tempCell.getX() == this->possibleMove.moves[i].getX()
                and tempCell.getY() == this->possibleMove.moves[i].getY()) {
                this->setLastMove(input[0] - '0' - 1, input[2] - '0' - 1);
                return true;
            }
        }
    }
    return false;
}

void HumanPlayer::getPlayerMoves() {
    this->possibleMove = this->gameLogic->getPossibleMoves(this->board, this->getType());
}

bool HumanPlayer::getPossibleMoveStatus() {
    return this->possibleMove.possible;
}

void HumanPlayer::playTurn() {

    string userInput;

    cout << "Your possible moves: ";

    this->printMoves();

    cout << "\nPlease enter your move row, col: ";

    // run loop until gets correct input for possible move
    while (true) {
        getline(cin, userInput);
        //wrong input
        if (!this->checkInput(userInput)) {
            cout << "\nWrong input! Please enter your move row, col: ";
        }
            // true input
        else {
            for (int i = 0; i < (int)this->possibleMove.moves.size(); i++) {
                if (this->lastMove.getX() == this->possibleMove.moves[i].getX()
                    and this->lastMove.getY() == this->possibleMove.moves[i].getY()) {
                    this->gameLogic->switchCells(this->board, this->lastMove.getX(), this->lastMove.getY()
                            , &this->possibleMove, this->getType());
                }
            }
            break;
        }
    }
}