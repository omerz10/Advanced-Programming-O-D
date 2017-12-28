//
// Created by omerz on 01/12/17.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H



//using namespace std;
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <poll.h>
#include <map>
#include <sstream>
#include <arpa/inet.h>
#include "Controller.h"
#include "GameManager.h"

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




#endif //EX4_SERVER_H
