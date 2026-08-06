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

#ifndef KEO_SHIP_STACK_TRANSPORT_TLS_SRC_OPENSSLCONNECTION_H_
#define KEO_SHIP_STACK_TRANSPORT_TLS_SRC_OPENSSLCONNECTION_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <mutex>
#include <openssl/ssl.h>
#include <string>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <keo_ship/ShipSecurity.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */


/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */


/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_ship
{

/**
 * @addtogroup ship
 * @{
 */

class OpenSSLConnection
{
public:
    /**
     * Constructor
     *
     * @param pSSL pointer to SSL object
     */
    OpenSSLConnection(SSL* pSSL);

    /**
     * Destructor
     */
    ~OpenSSLConnection();

    //==============general methods ==================

    /**
     * Check if the instance is valid. It is valid if the underlying SSL pointer differs from NULL.
     *
     * @return true if valid, false otherwise
     */
    bool isValid() const;

    /**
     * Set the file descriptor
     *
     * @param socket the socket to use
     *
     * @return the result of the underlying SSL_set_fd call, 0 on error.
     */
    int set_fd(int socket);

    /** Returns the file descriptor which is linked to SSL
     *
     * @return The file descriptor, -1 on error or if the underlying SSL is not valid.
     */
    int get_fd();

    /**
     * Connect
     *
     * @return the result of the underlying SSL_connect call, 0 on error.
     */
    int connect();

    /**
     * Accept a connection
     *
     * @return the result of the underlying SSL_accept call, 0 on error.
     */
    int accept();

    /**
     * Check if there was an error and if yes, evaluate and log that error
     *
     * @param result the result of a previous operation
     *
     * @return true if there was an error, false if there was no error
     */
    bool noError(int ret);

    /**
     * Write data to the connection
     *
     * @param txBuffer the buffer to retrieve data from
     * @param txBufferLength the number of bytes to write
     *
     * @return Values > 0 = the number of bytes written. Values <= 0 = error. Call noError to see whether it's a
     * retryable situation.
     */
    int write(void const* txBuffer, int txBufferLength);

    /**
     * Read data from the connection
     *
     * @param rxBuffer the buffer to read data into
     * @param rxBufferLength the number of bytes to read
     *
     * @return Values > 0 = the number of bytes read. Values <= 0 = error. Call noError to see whether it's a retryable
     * situation.
     */
    int read(void* rxBuffer, int rxBufferLength);

    /**
     * Get the number of bytes pending to be read
     *
     * @return the result of the underlying SSL_pending call, 0 on error.
     */
    int pending();
    // FIXME 0 on error makes no sense because SSL_pending can return 0 as a perfectly valid value.

    void close();

    void socketModeBlock(bool block) const;

    void setPeerCertificate(const X509Certificate& certificate);

    X509Certificate getPeerCertificate() const;

    SSL_SESSION* getSSLSession1();

    SSL_SESSION* getSSLSession0() const;

    void setSSLSession(SSL_SESSION* session);

    bool sessionReused() const;

protected:
    /**
     * Dump buffer to hex string
     * @param buffer
     *        pointer to buffer to dump
     * @param len
     *        Length of buffer in byte
     */
    std::string dumpData(void const* buffer, int len);

private:
    SSL* m_pSSL;
    X509Certificate peerCertificate;
    mutable std::recursive_mutex mtx;
};

/** @}
 */

} /* namespace keo_ship */

#endif /* KEO_SHIP_STACK_TRANSPORT_TLS_SRC_OPENSSLCONNECTION_H_ */
