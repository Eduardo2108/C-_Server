#pragma once

#include <iostream>
#include "src/Socket/Server.h"
#include "src/Util/Coms/Message.h"
#include <thread>
#include "src/Util/Json.h"
#include "src/ServerManager.h"

using namespace std;

/*
void RunServer(){
    Server::getInstance()->InitServer();
    cout << "Server ON" << endl;
}

int main() {
    thread RunS (RunServer);
    RunS.join();
    return 0;
}
*/


int main() {

    string msg = R"({"action":"CREATE","contentJson":"{\"key\":\"help\",\"value\":\"1\"}","type":"Integer","size":4})";
    string msg2 = R"({"action":"CREATE","contentJson":"{\"key\":\"help\",\"value\":\"666\"}","type":"Integer","size":4})";
    string msg3 = R"({"action":"MODIFY", "firstVariable": "help", "secondVariable":"var", "operation":"+" })";


    cout << ServerManager::getInstance()->processRequest(msg) << endl;
    cout << ServerManager::getInstance()->processRequest(msg2) << endl;
   // cout << ServerManager::getInstance()->processRequest(msg3) << endl;


}

