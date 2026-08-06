/*
 * KETimerTest.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: gutsche
 */

/**
 *     @file       KETimerTest.cpp
 *     @brief      class definition
 *     @author     KEO GmbH 2016
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <gtest/gtest.h>

#include <keo_util/KETimer.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <condition_variable>
#include <mutex>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

using namespace keo_util;

void testSingleshot(int startms)
{
    class TestHandler : public keo_util::TimerHandlerInterface
    {
    public:
        std::mutex mtx;
        std::condition_variable cond;
        bool executed;
        keo_util::Timer* timer;

        TestHandler()
        {
            timer = new keo_util::Timer(this);
            executed = false;
        }

        ~TestHandler()
        {
            delete timer;
        }

        void startAndWait(int startms)
        {
            std::unique_lock<std::mutex> locker(mtx);
            timer->start(startms);
            cond.wait(locker);
        }

    protected:
        virtual void handleTimer(keo_util::Timer::id_t timerId)
        {
            (void)timerId;
            executed = true;
            {
                std::lock_guard<std::mutex> locker(mtx);
                cond.notify_all();
            }
        }
    };

    TestHandler handler;
    handler.startAndWait(startms);
    ASSERT_TRUE(handler.executed);
}

void testPeriodic(int startms, int intervals)
{
    class TestHandler : public keo_util::TimerHandlerInterface
    {
    public:
        keo_util::Timer* timer;
        std::mutex mtx;
        std::condition_variable cond;
        int intervals;
        int executed;

        TestHandler(int intervals)
            : intervals(intervals)
            , executed(0)
        {
            timer = new keo_util::Timer(this);
        }

        ~TestHandler()
        {
            delete timer;
        }

        void startAndWait(int startms)
        {
            std::unique_lock<std::mutex> locker(mtx);
            timer->start(startms, startms);
            cond.wait(locker);
        }

    protected:
        virtual void handleTimer(keo_util::Timer::id_t timerId)
        {
            executed++;
            if (--intervals == 0)
            {
                keo_util::Timer::stop(timerId);
                std::lock_guard<std::mutex> locker(mtx);
                cond.notify_all();
            }
        }
    };

    TestHandler handler(intervals);
    handler.startAndWait(startms);
    ASSERT_LE(handler.executed, intervals);
}

TEST(KETimerTest, Singleshot_1000)
{
    testSingleshot(1000);
}

TEST(KETimerTest, Singleshot_500)
{
    testSingleshot(500);
}

TEST(KETimerTest, Singleshot_100)
{
    testSingleshot(100);
}

TEST(KETimerTest, Singleshot_20)
{
    testSingleshot(20);
}

TEST(KETimerTest, Periodic_1000)
{
    testPeriodic(1000, 2);
}

TEST(KETimerTest, Periodic_500)
{
    testPeriodic(500, 2);
}

TEST(KETimerTest, Periodic_100)
{
    testPeriodic(100, 2);
}

TEST(KETimerTest, Periodic_10)
{
    testPeriodic(10, 2);
}
