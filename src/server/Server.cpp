//
// Created by omerz on 01/12/17.
//

#include "Server.h"
#include "StartCommand.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <sstream>


#define MAX_CLIENTS 100
#define DATALEN 512



Server::Server(int port): port(port) {
}


void Server::initialize() {
    char temp[DATALEN];

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

}

void Server::listener() {
    string buffer;
    struct sockaddr_in clientAddress;
    socklen_t client1AddressLen = sizeof((struct sockaddr*) &clientAddress);

    cout << "Listening to clients.." << endl;
    listen(this->serverSock, MAX_CLIENTS);

    while (strcmp(buffer, "exit")) {
        string buff;
        char temp[DATALEN];
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(this->serverSock, (struct sockaddr *)&clientAddress, &client1AddressLen);
        if (clientSocket == -1) {
            throw "Error on accept";
        }
        cout << "Received connection from " << inet_ntoa(clientAddress.sin_addr) << " port " <<
             ntohs(clientAddress.sin_port) << endl;


        // open a thread

        {
            ssize_t msg;
            msg = read(clientSocket, temp, DATALEN); // socket comes from outside
            strcpy(buff, temp);
            this->controller->executeCommand(this, buff, clientSocket);
            // close thread
        }

    }


void Server::join(string gameName, int clientSocket) {

    this->games[gameName].player2Socket = clientSocket;

    cout << "Received connection from " << inet_ntoa(clientAddress2.sin_addr) << " port " <<
         ntohs(clientAddress2.sin_port) << endl;
    cout << "Server completed connection with 2 players.." << endl;
    cout << "----- The Game Begins -----" << endl;
    memset(temp, 0, DATALEN);
    strcpy(temp, "wait");
    // update second player he is connected
    if (write(client2Sock, temp, DATALEN) == -1) {
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

    try {
        this->handleClients(client1Sock, client2Sock);
    } catch (const char *exception) {
        throw exception;
    }
}


void Server::handleClients(int client1Sock, int client2Sock) {
    // init buffer for getting msg from player
    char buffer[DATALEN];
    char temp[DATALEN];
    // messages from each player
    ssize_t blackMsg, whiteMsg;

    // send & receive from players until gets "isEnd" message
    while(true) {
        // read from player 1's client
        memset(buffer, 0, DATALEN);
        blackMsg = read(client1Sock, buffer, DATALEN);



        // check input
        if (blackMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (blackMsg == -1) {
            throw "Error: connect to black player ";
        }

        // send to 2nd player that black didn't play a move
        if (strcmp(buffer, "NoMove") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "NoMove");
            write(client2Sock, &temp, DATALEN);
        } else if (strcmp(buffer, "End") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "End");
            write(client2Sock, &temp, DATALEN);
            break;
        }
        memset(temp, 0, DATALEN);
        strcpy(temp, buffer);

        // check if connection still alive with first client
        if (pollClient(client1Sock, client2Sock)) {
            break;
        }

        write(client2Sock, &temp, DATALEN);



        // read from player 2's client
        memset(temp, 0, DATALEN);
        whiteMsg = read(client2Sock, temp, DATALEN);
        strcpy(buffer, temp);

        if (whiteMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (whiteMsg == -1) {
            throw "Error: connect to black player ";
        }

        // send to white player that black didn't play a move
        if (strcmp(buffer, "NoMove") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "NoMove");
            write(client1Sock, &temp, DATALEN);
        } else if (strcmp(buffer, "End") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "End");
            write(client1Sock, &temp, DATALEN);
            break;
        }

        // check if connection still alive
        if (pollClient(client2Sock, client1Sock)) {
            break;
        }

        write(client1Sock, &buffer, DATALEN);
    } // end of while

    // close client sockets
    close(client1Sock);
    close(client2Sock);
}

bool Server::isClientClosed(int clientNumber) {
    pollfd pfd;
    pfd.fd = clientNumber;
    pfd.events = POLLIN | POLLHUP | POLLRDNORM;
    pfd.revents = 0;
    if (pfd.revents == 0) {
        // call poll every 500 miliseconds
        if (poll(&pfd, 1, 500) > 0) {
            // if result is bigger than 0, it means there is either data
            // on the socket, or played closed his window(closed socket)
            char buff[32];
            if (recv(clientNumber, buff, sizeof(buff), MSG_PEEK | MSG_DONTWAIT) == 0) {
                // if recv function returns zero it means the connection has been closed.
                return true;
            }
        }
    }
    return false;
}

bool Server::pollClient(int currentClient, int otherClient) {
    char temp[DATALEN];
    // check for lost connection
    if (isClientClosed(otherClient)) {
        cout << "Other player has disconnected from the game, restarting.." << endl;
        memset(temp, 0, DATALEN);
        strcpy(temp, "End");
        write(currentClient, &temp, DATALEN);
        return true;
    }
    return false;
}

map<string, GameThread> Server::getGames() {
    return map<string, GameThread>();
}






    //handleClient(clientSocket);
    // Close communication with the client
    //close(clientSocket);

}

