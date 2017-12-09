//
// Created by omerz on 09/12/17.
//


#include "RemotePlayer.h"

#define DATALEN 4096

RemotePlayer::RemotePlayer(char type, Board *board, Logic *gLogic, Client *c): type(type), board(board),
                                                                               gameLogic(gLogic) {
    this->lastMove = Cell();
    this->client = c;
}

string RemotePlayer::getCellFromServer() {
    char buff[DATALEN];
    read(*this->client->getClientSock(), buff, sizeof(buff));
    string str = (string)buff;
    return str;
}

 bool RemotePlayer::checkInput(string input) {

 }
