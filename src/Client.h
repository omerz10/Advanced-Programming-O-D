//
// Created by omerz on 07/12/17.
//

#ifndef ADVANCED_PROGRAMMING_O_D_CLIENT_H
#define ADVANCED_PROGRAMMING_O_D_CLIENT_H


#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

class Client {

private:
    const char *serverIP;
    int serverPort;
    int clientSocket;

public:
    Client(const char *serverIP, int serverPort);
    void connectToServer();
    int sendExercise(int arg1, char op, int arg2);
    void playLocalTurn(char *buffer);


};


#endif //ADVANCED_PROGRAMMING_O_D_CLIENT_H
