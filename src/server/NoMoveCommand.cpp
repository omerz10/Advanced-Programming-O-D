//
// Created by omerz on 31/12/17.
//

#include <zconf.h>
#include "NoMoveCommand.h"

void NoMoveCommand::execute(ClientThread *clientT, string args) {
    string temp = "NoMove";
    write(clientT->clientSocket, temp.c_str(), sizeof(temp.c_str()));
}

NoMoveCommand::NoMoveCommand(Controller *controller) {
    this->controller = controller;
}
