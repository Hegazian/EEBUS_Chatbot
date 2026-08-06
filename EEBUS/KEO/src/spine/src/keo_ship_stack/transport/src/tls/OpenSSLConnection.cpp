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
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <cassert>
#include <chrono>
#include <fcntl.h>
#include <iomanip>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "OpenSSLConnection.h"
#include <keo_util/KELogging.h>

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

OpenSSLConnection::OpenSSLConnection(SSL* pSSL)
    : m_pSSL(pSSL)
{
    assert(m_pSSL);
}

OpenSSLConnection::~OpenSSLConnection()
{
    close();
}

//==============general methods ==================
bool OpenSSLConnection::isValid() const
{
    return nullptr != m_pSSL;
}

int OpenSSLConnection::set_fd(int socket)
{
    if (isValid())
    {
        return SSL_set_fd(m_pSSL, socket);
    }
    return 0; // return error
}

int OpenSSLConnection::get_fd()
{
    if (isValid())
    {
        return SSL_get_fd(m_pSSL);
    }
    return -1;
}

int OpenSSLConnection::connect()
{
    if (isValid())
    {
        return SSL_connect(m_pSSL);
    }
    return 0; // return error
}

int OpenSSLConnection::accept()
{
    if (isValid())
    {
        return SSL_accept(m_pSSL);
    }
    return 0; // return error
}

bool OpenSSLConnection::noError(int ret)
{
    bool status = true;
    if (isValid())
    {
        if (ret <= 0)
        {
            int error = SSL_get_error(m_pSSL, ret);
            if (ret == 0)
            {
                LOG_ERROR() << "protocol violation";
                status &= false;
            }

            switch (error)
            {
                case SSL_ERROR_NONE:
                    // LOG_ERROR()
                    //    << "SSL_ERROR_NONE: The TLS/SSL I/O operation completed. This result code is returned if"
                    //       " and only if ret > 0.";
                    status &= true;
                    break;
                case SSL_ERROR_ZERO_RETURN:
                     LOG_ERROR() << "SSL_ERROR_ZERO_RETURN: The TLS/SSL connection has been closed.";
                    status &= false;
                    break;
                case SSL_ERROR_WANT_READ:
                    LOG_ERROR() << "SSL_ERROR_WANT_READ: The operation did not complete; the same TLS/SSL I/O function should be called again later.";
                    status &= true;
                    break;
                case SSL_ERROR_WANT_WRITE:
                     LOG_ERROR() << "SSL_ERROR_WANT_WRITE: The operation did not complete; the same TLS/SSL I/O function should be called again later.";
                    status &= true;
                    break;
                case SSL_ERROR_WANT_CONNECT:
                    LOG_ERROR() << "SSL_ERROR_WANT_CONNECT: The operation did not complete; the same TLS/SSL I/O function should be called again later.";
                    status &= true;
                    break;
                case SSL_ERROR_WANT_ACCEPT:
                    LOG_ERROR() << "SSL_ERROR_WANT_ACCEPT: The operation did not complete; the same TLS/SSL I/O function should be called again later.";
                    status &= true;
                    break;
                case SSL_ERROR_WANT_X509_LOOKUP:
                    // LOG_ERROR()
                    //    << "SSL_ERROR_WANT_X509_LOOKUP: The operation did not complete because an application"
                    //       " callback set by SSL_CTX_set_client_cert_cb() has asked to be called again. The TLS/SSL
                    //       I/O"
                    //       " function should be called again later.";
                    status &= true;
                    break;
                case SSL_ERROR_SYSCALL:
                {
                    LOG_ERROR() << "SSL_ERROR_SYSCALL: Some I/O error occurred.";
                    long lerr = 0;
                    while ((lerr = ERR_get_error()) != 0)
                    {
                        char buf[1024];
                        ERR_error_string_n(lerr, buf, 1023);
                        LOG_ERROR() << std::string(buf, 1024);
                    }
                    status &= false;
                    break;
                }
                case SSL_ERROR_SSL:
                {
                    LOG_ERROR() << "SSL_ERROR_SSL: A failure in the SSL library occurred, usually a protocol error.";
                    long lerr = 0;
                    while ((lerr = ERR_get_error()) != 0)
                    {
                        char buf[1024];
                        ERR_error_string_n(lerr, buf, 1023);
                        LOG_ERROR() << std::string(buf, 1024);
                    }
                    status &= false;
                    break;
                }
                default:
                    LOG_ERROR() << "SSL_ERROR: Unknown SSL error!";
                    status &= false;
                    break;
            }
        }
        else
        {
            status &= true;
        }
    }
    else
    {
        LOG_ERROR() << "SSL == NULL";
        status &= false;
    }
    return status; // return error
}

std::string OpenSSLConnection::dumpData(void const* buffer, int len)
{
    std::stringstream os;
    for (int i = 0; i < len; ++i)
    {
        unsigned val = ((unsigned char*)buffer)[i];
        os << " " << std::hex << std::setfill('0') << std::setw(2) << val;
    }
    return os.str();
}

int OpenSSLConnection::write(void const* txBuffer, int txBufferLength)
{
    if (isValid())
    {
        if ((nullptr != txBuffer) && (0 < txBufferLength))
        {
            std::unique_lock<std::recursive_mutex> locker(mtx);
            LOG_VERBOSE(9) << "Tx"
                           << "(hdl "
                           << "0x" << std::hex << std::setfill('0') << std::setw(2) << SSL_get_fd(m_pSSL) << ", len 0x"
                           << txBufferLength << "):" << dumpData(txBuffer, txBufferLength);

            ::signal(SIGPIPE, SIG_IGN);

            ERR_clear_error();
            int result = SSL_write(m_pSSL, txBuffer, txBufferLength);

            if (result <= 0)
            {
                // log error message
                (void)noError(result);
            }
            else if (result != txBufferLength)
            {
                LOG_WARN() << std::dec << result << " bytes written. (expected: " << txBufferLength << " bytes)";
            }
            return result;
        }
        else
        {
            LOG_ERROR() << __FUNCTION__ << " Invalid argument";
        }
    }
    else
    {
        LOG_ERROR() << __FUNCTION__ << " SSL connection is not initialized.";
    }
    return 0; // return error
}

int OpenSSLConnection::read(void* rxBuffer, int rxBufferLength)
{
    if (isValid())
    {
        if ((nullptr != rxBuffer) && (0 < rxBufferLength))
        {
            std::unique_lock<std::recursive_mutex> locker(mtx);
            ERR_clear_error();
            int result = SSL_read(m_pSSL, rxBuffer, rxBufferLength);

            if (result > 0)
            {
                LOG_VERBOSE(9) << "Rx"
                               << "(hdl "
                               << "0x" << std::hex << std::setfill('0') << std::setw(2) << SSL_get_fd(m_pSSL)
                               << ", len 0x" << result << "):" << dumpData(rxBuffer, result);
            }
            else
            {
                // log error message
                bool isNoError = noError(result);
                if (!isNoError)
                {
                    result = -1;
                }
                else
                {
                    result = 0;
                }
            }
            return result;
        }
        else
        {
            LOG_ERROR() << __FUNCTION__ << " Invalid argument";
        }
    }
    else
    {
        LOG_ERROR() << __FUNCTION__ << " Connection is not initialized";
    }
    return 0; // return error
}

int OpenSSLConnection::pending()
{
    if (isValid())
    {
        std::unique_lock<std::recursive_mutex> locker(mtx);
        return SSL_pending(m_pSSL);
    }
    return 0; // return error
}

void OpenSSLConnection::close()
{
    std::unique_lock<std::recursive_mutex> locker(mtx);
    if (nullptr != m_pSSL && -1 != SSL_get_fd(m_pSSL))
    {
        int fd = get_fd();
        if (SSL_shutdown(m_pSSL) == 0)
        {
            // If SSL_shutdown returns 0 it should be called a second time, because
            // the shutdown is not finished, yet.
            // https://www.openssl.org/docs/man1.0.1/ssl/SSL_shutdown.html (Section RETURN VALUES)

            SSL_shutdown(m_pSSL);
        }
        set_fd(-1);
        SSL_free(m_pSSL);
        m_pSSL = nullptr;
        ::shutdown(fd, SHUT_RDWR);
        ::close(fd);
    }
}

void OpenSSLConnection::socketModeBlock(bool block) const
{
    if (nullptr != m_pSSL && -1 != SSL_get_fd(m_pSSL))
    {
        int sockFd = SSL_get_fd(m_pSSL);
        int flags = ::fcntl(sockFd, F_GETFL, 0);
        flags = (block ? flags & ~O_NONBLOCK : flags | O_NONBLOCK);
        if (-1 == ::fcntl(sockFd, F_SETFL, flags))
        {
            LOG_ERROR() << __FUNCTION__ << " : " << ::strerror(errno);
        }
    }
}

void OpenSSLConnection::setPeerCertificate(const X509Certificate& certificate)
{
    peerCertificate = certificate;
}

X509Certificate OpenSSLConnection::getPeerCertificate() const
{
    return peerCertificate;
}

SSL_SESSION* OpenSSLConnection::getSSLSession1()
{
    if (isValid())
    {
        return SSL_get1_session(m_pSSL);
    }
    return nullptr;
}

SSL_SESSION* OpenSSLConnection::getSSLSession0() const
{
    if (isValid())
    {
        return SSL_get0_session(m_pSSL);
    }
    return nullptr;
}

void OpenSSLConnection::setSSLSession(SSL_SESSION* session)
{
    if (isValid())
    {
        SSL_set_session(m_pSSL, session);
    }
}

bool OpenSSLConnection::sessionReused() const
{
    if (isValid())
    {
        return SSL_session_reused(m_pSSL);
    }
    return false;
}
}
