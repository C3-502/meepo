//
// Created by lxy on 2018/2/27.
//

#ifndef MEEPO_IO_LOOP_H
#define MEEPO_IO_LOOP_H

#include <vector>

namespace meepo
{

namespace net
{

class Poller;
class PollerEvent;
class IOLoop
{
public:
    enum IOLoopStatus
    {
        running,
        stopped
    };

public:
    IOLoop();
    ~IOLoop();

    void start();
    void stop() { status_ = stopped; }
    void update_event(PollerEvent* event);
    void delete_event(PollerEvent* event);

private:
    void handle_active_events();

private:
    Poller* poller_;
    IOLoopStatus status_;
    std::vector<PollerEvent*> active_events_;
};

}

}

#endif //MEEPO_IO_LOOP_H
