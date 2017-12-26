//
// Created by David Nakash on 23/12/2017.
//

#include "StartCommand.h"

#define GAME_NAME 0  // name of game chosen by user
#define DATALEN  512


void StartCommand::execute(Server *server, vector<string> args, int clientSocket) {

    std::map<string, GameThread >::iterator it;
    it = server->getGames().find(args[GAME_NAME]);

    // check if game exists
    if (it != server->getGames().end()) { // game found
        // send -1 to player
    } else { // game no found, start a new one

        server->getGames()[args[GAME_NAME]].player1Socket = clientSocket;
        server->getGames()[args[GAME_NAME]].FirstConnected;

        char temp[DATALEN];
        // update first player he is connected
        memset(temp, 0, DATALEN);
        strcpy(temp, "join");
        if (write(server->getGames()[args[GAME_NAME]].player1Socket, temp, DATALEN) == -1) {
            throw ("Error: sending to player 1");
        }
    }
}

