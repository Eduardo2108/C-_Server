//
// Created by josea4718 on 4/19/21.
//

#include <iostream>
#include "string"
#include "Server.h"
#include "stdio.h"

Server *Server::instance = nullptr;



Server* Server::getInstance() {
    if (Server::instance == nullptr) {
        Server::instance = new Server();
    }
    return Server::instance;
}


void Server::Send(char *msg) {
    send(clientSocket, msg, strlen(msg) , 0);
}