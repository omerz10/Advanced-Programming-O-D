//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H

#include <map>
#include "Command.h"
using namespace std;

class ListGamesCommand : public Command {
public:
    void execute(CommandArgument commandArgument);

};


#endif //ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H
