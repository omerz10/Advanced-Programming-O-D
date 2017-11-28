//
// Created by David Nakash on 28/11/2017.
//

#ifndef PROJECT_UPDATED_STRUCTS_H
#define PROJECT_UPDATED_STRUCTS_H

#include "Board.h"

struct PossibleMove {

    vector<vector<Cell> > changeableCells;

    vector<Cell> moves;

    bool possible;
};



#endif //PROJECT_UPDATED_STRUCTS_H
