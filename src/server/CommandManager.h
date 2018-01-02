//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_COMMANDMANAGER_H
#define ADVANCED_PROGRAMMING_O_D_COMMANDMANAGER_H
class Controller;
#include <map>
#include "StartCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "NoMoveCommand.h"
#include "EndCommand.h"
#include <iostream>
#include <sstream>
#include "Controller.h"

using namespace std;

class CommandManager {

private:
    map < string, Command* > commands; // map of commands according to name

public:

    CommandManager(Controller *controller);
    ~CommandManager();

    map < string, Command* > getCommands();
    void executeCommand(ClientThread *clientT, string str);

};



#endif //ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
