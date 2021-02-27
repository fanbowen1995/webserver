#include "server.h"

CServer::CServer(int port, int thread_num, int max_request, int max_event_num, const char* root) : 
    m_port(port), m_thread_num(thread_num), m_max_request(max_request), m_root(root), m_max_event_num(max_event_num) {
    mHandler = new CHttpConnHandler(m_thread_num, m_max_request);
    events = new epoll_event[m_max_event_num];
    connections = new CHttpConnection[MAX_FD];
}

CServer::~CServer() {
    close(epollfd);
    close(socketfd);
    delete[] events;
}

void CServer::run() {
    eventListen();
    eventLoop();
}

static void setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
}

static void add_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void CServer::eventListen() {
    printf("CServer::eventListen.\n");
    socketfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(socketfd >= 0);

    struct linger tmp = {0, 1};
    setsockopt(socketfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(m_port);

    int flag = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    ret = bind(socketfd, (sockaddr*) &address, sizeof(address));
    assert(ret >= 0);
    ret = listen(socketfd, 5);

    epollfd = epoll_create(5);
    assert(epollfd != -1);

    add_event(epollfd, socketfd, EPOLLIN | EPOLLET | EPOLLRDHUP);
    //add_event(epollfd, socketfd, EPOLLOUT);

    //http_conn::m_epollfd = m_epollfd;
}

void CServer::eventLoop() {
    while(true) {
        printf("CServer::eventLoop.\n");
        int number = epoll_wait(epollfd, events, m_max_event_num, -1);
        printf("number = %d.\n", number);
        if(number < 0 && errno != EINTR) {
            printf("epoll failure!\n");
            break;
        }

        for(int i = 0; i < number; i++) {
            int fd = events[i].data.fd;
            printf("fd = %d.\n", fd);
            if((fd == socketfd) && (events[i].events & EPOLLIN)) {
                dealClientAccept();
            }
            else if (events[i].events & EPOLLIN)
            {
                dealEpollIn(fd);
            }
            else if (events[i].events & EPOLLOUT)
            {
                dealEpollOut(fd);
            }
        }
    }
}

void CServer::dealClientAccept() {
    printf("CServer::dealClientAccept.\n");
    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof(client_address);
    int connfd = accept(socketfd, (struct sockaddr *)&client_address, &client_addrlength);
    if (connfd < 0)
    {
        printf("errno : accept error.\n");
    }
    setnonblocking(connfd);
    add_event(epollfd, connfd, EPOLLIN | EPOLLET);
    connections[connfd].fd = connfd;
}

void CServer::dealEpollIn(int fd) {
    printf("CServer::dealEpollIn.\n");
    mHandler->addHttpConnection(connections + fd, 0);
}

void CServer::dealEpollOut(int fd) {
    printf("CServer::dealEpollOut.\n");
    mHandler->addHttpConnection(connections + fd, 1);
}