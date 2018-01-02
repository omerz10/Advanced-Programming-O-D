//
// Created by omerz on 01/12/17.
//

//using namespace std;


#ifndef ADVANCED_PROGRAMMING_O_D_SERVER_H

#define ADVANCED_PROGRAMMING_O_D_SERVER_H


#include "Controller.h"

using namespace std;


class Server {

private:

    int port;
    int serverSock;
    Controller *controller;

public:

    Server(int port, Controller *controller);

    void initialize();

};




#endif //ADVANCED_PROGRAMMING_O_D_SERVER_H
