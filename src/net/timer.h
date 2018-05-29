//
// Created by lxy on 18-4-5.
//

#ifndef MEEPO_TIMER_H
#define MEEPO_TIMER_H

#include <functional>
#include <set>

#include "poller.h"
#include "../common/macro.h"

namespace meepo
{

namespace net
{

class TimerManager;
class Timer
{
public:
    friend class TimerManager;
    using TimerCallback = std::function<void()>;
public:
    Timer();
    explicit Timer(uint64_t interval, uint64_t start_time = 0);
    ~Timer() = default;

    void set_interval(uint64_t interval) { interval_ = interval; }
    void set_start_time(uint64_t start) { start_ = start; }
    void set_timeout_callback(const TimerCallback& cb);
    uint64_t interval() const { return interval_; }
    void run();
//    void run(uint64_t interval);
//    void run_after(uint64_t interval, uint64_t after);

private:
    void default_func_after_timeout();

private:
    uint64_t start_;
    uint64_t interval_;
    TimerCallback cb_;
};

class TimerManager
{
    DISABLE_COPY(TimerManager)
public:
    using TimerNode = std::pair<uint64_t, Timer*>;

public:
    void add_timer(Timer* timer, uint64_t interval, uint64_t start_after);
public:
    static TimerManager* instance();
private:
    TimerManager();
    ~TimerManager() = default;
    void init();
    void reset();
    void handle_timeout();
    std::vector<Timer*> get_expired_timers();
    uint64_t get_now_usec();
private:
    static TimerManager* instance_;
private:
    int timer_fd_;
    uint64_t last_min_timeout_;
    PollerEvent event_;
    std::set<TimerNode> timer_set_;
};

}

}

#endif //MEEPO_TIMER_H
