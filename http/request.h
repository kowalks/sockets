#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <map>
#include <vector>
#include <iostream>

#include "protocol.h"
#include "../net/url.h"

class HTTPReq : HTTPProtocol {
    Method method;
    Url url;
    std::map <std::string, std::string> headers;
    std::string data;

public:
    std::string encode();
    std::vector <uint8_t> bytecode();

    void setURL(Url url) { this->url = url; }
    void setMethod(Method method) { this->method = method; }
    void setHeader(std::string key, std::string value) { this->headers[key] = value; }
};

#endif