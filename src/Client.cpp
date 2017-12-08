//
// Created by omerz on 07/12/17.
//

#include <arpa/inet.h>
#include <netdb.h>
#include "Client.h"


using namespace std;

Client::Client(const char *serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0) {


}

void Client::connectToServer() {
    // create a socket
    this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error: opening socket";
    }
    struct in_addr address;
    // Convert the ip string to a network address
    if (!inet_aton(serverIP, &address)) {
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
    memcpy((char *)&serverAddress.sin_addr.s_addr, server->h_addr, (size_t)server->h_length);
    serverAddress.sin_port = htons(serverPort);

    if (connect(clientSocket, (struct sockaddr*)&serverIP, sizeof(serverIP)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;
}


void playLocalTurn(char* buffer) {
    int a;

    // send to server

}
