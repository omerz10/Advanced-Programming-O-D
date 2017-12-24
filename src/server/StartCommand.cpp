//
// Created by David Nakash on 23/12/2017.
//

#include "StartCommand.h"

#define ARGUMENT 0  // name of game chosen by user
#define DATALEN  512

StartCommand::StartCommand(map<string, GameThread> gMap) {
    this->gamesList = gMap;
}

int StartCommand::execute(Server* server,vector<string> stringV, int clientSocket) {

    std::map<string, GameThread >::iterator it;
    it = this->gamesList.find(stringV[ARGUMENT]);

    // check if game exists
    if (it != this->gamesList.end()) { // game found
        return -1;
    } else { // game no found, start a new one
        this->gamesList[stringV[ARGUMENT]].player1Socket = clientSocket;
        this->gamesList[stringV[ARGUMENT]].running =  false;

        char temp[DATALEN];
        // update first player he is connected
        memset(temp, 0, DATALEN);
        strcpy(temp, "join");
        if (write(this->gamesList[stringV[ARGUMENT]].player1Socket, temp, DATALEN) == -1) {
            throw ("Error: sending to player 1");
        }
    }
    return 0;
}

