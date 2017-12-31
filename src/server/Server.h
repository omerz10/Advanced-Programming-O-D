//
// Created by omerz on 01/12/17.
//

//using namespace std;


#ifndef ADVANCED_PROGRAMMING_O_D_SERVER_H

#define ADVANCED_PROGRAMMING_O_D_SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <poll.h>
#include <map>
#include <sstream>
#include <arpa/inet.h>
#include <pthread.h>
#include "Controller.h"


#include "GameManager.h"
#include "ServerStructs.h"

using namespace std;


class Server {

private:

    int port;
    int serverSock;
    Controller *controller;
    GameManager *gameManager;
    vector<pthread_t> clientsThreads;
    vector <ClientThread> socketsStatus;

public:

    /*
 * construct a server
 */
    Server(int port, GameManager *gameManager, Controller *controller);

    vector<pthread_t> getClientsThreads();

    void addThread(pthread_t thread);

    void removeSockets(vector <ClientThread> v);
    /*
     * initialize server
     */
    void initialize();

    void runServer();

    int getServerSocket();

    vector <ClientThread> getSocketsStatus();

    void closeClientsConnectios();

};




#endif //ADVANCED_PROGRAMMING_O_D_SERVER_H
