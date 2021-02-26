#include "config.h"
#include "server/server.h"
#include "server/epollserver.h"

const char* ROOT = "";

const int PORT = 1234;

const int THREAD_NUM = 5;

const int MAX_REQUEST = 10000;

const int MAX_EVENT_NUM = 10000;

int main(int argc, char const *argv[])
{
    CServer* server = new CEpollServer(PORT, THREAD_NUM, MAX_REQUEST, MAX_EVENT_NUM, ROOT);
    server->run();
    return 0;
}
