//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H


//#include <map>
#include <map>
#include "Command.h"
using namespace std;

class ListGamesCommand : public Command {
public:
    ListGamesCommand(map<string, GameThread> gMap);

    int execute(Server* server,vector<string> stringV, int clientSocket);

private:
    map<string, GameThread> gamesList; // reference
};


#endif //ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H
