//
// Created by David Nakash on 24/12/2017.
//


#include "Controller.h"
#include "StartCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"


Controller::Controller(map < string, GameThread > gamesMap) {
    this->games = gamesMap;
    this->commands["start"] = new StartCommand();
    this->commands["list_games"] = new ListGamesCommand();
    this->commands["join"] = new JoinCommand();
    this->commands["play"] = new PlayCommand();
}

void* Controller::executeCommand(void* cArgs) {

    CommandArgument *cmdArgs = (CommandArgument *)cArgs;

    // now execute function
    map<string, Command* >::iterator it;
    it = this->commands.find((*cmdArgs).commandName);
    // check if command is part of specified commands
    if (it != this->commands.end()) { // found command
        this->commands[(*cmdArgs).commandName]->execute(*cmdArgs);
    } else {
        cout << "Error in command!" << endl;
    }
}


