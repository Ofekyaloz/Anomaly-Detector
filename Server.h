/*
 * Authors: Gili Gutfeld & Ofek Yaloz
 */

#ifndef SERVER_H_
#define SERVER_H_


#include <iostream>
#include <sys/socket.h>  // The header file socket.h includes a number of definitions of structures needed for sockets.
#include <netinet/in.h>  // The header file in.h contains constants and structures needed for internet domain addresses.

#include <pthread.h>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<signal.h>
#include <sstream>

#include "CLI.h"

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file

class socketIO:public DefaultIO{
    int clientID;
public:
    socketIO(int clientID):clientID(clientID){}
    virtual string read();
    virtual void read(float *f);
    virtual void write(string text);
    virtual void write(float f);
};

// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler {
public:
    virtual void handle(int clientID) {
        socketIO sock(clientID);
        CLI cli(&sock);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    std::thread* t; // the thread to run the start() method in
    int socketID;
    sockaddr_in server;
    sockaddr_in client;
    volatile bool shouldStop;

public:
    Server(int port) throw(const char *);
    virtual ~Server();
    void start(ClientHandler &ch) throw(const char *);
    void stop();
    void run(ClientHandler &ch);
};

#endif /* SERVER_H_ */
