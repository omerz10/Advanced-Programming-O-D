//
// Created by David Nakash on 27/11/2017.
//

#include "Game.h"


Game :: Game(Player* P1, Player *P2, Board *board) {
    // initialize values
    this->P1 = P1;
    this->P2 = P2;
    this->board = board;

    // create the board "fresh" as the game is instantiated..
    this->board->create();
}


bool Game ::playOneMove(Player *p, Player **lastPlayer) {
    string userInput; // stores user input
    bool pMoves;

    // get possible moves for Player..
    pMoves = p->getPossibleMoves();
    cout << p->getType() << ": It's your move." << endl;

    // Are there are possible moves for Player?
    if (pMoves) {
        cout << "Your possible moves: ";
        p->printMoves();
        cout << "\nPlease enter your move row, col: ";
        // run loop until gets correct input for possible move
        while (true) {
            getline(cin, userInput);
            //wrong input
            if (!checkInput(userInput, p)) {
                cout << "\nWrong input! Please enter your move row, col: ";
            }
                // true input
            else { break; }
        }
        // now assign p to lastPlayer ptr for future reference..
        *lastPlayer = p;
        // return
        return true;
    } else {

        // print msg to user to press any key and "eat" the next char..
        cout << "No possible moves. Play passes back to the other player. Press any key to continue." << endl;
        cin.get();

        // no moves for Player, return false..
        return false;
    }
}

// checks input AND plays the turn
bool Game :: checkInput(string input, Player *currPlayer) {
    if (input.length() == 3 and isdigit(input.at(0)) and input.at(1) == ' ' and isdigit(input.at(2))) {
        currPlayer->setLastMove(input[0] - '0' - 1, input[2] - '0' - 1);
    }
    for (int i = 0; i < (int)currPlayer->getMoves().size(); i++) {
        if (currPlayer->getLastMove().getX() == currPlayer->getMoves()[i].getX()
            and currPlayer->getLastMove().getY() == currPlayer->getMoves()[i].getY()) {
            currPlayer->switchCells(currPlayer->getLastMove().getX(), currPlayer->getLastMove().getY());
            return true;
        }
    }
    return false;
}


Player* Game :: getP1() {
    return this->P1;
}

Player* Game :: getP2() {
    return this->P2;
}

void Game::showBoard() {
    this->board->show();
}

void Game::resetPlayerData() {
    this->P1->resetPlayerData();
    this->P2->resetPlayerData();
}

void Game::updatePlayerScores() {

    int countP1 = 0, countP2 = 0;
    // run through the board, and update players' scores..
    for (int i = 0; i < this->board->getSize(); i++) {
        for (int j = 0; j < this->board->getSize(); j++) {
            if (this->board->getValueAtIndexes(i, j) == this->P1->getType()) {
                countP1++;
            } else if (this->board->getValueAtIndexes(i, j) == this->P2->getType()) {
                countP2++;
            }
        }
    }

    this->scoreP1 = countP1;
    this->scoreP2 = countP2;
}

int Game::getP1Score() {
    return this->scoreP1;
}

int Game::getP2Score() {
    return this->scoreP2;
}

