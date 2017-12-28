//
// Created by David Nakash on 28/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_COMMANDARGUMENT_H
#define ADVANCED_PROGRAMMING_O_D_COMMANDARGUMENT_H


#include "GameManager.h"
#include "Controller.h"

class CommandArgument {
private:
    GameManager *gameManager;
    Controller *controller;
    string commandName;
    string commandParam;
    int clientSocket;
public:
    CommandArgument(GameManager *gM, Controller *cont);
    void setCommandName(string commandName);
    void setCommandParam(string commandParam);
    void setClientSocket(int clientSocket);

};


#endif //ADVANCED_PROGRAMMING_O_D_COMMANDARGUMENT_H
