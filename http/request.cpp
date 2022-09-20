#include <iostream>
#include <string.h>
#include <sstream>

#include "request.h"


std::string HTTPReq::encode() {
    std::stringstream message;

    std::string protocol = getProtocolVersion();
    std::string path = url.getPath();
    if (path.empty())
        path = "/";

    message << method << " " << path << " " << protocol << std::endl;
    message << "Host: " << url.getHost() << std::endl;
    for (auto& header : headers)
        message << header.first << ": " << header.second << std::endl;
    message << std::endl;
    
    message << data;
    
    return message.str();
}

std::vector <uint8_t> HTTPReq::bytecode() {
    std::string message = encode();
    std::vector <uint8_t> bytecode(message.begin(), message.end());
    return bytecode;
}