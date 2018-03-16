//
// Created by lxy on 18-3-10.
//

#ifndef MEEPO_TCP_CONNECTION_H
#define MEEPO_TCP_CONNECTION_H

#include <functional>
#include <string>

#include "io_buffer.h"
#include "poller.h"
#include "net_common.h"

namespace meepo
{

namespace net
{

class TcpConnection
{
    FD_GETTER_SETTER
public:
    using OnMsgCallbackType = std::function<int(TcpConnection&, IOBuffer&)>;
    using OnCloseCallbackType = std::function<void()>;
public:
    TcpConnection() {}
    TcpConnection(int fd);

    void send(const std::string& msg);
    void set_msg_callback(const OnMsgCallbackType& cb) { on_msg_callback_ = cb; }
    void set_close_callback(const OnCloseCallbackType& cb) { on_close_callback_ = cb; }

private:
    void handle_read();
    void handle_write();

private:
    int fd_;
    IOBuffer in_buffer_;
    IOBuffer out_buffer_;
    PollerEvent event_;
    OnMsgCallbackType on_msg_callback_;
    OnCloseCallbackType on_close_callback_;
};


}

}

#endif //MEEPO_TCP_CONNECTION_H
