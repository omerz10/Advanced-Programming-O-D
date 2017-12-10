/*
 * GameFlow.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */
#include <sstream>
#include "GameFlow.h"

#define DATALEN 4096


GameFlow::GameFlow (Game *g): game(g){}

GameFlow::GameFlow(Game *g, Client *c): game(g), client(c) {}

// readability function - less clutter in playOneTurn() function..
void GameFlow::lastPlayerMoveMsg(Player *lastPlayer, bool playerMoves) {
    if (playerMoves) {
        // print "last player played..." msg here
        cout << lastPlayer->getType() << " played (" << lastPlayer->getLastMove().getX() + 1 << "," <<
             lastPlayer->getLastMove().getY() + 1 << ")" << endl << endl;
    }
}


void GameFlow::play() {
    char buff[DATALEN];
    memset(&buff, 0, sizeof(buff));
    bool endMovesForP1 = true, endMovesForP2 = true;

    // show board for the first time...
    this->game->getP1()->showBoard();

    // stop when end moves for both P1 & P2
    while(endMovesForP1 and endMovesForP2) {

        // play move for P1
        endMovesForP1 = this->game->playOneMove(this->game->getP1());

        // print out the board
        this->game->getP1()->showBoard();

        // print "last played msg.."
        lastPlayerMoveMsg(this->game->getLastPlayer(), endMovesForP1);

        // play move for P2
        endMovesForP2 = this->game->playOneMove(this->game->getP2());

        // print out the board
        this->game->getP2()->showBoard();


        // print "last played msg.."
        lastPlayerMoveMsg(this->game->getLastPlayer(), endMovesForP2);

        // end of turn, clear both of the players' members for the next turn

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

void GameFlow::parseToString(Cell c, char *buff) {

    memset(&buff, 0, sizeof(buff));
    stringstream ss;
    ss << c.getX();
    ss << ", ";
    ss << c.getY();
    string str = ss.str();

    strcpy(buff, str.c_str());
}

Cell GameFlow::parseFromString(char *str) {
    int x,y;
    x = str[0] - '0';
    y = str[3] - '0';
    return Cell(x, y);
}

void GameFlow::playOnline() {
    Player *localPlayer = this->game->getP1();
    Player *remotePlayer = this->game->getP2();
    bool isFirst = false;
    char buff[DATALEN];
    memset(&buff, 0, sizeof(buff));
    bool endMovesForLocal = true, endMovesForRemote = true;

    this->client->getMessage(buff); // for local player proceed with game, for remote player - wait.

    // play first move for "local player"
    if (strcmp(buff, "first") == 0) { // black player
        isFirst = true;
        localPlayer->showBoard(); // show board for the first time...
        this->game->playOneMove(localPlayer); // play move
        parseToString(this->game->getLastPlayer()->getLastMove(), buff); // parse move
        this->client->sendExercise(buff); // send move to server
        this->client->waitingForOtherPlayer();// wait for response from server
    }

    while(1) {
        // gets message from server
        if (isFirst) {
            this->client->getMessage(buff);
        }
        if (strcmp(buff, "End") == 0) {
            break;
        } else if (strcmp(buff, "NoMove") == 0) {
            endMovesForRemote = false;
        } else {
            Cell tempCell = parseFromString(buff); // parse move from server
            remotePlayer->setLastMove(tempCell.getX(), tempCell.getY()); // set last move
            remotePlayer->playTurn(); // play turn
        }

        localPlayer->showBoard(); // show board
        lastPlayerMoveMsg(this->game->getLastPlayer(), endMovesForRemote); // print moves if they exist
        endMovesForLocal = this->game->playOneMove(localPlayer); // play one move for local

        localPlayer->showBoard(); // show board
        if (endMovesForLocal) { // moves exist for local player
            parseToString(localPlayer->getLastMove(), buff); // parse cell to string
            this->client->sendExercise(buff); // send to server
            this->client->waitingForOtherPlayer(); // wait for player
        } else { // no moves for local player
            if (!endMovesForRemote) { // no moves for remote as well
                this->client->sendExercise("End"); // end game
            } else { // no moves for local but there were moves for remote
                this->client->sendExercise("NoMove");
                // wait for other player
                this->client->waitingForOtherPlayer();
            }
        }
        if (!isFirst) {
            isFirst = true;
        }
    }
    // end of game
    cout << "Game over!" << endl;
    updateScores();
    showScores();

}
