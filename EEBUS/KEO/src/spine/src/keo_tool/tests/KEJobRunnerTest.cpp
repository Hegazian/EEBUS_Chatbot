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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_tool/KEJobRunner.h>

#include "gtest/gtest.h"
#include <keo_tool/KESemaphore.h>
#include <sched.h>

#include <stddef.h>
#include <stdlib.h>


/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

using namespace keo_tool;

int randomRange(int lowerBound, int upperBound)
{
    return lowerBound + rand() / (RAND_MAX / (upperBound - lowerBound + 1) + 1);
}

class TestJob : public KEJobRunnerJob
{
public:
    TestJob(keo_tool::KESemaphore* sem)
        : pSem(sem){};

protected:
    virtual void run()
    {
        sched_yield();
        usleep(randomRange(1, 50));
        if (pSem)
        {
            pSem->post();
        }
    };

private:
    keo_tool::KESemaphore* pSem;
};

void jobTestWait(int jobCount)
{

    keo_tool::KESemaphore* sem = new keo_tool::KESemaphore[jobCount];

#ifdef ADDITIONAL_OUTPUT
    std::cout << "Creating pool" << std::endl;
#endif

    KEJobRunner* jr = KEJobRunner::start();
    int i;

    EXPECT_TRUE(NULL != jr);
    EXPECT_TRUE(jr->isRunning());
    EXPECT_EQ(0, jr->isTerminating());
    for (i = 0; i < jobCount; ++i)
    {
        EXPECT_EQ(0, jr->addJob(new TestJob(&sem[i])));
    }

    for (i = 0; i < jobCount; i++)
    {
        sem[i].wait();
    }

    EXPECT_EQ(0, KEJobRunner::stop(jr));
    EXPECT_FALSE(jr->isRunning());
    EXPECT_FALSE(jr->isTerminating());
    delete jr;

    delete[] sem;
}

void jobTestNoWait(int jobCount)
{
    KEJobRunner* jr = KEJobRunner::start();

    EXPECT_TRUE(NULL != jr);
    EXPECT_TRUE(jr->isRunning());
    EXPECT_EQ(0, jr->isTerminating());
    for (int i = 0; i < jobCount; ++i)
    {
        EXPECT_EQ(0, jr->addJob(new TestJob(NULL)));
    }

    EXPECT_EQ(0, KEJobRunner::stop(jr));
    EXPECT_FALSE(jr->isRunning());
    EXPECT_FALSE(jr->isTerminating());
    delete jr;
}

/**
 * Tests regarding creating and execution of jobs
 */
TEST(KEJobRunner, SingleJob)
{
    jobTestWait(1);
}

TEST(KEJobRunner, SingleJobNoWait)
{
    jobTestNoWait(1);
}

TEST(KEJobRunner, 1000JobsWait)
{
    jobTestWait(1000);
}

TEST(KEJobRunner, 1000JobsNoWait)
{
    jobTestNoWait(1000);
}
