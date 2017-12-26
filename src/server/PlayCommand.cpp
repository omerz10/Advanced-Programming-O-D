//
// Created by David Nakash on 24/12/2017.
//

#include "PlayCommand.h"
#define X 0
#define Y 1



PlayCommand::PlayCommand(Server *server) {
    this->server = server;
}

void PlayCommand::execute(vector<string> args, int clientSocket) {
    string tempString;

    tempString += args[X];
    tempString += " ";
    tempString += args[Y];


    //server->handleClients(server->getGames()[],  , );

}
