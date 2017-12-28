//
// Created by David Nakash on 23/12/2017.
//

#include "StartCommand.h"

#define GAME_NAME 0  // name of game chosen by user
#define DATALEN  512


void StartCommand::execute(CommandArgument *cArgs) {

    map<string, GameThread >::iterator it;
    cArgs->controller->getCommands()["start"]
    it = cArgs->gameManager->getGames().find(cArgs.commandParam);

    // check if game exists
    if (it != cArgs.gameManager->getGames().end()) { // game found
        // send -1 to player
    } else { // game no found, start a new one

        cArgs->gameManager->getGames()[cArgs.commandParam].player1Socket = cArgs.clientSocket;
        cArgs.gameManager->getGames()[cArgs.commandParam].status = FirstConnected;

        char temp[DATALEN];
        // update first player he is connected
        memset(temp, 0, DATALEN);
        strcpy(temp, "join");
        if (write(cArgs.gameManager->getGames()[cArgs.commandParam].player1Socket, temp, DATALEN) == -1) {
            throw ("Error: sending to player 1");
        }
    }
}

