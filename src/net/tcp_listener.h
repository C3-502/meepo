//
// Created by lxy on 18-3-10.
//

#ifndef MEEPO_TCPLISTENER_H
#define MEEPO_TCPLISTENER_H

#include <functional>

#include "net_common.h"
#include "net_addr.h"
#include "poller.h"

namespace meepo
{

namespace net
{

class TcpListener
{
    FD_GETTER_SETTER
public:
    using CallbackType = std::function<void(int, const NetAddr&, uint16_t)>;
public:
    TcpListener();
    ~TcpListener() {}
    void listen(const NetAddr& addr, uint16_t port);
    void set_new_connection_callback(const CallbackType& cb) { new_connection_cb_ = cb; }
private:
    void make_listen_socket(const NetAddr& addr, uint16_t port);
    void on_accept();
    int accept(NetAddr& addr, uint16_t& port);
private:
    int fd_;
    PollerEvent event;
    CallbackType new_connection_cb_;
    NetAddr addr_;
    uint16_t port_;
};

}

}

#endif //MEEPO_TCPLISTENER_H
