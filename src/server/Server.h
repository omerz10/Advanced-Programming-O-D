//
// Created by omerz on 01/12/17.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <poll.h>


using namespace std;

class Server {

private:

    int port;
    int serverSock;

public:

    /*
     * construct a server
     */
    Server(int port);

    /*
     * initialize a server by its all functions
     */
    void start();

    /*
     * send data to a client
     */
    void handleClients(int c1, int c2);

    bool pollClient(int currentClient, int otherClient);

    bool isClientClosed(int clientNumber);
};


#endif //EX4_SERVER_H
