/*
 * GameFlow.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */
#include "GameFlow.h"


GameFlow::GameFlow (Game *g): game(g){}

// readability function - less clutter in playOneTurn() function..
void GameFlow::lastPlayerMoveMsg(Player *lastPlayer, bool playerMoves) {
    if (playerMoves) {
        // print "last player played..." msg here
        cout << lastPlayer->getType() << " played (" << lastPlayer->getLastMove().getX() + 1 << "," <<
             lastPlayer->getLastMove().getY() + 1 << ")" << endl << endl;
    }
}

void GameFlow::play() {
    string userInput; // stores user input

    bool endMovesForP1 = true, endMovesForP2 = true; // flags/trackers for game flow..
    //Player *lastPlayer; // keep a ptr for the last player that played..

    // show board for the first time...
    this->game->showBoard();

    // stop when end moves for both P1 & P2
    while(endMovesForP1 and endMovesForP2) {

        // play move for P1
        endMovesForP1 = this->game->playOneMove(this->game->getP1(), &this->lastPlayer);


        // print out the board
        this->game->showBoard();

        // print "last played msg.." if needed
        lastPlayerMoveMsg(this->lastPlayer, endMovesForP1);

        // play move for P2
        endMovesForP2 = this->game->playOneMove(this->game->getP2(), &this->lastPlayer);

        // print out the board
        this->game->showBoard();

        // print "last played msg.." if needed
        lastPlayerMoveMsg(this->lastPlayer, endMovesForP2);

        // end of turn, clear both of the players' members for the next turn
        //resetPlayers();

    } // end of game

    cout << "Game over!" << endl;
    updateScores();
    showScores();

}

void GameFlow::updateScores() {
    this->game->updatePlayerScores();
}

void GameFlow::showScores() {
    cout << "FINAL SCORE" << endl << this->game->getP1()->getType()
         << ": " << this->game->getP1Score() << endl << this->game->getP2()->getType()
            << ": " << this->game->getP2Score() << endl;
}









