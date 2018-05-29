//
// Created by lxy on 18-3-15.
//

#include <string.h>
#include <sys/uio.h>

#include "io_buffer.h"

namespace meepo
{

namespace net
{
IOBuffer::IOBuffer()
    : data_(nullptr), start_(0), end_(0), capacity_(0)
{
    init(4096);
}

void IOBuffer::init(int size)
{
    capacity_ = size;
    if (!data_)
    {
        data_ = new char[size];
    }
}

void IOBuffer::push(const char *data, int len)
{
    if (capacity_ < len)
    {
        resize(capacity_ * 2);
    }
    else if (rsize() < len && remain_size() >= len)
    {
        adjust();
    }
    memcpy(data_ + start_, data, len);
}

void IOBuffer::resize(int size)
{

}

void IOBuffer::adjust()
{

}

void IOBuffer::read_from_fd(int fd)
{
    int staff_buffer_size = 4096;
    char stack_buffer[staff_buffer_size] = {0};

    int origin_rsize = rsize();
    struct iovec buffer[2];
    buffer[0].iov_base = data_ + end_;
    buffer[0].iov_len = origin_rsize;
    buffer[1].iov_base = stack_buffer;
    buffer[1].iov_len = staff_buffer_size;
    int nsize = ::readv(fd, buffer, 2);
    if (nsize < 0)
    {

    }
    if (origin_rsize < nsize)
    {
        int stack_buffer_len = nsize - origin_rsize;
        push(stack_buffer, stack_buffer_len);
    }
    else
    {
        end_ += nsize;
    }
}
void IOBuffer::pop(int size)
{
    // pop from the front of the buffer
    if (size >= this->size())
        this->pop_all();
    else
        start_ += size;
}
void IOBuffer::pop_all()
{
    start_ = end_ = 0;
}

}

}
