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
    int client1Sock;
    int client2Sock;
    struct sockaddr_in client1Address;
    struct sockaddr_in client2Address;
    unsigned int sockLen;


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
     * send data to a client
     */
    int handleClients();

    /*
     * stop connection with all clients
     */
    void stop();

};


#endif //EX4_SERVER_H
