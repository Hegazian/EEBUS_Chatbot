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
 *     @brief      A Thread pool to run multi-threaded jobs
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <keo_tool/KEJobRunner.h>

#include <keo_util/KELogging.h>
#include <sstream>
#include <string.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_tool
{

std::string KEJobRunner::error(int errorNumber, const std::string& module)
{
    std::ostringstream oss;
    oss << "JobRunner module : " << module << " (" << std::dec << errorNumber << ") :" << ::strerror(errorNumber);
    return oss.str();
}

void* KEJobRunnerJob::runFunction(void* arg)
{
    ((KEJobRunnerJob*)arg)->run();
    return NULL;
}

KEJobRunner::KEJobRunner()
    : jobQueue()
    , exitValue(NULL)
    , workerThread()
    , running(false)
    , terminating(false)
    , skipJobs()
    , threadHasBeenStarted()
{
    LOG_TRACE() << std::string(20, '#') << " "
                << "JobRunner created " << (void*)this << " " << std::string(20, '#');
}

KEJobRunner::~KEJobRunner()
{
    sem_destroy(&threadHasBeenStarted);
    LOG_TRACE() << std::string(20, '#') << " "
                << "JobRunner deleted " << (void*)this << " " << std::string(20, '#');
}

KEJobRunner* KEJobRunner::start()
{
    KEJobRunner* runner = new KEJobRunner();

    if (0 == runner->init())
    {
        if (0 == runner->create())
        {
            runner->waitUntilRunning();
        }
        else
        {
            LOG_ERROR() << "Create job runner " << (void*)runner << " failed";
            delete runner;
            runner = NULL;
        }
    }
    else
    {
        LOG_ERROR() << "Initialize job runner " << (void*)runner << " failed";
        delete runner;
        runner = NULL;
    }
    return runner;
}

int KEJobRunner::stop(KEJobRunner* jobRunner, bool processPendingJobs)
{
    int result = 0;
    if (NULL != jobRunner)
    {
        if (0 == jobRunner->terminate(processPendingJobs))
        {
            if (0 != jobRunner->join())
            {
                result = -1;
            }
        }
    }
    return result;
}

int KEJobRunner::init()
{
    int result = sem_init(&threadHasBeenStarted, 0, 0);
    if (result != 0)
    {
        LOG_ERROR() << error(result, "sem_init");
    }
    return result;
}

int KEJobRunner::create()
{
    int result = 0;
    workerThread = std::thread(&KEJobRunner::startRoutine, this);
    return result;
}

void KEJobRunner::waitUntilRunning()
{
    sem_wait(&threadHasBeenStarted);
}

int KEJobRunner::terminate(bool process)
{
    int result = 0;
    if (running)
    {
        if (!terminating)
        {
            if (!process)
            {
                skipJobs++;
            }
            terminating = true;

            {
                std::lock_guard<std::mutex> lock(m_mutex);
                jobQueue.push(nullptr); // Add null-job that triggers termination of worker thread
            }
            m_condEmpty.notify_one();
        }
        else
        {
            result = -2;
        }
    }
    else
    {
        result = -1;
    }
    return result;
}

int KEJobRunner::join()
{
    int result = 0;
    if (terminating)
    {
        workerThread.join();
        terminating = false;
    }
    else
    {
        result = -1;
    }
    return result;
}

void* KEJobRunner::startRoutine(void* arg)
{
    KEJobRunner* jobRunner = ((KEJobRunner*)arg);
    void* exitValue = jobRunner->run();
    return exitValue;
}

int KEJobRunner::addJob(KEJobRunnerJob* newJob)
{
    int result = 0;
    if (nullptr != newJob)
    {
        if (running && !terminating)
        {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                jobQueue.push(newJob);
            }
            m_condEmpty.notify_one();
        }
        else
        {
            result = -2;
        }
    }
    else
    {
        LOG_ERROR() << "Job rejected! Job is NULL!";
        result = -1;
    }
    return result;
}

bool KEJobRunner::isRunning() const
{
    return running && !terminating;
}

bool KEJobRunner::isTerminating() const
{
    return terminating;
}

void* KEJobRunner::run()
{
    running = true;

    sem_post(&threadHasBeenStarted);

    while (true)
    {
        // Wait until a job is available
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condEmpty.wait(lock, [&] { return !jobQueue.empty(); });

        KEJobRunnerJob* job = jobQueue.front();
        jobQueue.pop();
        if (nullptr != job)
        {
            if (skipJobs == 0)
            {
                // Release the lock, because running a job might call KEJobRunner::addJob
                lock.unlock();
                job->run();
            }
            delete job;
        }
        else
        {
            break;
        }
    }
    running = false;
    return nullptr;
}

} /* namespace keo_util */
