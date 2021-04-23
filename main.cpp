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
    string msg2 = R"({"action":"CREATE","contentJson":"{\"key\":\"var\",\"value\":\"666\"}","type":"Integer","size":4})";
    string msg3 = R"({"action":"MODIFY", "firstVariable": "help", "secondVariable":"var", "operation":"+" })";


    Response *r = ServerManager::getInstance()->processRequest(msg);
    Response *r2 = ServerManager::getInstance()->processRequest(msg2);
    Response *r3 = ServerManager::getInstance()->processRequest(msg3);


    cout << Json::generateJson(r) << endl;
    cout << Json::generateJson(r2) << endl;
    cout << Json::generateJson(r3) << endl;


}

