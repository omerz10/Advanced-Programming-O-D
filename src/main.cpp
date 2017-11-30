/*
 * main.cpp
 *	Omer Zucker
 *	ID: 200876548
 *  Created by omerz on 30/10/17.
 *      Author: zuckero
 */

#include <cstdio>
#include <cstring>
#include "GameFlow.h"

int main()
{
    int size = 8;

    string input;

    Board board = Board(size);

    GenericLogic gameLogic = GenericLogic(&board);

    printf("Hello!\n");
    printf("Press P - to play against PLAYER\n");
    printf("Press C - to play against COMPUTER\n");
    cin >> input;

    while (!strcmp(input, "p") and !strcmp(input, "P") and !strcmp(input, "c") and !strcmp(input, "C")) {
        printf("Wrong input! Please enter again");
        cin >> input;
    }

    // play against a player
    if (strcmp(input, "p") or strcmp(input, "P")) {
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        HumanPlayer p2 = HumanPlayer('X', &board, &gameLogic);
        Game game = Game(&p1, &p2, &board);
        GameFlow gameFlow = GameFlow(&game);
        gameFlow.play();
    }

    // play against a player
    if (strcmp(input, "c") or strcmp(input, 'C')) {
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        AIPlayer aiPlayer = AIPlayer('O', &board, &gameLogic);
        Game game = Game(&p1, &aiPlayer, &board);
        GameFlow gameFlow = GameFlow(&game);
        gameFlow.play();
    }

    return 0;
}