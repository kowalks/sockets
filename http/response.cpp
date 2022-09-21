#include "response.h"



void HTTPResp::parse(std::string buff) {
    auto pos = buff.find("\r\n\r\n");
    auto head = buff.substr(0, pos);
    body = buff.substr(pos+4);

    // std::cout << "pos: " << pos << std::endl;
    // std::cout << "head: " << head << std::endl;
    // std::cout << "body: " << body << std::endl;

    // Head processing: HTTP/1.1 statusCode + headers
    pos = head.find("\n");
    if (pos == std::string::npos)
        pos = head.length();

    auto statusLine = head.substr(0, pos);
}