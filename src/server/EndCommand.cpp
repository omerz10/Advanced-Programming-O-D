//
// Created by omerz on 31/12/17.
//

#include <zconf.h>
#include "EndCommand.h"


void EndCommand::execute(ClientThread *clientT, string args) {
    string temp = "End";
    write(clientT->clientSocket, temp.c_str(), sizeof(temp.c_str()));
    // delete game from games list of server
    this->controller->deleteGame(args);
}

EndCommand::EndCommand(Controller *controller) {
    this->controller = controller;
}



