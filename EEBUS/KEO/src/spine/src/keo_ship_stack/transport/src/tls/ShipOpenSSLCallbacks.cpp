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

/**
 * This callback gets called as soon as a handshake has been performed.
 *
 * @param preverify_ok indicates whether certificate verification was ok (1) or not (0).
 * @param x509_store_ctx pointer to the x509 context used for the verification.
 *
 * @return 0 to indicate that certificate verification should stop immediately, 1 to continue.
 */
int ShipOpenSSL::verify_callback(int preverify_ok, X509_STORE_CTX* x509_store_ctx)
{
    DEBUG_FUNC();
    // Default verify result is 1 = continue handshake
    int verify_result = 1;

    if (!preverify_ok)
    {
        // Assumption: we don't get certificate chains. Therefore we only need to check depth 0.
        // For depth != 0 we terminate the handshake.
        if (X509_STORE_CTX_get_error_depth(x509_store_ctx) != 0)
        {
            return 0;
        }

        int err = X509_STORE_CTX_get_error(x509_store_ctx);
        switch (err)
        {
            // Self-signed certs are okay
            case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
            {
                LOG_INFO() << "The peer's certificate is self-signed. Accepting it anyway.";
                break;
            }

            // Issued certs are okay even if the issuer cert isn't available.
            case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
            {
                LOG_INFO() << "The peer's certificate was issued by a CA, but we don't have the issuer certificate. "
                              "Accepting the certificate.";
                break;
            }

            // The unable to verify leaf signature error is okay because it is a follow-up to a non-resolvable issuer
            // cert.
            case X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE:
            {
                LOG_INFO() << "The peer's certificate could not be verified, probably due to a missing issuer "
                              "certificate. Accepting the certificate.";
                break;
            }

            // Expired or not yet valid certs are okay
            case X509_V_ERR_CERT_HAS_EXPIRED:
            {
                LOG_INFO()
                    << "The peer's certificate is no longer valid relative to the system time. Accepting it anyway.";
                break;
            }
            case X509_V_ERR_CERT_NOT_YET_VALID:
            {
                LOG_INFO()
                    << "The peer's certificate is not yet valid relative to the system time. Accepting it anyway.";
                break;
            }
            case X509_V_ERR_CERT_UNTRUSTED:
            {
                LOG_INFO() << "Certificate not trusted! The root CA is not marked as trusted for the specified "
                              "purpose. Accepting it anyway.";
                break;
            }
            default:
            {
                LOG_ERROR() << "Error in certificate verification: " << X509_verify_cert_error_string(err) << ". Terminating SSL handshake.";
                // 0 = terminate handshake immediately
                return 0;
            }
        }
    }

    // We have no further indication about the quality, validity, trustworthiness etc. of the peer's certificate.
    // Therefore, we always pass it to the application.

    // make an X509Certificate object
    unsigned char* certDER = NULL;
    int lengthDER = i2d_X509(X509_STORE_CTX_get_current_cert(x509_store_ctx), &certDER);
    if (lengthDER < 0)
    {
        LOG_ERROR() << "Error converting peer certificate to DER format. Rejecting the certificate.";
        return 0;
    }

    // TODO this approach still has a slight design flaw: we convert internal -> DER and the constructor immediately
    // converts DER -> internal. Redesigning the wrapper class would be better.
    keo_ship::X509Certificate certificate(std::vector<unsigned char>(certDER, certDER + lengthDER));
    OPENSSL_free(certDER);

    if (certificate.isValid())
    {
        SSL* ssl = (SSL*)X509_STORE_CTX_get_ex_data(x509_store_ctx, SSL_get_ex_data_X509_STORE_CTX_idx());

        if (NULL != ssl)
        {
            ShipOpenSSL* parent = static_cast<ShipOpenSSL*>(SSL_get_ex_data(ssl, 0));

            if (NULL != parent && parent->isValid())
            {
                verify_result &= parent->onCertificateVerify(
                    static_cast<OpenSSLConnection*>(SSL_get_ex_data(ssl, 1)), preverify_ok, certificate);
            }
        }

        if (verify_result > 0)
        {
            DEBUG_INFO() << "A certificate in the certificate chain has been accepted by the SSL library";
        }
        else
        {
            LOG_WARN() << "A certificate in the certificate chain has been rejected by SSL the library";
        }
    }
    else
    {
        LOG_ERROR() << "Certificate parsing error! Terminating SSL handshake.";
    }

    return verify_result;
}

/**
 * This callback gets called during the check of client / server hello. We use it
 * to decide which SSL context we must use for the given server name.
 *
 * @param ssl the SSL context
 * @param ad the server name check status (not required by us)
 * @param arg a pointer to tlsextctx (not required by us)
 *
 * @return either SSL_TLSEXT_ERR_NOACK or SSL_TLSEXT_ERR_OK
 */
int ShipOpenSSL::servername_callback(SSL* ssl, int* ad, void* arg)
{
    (void)ad;
    (void)arg;

    DEBUG_FUNC();

    int status = SSL_TLSEXT_ERR_NOACK;
    if (NULL != ssl)
    {
#if OPENSSL_VERSION_NUMBER < 0x10100000L
        if (ssl->server)
#else
        if (SSL_is_server(ssl))
#endif
        {
            LOG_INFO() << "client requests server name";
            ShipOpenSSL* parent = static_cast<ShipOpenSSL*>(SSL_get_ex_data(ssl, 0));
            if (NULL != parent)
            {
                if (parent->isValid())
                {
                    SSL_CTX* ServerNameSslCtx
                        = parent->onServerNameIndication(static_cast<OpenSSLConnection*>(SSL_get_ex_data(ssl, 1)),
                            SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name));

                    if (NULL != ServerNameSslCtx)
                    {
                        if (ServerNameSslCtx != parent->get_SSL_CTX())
                        {
                            if (ServerNameSslCtx == SSL_set_SSL_CTX(ssl, ServerNameSslCtx))
                            {
                                LOG_VERBOSE(7) << "switched SSL_CTX";
                                status = SSL_TLSEXT_ERR_OK;
                            }
                        }
                        else if (ServerNameSslCtx == parent->get_SSL_CTX())
                        {
                            LOG_VERBOSE(9) << "current SSL_CTX is already the right one => no SSLT_CTX switch";
                            status = SSL_TLSEXT_ERR_OK;
                        }
                    }
                }
            }
        }
        else //(ssl->client)
        {
            status = SSL_TLSEXT_ERR_OK;
        }
    }

    if (SSL_TLSEXT_ERR_OK != status)
    {
        LOG_ERROR() << "Error in servername_callback.";
    }

    return status;
}

/**
 * This callback is called as soon as a session has been negotiated and only if caching
 * is enabled.
 *
 * @param ssl the SSL connection
 * @param sess the newly negotiated SSL session
 *
 * @return 0 to immediately remove the new session, 1 to keep it
 */
int ShipOpenSSL::new_session_callback(SSL* ssl, SSL_SESSION* sess)
{
    int status = 0;
    DEBUG_FUNC();

    ShipOpenSSL* parent = static_cast<ShipOpenSSL*>(SSL_get_ex_data(ssl, 0));

    DEBUG_INFO() << "new session was generated";

    if (NULL != parent)
    {
        if (parent->isValid())
        {
            status = parent->onSessionNegotiated(static_cast<OpenSSLConnection*>(SSL_get_ex_data(ssl, 1)), sess);
        }
    }

    return status;
}

/**
 * This callback is only called on the server side, and independent of whether caching is
 * enabled or not. It is used to retrieve an existing session for resumption.
 *
 * @param ssl the SSL connection
 * @param sessionId the session ID
 * @param sessionIdLength the length of the session ID
 * @param copy not used by us
 *
 * @return the session to be resumed, if it exists. NULL otherwise.
 */
SSL_SESSION* ShipOpenSSL::get_session_callback(SSL* ssl, const unsigned char* sessionId, int sessionIdLength, int* copy)
{
    (void)copy;

    SSL_SESSION* session = NULL;
    ShipOpenSSL* parent = static_cast<ShipOpenSSL*>(SSL_get_ex_data(ssl, 0));

    DEBUG_INFO() << "Client asks to resume a session.";

    if (NULL != parent && parent->isValid())
    {
        session = parent->onGetSession(
            static_cast<OpenSSLConnection*>(SSL_get_ex_data(ssl, 1)), sessionId, sessionIdLength);
    }

    if (NULL != session)
    {
#if OPENSSL_VERSION_NUMBER < 0x10100000L
        if (0 == memcmp(session->session_id, sessionId, sessionIdLength))
#else
        if (SSL_has_matching_session_id(ssl, sessionId, sessionIdLength))
#endif
        {
            // DBG_MODULE_INFO_1("reuse of session with identifier: %s",(char*)(session->session_id));
            // todo
            LOG_VERBOSE(7) << "reuse of session";
        }
        else
        {
            session = NULL;
            LOG_VERBOSE(7) << "invalid session given";
        }
    }
    else
    {
        LOG_VERBOSE(7) << "could not get session from given context";
    }

    return session;
}

/**
 * This callback is called upon any state changes, alerts, and errors, during connection
 * setup and use.
 *
 * @param ssl the SSL connection
 * @param where indication from where the callback was called
 * @param ret return value of the last internal engine call
 */
void ShipOpenSSL::info_callback(const SSL* ssl, int where, int ret)
{
// DEBUG_FUNC();

// FIXME is this function sufficiently smart? (helpful?)

#if OPENSSL_VERSION_NUMBER < 0x10100000L
    std::string errorString = ssl->server ? "Server: " : "Client: ";
#else
    std::string errorString = SSL_is_server(ssl) ? "Server: " : "Client: ";
#endif

    // print the last given (current) return value
    switch (ret)
    {
        case 0:
            errorString += "FAILURE";
            break;
        case 1:
            errorString += "OK";
            break;
        default:
            errorString += std::string(SSL_alert_type_string_long(ret));
            break;
    }

    // print from where in OpenSSL the callback was called
    errorString += " ";
    switch (where)
    {
        case SSL_CB_LOOP:
            errorString += "SSL_CB_LOOP";
            break;
        case SSL_CB_EXIT:
            errorString += "SSL_CB_EXIT";
            break;
        case SSL_CB_READ:
            errorString += "SSL_CB_READ";
            break;
        case SSL_CB_WRITE:
            errorString += "SSL_CB_WRITE";
            break;
        case SSL_CB_ALERT:
            errorString += "SSL_CB_ALERT";
            break;
        case SSL_CB_READ_ALERT:
            errorString += "SSL_CB_READ_ALERT";
            break;
        case SSL_CB_WRITE_ALERT:
            errorString += "SSL_CB_WRITE_ALERT";
            break;
        case SSL_CB_ACCEPT_LOOP:
            errorString += "SSL_CB_ACCEPT_LOOP";
            break;
        case SSL_CB_ACCEPT_EXIT:
            errorString += "SSL_CB_ACCEPT_EXIT";
            break;
        case SSL_CB_CONNECT_LOOP:
            errorString += "SSL_CB_CONNECT_LOOP";
            break;
        case SSL_CB_CONNECT_EXIT:
            errorString += "SSL_CB_CONNECT_EXIT";
            break;
        case SSL_CB_HANDSHAKE_START:
            errorString += "SSL_CB_HANDSHAKE_START";
            break;
        case SSL_CB_HANDSHAKE_DONE:
            errorString += "SSL_CB_HANDSHAKE_DONE";
            break;
        default:
            errorString += "unknown state";
            break;
    }

    LOG_VERBOSE(7) << errorString.c_str() << "  " << SSL_state_string_long(ssl);
}
}
