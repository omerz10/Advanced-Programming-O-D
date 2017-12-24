//
// Created by David Nakash on 24/12/2017.
//

#include "PlayCommand.h"
#define X 0
#define Y 1



PlayCommand::PlayCommand(map<string, GameThread> gMap) {
    this->gamesList = gMap;
}

int PlayCommand::execute(Server* server,vector<string> stringV, int clientSocket) {
    string tempString;

    tempString += stringV[X];
    tempString += " ";
    tempString += stringV[Y];

    server->handleClients(server->getGames()[],  , );
    return 0;
}
