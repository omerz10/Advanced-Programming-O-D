//
// Created by David Nakash on 24/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H
#define ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H


#include <map>
#include "Command.h"

class PlayCommand : public Command {
public:
    PlayCommand(Server *server);

    void execute(Server *server, vector<string> args, int clientSocket);
private:
    Server *server;
};

#endif //ADVANCED_PROGRAMMING_O_D_PLAYCOMMAND_H
