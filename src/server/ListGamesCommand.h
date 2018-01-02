//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H

#define ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H

#include <map>
#include "Command.h"


using namespace std;



class ListGamesCommand : public Command {
private:
    Controller *controller;
public:
    ListGamesCommand(Controller *controller);
    void execute(ClientThread *clientT, string args);

};


#endif //ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H
