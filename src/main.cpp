/*
 * main.cpp
 *	Omer Zucker
 *	ID: 200876548
 *
 *  David Nakash
 *  ID: 203752902
 */

#include <cstdio>
#include <fstream>
#include <sstream>
#include "GameFlow.h"
#include "struct.h"


#define CLIENTSNUMBER 2
#define DATALEN 4096

ServerDetails getServerDetails(string fileName) {
    ServerDetails serverDetails;
    string buffer;
    std::ifstream file;
    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try {
        file.open (fileName);
        while (!file.eof()){
            getline (file,buffer);
            cout << buffer;
        }

        file.close();
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }

    // Insert the string into a stream
    stringstream ss(buffer);
    // extract ip and port
    string temp;
    ss >> serverDetails.serverIP;
    ss >> temp;
    serverDetails.serverPort = atoi(temp.c_str());
    return serverDetails;

}


void menuSelection(int *sizeOfBoard, int *playerSelection) {

    //string userInput;
    int userInput;
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
    cout << "Welcome to reversi!" << endl << endl;
    cout << "Choose an oppenent type:" << endl;
    cout << "1. a human local player" << endl << "2. an AI player" << endl << "3. a remote player" << endl;

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
    char buff[DATALEN];
    memset(&buff, 0, sizeof(buff));
    int sizeOfBoard, playerSelection;

    menuSelection(&sizeOfBoard, &playerSelection);
    cin.get();

    // play against a player
    if (playerSelection == 1) {
        Board board = Board(sizeOfBoard); // board is created and initialized
        GenericLogic gameLogic = GenericLogic(&board);
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        HumanPlayer p2 = HumanPlayer('O', &board, &gameLogic);
        Game game = Game(&p1, &p2);

        GameFlow gameFlow = GameFlow(&game);
        gameFlow.play();
    }

    // play against a AI player
    if (playerSelection == 2) {
        Board board = Board(sizeOfBoard);
        GenericLogic gameLogic = GenericLogic(&board);
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        AIPlayer aiPlayer = AIPlayer('O', &board, &gameLogic);
        Game game = Game(&p1, &aiPlayer);
        GameFlow gameFlow = GameFlow(&game);
        gameFlow.play();
    }

    if (playerSelection == 3) {
        Board board1 = Board(sizeOfBoard);
        Board board2 = Board(sizeOfBoard);
        GenericLogic gameLogic = GenericLogic(&board1);
        ServerDetails serverDetails = getServerDetails("/exe/clientConfig.txt");

        Client client(serverDetails.serverIP.c_str(), serverDetails.serverPort);
        client.connectToServer();
        client.waitingForOtherPlayer();

        if (read(*client.getClientSock(), &buff, sizeof(buff) == -1)) {
            throw "Error: reading result from socket";
        }
        // the client get "1" from server
        if (!strcmp(buff, "1")) {
            HumanPlayer p1 = HumanPlayer('X', &board1, &gameLogic);
            HumanPlayer p2 = HumanPlayer('O', &board2, &gameLogic);
            Game game = Game(&p1, &p2);
            GameFlow gameFlow = GameFlow(&game);
            gameFlow.play();
        }
        // the client get "1" from server
        if (!strcmp(buff, "2")) {
            HumanPlayer p1 = HumanPlayer('O', &board2, &gameLogic);
            HumanPlayer p2 = HumanPlayer('X', &board1, &gameLogic);
            Game game = Game(&p1, &p2);
            GameFlow gameFlow = GameFlow(&game);
            gameFlow.play();
        }
    }
}

int main()
{
    menu();

    return 0;
}