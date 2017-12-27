//
// Created by David Nakash on 24/12/2017.
//

#include <map>
#include <arpa/inet.h>
#include "JoinCommand.h"
#include "../client/Structs.h"
#define GAME_NAME 0  // name of game chosen by user
#define DATALEN 512


void JoinCommand::execute(CommandArgument cArgs) {
    char temp[DATALEN];

    // iterator
    map<string, GameThread >::iterator it;
    it = cArgs.server->getGames().find(cArgs.commandParam);

    // look for game
    if (it != cArgs.server->getGames().end()) { // game found
        // check if possible to join game
        if (cArgs.server->getGames()[cArgs.commandParam].status == PlayingGame) { // check if game NOT running
            // insert 2nd player into the game
            cArgs.server->getGames()[cArgs.commandParam].player2Socket = cArgs.clientSocket;

            cout << "Server completed connection with 2 players.." << endl;
            cout << "----- The Game Begins -----" << endl;
            memset(temp, 0, DATALEN);

            strcpy(temp, "wait");
            // update second player he is connected
            if (write(cArgs.server->getGames()[cArgs.commandParam].player2Socket, temp, DATALEN) == -1) {
                throw ("Error: sending to player 2");
            }

            int firstClient = CompleteBlackPlayer;
            // send '1' (black) to first player
            if (write(cArgs.server->getGames()[cArgs.commandParam].player1Socket, &firstClient, sizeof(firstClient)) == -1) {
                throw ("Error: sending to player 1");
            }
            int secondClient = CompleteWhitePlayer;
            // send '2' (white) to second player
            if (write(cArgs.server->getGames()[cArgs.commandParam].player2Socket, &secondClient, sizeof(secondClient)) == -1) {
                throw ("Error: sending to player 1");
            }

            // set game running to true
            cArgs.server->getGames()[cArgs.commandParam].status = SecondConnected;

            try {
                // run game
                (*cArgs.server).runOneGame(cArgs.server->getGames()[cArgs.commandParam].player1Socket,
                                           cArgs.server->getGames()[cArgs.commandParam].player2Socket);
            } catch (const char *exception) {
                throw exception;
            }
        } else { // game is running, cannot join this game
            int error = CannotJoinGame;
            if (write(cArgs.server->getGames()[cArgs.commandParam].player1Socket, &error, sizeof(error)) == -1) {
                throw ("Error: sending to player 1");
            }
        }
    } else { // game not found, cannot execute join
        // return error value
        int error = GameNotFound;
        if (write(cArgs.server->getGames()[cArgs.commandParam].player1Socket, &error, sizeof(error)) == -1) {
            throw ("Error: sending to player 1");
        }
    }

}
