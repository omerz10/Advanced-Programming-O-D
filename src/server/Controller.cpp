//
// Created by omerz on 02/01/18.
//


#include <poll.h>
#include "Controller.h"
#include "CommandManager.h"

#define MAX_CLIENTS 1000
#define DATALEN 512


CommandManager *cManager;


struct ClientData {
    Controller *controller;
    ClientThread clientThread;
};


struct ServerData {
    int serverSocket;
    Controller *controller;
};

void executeEnvelope(ClientThread* clientT, string command) {
    cManager->executeCommand(clientT, command);
}

void *handleClient(void *data) {
    ClientData *cData = (ClientData *)data;
    // get command from client
    char buffer[DATALEN];
    string commandString;
    ssize_t statusRead;

    while (cData->clientThread.status == ClientChoice) {
        statusRead = read(cData->clientThread.clientSocket, buffer, DATALEN);
        if (statusRead == 0) {
            close(cData->clientThread.clientSocket);
            break;
        }
        commandString = buffer;
        executeEnvelope(&cData->clientThread, commandString);

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
        int clientSocket = accept(sData->serverSocket, (struct sockaddr *) &clientAddress
                , &client1AddressLen);
        if (clientSocket == -1) {
            throw "Error on accept";
        }
        cout << "Received connection from " << inet_ntoa(clientAddress.sin_addr) << " port " <<
             ntohs(clientAddress.sin_port) << endl;

        clientData.clientThread.clientSocket = clientSocket;
        clientData.clientThread.status = ClientChoice;
        clientData.controller = sData->controller;

        int rc = pthread_create(&newThread, NULL, handleClient, &clientData);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
        // adding thread
        sData->controller->addThread(newThread);
        // remove sockets and statuses from vector of ClientThread
        sData->controller->removeSockets(sData->controller->getSocketsStatus());
    }
    return NULL;
}

/*
 * main thread listener
 */
void Controller::mainThreadListener(int serverSocket) {
    pthread_t mainThread;
    char consoleBuffer[DATALEN];
    ServerData serverData;
    bzero((void*) &serverData, sizeof(serverData));

    serverData.serverSocket = serverSocket;
    serverData.controller = this;
    CommandManager manager(this);
    cManager = &manager;

    // get input from user
    cin >> consoleBuffer;
    cout << "Listening to clients.." << endl;
    listen(serverSocket, MAX_CLIENTS);

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
    for (unsigned int i = 0; i < getClientsThreads().size(); i++) {
        pthread_cancel(getClientsThreads()[i]);
        pthread_join(getClientsThreads()[i], NULL);
    }

    // close main thread
    pthread_cancel(mainThread);
    pthread_join(mainThread, NULL);
}








vector<pthread_t> Controller::getClientsThreads() {
    return clientsThreads;
}

void Controller::addThread(pthread_t thread) {
    this->clientsThreads.push_back(thread);
}

void Controller::removeSockets(vector <ClientThread> socketsStatus) {
    vector<ClientThread>::iterator it;
    for (it = socketsStatus.begin(); it != socketsStatus.end(); it++) {
        if (it->status == ClientEndGame) {
            socketsStatus.erase(it);
        }
    }

}
/*
int Controller::getServerSocket() {
    return this->serverSock;
}
*/

vector <ClientThread> Controller::getSocketsStatus() {
    return this->socketsStatus;
}


void Controller::closeClientsConnections() {
    vector <ClientThread>::iterator it;
    char buffer[DATALEN];
    bzero((void*)buffer, sizeof(buffer));
    strcpy(buffer, "exit");
    for (it = this->socketsStatus.begin(); it != this->socketsStatus.end(); it++) {
        write(it->clientSocket, buffer, DATALEN);
        close(it->clientSocket);
    }
}

CmdArg Controller::parseMessage(string msg, int clientSocket) {
    CmdArg cmdArgs;
    cmdArgs.clientThread.clientSocket = clientSocket;
    cmdArgs.commandManager = cManager;
    stringstream ss(msg);
    // extract command name
    ss >> cmdArgs.name;
    // extract command parameters
    ss >> cmdArgs.param;
    return cmdArgs;
}

void Controller::runOneGame(string gameName) {

    int clientSocket1 = this->games[gameName].player1.clientSocket;
    int clientSocket2 = this->games[gameName].player2.clientSocket;

    // init buffer for getting msg from player
    char buffer[DATALEN];
    char temp[DATALEN];
    // messages from each player
    ssize_t blackMsg, whiteMsg;
    // send & receive from players until gets "isEnd" message
    while(this->games[gameName].player1.status == Playing && this->games[gameName].player2.status == Playing) {
        // read move from player 1
        memset(buffer, 0, DATALEN);
        blackMsg = read(clientSocket1, buffer, DATALEN);
        // check input
        if (blackMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (blackMsg == -1) {
            throw "Error: connect to black player ";
        }

        memset(temp, 0, DATALEN);
        strcpy(temp, buffer);

        // check if connection still alive with first client
        if (pollClient(clientSocket1, clientSocket2)) {
            break;
        }

        ClientThread clientT;
        clientT.clientSocket = clientSocket2;
        clientT.status = this->games[gameName].player2.status;
        executeEnvelope(&clientT, temp);

        // end of game
        if (clientT.status == ClientEndGame) {
            break;
        }

        // read from player 2's client
        memset(temp, 0, DATALEN);
        whiteMsg = read(clientSocket2, temp, DATALEN);
        strcpy(buffer, temp);

        if (whiteMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (whiteMsg == -1) {
            throw "Error: connect to black player ";
        }

        // check if connection still alive with first client
        if (pollClient(clientSocket2, clientSocket1)) {
            break;
        }

        ClientThread clientT2;
        clientT.clientSocket = clientSocket1;
        clientT.status = this->games[gameName].player1.status;
        executeEnvelope(&clientT2, temp);

        // end of game
        if (clientT2.status == ClientEndGame) {
            break;
        }
    } // end of while

    // close client sockets
    close(clientSocket1);
    close(clientSocket2);
}

bool Controller::isClientClosed(int clientNumber) {
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

bool Controller::pollClient(int currentClient, int otherClient) {
    char temp[DATALEN];
    // check for lost connection
    if (isClientClosed(otherClient)) {
        //cout << "Other player has disconnected from the game, restarting.." << endl;
        memset(temp, 0, DATALEN);
        strcpy(temp, "End");

        write(currentClient, &temp, DATALEN);
        return true;
    }
    return false;
}

map< string, GameThread > Controller::getGames() {
    return this->games;
}


void Controller::deleteGame(string gameName) {
    // update status of both player
    this->games[gameName].player1.status = ClientEndGame;
    this->games[gameName].player2.status = ClientEndGame;
    // delete game
    this->games.erase(gameName);
}

void Controller::addNewGame(string gameName, ClientThread *clientThread) {
    GameThread gameThread;
    bzero((void*) &gameThread, sizeof(gameThread));
    gameThread.player1 = *clientThread;
    // insert new game to games
    this->games.insert(std::pair<string , GameThread> (gameName, gameThread));
    this->joinable_games.push_back(gameName);
}

vector <string> Controller:: getJoinableGames() {
    return this->joinable_games;
}
