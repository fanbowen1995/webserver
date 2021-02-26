#ifndef EPOLLSERVER_H
#define EPOLLSERVER_H

#include "../config.h"
#include "server.h"
#include "../httpconn/httpconn.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>

class CEpollServer : public CServer {
public:
    CEpollServer(int port, int thread_num, int max_request, int max_event_num, const char* root);
    virtual ~CEpollServer();
private:
    virtual void eventListen();
    virtual void eventLoop();
    virtual void dealClientData();
    virtual void dealEpollIn(int fd);
    virtual void dealEpollOut(int fd);
private:
    int socketfd;
    int epollfd;
    int m_max_event_num;
    epoll_event* events;
    CHttpConnection* connections;
};

#endif