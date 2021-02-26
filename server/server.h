#ifndef SERVER_H
#define SERVER_H

#include "../httpconnhandler/httpconnhandler.h"

class CServer {
public:
    CServer(int port, int thread_num, int max_request, const char* root);
    virtual ~CServer();
    virtual void run();
private:
    virtual void eventListen() = 0;
    virtual void eventLoop() = 0;
    // virtual bool dealClientData() = 0;
    // virtual bool dealEpollIn(int fd) = 0;
    // virtual bool dealEpollOut(int fd) = 0;
private:
    int m_port;
    const char* m_root;
    int m_max_request;
    int m_thread_num;
    CHttpConnHandler* mHandler;
};

#endif