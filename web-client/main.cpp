#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <fstream>

#include "../http/request.h"
#include "../http/response.h"   
#include "../net/dns.h"
#include "../net/url.h"
#include "./client.h"

int main (int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s url [url ...]\n", argv[0]);
        exit(-1);
    }

    for (int i=1; i < argc; i++) {
        Url url(argv[i]);

        std::string host = url.getHost();
        std::string port = url.getPort();
        if (port.length() == 0)
            port = "80";

        // choosing first ip from now on.
        std::vector <std::string> ips = dns_resolution(host, port);
        std::string ip = ips[0];

        WebClient client;
        // connecting with tcp to ip:port
        client.connect(ip, port);

        // building the request
        HTTPReq req(HTTPReq::GET, url);

        // sending request and receiving response
        HTTPResp resp = client.send(req);

        // saving into local dir (full response request)
        WebClient::saveLocal(resp, url);

        // closing connection
        client.disconnect();
    }

    return 0;
}