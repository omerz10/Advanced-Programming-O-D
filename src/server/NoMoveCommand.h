//
// Created by omerz on 31/12/17.
//

#ifndef ADVANCED_PROGRAMMING_O_D_NOMOVECOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_NOMOVECOMMAND_H


#include "ServerStructs.h"
#include "Command.h"

class NoMoveCommand : public Command {


    void NoMoveCommand::execute(CmdArg *cmdArgs);

};


#endif //ADVANCED_PROGRAMMING_O_D_NOMOVECOMMAND_H
