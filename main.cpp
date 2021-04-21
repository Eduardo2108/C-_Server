#pragma once

#include <iostream>
#include "src/Socket/Server.h"
#include "src/Util/Coms/Message.h"
#include <thread>
#include "src/Util/Json.h"
#include "src/ServerManager.h"


using namespace std;


/*void RunServer() {
    Server *s = new Server();
    cout << "Server ON" << endl;
    s->Start();
}*/

int main() {
/*
    thread RunS(RunServer);
    RunS.join();
*/
    string message = "{\"action\":\"CREATE\",\"contentJson\":\"{\\\"key\\\":\\\"x\\\",\\\"value\\\":\\\"2\\\"}\",\"type\":\"Integer\",\"size\":4}";

    auto *msg = new Message();
    msg = Json::readJsonMessage(message);
    ServerManager *sm = new ServerManager();
    Response *r = sm->processRequest(msg);
    r->show();
    return 0;
}
