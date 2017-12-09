#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Server.h"


int getServerPort(string fileName) {
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
    return atoi(buffer.c_str());
}

int main() {
    int serverPort = getServerPort("/exe/serverConfig.txt");
    Server server(serverPort);
    server.start();

}