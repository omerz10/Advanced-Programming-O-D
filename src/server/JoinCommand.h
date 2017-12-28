//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_JOINCOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_JOINCOMMAND_H


#include "Command.h"
#include "GameManager.h"
#include <map>

class JoinCommand : public Command {
public:
    void execute(CommandArgument *commandArgument);

};

#endif //ADVANCED_PROGRAMMING_O_D_JOINCOMMAND_H
