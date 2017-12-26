//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H


#include <map>
#include "Command.h"

class PlayCommand : public Command {
public:

    void execute(CommandArgument commandArgument);

};

#endif //ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H
