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
    string userInput;

    Board board = Board(size);
    GenericLogic gameLogic = GenericLogic(&board);
    HumanPlayer P1 = HumanPlayer('X', &board, &gameLogic);
    AIPlayer aiPlayer = AIPlayer('O', &board, &gameLogic);
    Game game = Game(&P1, &aiPlayer, &board);
    GameFlow gameFlow = GameFlow(&game);
    gameFlow.play();

    return 0;
}