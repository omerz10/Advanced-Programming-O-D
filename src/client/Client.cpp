//
// Created by omerz on 07/12/17.
//

#include <arpa/inet.h>
#include <netdb.h>
#include <cstdlib>
#include "Client.h"

#define DATALEN 512

using namespace std;

Client::Client(const char *serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0) {}


void Client::connectToServer() {
    // create a socket
    this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error: opening socket";
    }

    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(this->serverIP, &address)) {
        throw "Can't parse IP address";
    }

    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *)&address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *)&serverAddress.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    // htons converts values between host and network byte
    //orders
    serverAddress.sin_port = htons(this->serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;

}

void Client::waitingForOtherPlayer() {
    char buff[DATALEN];

    if (read(clientSocket, buff, DATALEN) == -1) {
        throw "Error reading result from socket";
    }
    if (strcmp(buff, "start") == 0) {
        cout << "Waiting for other player to join..." << endl;
    }
    if(strcmp(buff,"join") == 0) {
        cout << "Waiting for other player's move..." << endl;
    }
}


int Client::getClientSock() {
    return this->clientSocket;
}

void Client::getMessage(char *buffer) {
    char temp[DATALEN];
    memset(temp, 0, DATALEN);
    
    if (read(clientSocket, temp, DATALEN) == -1) {
        throw "Error reading from server";
    }
    strcpy(buffer, temp);
}

void Client::sendExercise(char *buffer) {
    char temp[DATALEN];
    strcpy(temp, buffer);
    if (write(clientSocket, &temp, DATALEN) == -1) {
        throw "Error: writing buffer";
    }
}

void Client::setID(int id) {
    this->id = id;

}

int Client::getID() {
    return this->id;
}

