//
// Created by David Nakash on 23/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_STARTCOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_STARTCOMMAND_H

#include <string>
#include <map>
#include "Command.h"

using namespace std;



class StartCommand : public Command {
public:
    void execute(CommandArguments *commandArgument);
};


#endif //ADVANCED_PROGRAMMING_O_D_STARTCOMMAND_H
