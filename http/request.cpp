#include <iostream>
#include <string.h>
#include <sstream>
#include <map>

#include "request.h"


std::string HTTPReq::encode() {
    std::stringstream message;

    std::string path = url.getPath();
    if (path.empty())
        path = "/";

    // HTTP request protocol
    message << method << " " << path << " " << protocolVersion << "\r\n";
    message << "Host: " << url.getHost() << "\r\n";
    for (auto& header : headers)
        message << header.first << ": " << header.second << "\r\n";
    message << "\r\n";
    message << body;
    
    return message.str();
}

std::vector <uint8_t> HTTPReq::bytecode() {
    std::string message = encode();
    std::vector <uint8_t> bytecode(message.begin(), message.end());
    return bytecode;
}

void HTTPReq::parse(std::string buff) {
    message = buff;

    auto pos = buff.find("\r\n\r\n");
    auto head = buff.substr(0, pos);
    body = buff.substr(pos+4);

    // Head processing: HTTP/1.1 statusCode + headers
    pos = head.find("\r\n");
    if (pos == std::string::npos)
        pos = head.length();
    
    headers_ = head.substr(pos+2); // TODO: parse headers into header map
    auto requestLine = head.substr(0, pos);

    // processing request line (TODO: parse URL)
    pos = requestLine.find(" ");
    method = stringToMethod[requestLine.substr(0,pos)];
    requestLine = requestLine.substr(pos+1);

    pos = requestLine.find(" ");
    url = Url("http://127.0.0.1" + requestLine.substr(0,pos));
    requestLine = requestLine.substr(pos+1);

    pos = requestLine.find(" ");
    auto protocol = requestLine.substr(pos+1);

    if (protocol != protocolVersion) {
        std::cout << "\tReceived protocol '" << protocol << "' is not supported." << std::endl;
        std::cout << "\tInterpreting it as 'HTTP/1.0'." << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, HTTPReq::Method m) {
    switch(m) {
        case HTTPReq::GET:     os << "GET";    break;
        case HTTPReq::POST:    os << "POST";   break;
        case HTTPReq::PUT:     os << "PUT";    break;
        case HTTPReq::DELETE:  os << "DELETE"; break;
        case HTTPReq::HEAD:    os << "HEAD";   break;
        default:               os.setstate(std::ios_base::failbit);
    }
    return os;
}