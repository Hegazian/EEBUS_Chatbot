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
 *     @file       KEEventLoop.h
 *     @brief      EventLoop class declaration
 *     @author     KEO GmbH 2015 @n
 *                 All rights reserved !
 */

#ifndef KEO_SPINE_DEVICE_SRC_TIMEOUT_SERVICE_H_
#define KEO_SPINE_DEVICE_SRC_TIMEOUT_SERVICE_H_

/******************************************************************************* *
 * keo_spine header files                                                          *
 ******************************************************************************* */
#include "TimeoutServiceInterface.h"

/******************************************************************************* *
 * KEO header files                                 ,                            *
 ******************************************************************************* */

#include <keo_util/KETimer.h>

/******************************************************************************* *
 * standard header files                                                         *
 ******************************************************************************* */

#include <list>
#include <mutex>

/******************************************************************************* *
 *  defines                                                                      *
 ******************************************************************************* */

/******************************************************************************* *
 *  types                                                                        *
 ******************************************************************************* */

/******************************************************************************* *
 *  class definition                                                             *
 ******************************************************************************* */
namespace keo_tool
{
class KEJobRunner;
}

namespace keo_spine
{

/** @ingroup framework
 * @{
 */

/**
 * Service to handle timeouts
 */
class TimeoutService : private keo_util::TimerHandlerInterface
{
public:
    explicit TimeoutService(TimeoutServiceInterface* timeoutInterface);

    virtual ~TimeoutService();

    /**
     * Add a timeout for a messageCounter
     *
     * @param msgCounter
     *            MessageCounter from a sent datagram
     * @param datagramTimeoutDelay
     *            Time until the timeout occurs
     */
    void addTimeout(uint64_t msgCounter, long datagramTimeoutDelay);

    /**
     * Remove a timeout
     *
     * @param msgCounter
     *            Corresponding messageCounter
     */
    void removeTimeout(uint64_t msgCounter);

    /**
     * Clear all timeouts
     */
    void clear();

    /**
     * Return the current system time in milliseconds since January 1, 1970.
     */
    unsigned long getNowMillis();

protected:
    /** KETimer */
    virtual void handleTimer(keo_util::Timer::id_t timerId);

private:
    class TimeoutElement
    {
    public:
        TimeoutElement()
            : msgCounter(0)
            , millis(0)
        {
        }
        ~TimeoutElement()
        {
        }

        inline uint64_t getMsgCounter() const;

        inline void setMsgCounter(uint64_t msgCounter);

        inline unsigned long getAbsoluteTime() const;

        inline void setAbsoluteTime(long sec);

    private:
        // Message counter of the transaction
        uint64_t msgCounter;
        // Timeout in seconds for the transaction
        unsigned long millis;
    };

private:
    void createTimeoutThread(long timeoutSec);
    void executeTimeout(uint64_t msgCounter);

    TimeoutServiceInterface* sender;
    /// list of timeouts
    std::list<TimeoutElement> timeoutSendQueue;
    // Only active timer for all timeout events
    keo_util::Timer timeoutEventTimer;

    mutable std::recursive_mutex mtx;

    class TimeoutExecutor;
    keo_tool::KEJobRunner* jobRunner;
};

inline uint64_t TimeoutService::TimeoutElement::getMsgCounter() const
{
    return msgCounter;
}

inline void TimeoutService::TimeoutElement::setMsgCounter(uint64_t newMsgCounter)
{
    msgCounter = newMsgCounter;
}

inline unsigned long TimeoutService::TimeoutElement::getAbsoluteTime() const
{
    return millis;
}

inline void TimeoutService::TimeoutElement::setAbsoluteTime(long newMillis)
{
    millis = newMillis;
}

/** @} */ //  end of group framework
} // namespace keo_spine

#endif // KEO_SPINE_DEVICE_SRC_TIMEOUT_SERVICE_H_
