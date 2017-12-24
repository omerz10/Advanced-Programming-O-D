//
// Created by David Nakash on 23/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_COMMAND_H
#define ADVANCED_PROGRAMMING_O_D_COMMAND_H

using namespace std;

#include <vector>
#include "../client/Structs.h"
#include "Server.h"


class Command {
private:

    map<string, GameThread> gamesList; // reference

public:
    virtual int execute(Server *server, vector<string> stringV, int clientSocket) = 0;

};





#endif //ADVANCED_PROGRAMMING_O_D_COMMAND_H
