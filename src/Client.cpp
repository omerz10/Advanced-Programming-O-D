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

    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(this->serverIP, &address)) {
        throw "Can't parse IP address";
    }

    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *)&address, sizeof
            address, AF_INET);
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
    if (connect(clientSocket, (struct sockaddr
    *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;

}

void Client::waitingForOtherPlayer() {
    char buff[DATALEN];
    memset(&buff, 0, sizeof(buff));

    if (read(clientSocket, &buff, static_cast<size_t>(sizeof(buff) == -1))) {
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

