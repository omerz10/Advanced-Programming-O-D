//
// Created by David Nakash on 23/12/2017.
//

#include <cstring>
#include "StartCommand.h"

#define GAME_NAME 0  // name of game chosen by user
#define DATALEN  512


void StartCommand::execute(ClientThread *clientT, string args) {
    char temp[DATALEN];
    memset(temp, 0, DATALEN);
    map<string, GameThread >::iterator it;
    
    it = this->controller->getGames().find((args));
    // check if game exists
    if (it != this->controller->getGames().end()) { // game found
        strcpy(temp, "not start");
        write(this->controller->getGames()[args].player1.clientSocket, temp, DATALEN);
    } else { // game no found, create a new one

        clientT->status = StartPlaying;
        this->controller->addNewGame(args, clientT);
        strcpy(temp, "start");
        if (write(this->controller->getGames()[args].player1.clientSocket, temp, DATALEN) == -1) {
            throw ("Error: sending to player 1");
        }
    }
}

StartCommand::StartCommand(Controller *controller) {
    this->controller = controller;
}


