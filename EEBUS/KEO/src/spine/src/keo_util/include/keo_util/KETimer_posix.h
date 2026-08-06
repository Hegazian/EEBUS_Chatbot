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
 *     @file       KETimer_posix.h
 *     @brief      Timer class declaration
 *     @author     KEO GmbH 2015 @n
 *                 All rights reserved !
 */

#ifndef _KEO_UTIL_TIMER_POSIX_H_
#define _KEO_UTIL_TIMER_POSIX_H_

#include <iostream>
#include <mutex>
#include <pthread.h>
#include <set>
#include <signal.h>
#include <time.h>

/** @ingroup KEToolsLibrary
 * @{
 */

namespace keo_util
{

class TimerHandlerInterface;

/**
 * @class Timer
 * @brief It is a per-process interval timer.
 * @ingroup keo_util
 */
class Timer
{
public:
    /// type of the timer ID
    typedef timer_t id_t;

    /**
     * Creates a new per-process interval timer.  The ID of
     * the new timer is returned by timerId() This ID is unique within the process,
     * until the timer is deleted. The new timer is initially disarmed.
     * @param timeoutHandler Handler interface of the invoked handler when the timer expired.
     */
    Timer(TimerHandlerInterface* timeoutHandler);

    /**
     * Deletes and disarms the timer.
     * If the timer was armed at the time of this call, it is disarmed before
     * being deleted.
     */
    ~Timer();

    /**
     * @param handler Handler interface of the invoked handler when the timer expires.
     */
    void setTimeoutHandler(TimerHandlerInterface* handler);

    /**
     * @return timeout handler
     */
    TimerHandlerInterface* getTimeoutHandler() const;

    /**
     * Get cyclic timer interval
     * @return msec interval in ms
     */
    int getCyclicInterval() const;

    /**
     * Get start timer interval
     * @return msec interval in ms
     */
    int getStartInterval() const;

    /**
     * Set timer interval
     * @param startms first interval in ms
     * @param cyclicms cyclic interval in ms (-1: singleshot )
     */
    void setInterval(int startms, int cyclicms = -1);

    /**
     * returns singleshot flag
     * @return true if it is a singleshot timer.
     */
    bool isSingleShot() const;

    /**
     * Arm the timer with an interval of msec.
     * @param startms first interval in ms
     * @param cyclicms cyclic intervals in ms (default -1: singleshot)
     * @return timerId
     */
    id_t start(int startms, int cyclicms = -1);

    /**
     * Arm the timer using the actual interval
     * @return timerId
     */
    id_t start();

    /**
     * ID of the timer.
     * This ID is unique within the process,
       until the timer is deleted.
     * @return timerId
     */
    id_t timerId() const;

    /**
     * Disarm the timer
     */
    void stop();

    /**
     * Disarm a timer with the given timerId
     * @param timerId
     */
    static void stop(id_t timerId);

private:
    typedef void (*TimerHandler)(sigval_t signum);
    static void timerCallback(sigval_t This);

    void startTimer(int startms, int cyclicms);

    mutable std::recursive_mutex m_mtx;
    TimerHandlerInterface* m_timeoutHandler;
    int m_startms;
    int m_cyclicms;
    id_t m_timerid;
};

/**
 * @class TimerHandlerInterface
 * @brief Timer event callback interface
 * @ingroup keo_util
 */
class TimerHandlerInterface
{
    static std::recursive_mutex timerHandlerMtx; // recursive
    static std::set<TimerHandlerInterface*> timerHandlerSet;

public:
    TimerHandlerInterface()
    {
        timerHandlerMtx.lock();
        timerHandlerSet.insert(this);
        timerHandlerMtx.unlock();
    }
    virtual ~TimerHandlerInterface()
    {
        timerHandlerMtx.lock();
        timerHandlerSet.erase(this);
        timerHandlerMtx.unlock();
    }
    static void callTimerHandler(TimerHandlerInterface* handler, keo_util::Timer::id_t timerId)
    {
        timerHandlerMtx.lock();
        if (timerHandlerSet.find(handler) != timerHandlerSet.end())
        {
            handler->handleTimer(timerId);
        }
        timerHandlerMtx.unlock();
    }

protected:
    /**
     * Issued when the timer expires
     * @param timerId
     */
    virtual void handleTimer(keo_util::Timer::id_t timerId) = 0;
};

} // namespace keo_ship

/** @}
 */

#endif /* _KEO_UTIL_TIMER_POSIX_H_ */
