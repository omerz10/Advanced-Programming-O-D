//
// Created by David Nakash on 23/12/2017.
//

#include "StartCommand.h"
#include "GameManager.h"

#define GAME_NAME 0  // name of game chosen by user
#define DATALEN  512


void StartCommand::execute(CmdArg *cArgs) {

    map<string, GameThread >::iterator it;
    
    it = cArgs->gameManager->games.find((cArgs->param));
    // check if game exists
    if (it != cArgs->gameManager->games.end()) { // game found
        // send -1 to player
    } else { // game no found, start a new one

        cArgs->gameManager->games[cArgs->param].player1Socket = cArgs->clientSocket;
        cArgs->gameManager->games[cArgs->param].status = FirstConnected;

        char temp[DATALEN];
        // update first player he is connected
        memset(temp, 0, DATALEN);
        strcpy(temp, "join");
        if (write(cArgs->gameManager->games[cArgs->param].player1Socket, temp, DATALEN) == -1) {
            throw ("Error: sending to player 1");
        }
    }
}


