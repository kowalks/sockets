#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <map>

#include "protocol.h"

class HTTPResp : public HTTPProtocol {
    std::string protocol;
    std::string statusCode;
    std::string reasonPhrase;
    std::string body;

    // TODO: parse into a map 
    std::string headers_;
    std::map <std::string, std::string> headers;

public:
    HTTPResp() { protocol = protocolVersion; };
    HTTPResp(std::string buff) { parse(buff); };
    HTTPResp(char *buff) { parse(std::string(buff)); };

    void parse(std::string buff);
    std::string encode();

    int getStatusCode() {return stoi(statusCode); };
    std::string getProtocol() { return protocol; };
    std::string getReasonPhrase() { return reasonPhrase; };
    std::string getBody() { return body; };

    void setReasonPhrase(std::string reasonPhrase) { this->reasonPhrase = reasonPhrase; };
    void setStatusCode(int statusCode) { this->statusCode = std::to_string(statusCode); };
    void setBody(std::string body) { this->body = body; };
};

#endif