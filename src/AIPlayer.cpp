//
// Created by David Nakash on 28/11/2017.
//

#include <algorithm>
#include "AIPlayer.h"
#include <limits.h>

AIPlayer::AIPlayer(char type, Board *board, Logic *gLogic) {
    this->type = type;
    this->board = board;
    this->gameLogic = gLogic;
}

void AIPlayer::playTurn() {
    // decisions : AI's logic here...

    Cell res = calculateBestPossibleMove();

    this->gameLogic->switchCells(this->board, res.getX(), res.getY(), &this->possibleMove, this->type);

    this->lastMove = res;

}

Cell AIPlayer::calculateBestPossibleMove() {

    // create lastMove cells...
    
    Cell lastMoves[this->possibleMove.moves.size()];

    // hold possible moves
    PossibleMove possibleMoves[this->possibleMove.moves.size()];


    // save best score
    int bestScore = INT_MIN;
    int saveFirstIndex=0, saveSecondIndex;

    // make tempBoard to work on..
    Board tempBoard = Board(this->board->getSize());

    Board tempBoardIndexI = Board(this->board->getSize());
    // copy first board to tempBoard
    this->board->copyBoardTo(&tempBoard);


    // run on each possibleMove of the AI..
    for (int i = 0; i < this->possibleMove.moves.size(); i++) {


        // run AI player move simulation...

        // switch the cells of the tempBoard according to the i-th move..
        int scoreFirst = this->gameLogic->switchCells(&tempBoard, this->possibleMove.moves[i].getX()
                , this->possibleMove.moves[i].getY(), &this->possibleMove, this->getType());

        // copy tempBoard to tempBoardIndexI
        tempBoard.copyBoardTo(&tempBoardIndexI);


        // get possible moves of other player after AI's imaginary move..
        possibleMoves[i] = this->gameLogic->getPossibleMoves(&tempBoard, getEnemyPlayerID());

        // now play all of the moves possible
        for (int j = 0; j < possibleMoves[i].moves.size(); j++) {
            // switch the cells of the tempBoard according to the j-th move..
            int scoreSecond = this->gameLogic->switchCells(&tempBoard, possibleMoves[i].moves[j].getX()
                    , possibleMoves[i].moves[j].getY(), &possibleMoves[i], getEnemyPlayerID());

            // check if max score, and keep values (i,j)..
            if (scoreFirst - scoreSecond > bestScore) {
                bestScore = scoreFirst - scoreSecond;
                saveFirstIndex = i;
                saveSecondIndex = j;

            }

            // now revert board to "I-th iteration board" and continue iterating..
            // copy first board to tempBoard
            tempBoardIndexI.copyBoardTo(&tempBoard);
        }
    }


    return Cell(this->possibleMove.moves[saveFirstIndex].getX()
    , this->possibleMove.moves[saveFirstIndex].getY());


}

bool AIPlayer::getPossibleMoveStatus() {
    return this->possibleMove.possible;
}

void AIPlayer::getPlayerMoves() {
    this->possibleMove = this->gameLogic->getPossibleMoves(this->board, this->getType());
}



void AIPlayer::printMoves() {
    sort(this->possibleMove.moves.begin(), this->possibleMove.moves.end());
    this->possibleMove.moves.erase(unique(this->possibleMove.moves.begin(), this->possibleMove.moves.end())
            , this->possibleMove.moves.end());
    for(int k = 0; k < (int)this->possibleMove.moves.size(); k++) {
        //for (int k : moves) {
        cout << "(" << this->possibleMove.moves[k].getX() + 1 << "," << this->possibleMove.moves[k].getY() + 1 << ")";
    }
    cout <<"\n";
}

void AIPlayer::setLastMove(int i, int j) {

    if (i > this->board->getSize() or j > this->board->getSize()) {
        throw invalid_argument("Out of range");
    }
    if (i < 0 or j < 0) {
        throw invalid_argument("Negative numbers");
    }
    lastMove.setX(i);
    lastMove.setY(j);
}

Cell AIPlayer::getLastMove() const {
    return this->lastMove;
}

char AIPlayer::getType() const {
    return this->type;
}

char AIPlayer::getEnemyPlayerID() {
    if (this->type == 'X') {
        return 'O';
    } else {
        return 'X';
    }
}





