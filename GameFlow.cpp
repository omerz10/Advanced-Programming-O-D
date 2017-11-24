/*
 * GameFlow.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#include "GameFlow.h"


// checking for git   !!!


GameFlow::GameFlow(Player *defaultPlayer, Board *board): player(defaultPlayer), board(board) {}

void GameFlow::play() {
    string userInput;
    bool moves = false, endMovesForX = false, endMovesForO = false;
    board->create();
    // stop when end moves for both X & O
    while(!endMovesForX and !endMovesForO) {
        board->show();
        if (moves) {
            if (player->getType() == 'X') {
                cout << "O played (" << player->getLastMove().getX() + 1 << "," <<
                 player->getLastMove().getY() + 1 << ")" << endl;
            }
            if (player->getType() == 'O') {
                cout << "X played (" << player->getLastMove().getX() + 1 << "," <<
                 player->getLastMove().getY() + 1 << ")" << endl;
            }
        }
        moves = player->getPossibleMoves();
        cout << player->getType() << ": It's your move." << endl;
        // There are possible moves
        if (moves) {
            cout << "Your possible moves: ";
            player->printMoves();
            cout << "\nPlease enter your move row,col: ";
            // run loop until gets correct input for possible move
            while (true) {
                getline(cin, userInput);
                //wrong input
                if (!checkInput(userInput)) {
                    cout << "\nWrong input! Please enter your move row, col: ";
                }
                // true input
                else { break; }
            }
        }
        // No possible for X or O
        else {
            if (player->getType() == 'X') {
                endMovesForX = true;
            }
            if (player->getType() == 'O') {
                endMovesForO = true;
            }
            cout << "No possible moves. Play passes back to the other player. Press any key to continue." << endl;
            cin.get();
        }
        player->switchPlayer(player->getType());
    } // end of game
    cout << "Game over!" << endl;
}


bool GameFlow::checkInput(string input) {
    if (input.length() == 3 and isdigit(input.at(0)) and input.at(1) == ' ' and isdigit(input.at(2))) {
        player->setLastMove(input[0] - '0' - 1, input[2] - '0' - 1);
    }
    for (int i = 0; i < (int)player->getMoves().size(); i++) {
        if (player->getLastMove().getX() == player->getMoves()[i].getX()
            and player->getLastMove().getY() == player->getMoves()[i].getY()) {
            player->switchCells(player->getLastMove().getX(), player->getLastMove().getY());
            return true;
        }
    }
    return false;
}


