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
    cData->clientThread.status = ClientChoice;

    while (cData->clientThread.status == ClientChoice) {
        read(cData->clientThread.clientSocket, buffer, DATALEN);
        commandString = buffer;
        cData->controller->executeCommand(cData->gameManager, cData->clientThread, commandString);
    }
    return NULL;
}

void *clientsListener(void* serverData) {
    pthread_t newThread;
    ClientData clientData;
    bzero((void *) &clientData, sizeof(clientData));
    ServerData *sData = (ServerData *) serverData;
    struct sockaddr_in clientAddress;
    socklen_t client1AddressLen = sizeof((struct sockaddr *) &clientAddress);

    while(true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(sData->server->getServerSocket(), (struct sockaddr *) &clientAddress
                , &client1AddressLen);
        if (clientSocket == -1) {
            throw "Error on accept";
        }
        cout << "Received connection from " << inet_ntoa(clientAddress.sin_addr) << " port " <<
             ntohs(clientAddress.sin_port) << endl;

        clientData.clientThread.clientSocket = clientSocket;
        clientData.clientThread.status = ClientChoice;
        clientData.controller = sData->controller;
        clientData.gameManager = sData->gameManager;

        int rc = pthread_create(&newThread, NULL, handleClient, &clientData);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
        // adding thread
        sData->server->addThread(newThread);
        // remove sockets and statuses from vector of ClientThread
        sData->server->removeSockets(sData->server->getSocketsStatus());
    }
    return NULL;
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
    listen(server->getServerSocket(), MAX_CLIENTS);

    int rc = pthread_create(&mainThread, NULL, clientsListener, &serverData);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
    string input;
    do {
        getline(cin, input);
    } while(strcmp(input.c_str(), "exit") != 0);

    // close all threads
    for (unsigned int i = 0; i < server->getClientsThreads().size(); i++) {
        pthread_cancel(server->getClientsThreads()[i]);
        pthread_join(server->getClientsThreads()[i], NULL);
    }

    // close main thread
    pthread_cancel(mainThread);
    pthread_join(mainThread, NULL);
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

vector<pthread_t> Server::getClientsThreads() {
    return clientsThreads;
}

void Server::addThread(pthread_t thread) {
    this->clientsThreads.push_back(thread);
}

void Server::removeSockets(vector <ClientThread> socketsStatus) {
    vector<ClientThread>::iterator it;
    for (it = socketsStatus.begin(); it != socketsStatus.end(); it++) {
        if (it->status == ClientEndGame) {
            socketsStatus.erase(it);
        }
    }

}

int Server::getServerSocket() {
    return this->serverSock;
}


vector <ClientThread> Server::getSocketsStatus() {
    return this->socketsStatus;
}


void Server::closeClientsConnectios() {
    vector <ClientThread>::iterator it;
    char buffer[DATALEN];
    memset(buffer, '\0', sizeof(buffer));
    strcpy(buffer, "exit");
    for (it = this->socketsStatus.begin(); it != this->socketsStatus.end(); it++) {
        write(it->clientSocket, buffer, DATALEN);
        close(it->clientSocket);
    }
}







