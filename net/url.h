#ifndef NET_URL_H
#define NET_URL_H

#include <iostream>

class Url {
    std::string scheme;
    std::string path;
    std::string query;
    std::string fragment;
    struct Authority {
        std::string userinfo;
        std::string host;
        std::string port;
    } authority;

public:
    void parse(std::string url);
    void parseAuth (std::string auth);

    std::string getScheme() { return scheme; };
    std::string getPath() { return path; };
    std::string getQuery() { return query; };
    std::string getFragment() { return fragment; };
    std::string getUserinfo() { return authority.userinfo; };
    std::string getHost() { return authority.host; };
    std::string getPort() { return authority.port; };
    Authority getAuthority() { return authority; };
};


#endif