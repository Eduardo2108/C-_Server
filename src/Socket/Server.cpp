//
// Created by josea4718 on 4/22/21.
//

#include <iostream>
#include <cstring>
#include "string"
#include "Server.h"

Server* Server::unique_instance = NULL;
Server::Server(int port, int size) {
    this->port = port;
    this->size = size;
}

Server::Server() {}

Server *Server::getInstance(int port, int size) {
    if (unique_instance == NULL) {
        unique_instance = new Server(port, size);
    }
    return unique_instance;
}