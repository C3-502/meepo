#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>

#include "net/io_loop.h"
#include "net/poller.h"
#include "net/net_addr.h"
#include "net/tcp_listener.h"
#include "net/tcp_connection.h"

using namespace meepo::net;

IOLoop *io_loop = IOLoop::instance();

int on_msg(TcpConnection& connection, IOBuffer& in_buffer)
{
    std::cout << "on_msg" << std::endl;
    std::string body = "<h1>test</h1>";
    std::string msg = "HTTP/1.1 200 OK\r\nServer: my-server\r\nContent-Length: 13\r\n\r\n";
    std::cout << msg + body << std::endl;
    connection.send(msg+body);
}

void on_new_connection(int fd, const NetAddr& addr, uint16_t port)
{
    TcpConnection *connection = new TcpConnection(fd);
    connection->set_msg_callback(on_msg);
}


int main()
{
    TcpListener listener;
    NetAddr addr;
    addr.set_addr("127.0.0.1");
    listener.listen(addr, 8080);
    listener.set_new_connection_callback(on_new_connection);
    io_loop->start();
    return 0;
}