#include <string>
#include <sstream>

#include "response.h"

void HTTPResp::parse(std::string buff) {
    message = buff;

    auto pos = buff.find("\r\n\r\n");
    auto head = buff.substr(0, pos);
    body = buff.substr(pos+4);

    // Head processing: HTTP/1.1 statusCode + headers
    pos = head.find("\r\n");
    if (pos == std::string::npos)
        pos = head.size();
    else
        headers_ = head.substr(pos+2);
    auto statusLine = head.substr(0, pos);

    // processing status line
    pos = statusLine.find(" ");
    protocol = statusLine.substr(0,pos);
    statusLine = statusLine.substr(pos+1);
    pos = statusLine.find(" ");
    statusCode = statusLine.substr(0,pos);
    reasonPhrase = statusLine.substr(pos+1);

    if (protocol != protocolVersion) {
        std::cout << "Received protocol '" << protocol << "' is not supported." << std::endl;
        exit(10);
    }
}

std::string HTTPResp::encode() {
    std::stringstream message;

    // HTTP response protocol
    message << protocol << " " << statusCode << " " << reasonPhrase << "\r\n";
    for (auto& header : headers)
        message << header.first << ": " << header.second << "\r\n";
    message << "\r\n";
    message << body;

    return message.str();
}