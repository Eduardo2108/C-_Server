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

    void Start() {

        listening = socket(AF_INET, SOCK_STREAM, 0);
        if (listening == -1) {
            std::cerr << "Can't create a socket! Quitting" << std::endl;
            exit(-1);
        }

        hint.sin_family = AF_INET;
        hint.sin_port = htons(PORT);
        inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

        bind(listening, (sockaddr *) &hint, sizeof(hint));

        // Tell Winsock the socket is for listening
        listen(listening, SOMAXCONN);

        clientSocket = accept(listening, (sockaddr *) &client, &clientSize);

        memset(host, 0, NI_MAXHOST);
        memset(service, 0, NI_MAXSERV);

        if (getnameinfo((sockaddr *) &client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
            std::cout << host << " connected on port " << service << std::endl;
        } else {
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
        }

        // Close listening socket
        close(listening);

        while (true) {
            std::cout << "Im running" << std::endl;
            memset(buf, 0, 4096);
            // Wait for client to send data
            bytesReceived = recv(clientSocket, buf, 4096, 0);
            if (bytesReceived == -1) {
                std::cerr << "Error in recv(). Quitting" << std::endl;
                break;
            }

            if (bytesReceived == 0) {
                std::cout << "Client disconnected " << std::endl;
                break;
            }

            std::cout << std::string(buf, 0, bytesReceived) << std::endl;

            // Echo message back to client
            //send(clientSocket, buf, bytesReceived - 1 , 0);
        }

        // Close the socket
        close(clientSocket);
    }

    void Send(char *);

    static Server *getInstance();
};
