//
// Created by David Nakash on 24/12/2017.
//


#include "JoinCommand.h"


#define DATALEN 512


void JoinCommand::execute(ClientThread *clientT, string args) {
    char temp[DATALEN];

    // iterator
    vector <string >::iterator it;

    it = this->controller->getJoinableGames().begin(); // for loop

    // look for game- check if possible to join game
    if (it != this->controller->getJoinableGames().end()) { // game found

        // remove this game from joinable_games
        this->controller->getJoinableGames().erase(it);
        // insert 2nd player into the game
        this->controller->getGames()[args].player2.clientSocket = clientT->clientSocket;

        cout << "Server completed connection with 2 players.." << endl;
        cout << "----- The Game Begins -----" << endl;
        memset(temp, 0, DATALEN);

        strcpy(temp, "join");
        // update second player he is connected
        if (write(this->controller->getGames()[args].player2.clientSocket, temp, DATALEN) == -1) {
            throw ("Error: sending to player 2");
        }

        int firstClient = CompleteBlackPlayer;
        // send '1' (black) to first player
        if (write(this->controller->getGames()[args].player1.clientSocket
                , &firstClient, sizeof(firstClient)) == -1) {
            throw ("Error: sending to player 1");
        }
        int secondClient = CompleteWhitePlayer;
        // send '2' (white) to second player
        if (write(this->controller->getGames()[args].player2.clientSocket
                , &secondClient, sizeof(secondClient)) == -1) {
            throw ("Error: sending to player 2");
        }

        // the players will now start playing with each other
        this->controller->getGames()[args].player1.status = Playing;
        this->controller->getGames()[args].player2.status = Playing;

        try {
            // run game
            this->controller->runOneGame(args);
        } catch (const char *exception) {
            throw exception;
        }

    } else { // game not found, cannot execute join
        // return error value
        int error = GameNotFound;
        if (write(this->controller->getGames()[args].player1.clientSocket, &error, sizeof(error)) == -1) {
            throw ("Error: sending to player 1");
        }
    }

}

JoinCommand::JoinCommand(Controller *controller) {
    this->controller = controller;
}

