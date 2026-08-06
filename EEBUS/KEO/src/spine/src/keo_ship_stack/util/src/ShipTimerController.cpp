/*
 *     Copyright KEO GmbH 2017 - All rights reserved!
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

#include <ShipTimer.h>

keo_ship::ShipTimerController::ShipTimerController()
    : run_(true)
    , mutex_()
    , cv_()
    , timer_()
    , worker_(std::thread(&ShipTimerController::workerThread, this))
{
}

keo_ship::ShipTimerController::~ShipTimerController()
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        run_ = false;
        timer_.clear();
    }
    cv_.notify_one();
    worker_.join();
}

void keo_ship::ShipTimerController::start(keo_ship::ShipTimer* t)
{
    std::unique_lock<std::mutex> lock(mutex_);
    t->timeout_ = std::chrono::steady_clock::now() + std::chrono::milliseconds(t->start_timeout_);
    enqueTimer(t);
}

void keo_ship::ShipTimerController::stop(keo_ship::ShipTimer* t)
{
    std::unique_lock<std::mutex> lock(mutex_);
    dequeTimer(t);
}

void keo_ship::ShipTimerController::enqueTimer(keo_ship::ShipTimer* t)
{
    dequeTimer(t);
    for (auto iter = timer_.begin(); iter != timer_.end(); ++iter)
    {
        if (t->timeout_ < (*iter)->timeout_)
        {
            timer_.insert(iter, t);
            return;
        }
    }
    timer_.push_back(t);
    cv_.notify_one();
}

void keo_ship::ShipTimerController::dequeTimer(keo_ship::ShipTimer* t)
{
    for (auto iter = timer_.begin(); iter != timer_.end(); ++iter)
    {
        if (*iter == t)
        {
            iter = timer_.erase(iter);
        }
    }
    cv_.notify_one();
}

void keo_ship::ShipTimerController::workerThread(void)
{
    std::unique_lock<std::mutex> lock(mutex_);

    while (run_)
    {
        if (timer_.empty())
        {
            cv_.wait(lock);
        }
        else
        {
            cv_.wait_until(lock, timer_.front()->timeout_);
        }

        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        while (run_ && !timer_.empty() && (timer_.front()->timeout_ <= now))
        {
            keo_ship::ShipTimer* t = timer_.front();
            timer_.pop_front();

            if (t->periodic_timeout_)
            {
                t->timeout_ = now + std::chrono::milliseconds(t->periodic_timeout_);
                enqueTimer(t);
            }

            lock.unlock();
            t->onTimeout();
            lock.lock();
            now = std::chrono::steady_clock::now();
        }
    }
}
