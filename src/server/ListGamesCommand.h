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

    void execute(Server *server, vector<string> args, int clientSocket);

private:
};


#endif //ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H
