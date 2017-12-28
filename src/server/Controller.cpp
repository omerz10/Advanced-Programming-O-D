//
// Created by David Nakash on 24/12/2017.
//


#include <iostream>
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

Controller::~Controller() {
    delete(this->commands["start"]);
    delete(this->commands["list_games"]);
    delete(this->commands["join"]);
    delete(this->commands["play"]);
}

void * executeCommand(void *cArgs) {
    CommandArgument *cmdArgs = (CommandArgument *)cArgs;
    // now execute function
    map<string, Command* >::iterator it;
    it = cmdArgs->getController()->getCommands().find(cmdArgs->getCommandName());
    // check if command is part of specified commands
    if (it != cmdArgs->getController()->getCommands().end()) { // found command
        cmdArgs->getController()->getCommands()[cmdArgs->getCommandName()]->execute(cmdArgs);
    } else {
        cout << "Error in command!" << endl;
    }
}


