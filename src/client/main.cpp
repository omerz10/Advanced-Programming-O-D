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
#include <cstdlib>
#include "GameFlow.h"
#include "Structs.h"
#include <pthread.h>


#define BOARD_SIZE 8
#define DATALEN 512

using namespace std;

ServerDetails getServerDetails(string *fileName) {
    ServerDetails serverDetails;
    string buffer;
    ifstream file;
    file.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        file.open((*fileName).c_str());
        while (!file.eof()) {
            getline(file, buffer);
        }
        file.close();
    }
    catch (ifstream::failure &e) {
        cerr << "Exception opening/reading/closing file\n";
    }
    // Insert the string into a stream
    stringstream ss(buffer);
    // extract ip and port
    string temp;
    char *ptr;
    ss >> serverDetails.serverIP;
    ss >> temp;
    serverDetails.serverPort = (int) strtol(temp.c_str(), &ptr, 10);
    //atoi(temp.c_str());

    return serverDetails;
}


void menuSelection(int *playerSelection) {
    int userInput = 0;
    bool flag = false;

    cout << "Welcome to Reversi!" << endl << endl;
    cout << "Choose an oppenent type:" << endl;
    cout << "1. A human local player" << endl << "2. An AI player" << endl << "3. A remote player" << endl;

    while (!flag) {
        cin >> userInput;

        if (cin.fail()) {
            cin.clear(); // clears error flags
            cin.ignore();

            // user inputs wrong type of input, print message..
            if (!flag) {
                cout << "Characters are not allowed, Please try again !" << endl;
            }
        } else {
            // check if input is legal?
            flag = (userInput == 1) or (userInput == 2) or (userInput == 3);
            // move is illegal, print message..
            if (!flag) {
                cout << "Illegal move, Please enter 1 to play against "
                        "Human Player and 2 to play against AIPlayer!" << endl;
            }
        }

    }
    cin.clear();
    *playerSelection = userInput;
}

void* countNumbers(void *tArgs) {
    GameThread *ptr = (GameThread *)tArgs;
    (*ptr).player1Socket = 6;

    pthread_exit(0);
}


void threadCheck() {
    GameThread gameThread;
    gameThread.player2Socket = 2;
    gameThread.player1Socket = 1;
    gameThread.running = true;

    cout<<"player 1 socket : " << gameThread.player1Socket << endl;

    pthread_t thread;
    int rc = pthread_create(&thread, NULL, countNumbers, &gameThread);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
    pthread_join(thread, NULL);

    cout<<"player 1 socket : " << gameThread.player1Socket << endl;

}

void menu() {

    threadCheck();

    string path = "clientConfig.txt";
    int playerSelection;
    char buff[DATALEN];
    memset(&buff, 0, sizeof(buff));
    menuSelection(&playerSelection);
    cin.get();


    // play against a player
    if (playerSelection == 1) {
        Board board = Board(BOARD_SIZE); // board is created and initialized
        GenericLogic gameLogic = GenericLogic();
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        HumanPlayer p2 = HumanPlayer('O', &board, &gameLogic);
        Game game = Game(&p1, &p2);

        GameFlow gameFlow = GameFlow(&game);
        gameFlow.play();
    }

    // play against a AI player
    if (playerSelection == 2) {
        Board board = Board(BOARD_SIZE);
        GenericLogic gameLogic = GenericLogic();
        HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
        AIPlayer aiPlayer = AIPlayer('O', &board, &gameLogic);
        Game game = Game(&p1, &aiPlayer);
        GameFlow gameFlow = GameFlow(&game);
        gameFlow.play();
    }
    // play against an remote player
    if (playerSelection == 3) {

        GenericLogic gameLogic = GenericLogic();
        Board board = Board(BOARD_SIZE);
        ServerDetails serverDetails = getServerDetails(&path);

        Client client =  Client(serverDetails.serverIP.c_str(), serverDetails.serverPort);
        client.connectToServer();
        client.waitingForOtherPlayer();
        int player;
        if (read(client.getClientSock(), &player, sizeof(player)) == -1) {
            throw "Error: get 1 or 2";
        }
        // the client get "1" from server
        if (player == 1) {
            HumanPlayer p1 = HumanPlayer('X', &board, &gameLogic);
            HumanPlayer p2 = HumanPlayer('O', &board, &gameLogic);
            Game game = Game(&p1, &p2);
            GameFlow gameFlow = GameFlow(&game, &client);
            client.setID(1);
            gameFlow.playOnline();
        // the client get "2" from server
        } else if(player == 2) {
            HumanPlayer p1 = HumanPlayer('O', &board, &gameLogic);
            HumanPlayer p2 = HumanPlayer('X', &board, &gameLogic);
            Game game = Game(&p1, &p2);
            GameFlow gameFlow = GameFlow(&game, &client);
            client.setID(2);
            gameFlow.playOnline();
        }
    }
}

int main() {
    menu();

    return 0;
}