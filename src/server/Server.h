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
#include "../client/Structs.h"
#include "Controller.h"

using namespace std;

class Server {

private:

    int port;
    int serverSock;
    map < string, GameThread > games; // map of games according to game name (real member)
    Controller *controller;

public:


    /*
     * construct a server
     */
    Server(int port);

    /*
     * initialize server
     */
    void initialize();


    void listener();
    /*
     *  second player connecting to the server
     */
    void join(string gameName, int clientSocket);

    map < string, GameThread > getGames();

    /*
     * send data to a client
     */
    void handleClients(int c1, int c2);

    bool pollClient(int currentClient, int otherClient);

    bool isClientClosed(int clientNumber);
};


#endif //EX4_SERVER_H
