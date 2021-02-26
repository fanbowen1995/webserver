#ifndef HTTPCONN_H
#define HTTPCONN_H

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <map>

#include "../locker/locker.h"

const int FILENAME_LEN = 200;
const int READ_BUFFER_SIZE = 2048;
const int WRITE_BUFFER_SIZE = 1024;


class CHttpConnection {
public:
    CHttpConnection();
    ~CHttpConnection();
    void process();
    bool read();
    bool write();
public:
    int m_state;
    int timer_flag;
    int improv;
    int fd;
    //static int m_user_count;
private:
    void init();
private:
    char m_read_buf[READ_BUFFER_SIZE];
    int m_read_idx;
    int m_checked_idx;
    int m_start_line;
    char m_write_buf[WRITE_BUFFER_SIZE];
    int m_write_idx;
};

#endif