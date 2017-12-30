//
// Created by David Nakash on 30/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_COMMANDARGUMENT_H
#define ADVANCED_PROGRAMMING_O_D_COMMANDARGUMENT_H

#include <string>
class Controller;
class GameManager;
using namespace std;


class CommandArgument {
private:
    GameManager *gameManager;
    Controller *controller;
    int clientSocket;
    string name;
    string param;

public:
    CommandArgument(GameManager *gameManager, Controller *controller, int clientSocket, string commandName
            , string commandParam);

    GameManager *getGameManager();

    Controller *getController();

    int getClientSocket();

    string getName();

    string getParam();
};


#endif //ADVANCED_PROGRAMMING_O_D_COMMANDARGUMENT_H
