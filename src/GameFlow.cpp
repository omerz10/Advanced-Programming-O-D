/*
 * GameFlow.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */
#include <sstream>
#include <cstdlib>
#include "GameFlow.h"

#define DATALEN 1024


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
    stringstream ss;
    ss << c.getX();
    ss << ", ";
    ss << c.getY();
    string str = ss.str();

    strcpy(buff, str.c_str());
}

Cell GameFlow::parseFromString(char *str) {
    int x,y;
    x = atoi(&str[0]);
    y = atoi(&str[2]);
    return Cell(x, y);
}

void GameFlow::playOnline() {
    Player *localPlayer = this->game->getP1();
    Player *remotePlayer = this->game->getP2();
    //Player *localPlayer;
    //Player *remotePlayer;
    char buff[DATALEN];
    memset(buff, 0, sizeof(buff));
    bool endMovesForLocal = true, endMovesForRemote = true;

    // play first move for "local player"
    if (this->client->getID() == 1) {
        //localPlayer = this->game->getP1();
        //remotePlayer = this->game->getP2();
        // black player
        localPlayer->showBoard(); // show board for the first time...
        this->game->playOneMove(localPlayer); // play move
        localPlayer->showBoard();
        parseToString(this->game->getLastPlayer()->getLastMove(), buff); // parse move
        this->client->sendExercise(buff); // send move to server
        cout << "Waiting for other player's move..." << endl;
        this->client->getMessage(buff);
    }
//    } else if (this->client->getID() == 2){
//        localPlayer = this->game->getP2();
//        remotePlayer = this->game->getP1();
//    }

    while(true) {
        // gets message from server
        this->client->getMessage(buff);

        if (strcmp(buff, "End") == 0) {
            break;
        } else if (strcmp(buff, "NoMove") == 0) {
            endMovesForRemote = false;
        } else {
            Cell tempCell = parseFromString(buff); // parse move from server
            remotePlayer->getPlayerMoves();
            remotePlayer->setLastMove(tempCell.getX(), tempCell.getY()); // set last move
            remotePlayer->playTurn(); // play turn
        }
        localPlayer->showBoard(); // show board
        //lastPlayerMoveMsg(this->game->getLastPlayer(), endMovesForRemote); // print moves if they exist
        endMovesForLocal = this->game->playOneMove(localPlayer); // play one move for local
        if (endMovesForLocal) { // moves exist for local player
            parseToString(localPlayer->getLastMove(), buff); // parse cell to string
            this->client->sendExercise(buff); // send to server

        } else { // no moves for local player
            if (!endMovesForRemote) { // no moves for remote as well
                this->client->sendExercise("End");
                break;// end game
            } else { // no moves for local but there were moves for remote
                this->client->sendExercise("NoMove");
                // wait for other player;
            }
        }
        this->client->getMessage(buff);
    }


    // end of game
    cout << "Game over!" << endl;
    updateScores();
    showScores();

}
