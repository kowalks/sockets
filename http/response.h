#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "protocol.h"

class HTTPResp : HTTPProtocol {
    int statusCode;
    
public:
    void setStatusCode(int statusCode) { this->statusCode = statusCode; };
};

#endif