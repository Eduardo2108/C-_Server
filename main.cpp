#pragma once
#include <iostream>
#include "src/Socket/Server.h"
#include "librerias/spdlog/spdlog.h"

using namespace std;

void RunServer(int port, int size) {
    Server::getInstance(port, size)->InitServer();
}
int main() {
    int port;
    int size;
    spdlog::info("***********************************************");
    spdlog::info("*            Welcome to C! Server             *");
    spdlog::info("***********************************************");

    spdlog::info("Specify a port for the server to run:");
    cin >> port;
    if (port <= 0) {
        spdlog::critical(to_string(port) + " is not a valid port.");
        return -1;
    }
    spdlog::info("Specify the size (in bytes) the server will reserve for variables:");
    cin >> size;

    if (size <= 0) {
        spdlog::critical(to_string(size) + " is not a valid memory size.");
        return -1;
    }

    spdlog::info("Starting the server...");

    RunServer(port, size);
/*    string msg_1 = R"({"action":"CREATE","contentJson":"{\"key\":\"x\",\"value\":\"3\"}","type":"Integer","size":4})";
    string msg_2 = R"({"action":"CREATE","contentJson":"{\"key\":\"y\",\"value\":\"7\"}","type":"Integer","size":4})";
    string msg_3 = R"({"action":"MODIFY","firstVariable":"x","secondVariable":"y","operation":"="})";

    ServerManager::getInstance(15000)->processRequest(msg_1);
    ServerManager::getInstance(15000)->processRequest(msg_2);

    ServerManager::getInstance(15000)->processRequest(msg_3);
    ServerManager::getInstance()->getMemory()->show();*/


}