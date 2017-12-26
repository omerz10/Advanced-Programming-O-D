//
// Created by David Nakash on 24/12/2017.
//

#include <map>
#include <arpa/inet.h>
#include "JoinCommand.h"
#include "../client/Structs.h"
#define GAME_NAME 0  // name of game chosen by user
#define DATALEN 512




void JoinCommand::execute(Server *server, vector<string> args, int clientSocket) {
    char temp[DATALEN];

    // iterator
    std::map<string, GameThread >::iterator it;
    it = server->getGames().find(args[GAME_NAME]);

    // look for game
    if (it != server->getGames().end()) { // game found
        // check if possible to join game
        if (!server->getGames()[args[GAME_NAME]].PlayingGame) { // check if game NOT running
            // insert 2nd player into the game
            server->getGames()[args[GAME_NAME]].player2Socket = clientSocket;

            cout << "Server completed connection with 2 players.." << endl;
            cout << "----- The Game Begins -----" << endl;
            memset(temp, 0, DATALEN);

            strcpy(temp, "wait");
            // update second player he is connected
            if (write(server->getGames()[args[GAME_NAME]].player2Socket, temp, DATALEN) == -1) {
                throw ("Error: sending to player 2");
            }

            int firstClient = 1;
            // send '1' (black) to first player
            if (write(server->getGames()[args[GAME_NAME]].player1Socket, &firstClient, sizeof(firstClient)) == -1) {
                throw ("Error: sending to player 1");
            }
            int secondClient = 2;
            // send '2' (white) to second player
            if (write(server->getGames()[args[GAME_NAME]].player2Socket, &secondClient, sizeof(secondClient)) == -1) {
                throw ("Error: sending to player 1");
            }

            // set game running to true
            server->getGames()[args[GAME_NAME]].SecondConnected;


            try {
                //server->handleClients(gameMap[stringV[ARGUMENT]].player1Socket, clientSocket);
            } catch (const char *exception) {
                throw exception;
            }



        } else { // game is running, cannot join this game
            //return -1;
        }
    } else { // game not found, cannot execute join
        // return error value
        //return -1;
    }
    // function output
    //return 0;
}
