//
// Created by lxy on 18-3-15.
//

#ifndef MEEPO_IO_BUFFER_H
#define MEEPO_IO_BUFFER_H

namespace meepo
{

namespace net
{

class IOBuffer
{
public:
    IOBuffer();
    ~IOBuffer() { delete data_; }

    int size() const { return end_ - start_; }
    int rsize() const { return capacity_ - end_; }
    int lsize() const { return start_; }
    int remain_size() const { return rsize() + lsize(); }
    bool empty() { return size() == 0; }

    void resize(int size);
    void adjust();
    void push(const char* data, int len);
    void read_from_fd(int fd);
    char* data() { return data_ + start_; }

private:
    void init(int size);


private:
    char *data_;
    int start_;
    int end_;
    int capacity_;
};

}

}


#endif //MEEPO_IO_BUFFER_H
