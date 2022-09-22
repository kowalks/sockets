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

    std::map<int, std::string> statusCodetoReasonPhrase {
        {100, "Continue"},
        {101, "Switching Protocols"},
        {200, "OK"},
        {201, "Created"},
        {202, "Accepted"},
        {203, "Non-Authoritative Information"},
        {204, "No Content"},
        {205, "Reset Content"},
        {206, "Partial Content"},
        {300, "Multiple Choices"},
        {301, "Moved Permanently"},
        {302, "Found"},
        {303, "See Other"},
        {304, "Not Modified"},
        {305, "Use Proxy"},
        {306, "(Unused)"},
        {307, "Temporary Redirect"},
        {400, "Bad Request"},
        {401, "Unauthorized"},
        {402, "Payment Required"},
        {403, "Forbidden"},
        {404, "Not Found"},
        {405, "Method Not Allowed"},
        {406, "Not Acceptable"},
        {407, "Proxy Authentication Required"},
        {408, "Request Timeout"},
        {409, "Conflict"},
        {410, "Gone"},
        {411, "Length Required"},
        {412, "Precondition Failed"},
        {413, "Request Entity Too Large"},
        {414, "Request-URI Too Long"},
        {415, "Unsupported Media Type"},
        {416, "Requested Range Not Satisfiable"},
        {417, "Expectation Failed"},
        {500, "Internal Server Error"},
        {501, "Not Implemented"},
        {502, "Bad Gateway"},
        {503, "Service Unavailable"},
        {504, "Gateway Timeout"},
        {505, "HTTP Version Not Supported"}
    };

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

    void setStatusCode(int statusCode) { this->statusCode = std::to_string(statusCode); reasonPhrase = statusCodetoReasonPhrase[statusCode]; };
    void setBody(std::string body) { this->body = body; };
};

#endif