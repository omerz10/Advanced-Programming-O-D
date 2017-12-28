//
// Created by omerz on 01/12/17.
//

#include "Server.h"


#define MAX_CLIENTS 100
#define DATALEN 512


/*
 * main thread listener
 */
void mainThreadListener(Server *server, GameManager *gameManager, Controller *controller) {
    pthread_t gameThread;
    char consoleBuffer[DATALEN];
    char buffer[DATALEN];
    string commandParam, commandName;
    struct sockaddr_in clientAddress;

    // get input from user
    cin >> consoleBuffer;

    socklen_t client1AddressLen = sizeof((struct sockaddr *) &clientAddress);
    cout << "Listening to clients.." << endl;
    listen(server->serverSock, MAX_CLIENTS);

    while (strcmp(consoleBuffer, "exit") != 0) {

        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(server->serverSock, (struct sockaddr *) &clientAddress, &client1AddressLen);
        if (clientSocket == -1) {
            throw "Error on accept";
        }
        cout << "Received connection from " << inet_ntoa(clientAddress.sin_addr) << " port " <<
             ntohs(clientAddress.sin_port) << endl;

        // create commandArgs
        read(clientSocket, buffer, DATALEN);
        string commandString;// = buffer;
        commandString = buffer;
        // build response

        //vector<string> arguments;
        stringstream ss(buffer);
        // extract command name
        ss >> commandName;
        // extract command parameters
        ss >> commandParam;
        CommandArgument *cArgs = new CommandArgument(gameManager, controller, commandName, commandParam, clientSocket);


        int rc = pthread_create(&gameThread, NULL, executeCommand, cArgs);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
    }
}

void *handle

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







