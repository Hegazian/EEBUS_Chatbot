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

#ifndef SHIP_OPENSSL_H
#define SHIP_OPENSSL_H

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "OpenSSLConnection.h"
#include <keo_ship/ShipSecurity.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <mutex>
#include <openssl/ssl.h>
#include <string>
#include <vector>

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

/**
 * @addtogroup ship
 * @{
 */

class ShipOpenSSL
{
public:
    /**
     * Construct a ShipOpenssl instance
     *
     * @param securityHandler shared pointer to the security handler implementation
     * @param sessionCacheSize Session cache size
     */
    ShipOpenSSL(SecurityHandlerPtr securityHandler, long sessionCacheSize);

    /**
     * Destructor
     */
    ~ShipOpenSSL();

    /**
     * Check whether the SSL context is valid. It is valid if it differs from NULL.
     *
     * @return true if valid, false otherwise
     */
    bool isValid();

    /**
     * Set the server's name
     *
     * @param serverName the server's name
     */
    // FIXME obsolete?
    void setServerName(const char* serverName);

    /**
     * Retrieve the SSL context
     * @return a pointer to the SSL context
     */
    SSL_CTX* get_SSL_CTX();

    /**
     * Create an SSL connection
     *
     * @param pServerNameIndication optional server name to be used "above" TLS
     *
     * @return a new SSL connection, or NULL in case of errors.
     */
    OpenSSLConnection* createSSLConnection(const char* pServerNameIndication);

    // ----- Callbacks -----

    /**
     * This callback provides the application with the server name information.
     *
     * @param pUserCtx pointer to the context from where the call was initiated
     * @param pServerName the server name
     *
     * @return the SSL context
     */
    // FIXME which SSL context?
    SSL_CTX* onServerNameIndication(OpenSSLConnection* openSSLConnection, const char* pServerName);

    /**
     * This callback gets called as soon as a handshake has finished. It provides the application with the certificate
     * and the public key
     * of the peer.
     *
     * @param pUserCtx pointer to the context from where the call was initiated
     * @param preverify_status indication about the type of certificate (PKI? Self signed?)
     * @param certificate the certificate received from the peer
     *
     * @return ???
     */
    // FIXME what do we return here?
    int onCertificateVerify(OpenSSLConnection* openSSLConnection, int preverify_status,
        const X509Certificate& certificate);

    /**
     * This callback gets called as soon as an SSL session has been negotiated successfully. It provides
     * the application with the session information.
     *
     * @param pUserCtx pointer to the context from where the call was initiated
     * @param pSession pointer to the SSL session
     *
     * @return ??? (was: int - if 0 session will not be stored in ShipSecurity/TLS)
     */
    // FIXME what do we return here?
    int onSessionNegotiated(OpenSSLConnection* openSSLConnection, SSL_SESSION* pSession);

    /**
     * This callback is called when the peer requests to reuse a session with a specific session ID. The
     * return value provides OpenSSL with a pointer to the valid session for this connection.
     *
     * @param pUserCtx pointer to the context from where the call was initiated
     * @param pSessionId the session ID
     * @param sessionIdLength the length of the session ID
     *
     * @return pointer to the session to be reused
     */
    SSL_SESSION* onGetSession(
        OpenSSLConnection* openSSLConnection, const unsigned char* pSessionId, size_t sessionIdLength);

private:
    // callback functions for OpenSSL
    static int verify_callback(int preverify_ok, X509_STORE_CTX* x509_store_ctx);
    static int servername_callback(SSL* ssl, int* ad, void* arg);
    static int new_session_callback(SSL* ssl, SSL_SESSION* sess);
    static SSL_SESSION* get_session_callback(SSL* ssl, const unsigned char* sessionId, int sessionIdLength, int* copy);
    static void info_callback(const SSL* ssl, int where, int ret);

private:
    // Helper class for OpenSSL setup and teardown
    class OpenSSLManager
    {
    public:
        OpenSSLManager();
        ~OpenSSLManager();

    private:
        // callback functions for OpenSSL
        static void locking_callback(int mode, int n, const char* file, int line);
        static unsigned long id_callback();

    private:
        void thread_setup();
        void thread_cleanup();
    };

private:
    // Static instance of the manager ensures start-to-shutdown lifecycle
    static OpenSSLManager libraryManager;

    std::recursive_mutex mtx_ssl;

    SSL_CTX* openSsl(SecurityHandlerPtr securityHandler, long sessionCacheSize, const unsigned char* caCert, long caCertSize, const unsigned char* cert,
        long certSize, const unsigned char* privateKey, long privateKeySize);
    SSL_CTX* configureSslCtx(long sessionCacheSize);
    SSL_CTX* createSslCtx();

private:
    SSL_CTX* m_pSSL_CTX;
};

/** @}
 */

} // namespace keo_ship

#endif // SHIP_OPENSSL_H
