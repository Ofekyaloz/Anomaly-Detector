
#include "Server.h"


Server::Server(int port)throw (const char*) {
    // create new socket in tcp protocol and ipv4
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    if (socketID < 0) {
        throw "Socket failed";
    }

    // define the type ip of the server, the ip and the port
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    shouldStop = false;

    // bind the server to the address
    if (bind(socketID, (struct sockaddr *) &server, sizeof(server)) < 0)
        throw "bind failure";

    // listen to four clients or less
    if (listen(socketID, 4) < 0)
        throw "listen failure";
}

void sigHandler(int sigNum){
    cout<<"sidH"<<endl;
}

void Server::start(ClientHandler& ch)throw(const char*) {
    t = new thread([&ch, this]() {
        signal(SIGALRM, sigHandler);
        // run the server while the shouldStop member is false (until call the stop function)
        while (!shouldStop) {
            alarm(1);

            // accept a new client and handle him
            socklen_t size = sizeof(client);
            int clientAccepted = accept(socketID, (struct sockaddr *) &client, &size);
            if (clientAccepted > 0) {
                ch.handle(clientAccepted);

                close(clientAccepted);
            }
            alarm(0);
        }

        // close the socket
        close(socketID);
    });
}

// update the stop member to close the server
void Server::stop() {
    shouldStop = true;
//	t->join();
}

Server::~Server() {
//    delete[] this->t;
}

// read the text
string socketIO::read() {
    string buffer = "";
    char c = ' ';

    // read characters until new line
    while (c != '\n') {
        recv(clientID, &c, sizeof(char), 0);
        buffer += c;
    }
    return buffer;
}

// read the number
void socketIO::read(float *f) {
    string buffer = read();
    *f = stof(buffer);
}

// write the text
void socketIO::write(string text) {
    const char *constText = text.c_str();
    send(clientID, constText, text.size(), 0);
}

// write the number
void socketIO::write(float f) {
    ostringstream ss;
    ss << f;
    string s(ss.str());
    write(s);
}
