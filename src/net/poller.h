//
// Created by lxy on 2018/2/27.
//

#ifndef MEEPO_POLLER_HPP
#define MEEPO_POLLER_HPP

#include <sys/epoll.h>

#include <vector>
#include <functional>
#include <unordered_map>

#include "../common/macro.h"

namespace meepo
{

namespace net
{

class IOLoop;
class PollerEvent
{
public:
    enum EventType
    {
        EventIn = BV(0),
        EventPri = BV(1),
        EventOut = BV(2),
        EventErr = BV(3)
    };

    enum EventStatus
    {
        New,
        Added,
        Deleted,
    };

    using EventCallback = std::function<void()>;
public:
    PollerEvent();
    ~PollerEvent()
    {}
    int fd()
    {
        return fd_;
    }
    void set_fd(int fd)
    {
        fd_ = fd;
    }
    EventStatus status()
    {
        return status_;
    }
    void set_status(EventStatus status)
    {
        status_ = status;
    }

    int events()
    {
        return events_;
    }
    int revents()
    {
        return events_;
    }
    void set_revents(int event)
    {
        revents_ = event;
    }
    void set_read_callback(const EventCallback &read_cb)
    {
        read_cb_ = read_cb;
    }
    void set_write_callback(const EventCallback &write_cb)
    {
        write_cb_ = write_cb;
    }

    void enable_read();

    void handle_event();

private:
    void update_to_poller();

private:
    int fd_;
    EventStatus status_;
    uint32_t events_;
    uint32_t revents_;
    EventCallback read_cb_;
    EventCallback write_cb_;
    IOLoop *io_loop_;
};

// 基于epoll
class Poller
{
public:
    Poller(IOLoop *io_loop);
    ~Poller();

    void update_events(PollerEvent *event);
    void delete_events(PollerEvent *event);

    void poll(int timeout, std::vector<PollerEvent *> &active_events);

private:
    void real_update(PollerEvent *event, int op);

private:
    int epfd_;
    std::unordered_map<int, PollerEvent *> event_map_;
    struct epoll_event *events_;
    IOLoop *io_loop_;
private:
    static const int events_size = 1024;
};

}

}

#endif //MEEPO_POLLER_HPP
