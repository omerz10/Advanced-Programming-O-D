//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
#define ADVANCED_PROGRAMMING_O_D_CONTROLLER_H

#include <string.h>
#include <map>
#include "Command.h"
#include "../client/Structs.h"

class Controller {
public:

    Controller(Server *server);

    void executeCommand(string commandString, int clientSocket);

private:

    map < string, Command* > commands; // map of commands according to name
    Server *server;
};



#endif //ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
