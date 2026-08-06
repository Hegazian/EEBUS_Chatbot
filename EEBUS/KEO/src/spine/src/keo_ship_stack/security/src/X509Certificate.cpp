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

#include <keo_ship/ShipSecurity.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <openssl/asn1.h>

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

X509Certificate::X509Certificate()
    : data()
    , ski()
    , certificateStruct(NULL)
{
}

X509Certificate::X509Certificate(const std::vector<unsigned char>& data)
    : data(data)
    , ski()
    , certificateStruct(NULL)
{
    createX509Structure();
}

X509Certificate::X509Certificate(const X509Certificate& rhs)
    : data(rhs.data)
    , ski()
    , certificateStruct(NULL)
{
    createX509Structure();
}

X509Certificate::~X509Certificate()
{
    DEBUG_FUNC();
    if (NULL != certificateStruct)
    {
        X509_free(certificateStruct);
        certificateStruct = NULL;
    }
}

X509Certificate& X509Certificate::operator=(const X509Certificate& rhs)
{
    DEBUG_FUNC();

    data.assign(rhs.data.begin(), rhs.data.end());
    ski.clear();

    createX509Structure();

    return *this;
}

bool X509Certificate::isValid() const
{
    return certificateStruct != NULL;
}

std::vector<unsigned char> X509Certificate::getPublicKey() const
{
    DEBUG_FUNC();

    if (!isValid())
    {
        LOG_ERROR() << "Certificate is invalid. Returning empty public key.";
        return std::vector<unsigned char>();
    }

    EVP_PKEY* publicKey = X509_get_pubkey(certificateStruct);
    if (NULL == publicKey)
    {
        LOG_ERROR() << "Unable to get public key from X509 certificate. Returning empty public key.";
        return std::vector<unsigned char>();
    }

    int length = i2d_PublicKey(publicKey, NULL);
    std::vector<unsigned char> publicKeyVector(length);
    unsigned char* p = &publicKeyVector[0];
    i2d_PublicKey(publicKey, &p);

    EVP_PKEY_free(publicKey);

    return publicKeyVector;
}

std::string keo_ship::X509Certificate::getSerial(bool hex) const
{
    DEBUG_FUNC();

    if (!isValid())
    {
        LOG_ERROR() << "Certificate is invalid. Returning empty serial.";
        return std::string();
    }

    ASN1_INTEGER* serial = X509_get_serialNumber(certificateStruct);
    BIGNUM* n = ASN1_INTEGER_to_BN(serial, NULL);

    char* str = (hex ? BN_bn2hex(n) : BN_bn2dec(n));
    std::string result(str);

    OPENSSL_free(str);
    BN_free(n);

    return result;
}

std::string X509Certificate::getIssuer() const
{
    DEBUG_FUNC();

    if (!isValid())
    {
        LOG_ERROR() << "Certificate is invalid. Returning empty issuer.";
        return std::string();
    }

    return convertNameToString(X509_get_issuer_name(certificateStruct));
}

std::string X509Certificate::getSubject() const
{
    DEBUG_FUNC();

    if (!isValid())
    {
        LOG_ERROR() << "Certificate is invalid. Returning empty subject.";
        return std::string();
    }

    return convertNameToString(X509_get_subject_name(certificateStruct));
}

std::string X509Certificate::getSki() const
{
    DEBUG_FUNC();

    if (ski.empty())
    {
        getSKIFromX509Structure();
    }

    return ski;
}

void X509Certificate::createX509Structure()
{
    DEBUG_FUNC();

    // ensure a consistent state
    X509_free(certificateStruct);
    certificateStruct = NULL;

    if (data.empty())
    {
        LOG_ERROR() << "Certificate is empty. Cannot parse anything.";
        return;
    }

    const unsigned char* pCert = &data[0];
    certificateStruct = d2i_X509(NULL, &pCert, data.size());
    if (NULL == certificateStruct)
    {
        LOG_ERROR() << "Unable to parse certificate into X509 struct.";
        return;
    }
}

bool X509Certificate::getSKIFromX509Structure() const
{
    DEBUG_FUNC();

    if (!isValid())
    {
        LOG_ERROR() << "Certificate is invalid. Cannot extract SKI.";
        return false;
    }

    size_t length;
    const unsigned char* data;

    ASN1_OCTET_STRING* ski
        = static_cast<ASN1_OCTET_STRING*>(X509_get_ext_d2i(certificateStruct, NID_subject_key_identifier, NULL, NULL));
    if (NULL == ski)
    {
        LOG_ERROR() << "Unable to retrieve SKI from certificate.";
        return false;
    }

    // TODO add SKI computation from public key? For now, we assume that the certificate contains the SKI already.

    length = ASN1_STRING_length(ski);
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    data = ASN1_STRING_data(ski);
#else
    data = ASN1_STRING_get0_data(ski);
#endif
    this->ski = keo_ship::Ski::fromRaw((const char*)data, length);

    ASN1_OCTET_STRING_free(ski);

    return true;
}

std::string X509Certificate::convertNameToString(X509_NAME* name) const
{
    DEBUG_FUNC();

    std::string s = "Failed to convert name entry to string";

    BIO* out = BIO_new(BIO_s_mem());
    X509_NAME_print_ex(out, name, 0, XN_FLAG_ONELINE);
    BUF_MEM* data = NULL;
    BIO_get_mem_ptr(out, &data);
    if (data)
    {
        s.assign(data->data, data->length);
    }
    BIO_free(out);

    return s;
}

const std::vector<unsigned char>& X509Certificate::getData() const
{
    return data;
}

void X509Certificate::setData(const std::vector<unsigned char>& data)
{
    this->data = data;

    ski.clear();
    createX509Structure();
}

const ASN1_TIME* X509Certificate::getEffectiveDate() const
{
    if (certificateStruct != nullptr)
    {
        return X509_get_notBefore(certificateStruct);
    }
    else
    {
        return nullptr;
    }
}

const ASN1_TIME* X509Certificate::getExpirationDate() const
{
    if (certificateStruct != nullptr)
    {
        return X509_get_notAfter(certificateStruct);
    }
    else
    {
        return nullptr;
    }
}

bool X509Certificate::isValidAt(time_t* time) const
{
    if (certificateStruct != nullptr)
    {
        return X509_cmp_time(getEffectiveDate(), time) == -1 && X509_cmp_time(getExpirationDate(), time) == 1;
    }
    else
    {
        return false;
    }
}

} /* namespace keo_ship */
