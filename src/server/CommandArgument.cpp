//
// Created by David Nakash on 28/12/2017.
//

#include "CommandArgument.h"

CommandArgument::CommandArgument(GameManager *gM, Controller *cont, string cN, string cP, int clientSocket) {
    this->gameManager = gM;
    this->controller = cont;
    this->commandName = cN;
    this->commandParam = cP;
    this->clientSocket = clientSocket;
}

Controller *CommandArgument::getController() {
    return this->controller;
}

GameManager *CommandArgument::getManager() {
    return this->gameManager;
}

string CommandArgument::getCommandParam() {
    return commandParam;
}

string CommandArgument::getCommandName() {
    return commandName;
}

int CommandArgument::getClientSocket() {
    return clientSocket;
}
