//
// Created by josea4718 on 4/19/21.
//

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


#pragma once

class Server {
private:
    int listening;
    int PORT = 5000;
    int clientSocket;
    int bytesReceived;
    sockaddr_in hint;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    char buf[4096];

    static Server *instance;

public:
    Server();
    void Start();
    void Send(char *);
    static Server* getInstance();
};
