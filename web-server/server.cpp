// #include <sys/types.h>
#include <sys/socket.h>
// #include <netinet/in.h>
#include <arpa/inet.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "server.h"

void WebServer::serve(std::string port) {
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

    // accept connection
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrSize);

    if (clientSockfd == -1) {
        perror("accept");
        exit(4);
    }

    // displays client ip
    char ipstr[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
    std::cout << "Accept a connection from: " << ipstr
         << ":" << ntohs(clientAddr.sin_port) << std::endl;


    while(true) {
        // receive and parse request
        char buf[65535] = {0};
        if (recv(clientSockfd, buf, 65535, 0) == -1) {
            perror("recv");
            exit(5);
        }
        HTTPReq req(buf);

        // send response
        if (req.method == HTTPReq::GET) {
            auto path = req.url.getPath();
            path = path.insert(0, ".");
            std::cout << "Serving file at " << path << std::endl;
            std::ifstream file(path);
            std::string body;

            std::ostringstream ss;
            ss << file.rdbuf();
            body = ss.str();

            std::cout << "body:" << body;

            HTTPResp resp;
            resp.setStatusCode(200);
            resp.setReasonPhrase("OK");
            resp.setBody(body);

            std::string message = resp.encode();
            if (send(clientSockfd, message.data(), message.size(), 0) == -1) {
                perror("send");
                return exit(6);
            }
            
            
            std::cout << "sent message:" << std::endl << message << "$";

        }

        break;
    }

    
}