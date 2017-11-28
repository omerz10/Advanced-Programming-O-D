/*
 * main.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#include "GameFlow.h"

int main()
{
    int size = 8;

    Board board = Board(size);

    GenericLogic gameLogic = GenericLogic(&board);

    HumanPlayer P1 = HumanPlayer('X', &board, &gameLogic);
    HumanPlayer P2 = HumanPlayer('O', &board, &gameLogic);

    Game game = Game(&P1, &P2, &board);

    GameFlow gameFlow = GameFlow(&game);

    gameFlow.play();

    return 0;
}