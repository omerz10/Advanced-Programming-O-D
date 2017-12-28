//
// Created by David Nakash on 23/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_COMMAND_H
#define ADVANCED_PROGRAMMING_O_D_COMMAND_H




using namespace std;

#include <vector>
#include "Server.h"


class Command {

public:
    virtual void execute(CommandArguments *commandArgument) = 0;
    virtual ~Command() { }
};



#endif //ADVANCED_PROGRAMMING_O_D_COMMAND_H
