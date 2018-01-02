//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H

#define ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H
#include <map>
#include "Command.h"


class PlayCommand : public Command {
private:
    Controller *controller;
public:
    PlayCommand(Controller *controller);
    void execute(ClientThread *clientT, string args);

};

#endif //ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H
