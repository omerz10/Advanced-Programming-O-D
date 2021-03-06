#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Server.h"
#include "Controller.h"


using namespace std;

int getServerPort(string *fileName) {

    string buffer;
    const char *begin;
    char *end;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open((*fileName).c_str());
        while (!file.eof()){
            getline (file,buffer);
        }
        file.close();
    }
    catch (std::ifstream::failure &e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    begin = buffer.c_str();
    end = (char*)(begin + strlen(begin));
    return (int)strtol(begin, &end,10);
            //atoi(buffer.c_str());
}

int main() {
    string path = "serverConfig.txt";
    int serverPort = getServerPort(&path);
    Controller controller = Controller();
    Server server(serverPort, &controller);
    server.initialize();
    while (true) {
        try {
            //server.start();
            controller.mainThreadListener(server.getServerSocket());
            cout << endl << "Restarting server.." << endl;
        } catch (const char *exception) {
            cout << exception << endl;
            break;
        }
    }
    //server.closeClientsConnectios();

}