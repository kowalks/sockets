// #include <sys/socket.h>
// #include <sys/types.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
#include <string.h>
// #include <netdb.h>
// #include <errno.h>
// #include <unistd.h>
#include <iostream>
// #include <sstream>

// #include "../http/protocol.h"
// #include "../http/request.h"
// #include "../http/response.h"
#include "server.h"

#define debug(x) std::cout << (x) << std::endl;




int main (int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s [host] [port] [dir]\n", argv[0]);
        exit(-1);
    }

    const char *host = argv[1];
    std::string dir = argv[3];
    int port = std::stoi(argv[2]);


    WebServer server;

    server.serve("8000");
}