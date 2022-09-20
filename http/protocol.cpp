#include <iostream>

#include "protocol.h"


std::ostream& operator<<(std::ostream& os, HTTPProtocol::Method m) {
    switch(m) {
        case HTTPProtocol::GET:     os << "GET";    break;
        case HTTPProtocol::POST:    os << "POST";   break;
        case HTTPProtocol::PUT:     os << "PUT";    break;
        case HTTPProtocol::DELETE:  os << "DELETE"; break;
        case HTTPProtocol::HEAD:    os << "HEAD";   break;
        default:                    os.setstate(std::ios_base::failbit);
    }
    return os;
}