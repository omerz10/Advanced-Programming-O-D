//
// Created by David Nakash on 23/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_COMMAND_H
#define ADVANCED_PROGRAMMING_O_D_COMMAND_H

using namespace std;
#include <vector>
#include "ServerStructs.h"

class Command {
public:
    virtual void execute(CommandArgument *commandArgument) = 0;

};





#endif //ADVANCED_PROGRAMMING_O_D_COMMAND_H
