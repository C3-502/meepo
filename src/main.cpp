#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <tuple>
#include <string>

#include "net/io_loop.h"
#include "net/poller.h"
#include "net/net_addr.h"
#include "net/tcp_listener.h"
#include "net/timer.h"
#include "net/tcp_connection.h"

using namespace meepo::net;
using namespace std;
IOLoop *io_loop = IOLoop::instance();

void on_timeout()
{
    cout << "timeout" << endl;
}

int on_msg(TcpConnection& connection, IOBuffer& in_buffer)
{

}

void on_new_connection(int fd, const NetAddr& addr, uint16_t port)
{
    TcpConnection *connection = new TcpConnection(fd);
    connection->set_msg_callback(on_msg);
}


int main()
{
//    TcpListener listener;
//    NetAddr addr;
//    addr.set_addr("127.0.0.1");
//    listener.listen(addr, 8080);
//    listener.set_new_connection_callback(on_new_connection);
//    io_loop->start();
    Timer timer(1000000);
    timer.set_timeout_callback(on_timeout);
    timer.run();
    io_loop->start();
    return 0;
}