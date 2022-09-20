#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <fstream>

#include "../http/protocol.h"
#include "../http/request.h"
#include "../http/response.h"   
#include "../net/dns.h"
#include "../net/url.h"

int main (int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s url [url ...]\n", argv[0]);
        exit(-1);
    }

    Url url(argv[1]);

    std::string host = url.getHost();
    std::string port = url.getPort();
    if (port.length() == 0)
        port = "80";

    std::vector <std::string> ips = dns_resolution(host, port);

    // choosing first ip from now on.
    std::string ip = ips[0];

    // Creating TCP socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Sock address structure
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(stoi(port));
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    // connects to server from socket
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("connect");
        return 2;
    }
 
    // getting and printing client ip (optional)
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    if (getsockname(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen) == -1) {
        perror("getsockname");
        return 3;
    }
    char ipstr[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
    std::cout << "Set up a connection from: " << ipstr
        << ":" << ntohs(clientAddr.sin_port) << std::endl;

    // building the request
    HTTPReq req;
    req.setMethod(HTTPProtocol::GET);
    req.setURL(url);

    // sending packages
    std::string message = req.encode();
    if (send(sockfd, message.c_str(), message.size(), 0) == -1) {
        perror("send");
        return 4;
    }

    // receiving packages
    char buf[2000000] = {0};
    if (recv(sockfd, buf, 2000000, 0) == -1) {
        perror("recv");
        return 5;
    }

    // Saving into local dir
    std::string path = url.getPath();
    if (path.empty() or path.compare("/") == 0)
        path = "index.html";
    else path.insert(0, ".");
    std::cout << "Saving received message into " << path << std::endl;
    std::ofstream file(path);
    file << buf;
    file.close();

    // closing the socket
    close(sockfd);

    return 0;
}