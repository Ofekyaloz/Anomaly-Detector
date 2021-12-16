/*
 * Authors: Gili Gutfeld & Ofek Yaloz
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "commands.h"
#include <thread>
#include <pthread.h>
#include <netinet/in.h>
#include "CLI.h"
#include <signal.h>
#include "sys/socket.h"
#include <unistd.h>
#include <sstream>

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
    thread *t; // the thread to run the start() method in
    int socketID;
    sockaddr_in server;
    sockaddr_in client;
    volatile bool shouldStop;

public:
    Server(int port) throw(const char *);
    virtual ~Server();
    void start(ClientHandler &ch) throw(const char *);
    void stop();
};

#endif /* SERVER_H_ */
