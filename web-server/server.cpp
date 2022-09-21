#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
// #include <errno.h>
// #include <unistd.h>
// #include <iostream>
// #include <sstream>

#include "../http/protocol.h"
#include "../http/request.h"
#include "../http/response.h"

#define debug(x) std::cout << (x) << std::endl;




int main (int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s [host] [port] [dir]\n", argv[0]);
        exit(-1);
    }

    const char *host = argv[1];
    std::string dir = argv[3];
    int port = std::stoi(argv[2]);


    // cria um socket para IPv4 e usando protocolo de transporte TCP
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Opções de configuração do SOCKETs
    // No sistema Unix um socket local TCP fica preso e indisponível 
    // por algum tempo após close, a não ser que configurado SO_REUSEADDR
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);     // porta tem 16 bits, logo short, network byte order
    addr.sin_addr.s_addr = inet_addr(host);
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

    // realizar o bind (registrar a porta para uso com o SO) para o socket
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        return 2;
    }

    // colocar o socket em modo de escuta, ouvindo a porta 
    if (listen(sockfd, 1) == -1) {
        perror("listen");
        return 3;
    }

    // aceitar a conexao TCP
    // verificar que sockfd e clientSockfd sao sockets diferentes
    // sockfd eh a "socket de boas vindas"
    // clientSockfd eh a "socket diretamente com o cliente"
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrSize);

    if (clientSockfd == -1) {
    perror("accept");
        return 4;
    }

    // usa um vetor de caracteres para preencher o endereço IP do cliente
    char ipstr[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ipstr, sizeof(ipstr));
    std::cout << "Accept a connection from: " << ipstr << ":"
        << ntohs(clientAddr.sin_port) << std::endl;

}