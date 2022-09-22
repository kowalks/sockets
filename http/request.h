#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <map>
#include <vector>
#include <iostream>

#include "protocol.h"
#include "../net/url.h"

class HTTPReq : public HTTPProtocol {

public:
    enum Method { GET, POST, PUT, DELETE, HEAD } method;
    Url url;

private:
    std::map <std::string, std::string> headers;
    std::string headers_;
    std::string body;

    std::map<std::string, Method> stringToMethod {
        {"GET", GET},
        {"POST", POST},
        {"PUT", PUT},
        {"DELETE", DELETE},
        {"HEAD", HEAD},
    };

public:
    HTTPReq() {};
    HTTPReq(Method method, Url url) : method(method), url(url) {};
    HTTPReq(std::string buff) { parse(buff); };
    HTTPReq(char *buff) { parse(std::string(buff)); };
    
    void parse(std::string buff);
    std::string encode();
    std::vector <uint8_t> bytecode();

    void setURL(Url url) { this->url = url; }
    void setHeader(std::string key, std::string value) { this->headers[key] = value; }

    friend std::ostream& operator<<(std::ostream& os, Method m);
};

#endif