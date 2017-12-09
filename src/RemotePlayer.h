//
// Created by omerz on 09/12/17.
//

#ifndef ADVANCED_PROGRAMMING_O_D_REMOTEPLAYER_H
#define ADVANCED_PROGRAMMING_O_D_REMOTEPLAYER_H


#include "Player.h"
#include "Client.h"

class RemotePlayer : public Player {

private:

    char type;

    Board* board;

    Logic *gameLogic;

    PossibleMove possibleMove;

    Cell lastMove;

    Client *client;


public:

    RemotePlayer(char type, Board *board, Logic *gLogic, Client *c);

    virtual char getType() const;

    virtual Cell getLastMove() const;

    virtual void setLastMove(int i, int j);

    virtual void printMoves();

    virtual void playTurn();

    virtual void getPlayerMoves();

    virtual bool getPossibleMoveStatus();

    virtual bool checkInput(string input);

    virtual int getBoardSize();

    virtual char getBoardValueAtIndexes(int i, int j);

    virtual void showBoard();

    virtual bool printGUI();

    string getCellFromServer();
};


#endif //ADVANCED_PROGRAMMING_O_D_REMOTEPLAYER_H
