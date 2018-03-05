//
// Created by lxy on 2018/3/2.
//

#ifndef MEEPO_NET_ADDR_H
#define MEEPO_NET_ADDR_H

#include <sys/types.h>
#include <sys/socket.h>

#include <string>

namespace meepo
{

namespace net
{

struct IPv4Addr
{
    uint32_t a4_32_;
};

union IPv6Addr
{
    uint8_t a6_8_[16];
    uint16_t a6_16_[8];
    uint32_t a6_32_[4];
};

class NetAddr
{
public:
    enum NetAddrType
    {
        IPv4,
        IPv6,
        None = -1
    };

public:
    NetAddr();
    ~NetAddr() {}
    void set_addr(const std::string &addr);

    NetAddrType type() { return type_; }
    IPv4Addr ipv4_addr(); //转化为ipv4地址
    IPv6Addr ipv6_addr(); //转化为ipv6地址

private:
    void set_addr_impl(uint32_t a4);
    void set_addr_impl(uint8_t *a6);

private:
    NetAddrType type_;
    IPv4Addr a4_;
    IPv6Addr a6_;
};

}

}

#endif //MEEPO_NET_ADDR_H
