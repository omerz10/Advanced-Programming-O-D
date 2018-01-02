//
// Created by omerz on 31/12/17.
//

#ifndef ADVANCED_PROGRAMMING_O_D_NOMOVECOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_NOMOVECOMMAND_H


#include "ServerStructs.h"
#include "Command.h"
#include <map>

class NoMoveCommand : public Command {
private:
    Controller *controller;
public:
    NoMoveCommand(Controller *controller);
    void execute(ClientThread *clientT, string args);

};


#endif //ADVANCED_PROGRAMMING_O_D_NOMOVECOMMAND_H
