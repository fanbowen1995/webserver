#ifndef HTTPCONNHANDLER_H
#define HTTPCONNHANDLER_H

#include <list>
#include <pthread.h>
#include <exception>

#include "../locker/locker.h"
#include "../httpconn/httpconn.h"

class CHttpConnHandler {
public:
    CHttpConnHandler(int thread_number, int max_request);
    ~CHttpConnHandler();
    bool addHttpConnection(CHttpConnection* conn, int state);
    bool addHttpConnection(CHttpConnection* conn);
private:
    static void* handle(void* arg);
    void run();
private:
    int m_thread_number;
    int m_max_request;
    pthread_t* m_threads;
    std::list<CHttpConnection*> m_queue;
    CMutex m_queueMutex;
    CSemaphore m_queueStat;
};

#endif