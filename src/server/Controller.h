//
// Created by omerz on 02/01/18.
//

#ifndef ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
#define ADVANCED_PROGRAMMING_O_D_CONTROLLER_H

#include <zconf.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include "ServerStructs.h"


class Controller {

private:
    vector<pthread_t> clientsThreads;
    vector <ClientThread> socketsStatus;
    map < string, GameThread > games;
    vector <string> joinable_games;

public:
    void mainThreadListener(int serverSocket);

    vector<pthread_t> getClientsThreads();

    void addThread(pthread_t thread);

    void removeSockets(vector <ClientThread> v);

    void runServer();

    int getServerSocket();

    vector <ClientThread> getSocketsStatus();

    void closeClientsConnectios();

    map < string, GameThread > getGames();

    void runOneGame(string gameName);

    bool isClientClosed(int clientNumber);

    bool pollClient(int currentClient, int otherClient);

    CmdArg parseMessage(string msg, int clientSocket);

    void deleteGame(string gameName);

    void addNewGame(string gameName, ClientThread *clientThread);

    vector <string> getJoinableGames();

};


#endif //ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
