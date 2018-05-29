//
// Created by lxy on 18-3-10.
//

#include <assert.h>
#include <unistd.h>

#include "tcp_connection.h"
namespace meepo
{

namespace net
{


TcpConnection::TcpConnection(int fd)
    : fd_(fd), event_(fd)
{
    event_.set_read_callback(std::bind(&TcpConnection::handle_read, this));
    event_.set_write_callback(std::bind(&TcpConnection::handle_write, this));
    event_.enable_read();
}

void TcpConnection::handle_read()
{
    in_buffer_.read_from_fd(fd_);
    on_msg_callback_(*this, in_buffer_);
}

void TcpConnection::handle_write()
{
    if (!out_buffer_.empty())
    {

    }
    int send_num = ::write(fd_, out_buffer_.data(), out_buffer_.size());

    if (send_num < 0)
    {

    }
    else if (send_num < out_buffer_.size())
    {
        out_buffer_.pop(send_num);
    }
    else
    {
        out_buffer_.pop_all();
        event_.disable_write();
    }
}

void TcpConnection::send(const std::string &msg)
{
    int send_num = 0;
    int len = msg.length();
    if (out_buffer_.empty())
    {
        int len = msg.length();
        send_num = write(fd_, msg.c_str(), len);
    }
    out_buffer_.push(msg.c_str() + send_num, len - send_num);
    event_.enable_write();
}

}

}