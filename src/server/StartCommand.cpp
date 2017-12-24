//
// Created by David Nakash on 23/12/2017.
//

#include "StartCommand.h"

#define ARGUMENT 0  // name of game chosen by user

StartCommand::StartCommand(map<string, GameThread> gMap) {
    this->gamesList = gMap;
}

int StartCommand::execute(vector<string> stringV, int clientSocket) {

    std::map<string, GameThread >::iterator it;
    it = this->gamesList.find(stringV[ARGUMENT]);

    // check if game exists
    if (it != this->gamesList.end()) { // game found
        return -1;
    } else { // game no found, start a new one
        this->gamesList[stringV[ARGUMENT]].player1Socket = clientSocket;
        this->gamesList[stringV[ARGUMENT]].running =  false;
        this->server->start(this->gamesList[stringV[ARGUMENT]].player1Socket);
    }

    return 0;

}

