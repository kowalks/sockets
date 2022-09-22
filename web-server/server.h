#ifndef WEB_SERVER_SERVER_H
#define WEB_SERVER_SERVER_H

#include "../http/request.h"
#include "../http/response.h"

class WebServer {
    int sockfd;

public:
    void serve(std::string port);
};

#endif