#ifndef WEB_SERVER_SERVER_H
#define WEB_SERVER_SERVER_H

#include "../http/request.h"
#include "../http/response.h"

class WebServer {
    int sockfd;

public:
    void connect(std::string ip, std::string port);
    HTTPReq receive(int* clisockfd);
    
    static void dispatch(HTTPResp (*serve)(HTTPReq), HTTPReq req, int clisockfd);
    static HTTPResp serveLocalFiles(HTTPReq req);
};

#endif