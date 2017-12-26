//
// Created by David Nakash on 23/12/2017.
//

#include "StartCommand.h"

#define GAME_NAME 0  // name of game chosen by user
#define DATALEN  512
/*
StartCommand::StartCommand(map<string, GameThread> gMap) {
    this->gamesList = gMap;
}
*/
void StartCommand::execute(vector<string> args, int clientSocket) {

    std::map<string, GameThread >::iterator it;
    it = gameMap.find(args[GAME_NAME]);

    // check if game exists
    if (it != gameMap.end()) { // game found
        // send -1 to player
    } else { // game no found, start a new one

        gameMap[args[GAME_NAME]].player1Socket = clientSocket;
        gameMap[args[GAME_NAME]].FirstConnected;

        char temp[DATALEN];
        // update first player he is connected
        memset(temp, 0, DATALEN);
        strcpy(temp, "join");
        if (write(gameMap[args[GAME_NAME]].player1Socket, temp, DATALEN) == -1) {
            throw ("Error: sending to player 1");
        }
    }
}

