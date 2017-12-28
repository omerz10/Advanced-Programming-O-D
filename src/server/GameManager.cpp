//
// Created by David Nakash on 27/12/2017.
//



#include <map>
#include "GameManager.h"

#define DATALEN 512
/*
bool isClientClosed(int clientNumber) {
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

bool pollClient(int currentClient, int otherClient) {
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

static void runOneGame(int client1Sock, int client2Sock) {

    // init buffer for getting msg from player
    char buffer[DATALEN];
    char temp[DATALEN];
    // messages from each player
    ssize_t blackMsg, whiteMsg;

    // send & receive from players until gets "isEnd" message
    while(true) {
        // read from player 1's client
        memset(buffer, 0, DATALEN);
        blackMsg = read(client1Sock, buffer, DATALEN);

        // check input
        if (blackMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (blackMsg == -1) {
            throw "Error: connect to black player ";
        }

        // send to 2nd player that black didn't play a move
        if (strcmp(buffer, "NoMove") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "NoMove");
            write(client2Sock, &temp, DATALEN);
        } else if (strcmp(buffer, "End") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "End");
            write(client2Sock, &temp, DATALEN);
            break;
        }
        memset(temp, 0, DATALEN);
        strcpy(temp, buffer);

        // check if connection still alive with first client
        if (pollClient(client1Sock, client2Sock)) {
            break;
        }

        write(client2Sock, &temp, DATALEN);

        // read from player 2's client
        memset(temp, 0, DATALEN);
        whiteMsg = read(client2Sock, temp, DATALEN);
        strcpy(buffer, temp);

        if (whiteMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (whiteMsg == -1) {
            throw "Error: connect to black player ";
        }

        // send to white player that black didn't play a move
        if (strcmp(buffer, "NoMove") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "NoMove");
            write(client1Sock, &temp, DATALEN);
        } else if (strcmp(buffer, "End") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "End");
            write(client1Sock, &temp, DATALEN);
            break;
        }

        // check if connection still alive
        if (pollClient(client2Sock, client1Sock)) {
            break;
        }

        write(client1Sock, &buffer, DATALEN);
    } // end of while

    // close client sockets
    close(client1Sock);
    close(client2Sock);
}
*/
void GameManager::runOneGame(Controller *controller, int client1Sock, int client2Sock) {
    // init buffer for getting msg from player
    char buffer[DATALEN];
    char temp[DATALEN];
    // messages from each player
    ssize_t blackMsg, whiteMsg;

    // send & receive from players until gets "isEnd" message
    while(true) {
        // read from player 1's client
        memset(buffer, 0, DATALEN);
        blackMsg = read(client1Sock, buffer, DATALEN);
        // check input
        if (blackMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (blackMsg == -1) {
            throw "Error: connect to black player ";
        }

        // send to 2nd player that black didn't play a move
        if (strcmp(buffer, "NoMove") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "NoMove");
            write(client2Sock, &temp, DATALEN);
        } else if (strcmp(buffer, "End") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "End");
            write(client2Sock, &temp, DATALEN);
            break;
        }
        memset(temp, 0, DATALEN);
        strcpy(temp, buffer);

        // check if connection still alive with first client
        if (pollClient(client1Sock, client2Sock)) {
            break;
        }

        write(client2Sock, &temp, DATALEN);

        // read from player 2's client
        memset(temp, 0, DATALEN);
        whiteMsg = read(client2Sock, temp, DATALEN);
        strcpy(buffer, temp);

        if (whiteMsg == 0) {
            throw "Error: connection with black player is closed";
        }
        if (whiteMsg == -1) {
            throw "Error: connect to black player ";
        }

        // send to white player that black didn't play a move
        if (strcmp(buffer, "NoMove") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "NoMove");
            write(client1Sock, &temp, DATALEN);
        } else if (strcmp(buffer, "End") == 0) {
            memset(temp, 0, DATALEN);
            strcpy(temp, "End");
            write(client1Sock, &temp, DATALEN);
            break;
        }

        // check if connection still alive
        if (pollClient(client2Sock, client1Sock)) {
            break;
        }

        write(client1Sock, &buffer, DATALEN);
    } // end of while

    // close client sockets
    close(client1Sock);
    close(client2Sock);
}

bool GameManager::isClientClosed(int clientNumber) {
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

bool GameManager::pollClient(int currentClient, int otherClient) {
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

map< string, GameThread > GameManager::getGames() {
    return this->games;
}


