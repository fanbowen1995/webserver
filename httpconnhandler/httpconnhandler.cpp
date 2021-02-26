#include "httpconnhandler.h"

CHttpConnHandler::CHttpConnHandler(int thread_number, 
    int max_request) : m_thread_number(thread_number), m_max_request(max_request) {
        m_threads = new pthread_t[m_thread_number];
        assert(!m_threads);
        for(int i = 0; i < m_thread_number; i++) {
            if(pthread_create(m_threads + i, nullptr, handle, this) != 0) {
                delete[] m_threads;
                throw std::exception();
            }
            if(pthread_detach(m_threads[i])) {
                delete[] m_threads;
                throw std::exception();
            }
        }
    }

CHttpConnHandler::~CHttpConnHandler() {
    delete[] m_threads;
}

bool CHttpConnHandler::addHttpConnection(CHttpConnection* conn, int state) {
    m_queueMutex.lock();
    if(m_queue.size() >= m_max_request) {
        m_queueMutex.unlock();
        return false;
    }
    conn->m_state = state;
    m_queue.push_back(conn);
    m_queueMutex.unlock();
    m_queueStat.post();
    return true;
}

bool CHttpConnHandler::addHttpConnection(CHttpConnection* conn) {
    m_queueMutex.lock();
    if(m_queue.size() >= m_max_request) {
        m_queueMutex.unlock();
        return false;
    }
    m_queue.push_back(conn);
    m_queueMutex.unlock();
    m_queueStat.post();
    return true;
}

void* CHttpConnHandler::handle(void* arg) {
    CHttpConnHandler* handler = (CHttpConnHandler*) arg;
    handler->run();
    return handler;
}

void CHttpConnHandler::run() {
    while(true) {
        m_queueStat.wait();
        m_queueMutex.lock();
        if(m_queue.empty()) {
            m_queueMutex.unlock();
            continue;
        }
        CHttpConnection* conn = m_queue.front();
        m_queue.pop_front();
        m_queueMutex.unlock();
        if(!conn) continue;
        if(0 == conn->m_state) {
            if(conn->read()) {
                conn->improv = 1;
                conn->process();
            }
            else {
                conn->improv = 1;
                conn->timer_flag = 1;
            }
        }
        else {
            if(conn->write()) {
                conn->improv = 1;
            }
            else {
                conn->improv = 1;
                conn->timer_flag = 1;
            }
        }
    }
}