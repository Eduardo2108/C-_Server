#pragma once
#include <iostream>
#include "src/Socket/Server.h"

using namespace std;

void RunServer(int port, int size) {
    Server::getInstance(port, size)->InitServer();
}

int main() {
    int port;
    int size;
    cout << "Welcome to C! Server" << endl;
    cout << "Specify a port for the server to run:" << endl;
    cin >> port;
    cout << "Port selected successfully: " << port << endl;
    cout << "Specify the size (in bytes) the server will reserve for variables:" << endl;
    cin >> size;
    cout << "Memory size  selected successfully: " << size << " bytes." << endl;

    if (port <= 0) {
        cout << port << " is not a valid port." << endl;
        return -1;
    }
    if (size <= 0) {
        cout << port << "bytes is not a valid space." << endl;
        return -1;
    } else {
        RunServer(52000, size);

    }

}