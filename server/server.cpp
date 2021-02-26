#include "server.h"

CServer::CServer(int port, int thread_num, int max_request, const char* root) : m_port(port), 
    m_thread_num(thread_num), m_max_request(max_request), m_root(root) {
    mHandler = new CHttpConnHandler(m_thread_num, m_max_request);
}

CServer::~CServer() {
    delete mHandler;
    
}

void CServer::run() {
    eventListen();
    eventLoop();
}