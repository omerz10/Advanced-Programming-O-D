//
// Created by omerz on 31/12/17.
//

#ifndef ADVANCED_PROGRAMMING_O_D_ENDCOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_ENDCOMMAND_H


#include "ServerStructs.h"
#include "Command.h"
#include <map>
#include "GameManager.h"

class EndCommand : public Command {


    void EndCommand::execute(CmdArg *cmdArgs);

};


#endif //ADVANCED_PROGRAMMING_O_D_ENDCOMMAND_H
