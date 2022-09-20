#include "url.h"

void Url::parseAuth(std::string auth) {
    auto pos = auth.find(":");

    if (pos != std::string::npos) {
        authority.port = auth.substr(pos+1);
        auth = auth.substr(0,pos);
    }

    if ((pos = auth.find("@")) != std::string::npos) {
        authority.userinfo = auth.substr(0,pos);
        auth = auth.substr(pos+1);
    }

    authority.host = auth;
}

void Url::parse(std::string url) {
    auto pos = url.find(":");
    if (pos != std::string::npos) {
        scheme = url.substr(0,pos);
        url = url.substr(pos+1);
    } else {
        std::cerr << "find: url parse warning. did you forget 'http' protocol?" << std::endl;
        scheme = std::string("http");
        url = url.insert(0, "//");
    }

    
    if (url.substr(0,2).compare("//") == 0) {
        url = url.substr(2);
        if ((pos = url.find("/")) == std::string::npos) {
            std::cerr << "find: url parse warning. did you forget last '/'?" << std::endl;
            parseAuth(url);
            return;
        }
        
        parseAuth(url.substr(0,pos));
        url = url.substr(pos);
    }

    if ((pos = url.find("#")) != std::string::npos) {
        fragment = url.substr(pos+1);
        url = url.substr(0,pos);
    }

    if ((pos = url.find("?")) != std::string::npos) {
        query = url.substr(pos+1);
        url = url.substr(0,pos);
    }

    path = url;

    // std::cout << "scheme: $" << scheme << "$" << std::endl;
    // std::cout << "userinfo: $" << authority.userinfo << "$" << std::endl;
    // std::cout << "host: $" << authority.host << "$" << std::endl;
    // std::cout << "port: $" << authority.port << "$" << std::endl;
    // std::cout << "path: $" << path << "$" << std::endl;
    // std::cout << "query: $" << query << "$" << std::endl;
    // std::cout << "fragment: $" << fragment << "$" << std::endl;
}