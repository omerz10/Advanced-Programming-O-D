/*
 * GameFlow.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */
#include "GameFlow.h"


GameFlow::GameFlow (Game *g): game(g), isOnline(false){}

GameFlow::GameFlow(Game *g, Client *c): game(g), client(c), isOnline(true) {}

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
    this->game->getP1()->showBoard();


    // stop when end moves for both P1 & P2
    while(endMovesForP1 and endMovesForP2) {

        // play move for P1
        endMovesForP1 = this->game->playOneMove(this->game->getP1());

        // print out the board
        this->game->getP1()->showBoard();

        if (this->isOnline) {
            //parser last move
            //client.sendexcercise(buffer)
        }

        // print "last played msg.." if needed
        lastPlayerMoveMsg(this->game->getLastPlayer(), endMovesForP1);

        // play move for P2
        endMovesForP2 = this->game->playOneMove(this->game->getP2());

        // print out the board
        this->game->getP2()->showBoard();


        // print "last played msg.." if needed
        lastPlayerMoveMsg(this->game->getLastPlayer(), endMovesForP2);

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
    cout << "Final Score:" << endl << this->game->getP1()->getType()
         << ": " << this->game->getP1Score() << endl << this->game->getP2()->getType()
            << ": " << this->game->getP2Score() << endl << endl;
    if (this->game->getP1Score() > this->game->getP2Score()) {
        cout << this->game->getP1()->getType() << " Win!";
    }
    if (this->game->getP2Score() > this->game->getP1Score()) {
        cout << this->game->getP2()->getType() << " Win!";
    }
    if (this->game->getP2Score() == this->game->getP1Score()) {
        cout << "It's a tiy!";
    }
}













