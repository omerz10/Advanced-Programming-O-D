//
// Created by omerz on 07/12/17.
//

#include <arpa/inet.h>
#include <netdb.h>
#include "Client.h"

#define DATALEN 4096

using namespace std;

Client::Client(const char *serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0) {}


void Client::connectToServer() {
    // create a socket
    this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error: opening socket";
    }

    //struct addr_in newAddress = (struct addr_in) this->serverIP;

    // Create a structure for the server address
    memset(&this->serverIP, 0, sizeof(this->serverIP));
    this->serverIP.sin_family = AF_INET;
    this->serverIP.sin_addr.s_addr = inet_addr(serverIP.c_str());
    this->serverIP.sin_port = htons(serverPort);


    if (connect(clientSocket, (struct sockaddr*)&serverIP, sizeof(serverIP)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;
}


void Client::waitingForOtherPlayer() {
    char buff[DATALEN];
    memset(&buff, 0, sizeof(buff));

    if (read(clientSocket, &buff, sizeof(buff) == -1)) {
        throw "Error reading result from socket";
    }
    if (!strcmp(buff, "join")) {
        cout << "Waiting for other player to join..." << endl;
    }
    if (!strcmp(buff, "wait")){
        cout << "Waiting for player's move..." << endl;
    }
}


int* Client::getClientSock() {
    return &this->clientSocket;
}

void Client::getMessage(char *buffer) {
    //char buffer[DATALEN];
    read(this->clientSocket, buffer, sizeof(buffer));
}

void Client::sendExercise(const char *buffer) {
    if (write(clientSocket, &buffer, sizeof(buffer) == -1)) {
        throw "Erro: writing buffer";
    }
}

