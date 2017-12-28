//
// Created by David Nakash on 28/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_SERVERSTRUCTS_H
#define ADVANCED_PROGRAMMING_O_D_SERVERSTRUCTS_H


#include <string>

enum clientStatus {};

enum gameStatus {ZeroConnected, FirstConnected, SecondConnected, PlayingGame};

enum Errors {CompleteBlackPlayer = 1, CompleteWhitePlayer = 2, CannotJoinGame = -1, GameNotFound = -2};


typedef struct GameThread {
    int player1Socket;
    int player2Socket;
    gameStatus status;
} GameThread;




#endif //ADVANCED_PROGRAMMING_O_D_SERVERSTRUCTS_H
