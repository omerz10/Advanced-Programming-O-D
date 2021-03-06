//
// Created by David Nakash on 28/11/2017.
//


#ifndef PROJECT_UPDATED_STRUCTS_H
#define PROJECT_UPDATED_STRUCTS_H

#include "Board.h"

/**
 Struct that holds the possible moves (in order to make it easier for the programmer...).
 */
struct PossibleMove {

    vector<vector<Cell> > changeableCells;

    vector<Cell> moves;

    bool possible;
};

struct ServerDetails {
    string serverIP;
    int serverPort;
};



#endif //PROJECT_UPDATED_STRUCTS_H
