#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <iostream>

#include "net/io_loop.h"
#include "net/poller.h"

using namespace meepo::net;

IOLoop *io_loop = new IOLoop;

void test_read_func()
{
    std::cout << "test" << std::endl;
    io_loop->stop();
}

int main()
{
    PollerEvent event;
    int ret;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    ret = bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    ret = listen(fd, 5);
    event.set_fd(fd);
    event.set_read_callback(test_read_func);
    io_loop->update_event(&event);
    io_loop->start();
    return 0;
}