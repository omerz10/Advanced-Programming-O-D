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
    //ListGamesCommand(map<string, GameThread> gMap);

    void execute(vector<string> args, int clientSocket,
                 map < string, struct GameThread > gameThread);

private:
    map<string, GameThread> gamesList; // reference
};


#endif //ADVANCED_PROGRAMMING_O_D_LISTGAMESCOMMAND_H
