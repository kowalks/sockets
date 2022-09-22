#include <sys/socket.h>
// #include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>


#include "../io/file.h"
#include "server.h"

void WebServer::connect(std::string ip, std::string port) {
    // creating TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // making socket avaliable
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    // socket address structure
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(stoi(port));     // porta tem 16 bits, logo short, network byte order
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

    // bind
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        exit(2);
    }

    //listen
    if (listen(sockfd, 1) == -1) {
        perror("listen");
        exit(3);
    }
}

HTTPReq WebServer::receive(int *clisockfd) {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    // accept connection at welcome socket
    *clisockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if (*clisockfd == -1) {
        perror("accept");
        exit(4);
    }

    // client info
    char ipstr[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
    std::cout << "Accept a connection from: " << ipstr
         << ":" << ntohs(clientAddr.sin_port) << std::endl;

    // receive request at welcome socket
    char buf[65535] = {0};
    if (recv(*clisockfd, buf, 65535, 0) == -1) {
        perror("recv");
        exit(5);
    }

    // constructs request
    HTTPReq req(buf);
    return req;
}

void WebServer::dispatch(HTTPResp (*serve)(HTTPReq), HTTPReq req, int clisockfd) {
    //executing serve function
    HTTPResp resp = (*serve)(req);

    // sending response message
    std::string message = resp.encode();
    if (::send(clisockfd, message.data(), message.size(), 0) == -1) {
        perror("send");
        return exit(6);
    }

    close(clisockfd);  
}

HTTPResp WebServer::serveLocalFiles(HTTPReq req) {
    HTTPResp resp;

    if (req.method == HTTPReq::GET) {
        auto path = req.url.getPath();
        auto body = rtrvfile(path);
        if (body.empty()) {
            resp.setStatusCode(404);
            std::cout << "\tstatus code 404 Not Found" << std::endl;
        } else {
            resp.setStatusCode(200);
            std::cout << "\tstatus code 200 OK" << std::endl;
            resp.setBody(body);
        }
    } else {
        resp.setStatusCode(405);
        std::cout << "\tstatus code 405 Method Not Allowed" << std::endl;
    }

    return resp;
}