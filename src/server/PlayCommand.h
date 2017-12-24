//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H


#include <map>
#include "Command.h"

class PlayCommand : public Command {
public:
    PlayCommand(map<string, GameThread> gMap);

    int execute(Server* server,vector<string> stringV, int clientSocket);
private:
    map<string, GameThread> gamesList; // reference
};

#endif //ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H
