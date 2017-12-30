//
// Created by David Nakash on 24/12/2017.
//

#include "ListGamesCommand.h"
/*
ListGamesCommand::ListGamesCommand(map<string, GameThread> gMap) {
    this->gamesList = gMap;
}
*/
#define DATALEN 512

void ListGamesCommand:: execute(CmdArg *commandArgument) {
    map<string, GameThread >::iterator it;
    string result;
    // build response
    /*
    for(it = commandArgument->getGameManager()->getGames().begin()
            ; it != commandArgument->getGameManager()->getGames().end(); ++it) {
        result += it->first;
        result += " ";
    }

    // send response to server
    char temp[DATALEN];
    // update first player he is connected
    memset(temp, 0, DATALEN);
    strcpy(temp, result.c_str());
    if (write(commandArgument->getClientSocket(), temp, DATALEN) == -1) {
        throw ("Error: sending to player 1");
    }
     */
}
