//
// Created by lxy on 18-3-10.
//

#include <sys/socket.h>
#include <netinet/in.h>

#include "tcp_listener.h"
namespace meepo
{

namespace net
{

TcpListener::TcpListener()
    : fd_(-1)
{

}

void TcpListener::listen(const NetAddr &addr, uint16_t port)
{
    make_listen_socket(addr, port);
    addr_ = addr;
    port_ = port;
    event.set_fd(fd_);
    event.set_read_callback(std::bind(&TcpListener::on_accept, this));
    event.enable_read();
}

void TcpListener::make_listen_socket(const NetAddr &addr, uint16_t port)
{
    int sock_type = AF_INET;
    if (addr.type() == NetAddr::IPv6)
        sock_type = AF_INET6;
    int fd = ::socket(sock_type, SOCK_STREAM | SOCK_CLOEXEC | SOCK_NONBLOCK, 0);
    if (fd < 0)
    {}
    sockaddr sock_addr = {0};
    sock_addr.sa_family = sock_type;
    if (sock_type == AF_INET)
    {
        auto a4 = reinterpret_cast<sockaddr_in *>(&sock_addr);
        a4->sin_addr.s_addr = addr.ipv4_addr().a4_32_;
        a4->sin_port = htons(port);
    }
    else
    {

    }

    if (::bind(fd, &sock_addr, sizeof(sock_addr)) < 0)
    {

    }

    if (::listen(fd, 1024) < 0)
    {

    }
    fd_ = fd;
}

int TcpListener::accept(NetAddr &addr, uint16_t &port)
{
    sockaddr sock_addr = {0};
    socklen_t len;
    int connection_fd = ::accept4(fd_, &sock_addr, &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    addr.set_addr(sock_addr);
    port = ntohs(reinterpret_cast<uint16_t *>(&sock_addr)[1]);
    return connection_fd;
}
void TcpListener::on_accept()
{
    NetAddr addr;
    uint16_t port;
    int confd = accept(addr, port);
    new_connection_cb_(confd, addr, port);
}

}

}