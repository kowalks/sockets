#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <map>
#include <vector>
#include <iostream>

#include "protocol.h"

class HTTPReq : HTTPProtocol {
    Method method;
    std::string host;
    std::string dir;
    std::string url;
    std::map <std::string, std::string> headers;

public:
    std::string encode();
    std::vector <uint8_t> bytecode();

    void setURL(std::string url) { this->url = url; }
    void setMethod(Method method) { this->method = method; }
    void setHeader(std::string key, std::string value) { this->headers[key] = value; }
};

#endif