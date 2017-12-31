//
// Created by David Nakash on 30/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_SERVERSTRUCTS_H

#define ADVANCED_PROGRAMMING_O_D_SERVERSTRUCTS_H

#include <string>
class GameManager;
class Controller;
using namespace std;

typedef struct CmdArg {
    GameManager *gameManager;
    Controller *controller;
    ClientThread clientThread;
    string name;
    string param;
} CmdArg;

enum gameStatus {FirstConnected, SecondConnected, PlayingGame, GameEnded};

enum clientStatus {clientChoice, clientPlaying, clientEndGame};

typedef struct ClientThread {
    int clientSocket;
    clientStatus status;
} ClientThread;

typedef struct GameThread {
    int player1Socket;
    int player2Socket;
    gameStatus status;
} GameThread;





#endif //ADVANCED_PROGRAMMING_O_D_SERVERSTRUCTS_H
