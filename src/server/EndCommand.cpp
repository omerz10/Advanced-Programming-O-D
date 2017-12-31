//
// Created by omerz on 31/12/17.
//

#include <zconf.h>
#include "EndCommand.h"


void EndCommand::execute(CmdArg *cmdArgs) {
    write(cmdArgs->clientThread.clientSocket, cmdArgs->param.c_str(), sizeof(cmdArgs->param.c_str()));
    // delete game from games list of server
    cmdArgs->gameManager->deleteGame(cmdArgs->param);
}



