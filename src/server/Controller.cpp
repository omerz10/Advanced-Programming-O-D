//
// Created by David Nakash on 24/12/2017.
//

#include <sstream>
#include "Controller.h"
#include "StartCommand.h"
#include "ListGamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "Server.h"

Controller::Controller(Server *server) {
    this->server = server;
    this->commands["start"] = new StartCommand(this->server->);
    this->commands["list_games"] = new ListGamesCommand(this->games);
    this->commands["join"] = new JoinCommand(this->games);
    this->commands["play"] = new PlayCommand(this->games);
}

void Controller::executeCommand(string commandString, int clientSocket) {
    vector<string> arguments;
    stringstream ss(commandString);
    // extract command name
    string commandName;
    ss >> commandName;
    // extract arguments
    while (!ss.eofbit) {
        string arg;
        ss >> arg;
        arguments.push_back(arg);
    }

    // now execute function
    std::map<string, Command* >::iterator it;
    it = this->commands.find(commandName);
    // check if command is part of specified commands
    if (it != this->commands.end()) { // found command
        this->commands[commandName]->execute(arguments, clientSocket);
    } else {
        cout << "Error in command!" << endl;
    }

}


