//
// Created by omerz on 31/12/17.
//

#include <zconf.h>
#include "EndCommand.h"


void EndCommand::execute(CmdArg *cmdArgs) {
    cmdArgs->gameManager->getGames()[cmdArgs->name].status = GameEnded;
    write(cmdArgs->clientSocket, cmdArgs->param.c_str(), sizeof(cmdArgs->param.c_str()));
}