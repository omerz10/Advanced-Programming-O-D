//
// Created by omerz on 31/12/17.
//

#include <zconf.h>
#include "NoMoveCommand.h"

void NoMoveCommand::execute(CmdArg *cmdArgs) {

    write(cmdArgs->clientThread.clientSocket, cmdArgs->name.c_str(), sizeof(cmdArgs->param.c_str()));
}