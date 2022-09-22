#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#include <iostream>
#include <fstream>

#include "../io/file.h"
#include "client.h"

void WebClient::connect(std::string ip, std::string port) {
    // creating TCP socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // socket address structure
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(stoi(port));
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    // connecting to server from socket
    if (::connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("connect");
        exit(2);
    }

    this->sockfd = sockfd;
}

void WebClient::disconnect() {
    close(sockfd);
    sockfd = 0;
}

void WebClient::client_ip_info() {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    if (getsockname(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen) == -1) {
        perror("getsockname");
        exit(3);
    }
    char ipstr[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
    std::cout << "Set up a connection from: " << ipstr
        << ":" << ntohs(clientAddr.sin_port) << std::endl;
}

HTTPResp WebClient::send(HTTPReq req, int buffersize) {
    // sending packages
    std::string message = req.encode();
    if (::send(sockfd, message.c_str(), message.size(), 0) == -1) {
        perror("send");
        exit(4);
    }

    // receiving packages
    message.clear();
    std::vector<char> buf(buffersize);
    int status;

    do {
        status = recv(sockfd, buf.data(), buf.size(), 0);
        message.append(buf.data(), status);
    } while(status > 0);

    if (status== -1) {
        perror("recv");
        exit(5);
    }

    HTTPResp resp(message);
    return resp;
}

void WebClient::saveLocal(HTTPResp resp, Url url) {
    std::cout << resp.getStatusCode() << " " << resp.getReasonPhrase() << std::endl;
    if (resp.getStatusCode() == 200) {
        // Normalizing path
        std::string path = url.getPath();
        if (path.empty() or path == "/")
            path = "index.html";
        else path.insert(0, ".");

        std::cout << "\tsaving received message into " << path << std::endl;
        savefile(path, resp.getBody());
    } else {
        std::cout << "\tcannot retrieve file" << std::endl;
    }
}