//
// Created by David Nakash on 24/12/2017.
//


#include "CommandManager.h"



#define DATALEN 512

CommandManager::CommandManager(Controller *controller) {
    this->commands["start"] = new StartCommand(controller);
    this->commands["list_games"] = new ListGamesCommand(controller);
    this->commands["join"] = new JoinCommand(controller);
    this->commands["play"] = new PlayCommand(controller);
    this->commands["NoMove"] = new NoMoveCommand(controller);
    this->commands["End"] = new EndCommand(controller);
}

CommandManager::~CommandManager() {

}


map<string, Command* > CommandManager::getCommands() {
    return this->commands;
}


void CommandManager::executeCommand(ClientThread *clientT, string commandString) {


    // create command struct
    string commandParam, commandName;

    stringstream ss(commandString);
    // extract command name
    ss >> commandName;
    // extract command parameters
    ss >> commandParam;

    this->commands[commandName]->execute(clientT, commandParam);


}







