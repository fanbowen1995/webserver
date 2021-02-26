#include "config.h"
#include "server/server.h"
#include "server/epollserver.h"

int main(int argc, char const *argv[])
{
    CServer* server = new CEpollServer(PORT, THREAD_NUM, MAX_REQUEST, MAX_EVENT_NUM, ROOT);
    server->run();
    return 0;
}
