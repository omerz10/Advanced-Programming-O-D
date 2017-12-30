//
// Created by David Nakash on 30/12/2017.
//

#include "CommandArgument.h"

CommandArgument::CommandArgument(GameManager *gameManager, Controller *controller, int clientSocket, string commandName,
                                 string commandParam) {
    this->gameManager = gameManager;
    this->controller = controller;
    this->clientSocket = clientSocket;
    this->name = commandName;
    this->param = commandParam;
}

GameManager *CommandArgument::getGameManager() {
    return gameManager;
}

Controller *CommandArgument::getController() {
    return controller;
}

int CommandArgument::getClientSocket() {
    return clientSocket;
}

string CommandArgument::getName() {
    return name;
}

string CommandArgument::getParam() {
    return param;
}

