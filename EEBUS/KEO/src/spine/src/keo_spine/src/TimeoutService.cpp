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

/******************************************************************************* *
 * project header files                                                          *
 ******************************************************************************* */

#include <TimeoutService.h>
#include <assert.h>
#include <chrono>
#include <errno.h>
#include <keo_tool/KEJobRunner.h>
#include <keo_util/KELogging.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/******************************************************************************* *
 *  defines                                                                      *
 ******************************************************************************* */

/******************************************************************************* *
 *  types                                                                        *
 ******************************************************************************* */

/******************************************************************************* *
 *  class definition                                                             *
 ******************************************************************************* */

namespace keo_spine
{

// Thread to send a timeout back to the sender
class TimeoutService::TimeoutExecutor : public keo_tool::KEJobRunnerJob
{
public:
    TimeoutExecutor(TimeoutService& parent, uint64_t msgCounter)
        : m_parent(parent)
        , m_msgCounter(msgCounter)
    {
    }

    virtual void run()
    {
        if (NULL != m_parent.sender)
        {
            m_parent.sender->timeout(m_msgCounter);
        }
    }

private:
    TimeoutService& m_parent;
    uint64_t m_msgCounter;
};

TimeoutService::TimeoutService(TimeoutServiceInterface* timeoutInterface)
    : sender(timeoutInterface)
    , timeoutSendQueue()
    , timeoutEventTimer(this)
    , mtx()
{
    jobRunner = keo_tool::KEJobRunner::start();
}

TimeoutService::~TimeoutService()
{
    DEBUG_FUNC();

    timeoutEventTimer.stop();
    if (jobRunner->isRunning())
    {
        keo_tool::KEJobRunner::stop(jobRunner);
    }
    delete jobRunner;
}

void TimeoutService::addTimeout(uint64_t msgCounter, long datagramTimeoutDelay)
{
    // TODO change type of datagramTimeoutDelay to unsigned long and ditch the datagramTimeoutDelay > 0 check
    assert(datagramTimeoutDelay > 0);
    if (msgCounter > 0 && datagramTimeoutDelay > 0)
    {
        unsigned long timeoutAbsolut = datagramTimeoutDelay + getNowMillis();

        TimeoutElement timeoutElement;
        timeoutElement.setMsgCounter(msgCounter);
        timeoutElement.setAbsoluteTime(timeoutAbsolut);
        std::lock_guard<std::recursive_mutex> locker(mtx);
        if (timeoutSendQueue.empty())
        {
            // First timeout event -> create a timer for the timeout callback
            createTimeoutThread(datagramTimeoutDelay);
            timeoutSendQueue.push_back(timeoutElement);
            LOG_TRACE() << "Insert first timeout (messageCounter=" << msgCounter << " delay=" << datagramTimeoutDelay
                        << " absoluteTime=" << timeoutAbsolut << ")";
        }
        else
        {
            // timeout timer is already started
            bool insertInBetween = false;
            auto listIter = timeoutSendQueue.begin();
            for (; listIter != timeoutSendQueue.end(); ++listIter)
            {
                if (listIter->getAbsoluteTime() > timeoutAbsolut)
                {
                    // found - now must be insert in between
                    insertInBetween = true;
                    break;
                }
            }
            // what is the difference between the previous element and timeoutMsec
            if (insertInBetween)
            {
                timeoutSendQueue.insert(listIter, timeoutElement);
                LOG_TRACE() << "Insert timeout in between (messageCounter=" << msgCounter
                            << " delay=" << datagramTimeoutDelay << " absoluteTime=" << timeoutAbsolut << ")";
            }
            else
            {
                timeoutSendQueue.push_back(timeoutElement);
                LOG_TRACE() << "Add timeout at end (messageCounter=" << msgCounter << " delay=" << datagramTimeoutDelay
                            << " absoluteTime=" << timeoutAbsolut << ")";
            }
        }
    }
}

void TimeoutService::removeTimeout(uint64_t msgCounter)
{
    bool removed = false;
    bool removingFirstElement = false;
    std::lock_guard<std::recursive_mutex> locker(mtx);
    for (auto listIter = timeoutSendQueue.begin(); listIter != timeoutSendQueue.end(); ++listIter)
    {
        if (listIter->getMsgCounter() == msgCounter)
        {
            removingFirstElement = listIter == timeoutSendQueue.begin();

            timeoutSendQueue.erase(listIter);
            removed = true;

            if (removingFirstElement && !timeoutSendQueue.empty())
            {
                // We are removing the timeout element that would fire next. That means that the timeout thread is
                // already scheduled with the time of this timeout element. In that case we need to stop the timeout
                // thread (because it is scheduled with the time of the removed timeout) and reschedule it with the time
                // of the next timeout element. If the second (and consecutive) timeout element(s) would have been fired
                // by now, we need to fire them directly (because else the calculation of newDelay would fail).

                if (timeoutSendQueue.begin()->getAbsoluteTime() > getNowMillis())
                {
                    uint64_t newDelay = timeoutSendQueue.begin()->getAbsoluteTime() - getNowMillis();
                    assert(newDelay > 0);
                    createTimeoutThread(newDelay);
                }
                else
                {
                    timeoutEventTimer.stop();
                    handleTimer(0);
                }
            }

            LOG_TRACE() << "Canceled timeout (messageCounter=" << msgCounter << ")";

            break;
        }
    }
    if (!removed)
    {
        LOG_TRACE() << "Could not remove timeout with messageCounter=" << msgCounter << " (not found)";
    }

    if (timeoutSendQueue.empty())
    {
        timeoutEventTimer.stop();
    }
}

void TimeoutService::clear()
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    timeoutEventTimer.stop();
    timeoutSendQueue.clear();
}

void TimeoutService::handleTimer(keo_util::Timer::id_t timerId)
{
    (void)timerId;
    std::lock_guard<std::recursive_mutex> locker(mtx);
    if (!timeoutSendQueue.empty())
    {
        TimeoutElement timeoutElement = timeoutSendQueue.front();
        timeoutSendQueue.pop_front();
        executeTimeout(timeoutElement.getMsgCounter());
        uint64_t nowMillis = getNowMillis();
        while (!timeoutSendQueue.empty())
        {
            timeoutElement = timeoutSendQueue.front();
            if (timeoutElement.getAbsoluteTime() <= nowMillis)
            {
                timeoutSendQueue.pop_front();
                executeTimeout(timeoutElement.getMsgCounter());
            }
            else
            {
                uint64_t newDelay = timeoutElement.getAbsoluteTime() - nowMillis;
                assert(newDelay > 0);
                createTimeoutThread(newDelay);
                break;
            }
        }
    }
}

void TimeoutService::executeTimeout(uint64_t msgCounter)
{
    LOG_TRACE() << "Handle timeout with messageCounter=" << msgCounter;

    TimeoutExecutor* job = new TimeoutExecutor(*this, msgCounter);

    if (0 != jobRunner->addJob(job))
    {
        delete job;
        LOG_FATAL() << "Cannot add job in executeTimeout()";
        //exit(EXIT_FAILURE);
    }
}

void TimeoutService::createTimeoutThread(long timeoutSec)
{
    assert(timeoutSec > 0);
    timeoutEventTimer.stop();
    timeoutEventTimer.start(timeoutSec, -1);
}

unsigned long TimeoutService::getNowMillis()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
        .count();
}

} // namespace keo_spine
