//
// Created by omerz on 01/12/17.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H


class Controller;

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <poll.h>
#include <map>

#include "Command.h"

#include "Controller.h"
#include "../client/Structs.h"

using namespace std;

class Server {

public:

    int port;
    int serverSock;
    map < string, struct GameThread > games; // map of games according to game name (real member)
    Controller *controller;


    /*
     * construct a server
     */
    Server(int port);

    /*
     * initialize server
     */
    void initialize();

    void runServer();

    void* executeCommand(void *cArgs);

    map < string, GameThread > getGames();


    void runOneGame(int client1Sock, int client2Sock);

    bool isClientClosed(int clientNumber);

    bool pollClient(int currentClient, int otherClient);

    static void* globalExecuteCommand(void *cArgs);
};




#endif //EX4_SERVER_H
