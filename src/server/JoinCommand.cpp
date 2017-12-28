//
// Created by David Nakash on 24/12/2017.
//


#include "JoinCommand.h"


#define GAME_NAME 0  // name of game chosen by user
#define DATALEN 512


void JoinCommand::execute(CommandArgument *cArgs) {
    char temp[DATALEN];

    // iterator
    map<string, GameThread >::iterator it;
    it = cArgs->getManager()->getGames().find(cArgs->getCommandParam());


    // look for game
    if (it != cArgs->getManager()->getGames().end()) { // game found
        // check if possible to join game
        if (cArgs->getManager()->getGames()[cArgs->getCommandParam()].status == PlayingGame) { // check if game NOT running
            // insert 2nd player into the game
            cArgs->getManager()->getGames()[cArgs->getCommandParam()].player2Socket = cArgs->getClientSocket();

            cout << "Server completed connection with 2 players.." << endl;
            cout << "----- The Game Begins -----" << endl;
            memset(temp, 0, DATALEN);

            strcpy(temp, "wait");
            // update second player he is connected
            if (write(cArgs->getManager()->getGames()[cArgs->getCommandParam()].player2Socket, temp, DATALEN) == -1) {
                throw ("Error: sending to player 2");
            }

            int firstClient = CompleteBlackPlayer;
            // send '1' (black) to first player
            if (write(cArgs->getManager()->getGames()[cArgs->getCommandParam()].player1Socket
                    , &firstClient, sizeof(firstClient)) == -1) {
                throw ("Error: sending to player 1");
            }
            int secondClient = CompleteWhitePlayer;
            // send '2' (white) to second player
            if (write(cArgs->getManager()->getGames()[cArgs->getCommandParam()].player2Socket
                    , &secondClient, sizeof(secondClient)) == -1) {
                throw ("Error: sending to player 1");
            }

            // set game running to true
            cArgs->getManager()->getGames()[cArgs->getCommandParam()].status = SecondConnected;

            try {
                // run game
                GameManager::runOneGame(cArgs->getController()
                        , cArgs->getManager()->getGames()[cArgs->getCommandParam()].player1Socket
                        , cArgs->getManager()->getGames()[cArgs->getCommandParam()].player2Socket);
            } catch (const char *exception) {
                throw exception;
            }
        } else { // game is running, cannot join this game
            int error = CannotJoinGame;
            if (write(cArgs->getManager()->getGames()[cArgs->getCommandParam()].player1Socket
                    , &error, sizeof(error)) == -1) {
                throw ("Error: sending to player 1");
            }
        }
    } else { // game not found, cannot execute join
        // return error value
        int error = GameNotFound;
        if (write(cArgs->getManager()->getGames()[cArgs->getCommandParam()].player1Socket
                , &error, sizeof(error)) == -1) {
            throw ("Error: sending to player 1");
        }
    }

}
