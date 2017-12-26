//
// Created by David Nakash on 23/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_STARTCOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_STARTCOMMAND_H

#include <string>
#include <map>
#include "Command.h"
#include "../client/Structs.h"
using namespace std;



class StartCommand : public Command {
public:
    //StartCommand(map<string, GameThread> gMap);

    void execute(Server *server, vector<string> args, int clientSocket));

private:
    map<string, GameThread> gamesList; // reference

};


#endif //ADVANCED_PROGRAMMING_O_D_STARTCOMMAND_H
