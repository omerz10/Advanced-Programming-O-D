//
// Created by David Nakash on 23/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_COMMAND_H
#define ADVANCED_PROGRAMMING_O_D_COMMAND_H
#include <vector>
#include "ServerStructs.h"
#include "Controller.h"


using namespace std;

enum Errors {CompleteBlackPlayer = 1, CompleteWhitePlayer = 2, GameNotFound = -1};

class Command {

public:

    //virtual Command(Controller *controller) = 0;

    virtual void execute(ClientThread *clientT, string args) = 0;
};

#endif //ADVANCED_PROGRAMMING_O_D_COMMAND_H
