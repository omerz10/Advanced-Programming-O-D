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
#define DATALEN 4096



Server::Server(int port): port(port) {
    this->isFirstClient = true;
}


void Server::initSocketsAndIPList() {
    // init server socket
    this->serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSock == -1) {
        throw "Error: opening socket";
    }
    // init clients sockets and ip's
    this->client1Sock = 0;
    this->client2Sock = 0;

    // init server ip address
    bzero((void *)&serverAddress, sizeof(serverAddress));
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    this->serverAddress.sin_port = htons(port);

}

void Server::bindSocket() {
    if (bind(serverSock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "error binding to socket";
    }
}

void Server::start() {
    this->initSocketsAndIPList();
    this->bindSocket();
    bzero((void *)&sockLen, sizeof(sockLen));
    // check if server is listening to all clients
    if (listen(this->serverSock, MAX_CLIENTS) == -1) {
        throw "Error: listening to a socket";
    }
    cout << "start listening to clients" << endl;
    // wait for second player to connect

    if (isFirstClient) {
        // connect to first player
        this->client1Sock = accept(serverSock,(struct sockaddr *) &client1Address,(socklen_t*)&sockLen);
        if (this->client1Sock == -1) {
            throw "Error: accepting client";
        }
        cout << "Server: got connection from %s port %d\n"<< inet_ntoa(client1Address.sin_addr)<<
             ntohs(client1Address.sin_port) << endl;
        // update first player he is connected
        string buff = "join";
        if (write(this->client1Sock, &buff , sizeof(buff)) == -1) {
            throw("Error: sending to player 1");
        }
        isFirstClient = false;
    }
    // connect to second player
    else {
        this->client2Sock = accept(serverSock,(struct sockaddr *) &client2Address,(socklen_t*)&sockLen);
        if (this->client2Sock == -1) {
            throw "Error: accepting client";
        }
        cout << "Server: got connection from %s port %d\n"<< inet_ntoa(client2Address.sin_addr)<<
             ntohs(client2Address.sin_port) << endl;
        cout << "Server complete connection with 2 players" << endl;
        char buff1 = '1';
        // send '1' (black) to first player
        if (write(this->client1Sock, &buff1, sizeof(buff1)) == -1) {
            throw("Error: sending to player 1");
        }
        char buff2 = '2';
        // send '2' (white) to second player
        if (write(this->client2Sock, &buff2, sizeof(buff2)) == -1) {
            throw("Error: sending to player 1");
        }

        // start read and write actions with both player
        this->isFirstClient = true;
        this->handleClients();
    }
}



int Server::handleClients() {
    // init buffer for getting msg from player
    char buffer[DATALEN];
    memset(&buffer, 0, sizeof(buffer));
    // messages from each player
    ssize_t blackMsg, whiteMsg;
    // future move from each player

    // send & receive from playyers until gets "isEnd" message
    while(true) {

        if (this->isFirstClient) {
            write(this->client1Sock, "first", sizeof("first"));
            this->isFirstClient = false;
        }
        // send and receive from player 'black'
        blackMsg = read(this->client1Sock, buffer, sizeof(buffer));
        if (blackMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (blackMsg == -1) {
            throw "Error: connect to black player ";
        }

        // send to white player that black didn't play a move
        if (strstr(buffer, "NoMove")) {
            write(this->client2Sock, "NoMove", sizeof("NoMove"));
        }
        //
        else if (strstr(buffer, "End")) {
            write(this->client2Sock, "End", sizeof("End"));
            break;
        }
        // black played a move
        else {
            write(this->client1Sock, "wait", sizeof("wait"));
            write(this->client2Sock, buffer, sizeof(buffer));
        }

        // send and receive from player 'white'
        whiteMsg = read(this->client2Sock, buffer, sizeof(buffer));
        // server get message from player 'black'
        if (whiteMsg == 0) {
            throw "Error: connection with white player is closed";
        }
        if (whiteMsg == -1) {
            throw "Error: connect to white player ";
        }
        // no move for white
        if (strstr(buffer, "NoMove")) {
            write(this->client1Sock, "NoMove", sizeof("NoMove"));
        }
        else if (strstr(buffer, "End")) {
            write(this->client1Sock, "End", sizeof("End"));
            break;
        }
        // white played a move
        else {
            write(this->client2Sock, "wait", sizeof("wait"));
            write(this->client1Sock, buffer, sizeof(buffer));
        }
    } // end of while
    stop();
}

void Server::stop() {
    close(client1Sock);
    close(client2Sock);
}
