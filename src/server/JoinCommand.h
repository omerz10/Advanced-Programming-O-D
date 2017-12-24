//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_JOINCOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_JOINCOMMAND_H


#include "Command.h"

class JoinCommand : public Command {
public:
    JoinCommand(map<string, GameThread> gMap);

    int execute(Server* server,vector<string> stringV, int clientSocket);

private:
    map<string, GameThread> gamesList; // reference
};

#endif //ADVANCED_PROGRAMMING_O_D_JOINCOMMAND_H
