//
// Created by lxy on 18-3-10.
//

#ifndef MEEPO_NET_COMMON_H
#define MEEPO_NET_COMMON_H

#ifndef FD_GETTER_SETTER
#define FD_GETTER_SETTER \
    public: \
        void set_fd(int fd) { fd_ = fd; } \
        int  get_fd() { return fd_; }
#endif

#endif //MEEPO_NET_COMMON_H
