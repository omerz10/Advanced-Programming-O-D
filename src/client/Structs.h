//
// Created by David Nakash on 28/11/2017.
//


#ifndef PROJECT_UPDATED_STRUCTS_H
#define PROJECT_UPDATED_STRUCTS_H

#include "Board.h"
#include "../server/Server.h"
typedef enum Status {ZeroConnected, FirstConnected, SecondConnected, PlayingGame};
/**
 Struct that holds the possible moves (in order to make it easier for the programmer...).
 */

typedef struct PossibleMove {

    vector<vector<Cell> > changeableCells;

    vector<Cell> moves;

    bool possible;
};

typedef struct ServerDetails {
    string serverIP;
    int serverPort;
};


typedef struct CommandArgument {
    Server *server;
    string commandName;
    string commandParam;
    Status status;
    int clientSocket;
};

typedef struct GameThread {
    int player1Socket;
    int player2Socket;
    Status status;
};


#endif //PROJECT_UPDATED_STRUCTS_H
