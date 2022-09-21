#include <string>

#include "response.h"

void HTTPResp::parse(std::string buff) {
    auto pos = buff.find("\r\n\r\n");
    auto head = buff.substr(0, pos);
    body = buff.substr(pos+4);

    // Head processing: HTTP/1.1 statusCode + headers
    pos = head.find("\n");
    if (pos == std::string::npos)
        pos = head.length();
    
    headers = head.substr(pos+1);
    auto statusLine = head.substr(0, pos);

    // processing status line
    pos = statusLine.find(" ");
    protocol = statusLine.substr(0,pos);
    statusLine = statusLine.substr(pos+1);
    pos = statusLine.find(" ");
    statusCode = statusLine.substr(0,pos);
    reasonPhrase = statusLine.substr(pos+1);

    // std::cout << "headers: " << headers << std::endl;
    // std::cout << "protocol: " << protocol << std::endl;
    // std::cout << "statusCode: " << statusCode << std::endl;
    // std::cout << "reasonPhrase: " << reasonPhrase << std::endl;
}