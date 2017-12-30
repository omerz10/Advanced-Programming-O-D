//
// Created by David Nakash on 23/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_COMMAND_H
#define ADVANCED_PROGRAMMING_O_D_COMMAND_H
#include <vector>
#include "ServerStructs.h"
using namespace std;

enum Errors {CompleteBlackPlayer = 1, CompleteWhitePlayer = 2, CannotJoinGame = -1, GameNotFound = -2};

class Command {
public:
    virtual void execute(CmdArg *commandArgument) = 0;
};

#endif //ADVANCED_PROGRAMMING_O_D_COMMAND_H
