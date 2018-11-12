/*
 * main.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#include <iostream>
#include "GameFlow.h"

int main()
{

    char defaultPlayer = 'X';
    int size = 8;
    Board board = Board(size);
    Player player = Player(defaultPlayer, &board);
    GameFlow g = GameFlow(&player, &board);
    g.play();

    return 0;
}