//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H

#define ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H

#include <map>
#include "Command.h"
#include "GameManager.h"


using namespace std;



class ListGamesCommand : public Command {
public:

    void execute(CmdArg *commandArgument);

};


#endif //ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H
