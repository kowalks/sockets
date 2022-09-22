CXX=g++
CXXOPTIMIZE= -O2
CXXFLAGS= -g -Wall -pthread -std=c++11 $(CXXOPTIMIZE)
USERID=cesarmarcondes
CLASSES=net/url.cpp net/dns.cpp http/protocol.cpp http/request.cpp http/response.cpp  web-client/client.cpp  web-server/server.cpp

all: server client
echo-server: 
	$(CXX) -o $@ $^ $(CXXFLAGS) $@.cpp
echo-client: 
	$(CXX) -o $@ $^ $(CXXFLAGS) $@.cpp
multi-thread:
	$(CXX) -o $@ $^ $(CXXFLAGS) $@.cpp
showip:
	$(CXX) -o $@ $^ $(CXXFLAGS) $@.cpp
clean:
	rm -rf *.o *~ *.gch *.swp *.dSYM multi-thread showip echo-server echo-client client server *.tar.gz
tarball: clean
	tar -cvf lab02-$(USERID).tar.gz *


server: $(CLASSES)
	$(CXX) -o $@ $^ $(CXXFLAGS) ./web-server/main.cpp

client: $(CLASSES)
	$(CXX) -o $@ $^ $(CXXFLAGS) ./web-client/main.cpp
