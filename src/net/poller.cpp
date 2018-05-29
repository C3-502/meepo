//
// Created by lxy on 2018/2/27.
//
#include "poller.h"
#include "io_loop.h"

namespace meepo
{

namespace net
{
PollerEvent::PollerEvent()
    : fd_(-1), status_(PollerEvent::New), io_loop_(IOLoop::instance())
{

}
void PollerEvent::handle_event()
{
    if (revents_ & EventIn)
    {
        read_cb_();
    }
    else if (revents_ & EventOut)
    {
        write_cb_();
    }
    else
    {

    }
}

void PollerEvent::update_to_poller()
{
    io_loop_->update_event(this);
}

void PollerEvent::enable_read()
{
    events_ |= EventIn;
    update_to_poller();
}

void PollerEvent::enable_write()
{
    events_ |= EventOut;
    update_to_poller();
}

PollerEvent::PollerEvent(int fd)
    : fd_(fd), status_(New), io_loop_(IOLoop::instance())
{

}
void PollerEvent::disable_write()
{
    events_ &= ~EventOut;
    update_to_poller();
}

void PollerEvent::disable_read()
{

    events_ &= ~EventIn;
    update_to_poller();
}

Poller::Poller(IOLoop* io_loop)
    : epfd_(-1), io_loop_(io_loop), events_(new epoll_event[Poller::events_size])
{
    epfd_ = epoll_create1(EPOLL_CLOEXEC);
    if (epfd_ < 0)
    {

    }
}

Poller::~Poller()
{

}

void Poller::poll(int timeout, std::vector<PollerEvent *> &active_events)
{
    int nevents = ::epoll_wait(epfd_, events_, Poller::events_size, timeout);
    if (nevents < 0)
    {
        // 错误处理
    }
    for (int i = 0; i < nevents; ++i)
    {
        PollerEvent* event = static_cast<PollerEvent*>(events_[i].data.ptr);
        event->set_revents(events_[i].events);
        active_events.push_back(event);
    }

}

void Poller::update_events(PollerEvent *event)
{
    int fd = event->fd();
    PollerEvent::EventStatus status = event->status();
    int op = EPOLL_CTL_MOD;
    if (event_map_.find(fd) != event_map_.end())
    {
        //更新map即可
        if (status == PollerEvent::Deleted)
        {
            op = EPOLL_CTL_DEL;
        }
    }
    else
    {
        //插入
        if (status == PollerEvent::New)
        {
            event_map_[fd] = event;
            op = EPOLL_CTL_ADD;
        }
    }
    real_update(event, op);
}

void Poller::delete_events(PollerEvent *event)
{
    int fd = event->fd();
    if (event_map_.find(fd) != event_map_.end())
    {
        PollerEvent* origin_event = event_map_[fd];
        if (origin_event == event and event->status() == PollerEvent::Deleted)
        {
            event_map_.erase(fd);
        }
    }
}

void Poller::real_update(PollerEvent *event, int op)
{
    struct epoll_event real_event = { 0 };
    real_event.data.ptr = event;
    real_event.events = event->events();
    if (::epoll_ctl(epfd_, op, event->fd(), &real_event) < 0)
    {

    }
}

}


}