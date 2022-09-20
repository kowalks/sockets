#include <iostream>
#include <string.h>
#include <sstream>

#include "request.h"


std::string HTTPReq::encode() {
    std::ostringstream message;
    std::string protocol = getProtocolVersion();
    // std::vector <uint8_t> bytecode;

    message << method << " " << url << " " << protocol << "\r\n\r\n";
    // std::memcpy(&bytecode, message.data(), message.length());
    // std::cout << message << std::endl;
    // return bytecode;
    return message.str();
}

// HTTPResp parse(std::vector <uint8_t> bytecode) {
//     return;
// }