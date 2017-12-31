//
// Created by David Nakash on 24/12/2017.
//

#include <iostream>
#include <sstream>
#include "Controller.h"
#include "NoMoveCommand.h"
#include "EndCommand.h"


#define DATALEN 512

map<string, Command* > Controller::getCommands() {
    return this->commands;
}

void Controller::init() {
    this->commands["start"] = new StartCommand();
    this->commands["list_games"] = new ListGamesCommand();
    this->commands["join"] = new JoinCommand();
    this->commands["play"] = new PlayCommand();
    this->commands["NoMove"] = new NoMoveCommand();
    this->commands["End"] = new EndCommand();
}

void Controller::executeCommand(GameManager *gm, ClientThread clientT, string str) {
    CmdArg cmdArgs;
    cmdArgs.gameManager = gm;
    cmdArgs.clientThread = clientT;
    cmdArgs.controller = this;

    // create command struct
    string commandParam, commandName;

    stringstream ss(str);
    // extract command name
    ss >> cmdArgs.name;
    // extract command parameters
    ss >> cmdArgs.param;

    map<string, GameThread >::iterator it;
    it = cmdArgs.gameManager->getGames().find(cmdArgs.name);

    //check if command is part of specified commands
    if (cmdArgs.gameManager->getGames().end() != it) { // found command
        cmdArgs.controller->commands[cmdArgs.name]->execute(&cmdArgs);
    } else {
        cout << "Error in command!" << endl;
    }


}







