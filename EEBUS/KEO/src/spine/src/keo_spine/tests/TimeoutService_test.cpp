/*
 *     Copyright KEO GmbH 2016 - All rights reserved!
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
 *     @brief      Test for TimeService
 *
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "gtest/gtest.h"
#include <TimeoutService.h>
#include <TimeoutServiceInterface.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <mutex>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

using namespace keo_spine;

class TimeoutReceiver : public TimeoutServiceInterface
{
public:
    TimeoutReceiver(){};

    virtual void timeout(uint64_t msgCounter)
    {
        std::lock_guard<std::mutex> locker(mtx);
        timeoutList.push_back(msgCounter);
    }

    virtual size_t getNumberOfTimeouts()
    {
        std::lock_guard<std::mutex> locker(mtx);
        return timeoutList.size();
    }

    virtual uint64_t getMsgCounterAt(unsigned int i)
    {
        std::lock_guard<std::mutex> locker(mtx);
        if (timeoutList.size() > i)
        {
            return timeoutList[i];
        }
        else
        {
            return 0;
        }
    }

    std::vector<uint64_t> timeoutList;
    std::mutex mtx;
};

TEST(TimeoutServiceTest, TimeoutServiceTest_initialisation)
{
    TimeoutReceiver receiver;
    TimeoutService timeoutService(&receiver);
}

TEST(TimeoutServiceTest, TestRemoveTimeout)
{
    TimeoutReceiver receiver;
    TimeoutService timeoutService(&receiver);
    timeoutService.addTimeout(1234, 10);
    timeoutService.removeTimeout(1234);
    usleep(100 * 1000);
    EXPECT_EQ(0U, receiver.getNumberOfTimeouts());
}

TEST(TimeoutServiceTest, TestRemoveLastOfMultipleTimeout)
{
    TimeoutReceiver receiver;
    TimeoutService timeoutService(&receiver);
    timeoutService.addTimeout(1234, 10);
    timeoutService.addTimeout(1235, 100);
    timeoutService.removeTimeout(1235);
    usleep(500 * 1000); // Both timeouts would have been fired by now
    EXPECT_EQ(1U, receiver.getNumberOfTimeouts());
    EXPECT_EQ(1234U, receiver.getMsgCounterAt(0));
}

/*
This test is disabled because it is not stable

TEST(TimeoutServiceTest, TestRemoveFirstOfMultipleTimeout)
{
    TimeoutReceiver receiver;
    TimeoutService timeoutService(&receiver);
    timeoutService.addTimeout(1234, 10);
    timeoutService.addTimeout(1235, 100);
    timeoutService.removeTimeout(1234);
    usleep(30 * 1000); // The first timeout would have been fired by now, but not the second
    EXPECT_EQ(0U, receiver.getNumberOfTimeouts());

    usleep(100 * 1000); // Wait for the second timeout
    EXPECT_EQ(1U, receiver.getNumberOfTimeouts());
    EXPECT_EQ(1235U, receiver.getMsgCounterAt(0));
}
*/

TEST(TimeoutServiceTest, TestSimultaneousTimeouts)
{
    TimeoutReceiver receiver;
    TimeoutService timeoutService(&receiver);
    timeoutService.addTimeout(1, 100);
    timeoutService.addTimeout(2, 100);
    timeoutService.addTimeout(3, 100);
    timeoutService.addTimeout(4, 150);

    usleep(500 * 1000); // Wait for all timeouts
    EXPECT_EQ(4U, receiver.getNumberOfTimeouts());
}
