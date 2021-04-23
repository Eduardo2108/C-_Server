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
int main() {*/
    /*
    auto *sm = new ServerManager();

    string message2 = R"({"action":"CREATE","contentJson":"{\"key\":\"help\",\"value\":\"666.6\"}","type":"Float","size":4})";
    string message = R"({"action":"CREATE","contentJson":"{\"key\":\"var\",\"value\":\"2\"}","type":"Integer","size":4})";
    string message3 = R"({"action":"SEARCH", "firstVariable": "help" })";


    Message *msg = Json::readJsonMessage(message);
    Message *msg2 = Json::readJsonMessage(message2);
    Message *msg3 = Json::readJsonMessage(message3);


    Response *r = sm->processRequest(msg);
    Response *r2 = sm->processRequest(msg2);

    Response *r3 = sm->processRequest(msg3);


    r->show();
    r2->show();
    sm->getMemory()->show();

    //r3->show();


    */

