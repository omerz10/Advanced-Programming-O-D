//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_JOINCOMMAND_H

#define ADVANCED_PROGRAMMING_O_D_JOINCOMMAND_H

#include "Command.h"

#include <map>

class JoinCommand : public Command {
private:
    Controller *controller;
public:
    JoinCommand(Controller *controller);
    void execute(ClientThread *clientT, string args);
};

#endif //ADVANCED_PROGRAMMING_O_D_JOINCOMMAND_H
