//
// Created by omerz on 01/12/17.
//

#include "Server.h"
#include "../src/Cell.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <vector>
#include <sstream>


#define MAX_CLIENTS 2
#define BLACK 0
#define WHITE 1

Server::Server(int port): port(port) {
    this->connectToAllPlayers = false;
    start();
}


void Server::initSocketsAndIPList() {
    // init server socket
    this->serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSock == -1) {
        throw "Error: opening socket";
    }
    // init clients sockets and ip's
    for (int i = 0; i < MAX_CLIENTS; i++) {
        this->clientsSock[i] = 0;
        bzero((void *)&ipList, sizeof(ipList[i]));
    }

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
    int i = 0;
    this->initSocketsAndIPList();
    this->bindSocket();
    bzero((void *)&sockLen, sizeof(sockLen));
    // check if server is listening to all clients
    if (listen(this->serverSock, MAX_CLIENTS) == -1) {
        throw "Error: listening to a socket";
    }
    // wait for second player to connect
    if (!this->connectToAllPlayers) {
        while (i < MAX_CLIENTS) {
            this->clientsSock[i] = accept(serverSock,(struct sockaddr *) &ipList[i],(socklen_t*)&sockLen);
            if (this->clientsSock[i] == -1) {
                throw "Error: accepting client";
            }
            printf("Server: got connection from %s port %d\n", inet_ntoa(ipList[i].sin_addr), ntohs(ipList[i].sin_port));
            i++;
        }
        this->connectToAllPlayers = true;
        printf("Server complete connection with 2 players");
    }
    char buff = '1', buff2 = '2';
    // send '1' (black) to first player
    if (send(this->clientsSock[BLACK], &buff, sizeof(buff), 0) == -1) {
        throw("Error: sending to player 1");
    }
    // send '2' (white) to second player
    if (send(this->clientsSock[WHITE], &buff2, sizeof(buff), 0) == -1) {
        throw("Error: sending to player 2");
    }
}



int Server::handleClients() {
    // init buffer for getting msg from player
    char buffer[4096];
    memset(&buffer, 0, sizeof(buffer));
    // messages from each player
    ssize_t blackMsg, whiteMsg;
    // future move from each player
    Cell newCell;

    // send & receive from playyers until gets "isEnd" message
    while(true) {

        // send and receive from player 'black'
        blackMsg = recv(this->clientsSock[BLACK], buffer, sizeof(buffer),0);
        if (blackMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (blackMsg == -1) {
            throw "Error: connect to black player ";
        }

        // send to white player that black didn't play a move
        if (strstr(buffer, "NoMove")) {
            send(this->clientsSock[WHITE], "NoMove", sizeof(buffer), 0);
        }
        //
        else if (strstr(buffer, "End")) {
            break;
        }
        // black played a move
        else {
            newCell = this->parseToCell(buffer);
            send(this->clientsSock[WHITE], buffer, sizeof(buffer), 0);
        }

        // send and receive from player 'white'
        whiteMsg = recv(this->clientsSock[WHITE], buffer, sizeof(buffer), 0);
        // server get message from player 'black'
        if (whiteMsg == 0) {
            throw "Error: connection with white player is closed";
        }
        if (whiteMsg == -1) {
            throw "Error: connect to white player ";
        }
        // no move for white
        if (strstr(buffer, "NoMove")) {
            send(this->clientsSock[WHITE], "NoMove", sizeof(buffer), 0);
        }
        else if (strstr(buffer, "End")) {
            break;
        }
        // white played a move
        else {
            newCell = this->parseToCell(buffer);
            send(this->clientsSock[BLACK], buffer, sizeof(buffer), 0);
        }
    }



}

Cell parseToCell(char *buffer) {
    stringstream str;
    int i, j;
    str << strtok (buffer, ",");
    str >> i;
    str << strtok (buffer, "\n");
    str >> j;
    Cell cell(i, j);
    return cell;
}
