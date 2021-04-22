#pragma once

#include <iostream>
#include "src/Socket/Server.h"
#include "src/Util/Coms/Message.h"
#include <thread>
#include "src/Util/Json.h"
#include "src/ServerManager.h"


using namespace std;
int main() {
    auto *sm = new ServerManager();

    string message = R"({"action":"CREATE","contentJson":"{\"key\":\"var\",\"value\":\"2\"}","type":"Integer","size":4})";
    string message2 = R"({"action":"CREATE","contentJson":"{\"key\":\"zzz\",\"value\":\"245\"}","type":"Integer","size":4})";

    string message3= R"({"action":"SEARCH", "firstVariable": "zzz" })";


    Message *msg = Json::readJsonMessage(message);
    Message *msg2 = Json::readJsonMessage(message2);
    Message *msg3 = Json::readJsonMessage(message3);


    Response *r = sm->processRequest(msg);
    r->show();
    sm->getMemory()->show();

    Response *r2 = sm->processRequest(msg2);
    r2->show();
    sm->getMemory()->show();

    //r3->show();



    return 0;

}
