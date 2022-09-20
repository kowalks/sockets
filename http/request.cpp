#include <iostream>
#include <string.h>
#include <sstream>

#include "request.h"


std::string HTTPReq::encode() {
    std::stringstream message;
    std::string protocol = getProtocolVersion();

    message << method << " " << url << " " << protocol << "\r\n\r\n";
    
    return message.str();
}

std::vector <uint8_t> HTTPReq::bytecode() {
    std::string message = encode();
    std::vector <uint8_t> bytecode(message.begin(), message.end());
    return bytecode;
}