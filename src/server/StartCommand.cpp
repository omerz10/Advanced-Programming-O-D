//
// Created by David Nakash on 23/12/2017.
//

#include "StartCommand.h"
#include "GameManager.h"

#define GAME_NAME 0  // name of game chosen by user
#define DATALEN  512


void StartCommand::execute(CmdArg *cArgs) {
    char temp[DATALEN];
    memset(temp, 0, DATALEN);
    map<string, GameThread >::iterator it;
    
    it = cArgs->gameManager->getGames().find((cArgs->param));
    // check if game exists
    if (it != cArgs->gameManager->getGames().end()) { // game found
        strcpy(temp, "not start");
        write(cArgs->gameManager->getGames()[cArgs->param].player1.clientSocket, temp, DATALEN);
    } else { // game no found, create a new one

        cArgs->clientThread.status = StartPlaying;
        cArgs->gameManager->addNewGame(cArgs->param, cArgs->clientThread);
        strcpy(temp, "start");
        if (write(cArgs->gameManager->getGames()[cArgs->param].player1.clientSocket, temp, DATALEN) == -1) {
            throw ("Error: sending to player 1");
        }
    }
}


