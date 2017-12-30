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
public:
    map < string, GameThread > games; // map of games according to game name (real member)
    map < string, GameThread > getGames();

    void runOneGame(Controller* controller, int client1Sock, int client2Sock);

    bool isClientClosed(int clientNumber);

    bool pollClient(int currentClient, int otherClient);

};


#endif //ADVANCED_PROGRAMMING_O_D_GAMEMANEGER_H
