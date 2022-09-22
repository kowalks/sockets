#ifndef HTTP_PROTOCOL_H
#define HTTP_PROTOCOL_H

#include <iostream>

class HTTPProtocol {
    
protected:
    std::string protocolVersion = "HTTP/1.0";
    std::string message;

public:
    friend std::ostream& operator<<(std::ostream& os, HTTPProtocol p) { return os << p.message; };
};

#endif