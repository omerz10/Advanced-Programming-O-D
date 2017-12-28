//
// Created by David Nakash on 24/12/2017.
//

#include "PlayCommand.h"
#define X 0
#define Y 1

#define DATALEN 512


void PlayCommand::execute(CommandArguments *cmdArgs) {

    write(cmdArgs->clientSocket, cmdArgs->param.c_str(), sizeof(cmdArgs->param.c_str()));
}
