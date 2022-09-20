#include "../http/protocol.h"
#include "../http/request.h"
#include "../http/response.h"   
#include "../net/dns.h"
#include "../net/url.h"

int main (int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s url [url ...]\n", argv[0]);
        exit(-1);
    }

    Url url(argv[1]);

    std::string host = url.getHost();
    std::string port = url.getPort();
    std::vector <std::string> ips = dns_resolution(host, port);

    // choosing first ip from now on.
    std::string ip = ips[0];

    // making the request
    HTTPReq req;
    req.setMethod(HTTPProtocol::GET);
    req.setURL(url);

    for (auto& ip : ips) {
        std::cout << ip << std::endl;
    }
}