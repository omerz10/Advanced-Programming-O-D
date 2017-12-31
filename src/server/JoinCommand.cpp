//
// Created by David Nakash on 24/12/2017.
//


#include "JoinCommand.h"


#define DATALEN 512


void JoinCommand::execute(CmdArg *cArgs) {
    char temp[DATALEN];

    // iterator
    map<string, GameThread >::iterator it;
    it = cArgs->gameManager->getGames().find(cArgs->param);


    // look for game
    if (it != cArgs->gameManager->getGames().end()) { // game found
        // check if possible to join game
        if (cArgs->gameManager->getGames()[cArgs->param].status == PlayingGame) { // check if game NOT running
            // insert 2nd player into the game
            cArgs->gameManager->getGames()[cArgs->param].player2Socket = cArgs->clientThread.clientSocket;

            cout << "Server completed connection with 2 players.." << endl;
            cout << "----- The Game Begins -----" << endl;
            memset(temp, 0, DATALEN);

            strcpy(temp, "join");
            // update second player he is connected
            if (write(cArgs->gameManager->getGames()[cArgs->param].player2Socket, temp, DATALEN) == -1) {
                throw ("Error: sending to player 2");
            }

            int firstClient = CompleteBlackPlayer;
            // send '1' (black) to first player
            if (write(cArgs->gameManager->getGames()[cArgs->param].player1Socket
                    , &firstClient, sizeof(firstClient)) == -1) {
                throw ("Error: sending to player 1");
            }
            int secondClient = CompleteWhitePlayer;
            // send '2' (white) to second player
            if (write(cArgs->gameManager->getGames()[cArgs->param].player2Socket
                    , &secondClient, sizeof(secondClient)) == -1) {
                throw ("Error: sending to player 2");
            }

            // set game running to true
            cArgs->gameManager->getGames()[cArgs->param].status = SecondConnected;

            try {
                // run game
                cArgs->gameManager->runOneGame(cArgs->param, cArgs->controller);
            } catch (const char *exception) {
                throw exception;
            }
        } else { // game is running, cannot join this game
            int error = CannotJoinGame;
            if (write(cArgs->gameManager->getGames()[cArgs->param].player1Socket
                    , &error, sizeof(error)) == -1) {
                throw ("Error: sending to player 1");
            }
        }
    } else { // game not found, cannot execute join
        // return error value
        int error = GameNotFound;
        if (write(cArgs->gameManager->getGames()[cArgs->param].player1Socket
                , &error, sizeof(error)) == -1) {
            throw ("Error: sending to player 1");
        }
    }

}

