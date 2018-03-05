//
// Created by lxy on 2018/3/2.
//
#include <arpa/inet.h>

#include "net_addr.h"

namespace meepo
{

namespace net
{

void NetAddr::set_addr(const std::string &addr)
{
    int ret;
    if (addr.find(':') != string::npos)
    {
        // 处理ipv6
    }
    else
    {
        IPv4Addr ipv4_addr = { 0 };
        ret = inet_ntop(AF_INET, addr.c_str(), &ipv4_addr);
        if (ret < 0)
        {

        }
        else if (ret == 0)
        {

        }
        type_ = NetAddr::IPv4;
        set_addr_impl(ipv4_addr.a4_32_);
    }
}

void NetAddr::set_addr_impl(uint32_t a4)
{
    type_ = NetAddr::IPv4;
    a4_ = a4;
}

}

}