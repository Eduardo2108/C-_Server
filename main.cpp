#pragma once

#include <iostream>
#include "src/Socket/Server.h"
#include "src/Util/Coms/Message.h"
#include <thread>
#include "src/Util/Json.h"
#include "src/ServerManager.h"

using namespace std;

void RunServer(){
    Server::getInstance()->InitServer();
    cout << "Server ON" << endl;
}

int main() {
    thread RunS (RunServer);
    RunS.join();
    return 0;
}

