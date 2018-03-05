//
// Created by lxy on 2018/2/27.
//

#include "io_loop.h"
#include "poller.h"

namespace meepo
{

namespace net
{

IOLoop::IOLoop()
    : poller_(new Poller(this))
{
}

void IOLoop::start()
{
    while (status_ == IOLoop::running)
    {
        active_events_.clear();
        poller_->poll(-1, active_events_);
        handle_active_events();
    }
}

void IOLoop::handle_active_events()
{
    int nevents = active_events_.size();
    for (int i = 0; i < nevents; ++i)
    {
        PollerEvent*& event = active_events_[i];
        event->handle_event();
    }
}

void IOLoop::update_event(PollerEvent *event)
{
    poller_->update_events(event);
}

void IOLoop::delete_event(PollerEvent *event)
{
    poller_->delete_events(event);
}

}

}