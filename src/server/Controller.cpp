//
// Created by David Nakash on 24/12/2017.
//


#include "Controller.h"


Controller::Controller() {
    this->commands["start"] = new StartCommand();
    this->commands["list_games"] = new ListGamesCommand();
    this->commands["join"] = new JoinCommand();
    this->commands["play"] = new PlayCommand();
}

map<string, Command *> Controller::getCommands() {
    return this->commands;
}

void *executeCommand(void *cArgs) {
    CommandArgument *cmdArgs = (CommandArgument *)cArgs;

    // now execute function
    map<string, Command* >::iterator it;
    it = cmdArgs->controller->getCommands().find((*cmdArgs).commandName);
    // check if command is part of specified commands
    if (it != cmdArgs->controller->getCommands().end()) { // found command
        cmdArgs->controller->getCommands()[(*cmdArgs).commandName]->execute(cmdArgs);
    } else {
        cout << "Error in command!" << endl;
    }
}


