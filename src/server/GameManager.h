//
// Created by David Nakash on 27/12/2017.
//

#ifndef ADVANCED_PROGRAMMING_O_D_GAMEMANEGER_H
#define ADVANCED_PROGRAMMING_O_D_GAMEMANEGER_H

using namespace std;

#include <iostream>
#include <string>
#include <cstring>
#include <zconf.h>
#include <poll.h>
#include <sys/socket.h>
#include "ServerStructs.h"

class GameManager {
private:
    map < string, GameThread > games; // map of games according to game name (real member)
public:
    map < string, GameThread > getGames();



    static void runOneGame(int client1Sock, int client2Sock);

    static bool isClientClosed(int clientNumber);

    static bool pollClient(int currentClient, int otherClient);

};


#endif //ADVANCED_PROGRAMMING_O_D_GAMEMANEGER_H
