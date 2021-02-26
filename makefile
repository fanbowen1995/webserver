CXX ?= g++

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g
else
    CXXFLAGS += -O2

endif

server: main.cpp  ./http_conn/httpconn.cpp ./server/server.cpp ./server/epollserver.cpp ./httpconnhandler/httpconnhandler.cpp ./locker/locker.cpp
	$(CXX) -o server  $^ $(CXXFLAGS) -lpthread

clean:
	rm  -r server
