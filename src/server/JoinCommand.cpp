//
// Created by David Nakash on 24/12/2017.
//

#include <map>
#include "JoinCommand.h"
#include "../client/Structs.h"
#define ARGUMENT 0  // name of game chosen by user

JoinCommand::JoinCommand(map <string, GameThread> gMap) {
    this->gamesList = gMap;
}

int JoinCommand::execute(Server* server,vector<string> stringV, int clientSocket) {
    // iterator
    std::map<string, GameThread >::iterator it;
    it = this->gamesList.find(stringV[ARGUMENT]);

    // look for game
    if (it != this->gamesList.end()) { // game found
        // check if possible to join game
        if (!this->gamesList[stringV[ARGUMENT]].running) { // check if game NOT running
            // insert 2nd player into the game
            this->gamesList[stringV[ARGUMENT]].player2Socket = clientSocket;
            // add player to game in server
            server->join(stringV[ARGUMENT], clientSocket);
            // set game running to true
            this->gamesList[stringV[ARGUMENT]].running = true;

        } else { // game is running, cannot join this game
            return -1;
        }
    } else { // game not found, cannot execute join
        // return error value
        return -1;
    }
    // function output
    return 0;
}
