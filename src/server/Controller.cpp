//
// Created by David Nakash on 24/12/2017.
//

#include <iostream>
#include "Controller.h"


#define DATALEN 512

map<string, Command* > Controller::getCommands() {
    return this->commands;
}

void Controller::init() {
    this->commands["start"] = new StartCommand();
    this->commands["list_games"] = new ListGamesCommand();
    this->commands["join"] = new JoinCommand();
    this->commands["play"] = new PlayCommand();
}







