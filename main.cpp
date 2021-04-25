#pragma once
#include <iostream>
#include "src/Socket/Server.h"
#include <thread>

using namespace std;

void RunServer(int port) {
    Server::getInstance(port)->InitServer();
}

int main() {
    RunServer(54000);
    
    return 0;
}