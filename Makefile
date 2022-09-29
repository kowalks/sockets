CXX=g++
CXXOPTIMIZE= -O2
CXXFLAGS= -g -Wall -pthread -std=c++11 $(CXXOPTIMIZE)
USERID=guilherme-kenji-yuri
CLASSES=net/url.cpp net/dns.cpp http/protocol.cpp http/request.cpp http/response.cpp  web-client/client.cpp  web-server/server.cpp io/file.cpp

all: server client

clean:
	rm -rf *.o *~ *.gch *.swp *.dSYM client server *.tar.gz

tarball: clean
	tar -cvf lab01-$(USERID).tar.gz *

server: $(CLASSES)
	$(CXX) -o $@ $^ $(CXXFLAGS) ./web-server/main.cpp

client: $(CLASSES)
	$(CXX) -o $@ $^ $(CXXFLAGS) ./web-client/main.cpp
