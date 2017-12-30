//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
#define ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
#include <map>
#include "StartCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
using namespace std;

class Controller {
private:
public:
    map < string, Command* > commands; // map of commands according to name
    map < string, Command* > getCommands();
    void init();
};



#endif //ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
