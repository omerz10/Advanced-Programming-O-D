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


using namespace std;

class Server {

private:

    int port;
    int serverSock;
    struct sockaddr_in serverAddress;
    int clientsSock[];
    struct sockaddr_in ipList[];
    unsigned int sockLen;
    bool connectToAllPlayers;


public:

    /*
     * construct a server
     */
    Server(int port);

    /*
     * create a sockets and ip's of all clients
     */
    void initSocketsAndIPList();

    /*
     * operate bind with client
     */
    void bindSocket();

    /*
     * initialize a server by its all functions
     */
    void start();

    /*
     * receiving data from a client
     */
    string receiveFromClient();

    /*
     * send data to a client
     */
    int handleClients();

    //Cell parseToCell(char *buffer);

};


#endif //EX4_SERVER_H
