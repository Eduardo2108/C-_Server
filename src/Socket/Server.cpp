//
// Created by josea4718 on 4/22/21.
//

#include <iostream>
#include <cstring>
#include "string"
#include "Server.h"

Server* Server::unique_instance = NULL;
Server::Server(int port) {}

Server::Server() {}

Server *Server::getInstance(int port = 0) {
    if (unique_instance == NULL) {
        unique_instance = new Server(port);
    }
    return unique_instance;
}