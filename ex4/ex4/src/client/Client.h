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
    int id;

public:

    Client(const char *serverIP, int serverPort);

    void connectToServer();

    void waitingForOtherPlayer();

    int getClientSock();

    void sendExercise(char *buffer);

    void getMessage(char *buffer);

    void setID(int id);

    int getID();
};


#endif //ADVANCED_PROGRAMMING_O_D_CLIENT_H
