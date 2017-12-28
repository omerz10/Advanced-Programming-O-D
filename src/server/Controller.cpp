//
// Created by David Nakash on 24/12/2017.
//


#include <iostream>
#include "Controller.h"
#include "Server.h"


#define DATALEN 512


Controller::Controller() {

    this->commands["start"] = new StartCommand();
    this->commands["list_games"] = new ListGamesCommand();
    this->commands["join"] = new JoinCommand();
    this->commands["play"] = new PlayCommand();
}

Controller::~Controller() {
    delete(this->commands["start"]);
    delete(this->commands["list_games"]);
    delete(this->commands["join"]);
    delete(this->commands["play"]);
}




map<string, Command *> Controller::getCommands() {
    return this->commands;
}





