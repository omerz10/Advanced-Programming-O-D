//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
#define ADVANCED_PROGRAMMING_O_D_CONTROLLER_H


class Command;
class Server;

#include <string.h>
#include <map>
#include "Command.h"
#include "../client/Structs.h"

class Controller {
public:

    explicit Controller(map < string, GameThread > gamesMap);

     void* executeCommand(void* cArgs);

private:
    map < string, Command* > commands; // map of commands according to name
    map < string, GameThread > games;
};



#endif //ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
