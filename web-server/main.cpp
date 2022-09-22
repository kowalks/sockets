#include <sys/socket.h>
// #include <sys/types.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
#include <string.h>
#include <thread>
// #include <netdb.h>
// #include <errno.h>
// #include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>

// #include "../http/protocol.h"
#include "../http/request.h"
#include "../http/response.h"
#include "server.h"


int main (int argc, char *argv[]) {
//     if (argc != 4) {
// std::cout << argc << "<<<<\n";
//         fprintf(stderr, "usage: %s [host] [port] [dir]\n", argv[0]);
//         exit(-1);
//     }

    // const char *host = argv[1];
    // std::string dir = argv[3];
    // int port = std::stoi(argv[2]);

    WebServer server;

    // open connection and listen to socket
    server.connect("127.0.0.1", "8000");

    // receive connection and multithread dispatch
    int sockfd;
    while(true) {
        HTTPReq req = server.receive(&sockfd);
        std::thread(WebServer::dispatch, WebServer::serveLocalFiles, req, sockfd).detach();
    }
}