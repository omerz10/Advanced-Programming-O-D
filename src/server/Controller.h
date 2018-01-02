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
#include <pthread.h>

class Controller {

private:
    vector<pthread_t> clientsThreads; // vector of pthreads - manages threads...

    vector <ClientThread> socketsStatus; // vector of ClientThread (which has clientSocket and status)

    map < string, GameThread > games; // map of games

    vector <string> joinable_games; // vector of joinable games

public:

    // runners
    void runServer();
    void mainThreadListener(int serverSocket); // controller function that executes the void* funcs (in threads..)
    void runOneGame(string gameName);
    void closeClientsConnections();

    // getters
    vector <string> getJoinableGames();
    vector<pthread_t> getClientsThreads(); // get vector of threads
    vector <ClientThread> getSocketsStatus();
    map < string, GameThread > getGames();

    // setters
    void addThread(pthread_t thread);
    void addNewGame(string gameName, ClientThread *clientThread);
    void deleteGame(string gameName);
    void removeSockets(vector <ClientThread> v);

    // polling
    bool isClientClosed(int clientNumber);
    bool pollClient(int currentClient, int otherClient);

    // parsing
    CmdArg parseMessage(string msg, int clientSocket);

};


#endif //ADVANCED_PROGRAMMING_O_D_CONTROLLER_H
