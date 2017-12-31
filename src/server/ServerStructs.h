//
// Created by David Nakash on 30/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_SERVERSTRUCTS_H

#define ADVANCED_PROGRAMMING_O_D_SERVERSTRUCTS_H

#include <string>
class GameManager;
class Controller;
using namespace std;


enum clientStatus {ClientChoice, StartPlaying, Playing, ClientEndGame};

typedef struct ClientThread {
    int clientSocket;
    clientStatus status;
} ClientThread;

typedef struct GameThread {
    ClientThread player1;
    ClientThread player2;

} GameThread;


typedef struct CmdArg {
    GameManager *gameManager;
    Controller *controller;
    ClientThread clientThread;
    string name;
    string param;
} CmdArg;





#endif //ADVANCED_PROGRAMMING_O_D_SERVERSTRUCTS_H
