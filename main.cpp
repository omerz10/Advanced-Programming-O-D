/*
 * main.cpp
 *	Omer Zucker
 *	ID: 200876548
 *
 *  David Nakash
 *  ID: 203752902
 */

#include <cstdio>
#include "GameFlow.h"


void menu() {
    int size, input;
    printf("Hello!\n");
    printf("Please enter size of board:\n");
    cin >> size;
    Board board = Board(size);
    GenericLogic gameLogic = GenericLogic(&board);

    printf("Press 1 - to play against PLAYER\n");
    printf("Press 2 - to play against COMPUTER\n");
    cin >> input;

    while (input != 1 and input != 2) {
        printf("Wrong input! Please enter again");
        cin >> input;
    }

    // play against a player
    if (input == 1) {
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        HumanPlayer p2 = HumanPlayer('X', &board, &gameLogic);
        Game game = Game(&p1, &p2, &board);
        GameFlow gameFlow = GameFlow(&game);
        gameFlow.play();
    }

    // play against a player
    if (input == 2) {
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        AIPlayer aiPlayer = AIPlayer('O', &board, &gameLogic);
        Game game = Game(&p1, &aiPlayer, &board);
        GameFlow gameFlow = GameFlow(&game);
        gameFlow.play();
    }
}

int main()
{
    menu();
    return 0;
}