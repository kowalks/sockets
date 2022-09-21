#ifndef WEB_CLIENT_CLIENT_H
#define WEB_CLIENT_CLIENT_H

#include "../http/request.h"
#include "../http/response.h"

class WebClient {
    int sockfd;

public:
    void connect(std::string ip, std::string port);
    void disconnect();
    void client_ip_info();
    HTTPResp send(HTTPReq req, int buffersize = 65535);
};

#endif