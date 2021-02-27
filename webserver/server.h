#ifndef EPOLLSERVER_H
#define EPOLLSERVER_H

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

const int MAX_FD = 65536;

class CServer {
public:
    CServer(int port, int thread_num, int max_request, int max_event_num, const char* root);
    ~CServer();
    void run();
private:
    void eventListen();
    void eventLoop();
    void dealClientAccept();
    void dealEpollIn(int fd);
    void dealEpollOut(int fd);
private:
    int m_port;
    const char* m_root;
    int m_max_request;
    int m_thread_num;
    CHttpConnHandler* mHandler;
    //epoll
    int socketfd;
    int epollfd;
    int m_max_event_num;
    epoll_event* events;
    CHttpConnection* connections;
};

#endif