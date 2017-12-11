//
// Created by omerz on 01/12/17.
//

#include "Server.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <sstream>


#define MAX_CLIENTS 2
#define DATALEN 1024



Server::Server(int port): port(port) {}

void Server::start() {
    // init server socket
    this->serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSock == -1) {
        throw "Error: opening socket";
    }
    // init server ip address
    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "error binding to socket";
    }
    cout << "start listening to clients" << endl;
    listen(serverSock, MAX_CLIENTS);
    //socklen_t sockLen;
    struct sockaddr_in clientAddress1;
    struct sockaddr_in clientAddress2;
    socklen_t client1AddressLen1 = sizeof((struct sockaddr*) &clientAddress1);
    socklen_t client1AddressLen2 = sizeof((struct sockaddr*) &clientAddress2);

    while (true) {
        int client1Sock = accept(serverSock, (struct sockaddr *) &clientAddress1, &client1AddressLen1);
        if (client1Sock == -1) {
            throw "Error: accepting client";
        }
        cout << "Server: got connection from " << inet_ntoa(clientAddress1.sin_addr) << " port " <<
             ntohs(clientAddress1.sin_port) << endl;

        // update first player he is connected
        if (write(client1Sock, "join", sizeof("join")) == -1) {
            throw ("Error: sending to player 1");
        }
        int client2Sock = accept(serverSock, (struct sockaddr *) &clientAddress2, &client1AddressLen2);
        if (client2Sock == -1) {
            throw "Error: accepting client";
        }
        cout << "Server: got connection from " << inet_ntoa(clientAddress2.sin_addr) << " port " <<
             ntohs(clientAddress2.sin_port) << endl;
        cout << "Server complete connection with 2 players" << endl;

        // update second player he is connected
        if (write(client2Sock, "wait", sizeof("wait")) == -1) {
            throw ("Error: sending to player 2");
        }

        int firstClient = 1;
        // send '1' (black) to first player
        if (write(client1Sock, &firstClient, sizeof(firstClient)) == -1) {
            throw ("Error: sending to player 1");
        }
        int secondClient = 2;
        // send '2' (white) to second player
        if (write(client2Sock, &secondClient, sizeof(secondClient)) == -1) {
            throw ("Error: sending to player 1");
        }
        this->handleClients(client1Sock, client2Sock);

    }
}



void Server::handleClients(int client1Sock, int client2Sock) {
    // init buffer for getting msg from player
    char buffer[DATALEN];
    char temp[DATALEN];
    memset(&buffer, 0, sizeof(buffer));
    // messages from each player
    ssize_t blackMsg, whiteMsg;
     bool isFirstClient = true;
    bool isSecondClient = true;
    // send & receive from players until gets "isEnd" message
    while(true) {

        // send and receive from player 'black'
        blackMsg = read(client1Sock, buffer, DATALEN);
        if (blackMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (blackMsg == -1) {
            throw "Error: connect to black player ";
        }

        // send to white player that black didn't play a move
        if (strcmp(buffer, "NoMove") == 0) {
            write(client2Sock, "NoMove", sizeof("NoMove"));
        }
        //
        else if (strcmp(buffer, "End") == 0) {
            write(client2Sock, "End", sizeof("End"));
            break;
        }
        
        write(client2Sock, buffer, DATALEN);
        strcpy(buffer, "wait");
        write(client1Sock, buffer, DATALEN);
        // send and receive from player 'black'
        whiteMsg = read(client2Sock, buffer, DATALEN);
        if (whiteMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (whiteMsg == -1) {
            throw "Error: connect to black player ";
        }

        // send to white player that black didn't play a move
        if (strcmp(buffer, "NoMove") == 0) {
            write(client1Sock, "NoMove", sizeof("NoMove"));
        }
            //
        else if (strcmp(buffer, "End") == 0) {
            write(client1Sock, "End", sizeof("End"));
            break;
        }
        
        write(client1Sock, buffer, DATALEN);
        strcpy(buffer, "wait");
        write(client2Sock, buffer, DATALEN);

    } // end of while
    close(client1Sock);
    close(client2Sock);
}

