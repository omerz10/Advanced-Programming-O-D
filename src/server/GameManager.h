//
// Created by David Nakash on 27/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_GAMEMANAGER_H
#define ADVANCED_PROGRAMMING_O_D_GAMEMANAGER_H
#include <iostream>
#include <string>
#include <cstring>
#include <zconf.h>
#include <poll.h>
#include <sys/socket.h>
#include <map>
#include "ServerStructs.h"
#include <map>
#include "Controller.h"
using namespace std;

class GameManager {

private:

    map < string, GameThread > games;

public:

    map < string, GameThread > getGames();

    void runOneGame(string gameName, Controller* controller);

    bool isClientClosed(int clientNumber);

    bool pollClient(int currentClient, int otherClient);

    CmdArg parseMessage(string msg, Controller *controller, int clientSocket);

    void deleteGame(string gameName);

    void addNewGame(string gameName, ClientThread clientThread);

};


#endif //ADVANCED_PROGRAMMING_O_D_GAMEMANEGER_H
