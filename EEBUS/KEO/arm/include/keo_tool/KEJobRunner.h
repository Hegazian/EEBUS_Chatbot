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
 *     @brief      Interface to a thread pool
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_UTIL_KETOOLSLIBRARY_INCLUDE_KEJOBRUNNER_H_
#define KEO_UTIL_KETOOLSLIBRARY_INCLUDE_KEJOBRUNNER_H_

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <semaphore.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_tool
{

/**
 * A Job Base class to be used with the JobRunner
 */
class KEJobRunnerJob
{
public:
    /**
     * Constructor
     * Initialize a job
     */
    KEJobRunnerJob()
    {
    }

    /**
     * Empty destructor
     */
    virtual ~KEJobRunnerJob()
    {
    }

    /**
     * Run function
     * Called when the job is executed
     */
    virtual void run() = 0;

private:
    /**
     * Job entry point
     */
    static void* runFunction(void* arg);
};

/**
 * Runs Jobs in a thread
 */
class KEJobRunner
{
    std::queue<KEJobRunnerJob*> jobQueue;
    void* exitValue;
    std::mutex m_mutex;
    std::thread workerThread;
    std::atomic<bool> running;
    std::atomic<bool> terminating;
    std::atomic<int> skipJobs;
    sem_t threadHasBeenStarted;
    std::condition_variable m_condEmpty;

public:
    /**
     * Destroys the JobRunner
     */
    ~KEJobRunner();

    /**
     * Creates and starts a JobRunner
     * @return A pointer to a new jobRunner object; NULL on error
     */
    static KEJobRunner* start();

    /**
     * Add work to the job queue
     * As soon the job is at the tail of job queue, the job runner thread,
     * takes the job out of the job queue and calls the jobs run() method.
     * When run() returns, the job will be deleted immediately by the thread.
     * @param job Job to processed. It has to be allocated with new by the caller.
     * returns  0 On success
     *         -1 when the job has been rejected. The caller has to delete the job.
     *         -2 when the job pointer was NULL
     */
    int addJob(KEJobRunnerJob* job);

    /**
     * Stops and joins jobRunner.
     * The jubRunner can be deleted afterwards.
     * @param jobRunner Job Runner
     * @param processPendingJobs Wait until all jobs are processed
     * @return 0 on success; -1 on error
     */
    static int stop(KEJobRunner* jobRunner, bool processPendingJobs = false);

    /**
     * Checks if the JobRunner thread is running
     * @return true if the JobRunner thread is running
     */
    bool isRunning() const;

    /**
     * Checks if the JobRunner thread is terminating
     * @return true if the JobRunner thread is terminating
     */
    bool isTerminating() const;

private:
    /**
     * @param jobQueueLimit
     */
    KEJobRunner();

    /**
     * Initializes the JobRunner
     * @return returns 0 on success; on error, -1 is returned
     */
    int init();

    /**
     * Creates the JobRunner
     * @return result of pthread_create
     */
    int create();

    /**
     * Waits after create() has been called, until the thread is up and running
     */
    void waitUntilRunning();

    /**
     *
     * @return 0 on success; -1 JobRunner is not running; -2 Is already terminating
     */
    int terminate(bool processPendingJobs);

    /**
     * waits after terminate() has been called until the thread has been joined
     * @note isRunning() must be false else result is EINVAL
     * @return result of pthread_join
     */
    int join();

    /**
     * Issued when thread has been started
     */
    void* run();

    /**
     * Copy not allowed
     * @param rhs
     */
    KEJobRunner(KEJobRunner& rhs);

    /**
     * Prints an error log
     * @param errorCode
     * @param module description string
     */
    std::string error(int errorCode, const std::string& module);

    /**
     * Thread entry point
     */
    static void* startRoutine(void* arg);
};

} /* namespace */

#endif /* KEO_UTIL_KETOOLSLIBRARY_INCLUDE_KEJOBRUNNER_H_ */
