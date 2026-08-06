/*
 *     Copyright KEO GmbH 2015 - All rights reserved!
 *
 *     This software is protected by the inclusion of the above copyright notice.
 *     This software may not be provided or otherwise made available to, or used
 *     by, any other person. No title to or ownership of the software is hereby
 *     transferred. The information contained in this document is considered the
 *     @b confidential and @b proprietary information of KEO GmbH
 *     and may not be disclosed or discussed with anyone who is not employed by
 *     KEO GmbH, unless the individual or company
 *     - has an express need to know such information, and
 *     - disclosure of information is subject to the terms of a duly
 *     executed "Confidentiality and Non-Disclosure Agreement" between
 *     KEO GmbH and the individual or company.
 */

/**
 *     @file       Timer.cpp
 *     @brief      Timer class definitions
 *     @author     KEO GmbH 2015 @n
 *                 All rights reserved !
 */

#include <keo_util/KELogging.h>
#include <keo_util/KETimer_posix.h>

#include <assert.h>
#include <stdint.h>
#include <unistd.h>

using namespace std;

namespace keo_util
{

std::recursive_mutex TimerHandlerInterface::timerHandlerMtx; // recursive
std::set<TimerHandlerInterface*> TimerHandlerInterface::timerHandlerSet;

Timer::Timer(TimerHandlerInterface* timeoutHandler)
    : m_mtx() // mutex is initially locked
    , m_timeoutHandler(timeoutHandler)
    , m_startms(0)
    , m_cyclicms(-1)
    , m_timerid(0)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    assert(NULL != m_timeoutHandler);
    sigevent sev;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    sched_param parm;

    parm.sched_priority = 255;
    pthread_attr_setschedparam(&attr, &parm);

    sev.sigev_notify_attributes = &attr;
    sev.sigev_notify = SIGEV_THREAD;
    TimerHandler handler_cb = &timerCallback;
    sev.sigev_notify_function = handler_cb;
    sev.sigev_signo = SIGUSR1;
    sev.sigev_value.sival_ptr = this;

    timer_create(CLOCK_REALTIME, &sev, &m_timerid);
}

Timer::~Timer()
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    stop(m_timerid);
    // timer_create/timer_delete might create valgrind warnings about possibly lost memory, but:
    //     I can find very similar reports on the Internet about possible memory leaks in
    //     calloc/allocate_dtv which are called from pthread_create. But the conclusion is
    //     "These are memory blocks associated with cached stacks. No memory is lost."
    // So, do not waste your time on this. https://bugs.launchpad.net/ubuntu/+source/glibc/+bug/483594
    timer_delete(m_timerid);
}

void Timer::setTimeoutHandler(TimerHandlerInterface* handler)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    m_timeoutHandler = handler;
}

TimerHandlerInterface* Timer::getTimeoutHandler() const
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    return m_timeoutHandler;
}

int Timer::getCyclicInterval() const
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    return m_cyclicms;
}

int Timer::getStartInterval() const
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    return m_startms;
}

Timer::id_t Timer::timerId() const
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    return m_timerid;
}

void Timer::setInterval(int startms, int cyclicms)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    m_cyclicms = cyclicms;
    m_startms = startms;
}

bool Timer::isSingleShot() const
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    return m_cyclicms == -1;
}

Timer::id_t Timer::start(int startms, int cyclicms)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    setInterval(startms, cyclicms);
    start();
    return m_timerid;
}

Timer::id_t Timer::start()
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    startTimer(m_startms, m_cyclicms);
    return m_timerid;
}

void Timer::startTimer(int startms, int cyclicms)
{
    itimerspec spec;

    assert(startms >= 0);
    assert(cyclicms >= -1);

    /* Start the timer */
    spec.it_value.tv_sec = startms / 1000;
    spec.it_value.tv_nsec = (startms == 0) ? 1 : ((startms % 1000) * 1000000); // zero value would disarm the timer

    if (m_cyclicms == -1)
    {
        spec.it_interval.tv_sec = 0;
        spec.it_interval.tv_nsec = 0;
    }
    else
    {
        /* for cyclic timer */
        spec.it_interval.tv_sec = cyclicms / 1000;
        spec.it_interval.tv_nsec
            = (cyclicms == 0) ? 1 : ((cyclicms % 1000) * 1000000); // zero value would disarm the timer
    }

    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    //    LOG_VERBOSE(7) << "timer id " << std::dec << m_timerid << " : start : startms " << std::dec << startms
    //                   << " cyclicms " << std::dec << cyclicms << " handler " << (void*)m_timeoutHandler;
    timer_settime(m_timerid, 0, &spec, NULL);
}

void Timer::stop()
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    Timer::stop(m_timerid);
}

void Timer::stop(id_t timerId)
{
    //    LOG_VERBOSE(7) << "timer id " << std::dec << timerId << " : stop";
    itimerspec spec;
    spec.it_value.tv_sec = 0;
    spec.it_value.tv_nsec = 0;
    spec.it_interval.tv_sec = 0;
    spec.it_interval.tv_nsec = 0;
    timer_settime(timerId, 0, &spec, NULL); // disarm
}

void Timer::timerCallback(sigval_t that)
{
    Timer* timer = (Timer*)that.sival_ptr;
    assert(NULL != timer);
    TimerHandlerInterface* handler = timer->getTimeoutHandler();
    Timer::id_t id = timer->timerId();
    if (NULL != handler)
    {
        //        LOG_VERBOSE(7) << "timer id " << std::dec << id << " : call handler " << (void*)handler;
        TimerHandlerInterface::callTimerHandler(handler, id);
    }
    else
    {
        LOG_WARN() << "timer id " << std::dec << id << " : handler not set";
    }
}

} // namespace keo_util
