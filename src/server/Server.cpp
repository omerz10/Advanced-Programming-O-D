//
// Created by omerz on 01/12/17.
//

#include <cstdlib>
#include "Server.h"


#define MAX_CLIENTS 1000
#define DATALEN 512


struct ClientData {
    GameManager *gameManager;
    Controller *controller;
    ClientThread clientThread;
};


struct ServerData {
    Server *server;
    GameManager *gameManager;
    Controller *controller;
};



void *handleClient(void *data) {
    ClientData *cData = (ClientData *)data;

    // get command from client
    char buffer[DATALEN];
    string commandString;

    bool flag = true; //TODO: change for enums for one client (choose / waiting / playing)

    while (cData->clientThread.status != clientEndGame) {
        read(cData->clientThread.clientSocket, buffer, DATALEN);
        strcpy(commandString, buffer);
        if (cData->clientThread.status != clientChoice) {
            break;
        }
        cData->controller->executeCommand(cData->gameManager, cData->clientThread, commandString);
    }
}

void *clientsListener(void* serverData) {
    pthread_t newThread;
    ClientData clientData;
    ServerData *sData = (ServerData *) serverData;
    struct sockaddr_in clientAddress;
    socklen_t client1AddressLen = sizeof((struct sockaddr *) &clientAddress);

    while(true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(sData->server->serverSock, (struct sockaddr *) &clientAddress, &client1AddressLen);
        if (clientSocket == -1) {
            throw "Error on accept";
        }
        cout << "Received connection from " << inet_ntoa(clientAddress.sin_addr) << " port " <<
             ntohs(clientAddress.sin_port) << endl;

        clientData.clientThread.clientSocket = clientSocket;
        clientData.clientThread.status = clientChoice;
        clientData.controller = sData->controller;
        clientData.gameManager = sData->gameManager;

        int rc = pthread_create(&newThread, NULL, handleClient, &clientData);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
    }

}

/*
 * main thread listener
 */
void mainThreadListener(Server *server, GameManager *gM, Controller *controller) {
    pthread_t mainThread;
    char consoleBuffer[DATALEN];
    ServerData serverData;
    serverData.server = server;
    serverData.gameManager = gM;
    serverData.controller = controller;

    // get input from user
    cin >> consoleBuffer;
    cout << "Listening to clients.." << endl;
    listen(server->serverSock, MAX_CLIENTS);

    int rc = pthread_create(&mainThread, NULL, clientsListener, &serverData);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }

    string input;
    do {
        getline(cin, input);
    } while(strcmp(input.c_str(), "exit") != 0);
}






Server::Server(int port, GameManager *gameManager, Controller *controller): port(port)
        , gameManager(gameManager), controller(controller) {}


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


void Server::runServer() {
    mainThreadListener(this, this->gameManager, this->controller);
}







