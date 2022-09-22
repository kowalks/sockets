#include <string.h>
#include <thread>

#include "../net/dns.h"
#include "../http/request.h"
#include "../http/response.h"
#include "server.h"


int main (int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s [host] [port] [dir]\n", argv[0]);
        exit(-1);
    }

    std::string host = argv[1];
    std::string port = argv[2];
    std::string dir = argv[3];

    // choosing first ip from now on.
    std::vector <std::string> ips = dns_resolution(host, port);
    std::string ip = ips[0];

    WebServer server;
    server.chdir(dir);

    // open connection and listen to socket
    server.connect(ip, port);

    // receive connection and multithread dispatch
    int sockfd;
    while(true) {
        HTTPReq req = server.receive(&sockfd);
        std::thread(WebServer::dispatch, WebServer::serveLocalFiles, req, sockfd).detach();
    }
}