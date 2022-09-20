// #include <sys/socket.h>
// #include <sys/types.h>
// #include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <vector>

#include "dns.h"

std::vector <std::string> dns_resolution(std::string node, std::string service) {
    struct addrinfo hints;
    struct addrinfo* res;
    std::vector <std::string> ips;

    // hints - modo de configurar o socket para o tipo  de transporte
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP

    // funcao de obtencao do endereco via DNS - getaddrinfo 
    // funcao preenche o buffer "res" e obtem o codigo de resposta "status" 
    int status = 0;
    if ((status = getaddrinfo(node.c_str(), service.c_str(), &hints, &res)) != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
        return std::vector <std::string>();
    }

    for(struct addrinfo* p = res; p != 0; p = p->ai_next) {
        // a estrutura de dados eh generica e portanto precisa de type cast
        struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;

        // e depois eh preciso realizar a conversao do endereco IP para string
        char ipstr[INET_ADDRSTRLEN] = {'\0'};
        inet_ntop(p->ai_family, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
        ips.push_back(std::string(ipstr));
    }

    freeaddrinfo(res);
    return ips;
}