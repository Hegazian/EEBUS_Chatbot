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
 *     @file       KESemaphore.h
 *     @brief      Semaphore class declaration
 *     @author     KEO GmbH 2015 @n
 *                 All rights reserved !
 */

#ifndef _KEO_UTIL_SEMAPHORE_H_
#define _KEO_UTIL_SEMAPHORE_H_

#include <semaphore.h>

/** @ingroup KEOToolsLibrary
 * @{
 */

namespace keo_tool
{

/**
 * @class Semaphore
 * @brief Implements a semaphore object.
 * @ingroup     keo_util
 */
class KESemaphore
{
    sem_t m_sem;

public:
    /**
     * Constructor
     * Initialize semaphore instance with appropriate parameters.
     * @param pshared Zero means 'only visible to the local process and its threads'.
     *                Otherwise, this semaphore can be used by different processes.
     * @param value The initial value for the semaphore
     */
    KESemaphore(int pshared = 0, unsigned int value = 0)
    {
        if (sem_init(&m_sem, pshared, value))
        {
            /* TODO: What about the result code? */
        }
    }

    /**
     * Destructor
     */
    ~KESemaphore()
    {
        if (sem_destroy(&m_sem))
        {
            /* TODO: What about the result code? */
        }
    }

    /**
     * Releases the semaphore
     * @return zero if successful otherwise -1 and sets errno
     */
    int post()
    {
        return sem_post(&m_sem);
    }

    /**
     * Locks the semaphore
     * @return zero if the lock on the semaphore was successful otherwise -1 and sets errno
     */
    int wait()
    {
        return sem_wait(&m_sem);
    }
};

} // namespace keo_util

/** @}
 * end of file
 */

#endif /* _KEO_UTIL_SEMAPHORE_H_ */
