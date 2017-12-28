//
// Created by David Nakash on 28/12/2017.
//

#include "CommandArgument.h"

CommandArgument::CommandArgument(GameManager *gM, Controller *cont) {
    this->gameManager = gM;
    this->controller = cont;
}

void CommandArgument::setCommandParam(string commandParam) {
    strcpy(this->commandParam, commandParam);
}

void CommandArgument::setCommandName(string commandName) {
    strcpy(this->commandName, commandName);
}

void CommandArgument::setClientSocket(int clientSocket) {
    this->clientSocket = clientSocket;
}
