//
// Created by josea4718 on 4/22/21.
//

#include <iostream>
#include <cstring>
#include "string"
#include "Server.h"

Server* Server::unique_instance = NULL;
Server::Server() {}

Server *Server::getInstance() {
    if (unique_instance == NULL){
        unique_instance = new Server();
    }
    return unique_instance;
}