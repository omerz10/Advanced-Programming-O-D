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

#define DATALEN 512


GameFlow::GameFlow (Game *g): game(g){}

GameFlow::GameFlow(Game *g, Client *c): game(g), client(c) {}

// readability function - less clutter in playOneTurn() function..
void GameFlow::lastPlayerMoveMsg(Player *lastPlayer, bool playerMoves) {
    if (playerMoves) {
        // print "last player played..." msg here
        cout << lastPlayer->getType() << " played (" << lastPlayer->getLastMove().getX() + 1 << "," <<
             lastPlayer->getLastMove().getY() + 1 << ")" << endl << endl;
    } else {
        cout << "Player " << lastPlayer->getType() << " had no moves" << endl << endl;
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
        cout << "Player " << this->game->getP1()->getType() << " Won!";
    }
    if (this->game->getP2Score() > this->game->getP1Score()) {
        cout << "Player " << this->game->getP2()->getType() << " Won!";
    }
    if (this->game->getP2Score() == this->game->getP1Score()) {
        cout << "It's a tie!";
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
    char buff[DATALEN], temp[DATALEN];
    memset(buff, 0, DATALEN);
    bool endMovesForLocal, endMovesForRemote;

    // play first move for "local player"
    if (this->client->getID() == 1) {
        //localPlayer = this->game->getP1();
        //remotePlayer = this->game->getP2();
        // black player
        localPlayer->showBoard(); // show board for the first time...
        endMovesForLocal = this->game->playOneMove(localPlayer); // play move
        localPlayer->showBoard();
        parseToString(this->game->getLastPlayer()->getLastMove(), buff); // parse move
        this->client->sendExercise(buff); // send move to server
        cout << endl <<"Waiting for other player's move..." << endl;
    }

    while(true) {
        // gets message from server
        this->client->getMessage(buff);

        if (strcmp(buff, "End") == 0) {
            break;
        } else if (strcmp(buff, "NoMove") == 0) {
            endMovesForRemote = false;
        } else {
            endMovesForRemote = true;
            Cell tempCell = parseFromString(buff); // parse move from server
            remotePlayer->getPlayerMoves();
            remotePlayer->setLastMove(tempCell.getX(), tempCell.getY()); // set last move
            remotePlayer->playTurn(); // play turn

        }

        localPlayer->showBoard(); // show board
        lastPlayerMoveMsg(remotePlayer, endMovesForRemote); // show last player's move

        endMovesForLocal = this->game->playOneMove(localPlayer); // play one move for local

        if (endMovesForLocal) { // moves exist for local player
            parseToString(localPlayer->getLastMove(), buff); // parse cell to string
            this->client->sendExercise(buff); // send to server
        } else { // no moves for local player
            if (!endMovesForRemote) { // no moves for remote as well
                memset(temp, 0, DATALEN);
                strcpy(temp, "End");
                this->client->sendExercise(temp);
                break;// end game
            } else { // no moves for local but there were moves for remote
                memset(temp, 0, DATALEN);
                strcpy(temp, "NoMove");
                this->client->sendExercise(temp);
                // wait for other player;
            }
        }
        cout << endl << "Waiting for other player's move..." << endl;
    }


    // end of game
    cout << "Game Over!" << endl;
    updateScores();
    showScores();

}

void GameFlow::playOnlineSelection() {
    cout << "Please choose one of the following options:\n"
         << "1. Start a new online game.\n"
         << "2. Join an ongoing game.\n"
         << "3. Show list of ongoing games.\n";
    int selection;
    ClientSelection clientSelection = Choosing;
    cin >> selection;
    if (selection == StartGame) {
        char command[DATALEN] = "";
        string gameName;
        system("CLS");
        cout << "Please choose a name for your new game:\n";
        cin >> gameName;
        strcat(command, "start ");
        strcat(command, gameName.c_str());
        // now we send the chosen game name to the server
        this->client->sendExercise(command);
        // call playOnline() which waits for other player to join
        this->playOnline();
    } else if (selection == JoinGame) {
        char command[DATALEN] = "";
        string gameName;
        system("CLS");
        cout << "Please choose the game to join by name:\n";
        cin >> gameName;
        strcat(command, "join ");
        strcat(command, gameName.c_str());
        // now we send the chosen game name to the server
        this->client->sendExercise(command);
        this->playOnline();
    } else if (selection == ShowListOfGames) {
        char command[DATALEN] = "";
        system("CLS");
        strcat(command, "list_games");
        this->client->sendExercise(command);
    }
}
