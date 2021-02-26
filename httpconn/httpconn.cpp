#include "httpconn.h"

CHttpConnection::CHttpConnection() {

}

CHttpConnection::~CHttpConnection() {

}

bool CHttpConnection::read() {
    printf("CHttpConnection::read.\n");
    if (m_read_idx >= READ_BUFFER_SIZE)
    {
        return false;
    }
    int bytes_read = 0;

    bytes_read = recv(fd, m_read_buf + m_read_idx, READ_BUFFER_SIZE - m_read_idx, 0);
    m_read_idx += bytes_read;

    if (bytes_read <= 0)
    {
        return false;
    }

    return true;
    
    printf("socket read : %s.\n", m_read_buf);
    return true;
}

bool CHttpConnection::write() {
    printf("CHttpConnection::write.\n");
    return false;
}

void CHttpConnection::process() {

}