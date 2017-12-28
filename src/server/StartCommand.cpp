//
// Created by David Nakash on 23/12/2017.
//

#include "StartCommand.h"

#define GAME_NAME 0  // name of game chosen by user
#define DATALEN  512


void StartCommand::execute(CommandArgument *cArgs) {

    map<string, GameThread >::iterator it;
    it = cArgs->getManager()->getGames().find(cArgs->getCommandParam());

    // check if game exists
    if (it != cArgs->getManager()->getGames().end()) { // game found
        // send -1 to player
    } else { // game no found, start a new one

        cArgs->getManager()->getGames()[cArgs->getCommandParam()].player1Socket = cArgs->getClientSocket();
        cArgs->getManager()->getGames()[cArgs->getCommandParam()].status = FirstConnected;

        char temp[DATALEN];
        // update first player he is connected
        memset(temp, 0, DATALEN);
        strcpy(temp, "join");
        if (write(cArgs->getManager()->getGames()[cArgs->getCommandParam()].player1Socket, temp, DATALEN) == -1) {
            throw ("Error: sending to player 1");
        }
    }
}

