// #include <sys/socket.h>
// #include <sys/types.h>
// #include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <vector>

#include "dns.h"

std::vector <std::string> dns_resolution(std::string node, std::string service) {
    struct addrinfo hints;
    struct addrinfo* res;
    std::vector <std::string> ips;

    // hints for configuring TCP transport layer
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP

    // getaddrinfo loads "res" buffer and gets "status" response code 
    int status = 0;
    if ((status = getaddrinfo(node.c_str(), service.c_str(), &hints, &res)) != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
        return std::vector <std::string>();
    }

    for(struct addrinfo* p = res; p != 0; p = p->ai_next) {
        struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;

        // converts ip address to string
        char ipstr[INET_ADDRSTRLEN] = {'\0'};
        inet_ntop(p->ai_family, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
        ips.push_back(std::string(ipstr));
    }

    freeaddrinfo(res);
    return ips;
}