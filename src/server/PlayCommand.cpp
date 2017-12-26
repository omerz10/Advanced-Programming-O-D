//
// Created by David Nakash on 24/12/2017.
//

#include "PlayCommand.h"
#define X 0
#define Y 1




void PlayCommand::execute(Server *server, vector<string> args, int clientSocket) {
    string tempString;

    tempString += args[X];
    tempString += " ";
    tempString += args[Y];


    //server->handleClients(server->getGames()[],  , );

}
