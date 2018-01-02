//
// Created by David Nakash on 24/12/2017.
//

#include <zconf.h>
#include "PlayCommand.h"
#define X 0
#define Y 1

#define DATALEN 512


void PlayCommand::execute(ClientThread *clientT, string args) {

    write(clientT->clientSocket, args.c_str(), sizeof(args.c_str()));
}

PlayCommand::PlayCommand(Controller *controller) {
    this->controller = controller;
}
