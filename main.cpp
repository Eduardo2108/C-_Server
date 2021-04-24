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


/*
int main() {

    string msg = R"({"message":"{\"key\":\"help\",\"addr\":\"0x5615eeb6b044\",\"value\":\"1\",\"offset\":1,\"referenceCount\":0,\"offset\":1}","log":"Integer help was created.","statusCode":200}})";
    Response *resp = Json::re(msg);
    // cout << ServerManager::getInstance()->processRequest(msg3) << endl;


}
*/

