#include "httpconn.h"

CHttpConnection::CHttpConnection() {

}

CHttpConnection::~CHttpConnection() {

}

bool CHttpConnection::read() {
    if (m_read_idx >= READ_BUFFER_SIZE)
    {
        return false;
    }
    int bytes_read = 0;

    while (true)
    {
        bytes_read = recv(fd, m_read_buf + m_read_idx, READ_BUFFER_SIZE - m_read_idx, 0);
        if (bytes_read == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            return false;
        }
        else if (bytes_read == 0)
        {
            return false;
        }
        m_read_idx += bytes_read;
    }
    printf("socket read : %s.\n", m_read_buf);
    return true;
}

void CHttpConnection::process() {

}