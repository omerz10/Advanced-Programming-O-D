//
// Created by David Nakash on 27/12/2017.
//




#include <sstream>
#include "GameManager.h"

#define DATALEN 512
CmdArg GameManager::parseMessage(string msg, Controller *controller, int clientSocket) {
    CmdArg cmdArgs;
    cmdArgs.gameManager = this;
    cmdArgs.clientThread.clientSocket = clientSocket;
    cmdArgs.controller = controller;
    stringstream ss(msg);
    // extract command name
    ss >> cmdArgs.name;
    // extract command parameters
    ss >> cmdArgs.param;
    return cmdArgs;
}
void GameManager::runOneGame(string gameName, Controller *controller) {

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

        CmdArg cmdArgs1 = parseMessage(buffer, controller, this->games[gameName].player2.clientSocket);
        controller->getCommands()[cmdArgs1.name]->execute(&cmdArgs1);

        // end of game
        if (cmdArgs1.clientThread.status == ClientEndGame) {
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

        CmdArg cmdArgs2 = parseMessage(buffer, controller, this->games[gameName].player1.clientSocket);
        controller->getCommands()[cmdArgs2.name]->execute(&cmdArgs2);
        // end of game
        if (cmdArgs2.clientThread.status == ClientEndGame) {
            break;
        }
    } // end of while

    // close client sockets
    close(clientSocket1);
    close(clientSocket2);
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


void GameManager::deleteGame(string gameName) {
    // update status of both player
    this->games[gameName].player1.status = ClientEndGame;
    this->games[gameName].player2.status = ClientEndGame;
    // delete game
    this->games.erase(gameName);
}

void GameManager::addNewGame(string gameName, ClientThread clientThread) {
    GameThread gameThread;
    bzero((void*) &gameThread, sizeof(gameThread));
    gameThread.player1 = clientThread;
    // insert new game to games
    this->games.insert(std::pair<string , GameThread> (gameName, gameThread));
}


