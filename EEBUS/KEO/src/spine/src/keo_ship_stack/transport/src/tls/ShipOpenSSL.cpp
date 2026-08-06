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
#include <keo_util/KELogging.h>

#include <openssl/err.h>
#include <openssl/opensslv.h>

#include <openssl/rand.h>
/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <algorithm>
#include <cassert>
#include <iomanip>

namespace keo_ship
{

static const size_t session_ctx_id_length = 10;
static const unsigned char session_ctx_id[10] = "KEO-SHIP-";

static std::string sessionIdToString(const unsigned char* sessionId, unsigned int len)
{
    std::stringstream os;
    for (size_t i = 0; i < len; ++i)
    {
        unsigned val = sessionId[i];
        os << std::hex << std::setfill('0') << std::setw(2) << val;
    }

    std::string s = os.str();
    std::string result;
    result.resize(s.size());
    std::transform(s.begin(), s.end(), result.begin(), ::toupper);
    return result;
}

#if defined SHIP_STACK_WITH_SESSION_RESUMPTION_DEBUG
static void remove_session_cb(SSL_CTX* /*ctx*/, SSL_SESSION* session)
{
    DEBUG_FUNC();
    unsigned int len = 0;
    const unsigned char* sessionId = SSL_SESSION_get_id(session, &len);

    DEBUG_INFO() << "Session-ID : " << sessionIdToString(sessionId, len);
}
  
#define MAX_SESSION_ID_ATTEMPTS 10
static int generate_session_id(const SSL* ssl, unsigned char* id, unsigned int* id_len)
{
    DEBUG_FUNC();

    std::string session_id_prefix = "KEO-SHIP";

    unsigned int count = 0;
    do
    {
        ::RAND_pseudo_bytes(id, *id_len);
        /* Prefix the session_id with the required prefix. NB: If our
         * prefix is too long, clip it - but there will be worse effects
         * anyway, eg. the server could only possibly create 1 session
         * ID (ie. the prefix!) so all future session negotiations will
         * fail due to conflicts. */
        ::memcpy(
            id, session_id_prefix.c_str(), (session_id_prefix.size() < *id_len) ? session_id_prefix.size() : *id_len);

    } while (SSL_has_matching_session_id(ssl, id, *id_len) && (++count < MAX_SESSION_ID_ATTEMPTS));

    DEBUG_INFO() << "Session-ID : " << sessionIdToString(id, *id_len);

    if (count >= MAX_SESSION_ID_ATTEMPTS)
    {
        return 0;
    }

    return 1;
}
#endif

ShipOpenSSL::ShipOpenSSL(SecurityHandlerPtr securityHandler, long sessionCacheSize)
    : mtx_ssl()
    , m_pSSL_CTX(NULL)
{
    if (!securityHandler)
    {
        LOG_FATAL() << "Cannot initialize OpenSSL! Invalid SecurityHandler.";
        //exit(EXIT_FAILURE);
        return;
    }

    /*
    std::vector<unsigned char> privateKey(securityHandler->getOwnPrivateKey());
    std::vector<unsigned char> certificate(securityHandler->getOwnCertificate().getData());

    if (privateKey.empty())
    {
        LOG_FATAL() << "Cannot initialize OpenSSL! Private key is empty.";
        //exit(EXIT_FAILURE);
        return;
    }

    if (certificate.empty())
    {
        LOG_FATAL() << "Cannot initialize OpenSSL! Certificate is empty.";
        //exit(EXIT_FAILURE);
        return;
    }
    */

    //m_pSSL_CTX = openSsl(sessionCacheSize, NULL, (long)0, &certificate[0], (long)certificate.size(), &privateKey[0], (long)privateKey.size());
    m_pSSL_CTX = openSsl(securityHandler, sessionCacheSize, NULL, (long)0, nullptr, 0, nullptr, 0);
    if (NULL == m_pSSL_CTX)
    {
        LOG_FATAL() << "Cannot initialize OpenSSL!";
        //exit(EXIT_FAILURE);
        return;
    }
}

ShipOpenSSL::~ShipOpenSSL()
{

    if (NULL != m_pSSL_CTX)
    {
        SSL_CTX_free(m_pSSL_CTX);
    }
}

SSL_CTX* ShipOpenSSL::openSsl(SecurityHandlerPtr securityHandler, long sessionCacheSize, const unsigned char* caCert, long caCertSize,
    const unsigned char* cert, long certSize, const unsigned char* privateKey, long privateKeySize)
{
    mtx_ssl.lock();
    SSL_CTX* ssl_ctx = configureSslCtx(sessionCacheSize);
    if (NULL != ssl_ctx)
    {
        int SSL_status = 1;
        if (!securityHandler->loadPrivateKeyAndCertificateIntoSSLCTX(ssl_ctx))
        {
            // try to load the private key
            std::vector<unsigned char> privateKeyV(securityHandler->getOwnPrivateKey());
            std::vector<unsigned char> certificateV(securityHandler->getOwnCertificate().getData());

            if (!privateKeyV.empty() && !certificateV.empty())
            {
                cert = &certificateV[0];
                privateKey = &privateKeyV[0];
                certSize = (long)certificateV.size();
                privateKeySize = (long)privateKeyV.size();
                
                // load own certificate
                if (NULL != cert)
                {
                    SSL_status &= SSL_CTX_use_certificate_ASN1(ssl_ctx, certSize, cert);
                }
                else
                {
                    SSL_status = 0;
                }

                // load own private key
                if (NULL != privateKey)
                {
                    SSL_status &= SSL_CTX_use_PrivateKey_ASN1(EVP_PKEY_EC, ssl_ctx, privateKey, privateKeySize);
                }
                else
                {
                    SSL_status = 0;
                }
            }
            else 
            {
                LOG_FATAL() << "Cannot initialize OpenSSL! Private key or certificate not available";
            }
        }
        
        // FIXME shelfware. (Not used atm)
        // Load CA certificate
        if (NULL != caCert)
        {
            X509* x509_ca_cert = NULL;
            if (!d2i_X509(&x509_ca_cert, &caCert, caCertSize))
            {
                LOG_ERROR() << "Error during SSL_CTX setup... Check if correct CACert is provided!";
                SSL_status = 0;
            }
            else
            {
                // Load the CAs we trust
                SSL_status &= SSL_CTX_add_client_CA(ssl_ctx, x509_ca_cert);
            }
        }
        // no else, CA-certificates are optional!
        // FIXME shelfware end

        // check if everything is running as expected, otherwise clean up and return
        if ((0 >= SSL_status) || (0 == SSL_CTX_check_private_key(ssl_ctx)))
        {
            LOG_ERROR() << "Error during SSL_CTX setup... Check if correct Cert and PrivateKey is provided!";
            SSL_CTX_free(ssl_ctx);
            ssl_ctx = NULL;
        }
    }
    mtx_ssl.unlock();
    return ssl_ctx;
}

/**
 * Configure the SSL context as required by the SHIP specification. A new context
 * is created internally. In case of any error, NULL is returned.
 *
 * @return the SSL context, NULL in case of errors.
 */
SSL_CTX* ShipOpenSSL::configureSslCtx(long sessionCacheSize)
{
    SSL_CTX* ssl_ctx = createSslCtx();

    if (NULL != ssl_ctx)
    {
        int SSL_status = 1;

        /*
         * Set some options:
         * - SSL_OP_NO_SSLv2       -> Exclude SSLv2
         * - SSL_OP_NO_SSLv3       -> Exclude SSLv3
         * - SSL_OP_NO_TLSv1(_1)   -> Exclude TLSv1(_1)
         * - SSL_OP_NO_COMPRESSION -> disable compression in all cases
         * - SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION -> speaks for itself
         * - SSL_OP_NO_TICKET      -> do not use tickets for session resumption
         */
        SSL_CTX_set_options(ssl_ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1
                | SSL_OP_NO_COMPRESSION | SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION | SSL_OP_NO_TICKET);

        // set the maximum fragment size to 1024
        // FIXME check if we need this, and check how it might relate to the websocket buffer size
        SSL_CTX_set_max_send_fragment(ssl_ctx, 1024);

        // set the information callback
        SSL_CTX_set_info_callback(ssl_ctx, info_callback);

// set quiet shutdown if no close notify (write alert) should be sent
// FIXME enabling this violates the standard - do we really need it?
// https://www.openssl.org/docs/man1.0.1/ssl/SSL_CTX_set_quiet_shutdown.html
#ifdef SSL_CLOSE_NOTIFY
        SSL_CTX_set_quiet_shutdown(ssl_ctx, 1);
#endif // SSL_CLOSE_NOTIFY

        // set authentication requirements:
        // - both peers must provide a certificate
        // - abort if the peer provides no certificate
        // - use verify_callback as the callback
        SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, verify_callback);

        // set the maximum depth of certificate chain validation
        SSL_CTX_set_verify_depth(ssl_ctx, 1);

        // set session options and callbacks
        if (0 < sessionCacheSize)
        {
            SSL_CTX_set_session_cache_mode(ssl_ctx, SSL_SESS_CACHE_SERVER);
            SSL_CTX_sess_set_cache_size(ssl_ctx, sessionCacheSize);
        }
        else
        {
            SSL_CTX_set_session_cache_mode(ssl_ctx, SSL_SESS_CACHE_BOTH | SSL_SESS_CACHE_NO_INTERNAL);
        }

        SSL_CTX_sess_set_new_cb(ssl_ctx, new_session_callback);
#if OPENSSL_VERSION_NUMBER < 0x10100000L
        SSL_CTX_sess_set_get_cb(
            ssl_ctx, reinterpret_cast<SSL_SESSION* (*)(SSL*, unsigned char*, int, int*)>(get_session_callback));
#else
        SSL_CTX_sess_set_get_cb(ssl_ctx, get_session_callback);
#endif

#if defined SHIP_STACK_WITH_SESSION_RESUMPTION_DEBUG
        SSL_CTX_sess_set_remove_cb(ssl_ctx, remove_session_cb);
        SSL_CTX_set_generate_session_id(ssl_ctx, generate_session_id);
#endif

        SSL_status &= SSL_CTX_set_session_id_context(ssl_ctx, session_ctx_id, session_ctx_id_length);

        // set the Server Name Indication (SNI) callback
        // FIXME check what this is
        SSL_CTX_set_tlsext_servername_callback(ssl_ctx, servername_callback);

        // register an index for application specific data, the parent pointer in this case
        // FIXME we don't seem to want that index, because we immediately forget about it.
        SSL_get_ex_new_index(0, (void*)"parent pointer", NULL, NULL, NULL);

        // check if everything is running as expected,
        // otherwise free ssl_ctx and set it to NULL.
        if (SSL_status <= 0)
        {
            LOG_ERROR() << "An error occurred during setup of the SSL context.";
            SSL_CTX_free(ssl_ctx);
            ssl_ctx = NULL;
        }
    }

    return ssl_ctx;
}

/**
 * Create and configure an SSL context with SHIP specific settings
 *
 * @return a pointer to the new SSL context. NULL if errors have happened.
 */
SSL_CTX* ShipOpenSSL::createSslCtx()
{
    int SSL_status = 1;

#if OPENSSL_VERSION_NUMBER < 0x10100000L
    // We "speak" TLS 1.2 exclusively
    SSL_CTX* ssl_ctx = SSL_CTX_new(TLSv1_2_method());
#else
    // We "speak" TLS 1.2 exclusively
    SSL_CTX* ssl_ctx = SSL_CTX_new(TLS_method());
    SSL_CTX_set_options(ssl_ctx, SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1);
#endif

    if (NULL != ssl_ctx)
    {
        // Use only ECDHE-ECDSA-AES128-SHA256 as the cipher
        SSL_status &= SSL_CTX_set_cipher_list(ssl_ctx, "ECDHE-ECDSA-AES128-SHA256");

        // Set the ECDH parameters
        // NID_X9_62_prime256v1 -> secp256r1
        EC_KEY* ecdh = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
        if (NULL != ecdh)
        {
            SSL_status &= SSL_CTX_set_tmp_ecdh(ssl_ctx, ecdh);
            EC_KEY_free(ecdh);
        }
        else
        {
            SSL_status = 0;
        }

        // In case of any error, tear down everything
        if (SSL_status <= 0)
        {
            SSL_CTX_free(ssl_ctx);
            ssl_ctx = NULL;
        }
    }
    else
    {
        LOG_ERROR() << "Failed to create a new SSL context: " << ERR_error_string(ERR_get_error(), nullptr);
    }

    return ssl_ctx;
}

bool ShipOpenSSL::isValid()
{
    return NULL != m_pSSL_CTX;
}

SSL_CTX* ShipOpenSSL::get_SSL_CTX()
{
    return m_pSSL_CTX;
}

void ShipOpenSSL::setServerName(const char* serverName)
{
    if (NULL != serverName)
    {
        LOG_VERBOSE(7) << "server name set to: " << serverName;
        SSL_CTX_set_tlsext_servername_arg(this->m_pSSL_CTX, const_cast<char*>(serverName));
    }
}

OpenSSLConnection* ShipOpenSSL::createSSLConnection(const char* serverNameIndication)
{
    if (NULL != m_pSSL_CTX)
    {
        SSL* pSSL = SSL_new(m_pSSL_CTX);
        if (NULL != pSSL)
        {
            SSL_set_ex_data(pSSL, 0, this);

            if (NULL != serverNameIndication)
            {
                SSL_set_tlsext_host_name(pSSL, serverNameIndication);
                LOG_INFO() << "server name indication is set to: " << serverNameIndication;
            }

            OpenSSLConnection* pConnection = new OpenSSLConnection(pSSL);
            SSL_set_ex_data(pSSL, 1, pConnection);
            return pConnection;
        }
        else
        {
            LOG_ERROR() << "Error: failed to generate m_pSSL (m_pSSL == NULL)";
        }
    }
    else
    {
        LOG_ERROR() << "Error: m_pSSL_CTX == NULL";
    }
    return NULL;
}

//==============Callbacks==================

SSL_CTX* ShipOpenSSL::onServerNameIndication(OpenSSLConnection* /*pUserCtx*/, const char* /*pServerName*/)
{
    // return this context; TODO find the matching context for the server name
    // currently only one context available
    DEBUG_FUNC();
    return m_pSSL_CTX;
}

int ShipOpenSSL::onSessionNegotiated(OpenSSLConnection* /*pUserCtx*/, SSL_SESSION* session)
{
    DEBUG_FUNC();

    unsigned int len = 0;
    const unsigned char* sessionId = SSL_SESSION_get_id(session, &len);

    DEBUG_INFO() << "Session-ID : " << sessionIdToString(sessionId, len);

    return 0;
}

SSL_SESSION* ShipOpenSSL::onGetSession(
    OpenSSLConnection* /*pUserCtx*/, const unsigned char* pSessionId, size_t sessionIdLength)
{
    DEBUG_FUNC();

    DEBUG_INFO() << "Session-ID : " << sessionIdToString(pSessionId, sessionIdLength);

    return NULL;
}

int ShipOpenSSL::onCertificateVerify(
    OpenSSLConnection* openSSLConnection, int sl_preverify_status,
    const keo_ship::X509Certificate& certificate)
{
    DEBUG_FUNC();
    (void)sl_preverify_status; // todo: unused variable

    assert(NULL != openSSLConnection);

    openSSLConnection->setPeerCertificate(certificate);

    return 1; // accept certificate
}

} // namespace keo_ship
