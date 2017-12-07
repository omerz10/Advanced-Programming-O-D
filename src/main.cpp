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


void menuSelection(int *sizeOfBoard, int *playerSelection) {

    //string userInput;
    int userInput;
    int selection;
    cout << "Hello!" <<  endl << "Please enter size of board:";

    bool flag = false;

    while (!flag) {
        // get input from user..
        cin >> userInput;

        if (cin.fail())
        {
            cin.clear(); // clears error flags
            cin.ignore();

            // user inputs wrong type of input, print message..
            if (flag == false) {
                cout << "Characters are not allowed, Please try again !" << endl;
            }
        } else {
            // check if input is legal?
            flag = ((userInput > 0));

            // move is illegal, print message..
            if (flag == false) {
                cout << "Illegal input, Please enter a positive integer size" << endl;
            }
        }

    }

    *sizeOfBoard = userInput;

    printf("Press 1 - to play against another PLAYER\n");
    printf("Press 2 - to play against the COMPUTER\n");

    // reset flag
    flag = false;
    while (!flag) {
        cin >> userInput;

        if (cin.fail())
        {
            cin.clear(); // clears error flags
            cin.ignore();

            // user inputs wrong type of input, print message..
            if (flag == false) {
                cout << "Characters are not allowed, Please try again !" << endl;
            }
        } else {
            // check if input is legal?
            flag = ((userInput == 1) or (userInput == 2));
            // move is illegal, print message..
            if (flag == false) {
                cout << "Illegal move, Please enter 1 to play against "
                        "Human Player and 2 to play against AIPlayer!" << endl;
            }
        }

    }
    cin.clear();
    *playerSelection = userInput;
}

void menu() {
    int sizeOfBoard, playerSelection;

    menuSelection(&sizeOfBoard, &playerSelection);

    Board board = Board(sizeOfBoard);
    GenericLogic gameLogic = GenericLogic(&board);


    cin.get();
    // play against a player
    if (playerSelection == 1) {
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        HumanPlayer p2 = HumanPlayer('X', &board, &gameLogic);
        Game game = Game(&p1, &p2, &board);
        GameFlow gameFlow = GameFlow(&game);
        gameFlow.play();
    }

    // play against a player
    if (playerSelection == 2) {
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        AIPlayer aiPlayer = AIPlayer('O', &board, &gameLogic);
        Game game = Game(&p1, &aiPlayer, &board);
        GameFlow gameFlow = GameFlow(&game);
        gameFlow.play();
    }

    if(playerSelection == 3) {
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        HumanPlayer p2 = HumanPlayer('0', &board, &gameLogic);
    }
}

int main()
{
    menu();
    return 0;
}