//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
#define ADVANCED_PROGRAMMING_O_D_CONTROLLER_H

#include <map>
#include "StartCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CommandArgument.h"

class Controller {
public:

    Controller();
    ~Controller();
    void executeCommand(void* cArgs);

    map < string, Command* > getCommands();
private:
    map < string, Command* > commands; // map of commands according to name
};



#endif //ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
