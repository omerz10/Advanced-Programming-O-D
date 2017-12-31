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

public:

    int port;
    int serverSock;
    Controller *controller;
    GameManager *gameManager;
    /*
     * construct a server
     */
    Server(int port, GameManager *gameManager, Controller *controller);

    /*
     * initialize server
     */
    void initialize();

    void runServer();

};




#endif //ADVANCED_PROGRAMMING_O_D_SERVER_H
