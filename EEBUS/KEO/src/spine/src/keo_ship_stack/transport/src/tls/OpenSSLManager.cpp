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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "ShipOpenSSL.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_ship
{

// Locking-related pointers
pthread_mutex_t* lock_mutexes;
long* lock_counts;

// Static library manager
ShipOpenSSL::OpenSSLManager ShipOpenSSL::libraryManager;

// Setup / cleanup functions
void ShipOpenSSL::OpenSSLManager::thread_setup()
{
    // get the number of required locks
    int num_locks = CRYPTO_num_locks();

    // get memory for mutexes
    lock_mutexes = (pthread_mutex_t*)OPENSSL_malloc(num_locks * sizeof(pthread_mutex_t));

    // get memory for lock counts
    lock_counts = (long*)OPENSSL_malloc(num_locks * sizeof(long));

    // Initialize lock counts and mutexes
    for (int i = 0; i < num_locks; i++)
    {
        lock_counts[i] = 0;
        pthread_mutex_init(&(lock_mutexes[i]), NULL);
    }

    // Set callback for thread identification
    CRYPTO_set_id_callback(id_callback);

    // Set callback for lock acquisition / release
    CRYPTO_set_locking_callback(locking_callback);
}

void ShipOpenSSL::OpenSSLManager::thread_cleanup()
{
    CRYPTO_set_locking_callback(NULL);
    CRYPTO_set_id_callback(NULL);

    for (int i = 0; i < CRYPTO_num_locks(); i++)
    {
        pthread_mutex_destroy(&(lock_mutexes[i]));
    }

    OPENSSL_free(lock_counts);
    OPENSSL_free(lock_mutexes);
}

// Callbacks
void ShipOpenSSL::OpenSSLManager::locking_callback(int mode, int n, const char* file, int line)
{
    (void)file;
    (void)line;

    pthread_mutex_t* mutex = &(lock_mutexes[n]);

    if (mode & CRYPTO_LOCK)
    {
        pthread_mutex_lock(mutex);
        lock_counts[n]++;
    }
    else
    {
        pthread_mutex_unlock(mutex);
    }
}

unsigned long ShipOpenSSL::OpenSSLManager::id_callback()
{
    return static_cast<unsigned long>(pthread_self());
}

ShipOpenSSL::OpenSSLManager::OpenSSLManager()
{
    SSL_library_init();
    SSL_load_error_strings();
    thread_setup();
}

ShipOpenSSL::OpenSSLManager::~OpenSSLManager()
{
    thread_cleanup();
}

} // namespace keo_ship
