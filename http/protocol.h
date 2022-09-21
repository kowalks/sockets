#ifndef HTTP_PROTOCOL_H
#define HTTP_PROTOCOL_H

#include <iostream>

class HTTPProtocol {
    std::string protocolVersion = "HTTP/1.1";

public:
    enum Method { GET, POST, PUT, DELETE, HEAD };
    friend std::ostream& operator<<(std::ostream& os, Method m);

    std::string getProtocolVersion() { return protocolVersion; };
};

#endif