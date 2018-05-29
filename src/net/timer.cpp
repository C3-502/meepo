//
// Created by lxy on 18-4-5.
//

#include <sys/timerfd.h>
#include <sys/time.h>
#include <unistd.h>

#include <climits>
#include <iostream>

#include "timer.h"

namespace meepo
{

namespace net
{
TimerManager* TimerManager::instance_ = nullptr;

TimerManager::TimerManager()
    : event_(-1), last_min_timeout_(static_cast<uint64_t >(-1))
{

}


TimerManager *TimerManager::instance()
{
    if (!instance_)
    {
        instance_ = new TimerManager;
        instance_->init();
    }
    return instance_;
}

void TimerManager::init()
{
    int timer_fd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);
    if (timer_fd < 0)
    {
        abort();
    }
    timer_fd_ = timer_fd;
    event_.set_fd(timer_fd);
    event_.set_read_callback(std::bind(&TimerManager::handle_timeout, this));
}

void TimerManager::add_timer(Timer *timer, uint64_t interval, uint64_t start_after)
{
    auto base_time = get_now_usec();
    uint64_t timeout = interval;
    if (start_after > 0)
        timeout = start_after;

    timeout += base_time;
    TimerNode node(timeout, timer);
    timer_set_.insert(node);
    reset();
}

void TimerManager::reset()
{
    if (timer_set_.empty())
        return;
    auto it = timer_set_.cbegin();
    uint64_t min_timeout = it->first;
    if (min_timeout >= last_min_timeout_)
        return;

    auto now = get_now_usec();
//    min_timeout -= now;

    uint64_t seconds = min_timeout / 1000000;
    uint64_t nanoseconds = (min_timeout % 1000000) * 1000;

    itimerspec timeout = { 0 };
    timeout.it_value.tv_sec = seconds;
    timeout.it_value.tv_nsec = nanoseconds;
    timeout.it_interval.tv_sec = 0;
    timeout.it_interval.tv_nsec = 0;

    int ret = timerfd_settime(event_.fd(), TFD_TIMER_ABSTIME, &timeout, nullptr);
    if (ret < 0)
    {

    }
    event_.enable_read();
}

void TimerManager::handle_timeout()
{
    // 马上把timer_fd给读了，不然一直触发
    uint64_t i = 0;
    read(timer_fd_, &i, sizeof(i));
    std::cout << "TimeManager handle_timeout, i=" << i << std::endl;
    last_min_timeout_ = static_cast<uint64_t >(-1); // 重置上次超时时间
    std::vector<Timer*> expired_times = get_expired_timers();
    for (Timer* timer : expired_times)
    {
        timer->cb_();
        if (timer->interval_ != 0)
        {

        }
    }
}

std::vector<Timer *> TimerManager::get_expired_timers()
{
    // lower_bound返回最后一个可以插入的位置，可能为end，如果是end代表所有的都过期了
    uint64_t now = get_now_usec();
    TimerNode sentry(now, (Timer*)(-1));
    auto lower_bound_it = timer_set_.lower_bound(sentry);

    std::vector<Timer*> vec;
    auto it = timer_set_.begin();
    while (it != lower_bound_it)
    {
        vec.push_back(it->second);
        ++it;
    }

    return vec;
}

/*
 * 获取的是微秒us
 * */
uint64_t TimerManager::get_now_usec()
{
    timeval now = {0};
    gettimeofday(&now, nullptr);
    return static_cast<uint64_t >(now.tv_sec * 1000000) + now.tv_usec;
}

Timer::Timer()
    : start_(0), interval_(0)
{

}

Timer::Timer(uint64_t interval, uint64_t start_time)
    : start_(start_time), interval_(interval)
{

}

void Timer::run()
{
    if (interval_ == 0 && start_ == 0)
        return;
    if (!cb_)
        cb_ = std::bind(&Timer::default_func_after_timeout, this);
    TimerManager* timer_mgr = TimerManager::instance();
    timer_mgr->add_timer(this, interval_, start_);
}

void Timer::default_func_after_timeout()
{
    std::cerr << "warnning: timeout, but there is no timeout callback set" << std::endl;
}

//void Timer::run(uint64_t interval)
//{
//    run_after(interval, 0);
//}
//
//void Timer::run_after(uint64_t interval, uint64_t after)
//{
//    interval_ = interval;
//    start_ = after;
//    TimerManager* timer_mgr = TimerManager::instance();
//    timer_mgr->add_timer(this, interval, after);
//}

void Timer::set_timeout_callback(const Timer::TimerCallback &cb)
{
    cb_ = cb;
}

}

}