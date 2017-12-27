//
// Created by David Nakash on 28/11/2017.
//


#ifndef PROJECT_UPDATED_STRUCTS_H
#define PROJECT_UPDATED_STRUCTS_H

#include "Board.h"
#include "../server/Server.h"
class Server;

enum Status {ZeroConnected, FirstConnected, SecondConnected, PlayingGame};

enum Errors {CompleteBlackPlayer = 1, CompleteWhitePlayer = 2, CannotJoinGame = -1, GameNotFound = -2};

/**
 Struct that holds the possible moves (in order to make it easier for the programmer...).
 */

typedef struct PossibleMove {

    vector<vector<Cell> > changeableCells;

    vector<Cell> moves;

    bool possible;
} PossibleMove;

typedef struct ServerDetails {
    string serverIP;
    int serverPort;
} ServerDetails;


typedef struct CommandArgument {
    Server *server;
    string commandName;
    string commandParam;
    Status status;
    int clientSocket;
} CommandArgument;

typedef struct GameThread {
    int player1Socket;
    int player2Socket;
    Status status;
} GameThread;


#endif //PROJECT_UPDATED_STRUCTS_H
