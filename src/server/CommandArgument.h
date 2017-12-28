//
// Created by David Nakash on 28/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_COMMANDARGUMENT_H
#define ADVANCED_PROGRAMMING_O_D_COMMANDARGUMENT_H

using namespace std;

#include <string>

class CommandArgument {

private:
    GameManager *gameManager;
    Controller *controller;
    string commandName;
    int clientSocket;
    string commandParam;
public:
    CommandArgument(GameManager *gM, Controller *cont, string cN, string cP, int clientSocket);
    // getters
    string getCommandName();
    string getCommandParam();
    int getClientSocket();
    Controller *getController();
    GameManager *getManager();

};


#endif //ADVANCED_PROGRAMMING_O_D_COMMANDARGUMENT_H
