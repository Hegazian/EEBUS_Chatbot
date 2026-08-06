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
 *     @brief      Ship Security
 *
 *     @par        The Ship Security API
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_SRC_SHIPSECURITY_H_
#define KEO_SRC_SHIPSECURITY_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <ctype.h>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <openssl/ssl.h>
#include <openssl/x509.h>

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

/**
 * @defgroup ship_security_handler Security handler
 * Security handler offers an API for all security related functions. Certificate handling, trust handling and storage.
 * @{
 */

class TrustLevel
{

public:
    static const unsigned short TRUST_VALUE_USER_UNTRUSTED;
    static const unsigned short TRUST_VALUE_USER_AUTO_ACCEPT;
    static const unsigned short TRUST_VALUE_USER_USER_VERIFIED;
    static const unsigned short TRUST_VALUE_USER_COMMISSIONED_MIN;
    static const unsigned short TRUST_VALUE_USER_COMMISSIONED_MAX;
    static const unsigned short TRUST_VALUE_USER_USER_INPUT;

    static const unsigned short TRUST_VALUE_PKI_SELF_SIGNED;
    static const unsigned short TRUST_VALUE_PKI_SIGNED_MIN;
    static const unsigned short TRUST_VALUE_PKI_SIGNED_MAX;

    static const unsigned short TRUST_VALUE_2NDFACTOR_NONE;
    static const unsigned short TRUST_VALUE_2NDFACTOR_PIN;
    static const unsigned short TRUST_VALUE_2NDFACTOR_PIN_SPECIAL;

public:
    /**
     * Default constructor, initializes the user trust level,
     * the PKI trust level and 2nd factor trust level to desired values
     * (default is 0).
     * @param userTrust
     *        User trust value to be set.
     * @param pkiTrust
     *        PKI trust value to be set.
     * @param secondFactorTrust
     *        2nd factor trust value to be set.
     */
    explicit TrustLevel(unsigned short userTrust = 0, unsigned short pkiTrust = 0, unsigned short secondFactorTrust = 0)
        : m_userTrust(userTrust)
        , m_pkiTrust(pkiTrust)
        , m_2ndFactorTrust(secondFactorTrust)
    {
    }

    /**
     * Set the user trust level value.
     * @param userTrust
     *        Trust value to be set.
     */
    void setUserTrust(unsigned short userTrust)
    {
        m_userTrust = userTrust;
    }

    /**
     * Retrieve the current user trust value.
     * @return Current user trust value.
     */
    unsigned short getUserTrust() const
    {
        return m_userTrust;
    }

    /**
     * Set the PKI trust level value.
     * @param pkiTrust
     *        Trust value to be set.
     */
    void setPkiTrust(unsigned short pkiTrust)
    {
        m_pkiTrust = pkiTrust;
    }

    /**
     * Retrieve the current PKI trust level value.
     * @return Current PKI trust level.
     */
    unsigned short getPkiTrust() const
    {
        return m_pkiTrust;
    }

    /**
     * Set the 2nd factor trust level value.
     * @param secondFactorTrust
     *        Trust value to be set.
     */
    void setSecondFactorTrust(unsigned short secondFactorTrust)
    {
        m_2ndFactorTrust = secondFactorTrust;
    }

    /**
     * Retrieve the current 2nd factor trust level.
     * @return Current 2nd factor trust level.
     */
    unsigned short getSecondFactorTrust() const
    {
        return (m_2ndFactorTrust);
    }

    std::string toString() const
    {
        std::stringstream ss;
        ss << "User trust: " << m_userTrust
           << " PKI trust: " << m_pkiTrust
           << " Second factor trust: " << m_2ndFactorTrust;
        return ss.str();
    }

    bool operator==(const TrustLevel& rhs)
    {
        return ( (m_userTrust == rhs.m_userTrust) && (m_pkiTrust == rhs.m_pkiTrust) && (m_2ndFactorTrust == rhs.m_2ndFactorTrust) );
    }

private:
    unsigned short m_userTrust;
    unsigned short m_pkiTrust;
    unsigned short m_2ndFactorTrust;
};

/**
 * @class Ski
 * Each SHIP node has a specific public key. The Subject Key Identifier (SKI) is derived from
 * this public key and is used as a cryptographically backed identification and authentication
 * criterion.
 *
 * This class implements support functions for SKI handling.
 */
class Ski
{
public:
    /**
     * Creates a lower case hex string from the data
     * @param data pointer to raw data
     * @param length length of the data (A length of 20 is expected)
     * @return normalized ski hex string or an empty string when the input was not valid
     */
    static std::string fromRaw(const char* data, size_t length);

    /**
     * Creates a lower case hex string from the input string
     * @param ski hex string (A length of 40 is expected)
     * @return normalized ski hex string or an empty string if the input was not valid
     */
    static std::string normalize(const std::string& ski);

    /**
     * validates a ski string
     * @param ski hex string (A length of 40 is expected)
     * @return true when the ski contains 40 lower case 'hex' ascii chars
     */
    static bool validate(const std::string& ski);

    /**
     * compares two ski hex strings
     * @param skiA
     * @param skiB
     * @return 0: They compare equal, >0: if skiA > skiB, <0:  if skiA < skiB
     */
    static int compare(const std::string& skiA, const std::string& skiB);
};

/**
 * @class X509Certificate
 *
 * \brief X509Certificate wraps OpenSSL's X509 struct.
 *
 * The class provides convenience methods to retrieve
 * information from the underlying certificate.
 */
class X509Certificate
{
public:
    /**
     * Construct an empty X509Certificate instance. This leaves the caller
     * with an object that has no further use.
     */
    X509Certificate();

    /**
     * Construct an X509Certificate object.
     *
     * @param data the certificate as a vector of unsigned char
     */
    explicit X509Certificate(const std::vector<unsigned char>& data);

    /**
     * Copy constructor.
     *
     * @param rhs the object to copy from.
     */
    X509Certificate(const X509Certificate& rhs);

    /**
     * Destructor.
     */
    ~X509Certificate();

    /**
     * Assignment operator.
     *
     * @param rhs the object to assign from.
     *
     * @return this
     */
    X509Certificate& operator=(const X509Certificate& rhs);

    /**
     * Check whether the certificate is structurally valid,
     * i.e., the given data was successfully parsed into
     * an OpenSSL X509 struct. This method does NOT check
     * if the certificate is valid in terms of the current date
     * (in respect to notBefore, notAfter).
     *
     * @return true if the given data represents a structurally
     *         valid certificate, false otherwise.
     */
    bool isValid() const;

    /**
     * Get the public key. If it is not set yet, the public key is
     * derived from the certificate, unless the certificate is
     * empty as well.
     *
     * @return the public key as a vector of unsigned char.
     */
    std::vector<unsigned char> getPublicKey() const;

    /**
     * Get the certificate's serial.
     * @param hex if true, create a hex string. If false, create a decimal string.
     * @return the certificate's serial.
     */
    std::string getSerial(bool hex = false) const;

    /**
     * Get the issuer.
     * @return the issuer as a string.
     */
    std::string getIssuer() const;

    /**
     * Get the subject.
     * @return the subject as a string.
     */
    std::string getSubject() const;

    /**
     * Get the SKI. If it is not set, an attempt is made to extract
     * the SKI from the certificate. If this fails, an empty string is
     * returned. Future versions of this class might have a fallback
     * method to compute the SKI from the certificate's public key,
     * but for now, we assume that the certificate contains an SKI that
     * can be extracted from it.
     *
     * @return the SKI, empty string in case of error.
     */
    std::string getSki() const;

    /**
     * Get the raw certificate data
     * @return the data
     */
    const std::vector<unsigned char>& getData() const;

    /**
     * Set the raw certificate data
     * @param data the data
     */
    void setData(const std::vector<unsigned char>& data);

    /**
     * Returns the effective date of this certificate, i.e. the date after which this certificate becomes valid.
     */
    const ASN1_TIME* getEffectiveDate() const;

    /**
     * Returns the expiration date of this certificate.
     */
    const ASN1_TIME* getExpirationDate() const;

    /**
     * Checks whether this certificate is valid at a given time, i.e. it is already valid but not expired.
     * @param time the time to validate against
     */
    bool isValidAt(time_t* time) const;

private:
    // fill the OpenSSL X509 struct
    void createX509Structure();

    // get the SKI from the X509 struct
    bool getSKIFromX509Structure() const;

    // convert a name to a concatenated string
    std::string convertNameToString(X509_NAME* name) const;

private:
    // raw data
    std::vector<unsigned char> data;

    // mutable in order to make all getters const, especially getSKI()
    mutable std::string ski;

    // internal structure
    X509* certificateStruct;
};

//! typedef for non-const smart pointer type X509Certificate
typedef std::shared_ptr<X509Certificate> X509CertificatePtr;

//! typedef for const type X509Certificate
typedef const X509Certificate X509CertificateConst;

//! typedef for const smart pointer type X509Certificate
typedef std::shared_ptr<X509CertificateConst> X509CertificateConstPtr;

/**
 * @class ShipSecurityHandler
 *
 * \brief ShipSecurityHandler represents the central API for trust management and own security data.
 *
 * The security handler provides the central API for two important security aspects:
 *
 *   1.) Managing if and how much foreign SHIP nodes are trusted, and <br />
 *   2.) Retrieving the "own security data", i.e. certificate, SKI, and private key.
 *
 * Nodes are identified by a combination of their SHIP ID and their SKI. All methods
 * in this interface that take a parameter named "shipId" expect it to be equal to the
 * respective node's SHIP ID. All parameters named "ski" are expected to contain a 160-bit SKI,
 * encoded as an all-lowercase hex string.
 *
 * This class is abstract by intention. Implementations of this interface are vendor-
 * and/or application-specific.
 */
class ShipSecurityHandler
{
public:
    /**
     * Constructor:
     * Create an instance of this object.
     */
    ShipSecurityHandler(){};
    /**
     * Destructor:
     * Destroy this instance and release all resources.
     */
    virtual ~ShipSecurityHandler(){};

    /**
     * Retrieve the certificate of the node identified by the given SHIP ID and SKI.
     *
     * @param shipId the SHIP ID of the node
     * @param ski the SKI of the node's certificate
     *
     * @return The desired certificate if available, empty object otherwise. Call X509Certificate::isValid() to check
     *         for the latter. The definition of "available" is specific depending on the implementation.
     */
    virtual X509Certificate getCertificate(const std::string& shipId, const std::string& ski) const = 0;

    /**
     * Get the trust level for the given SHIP ID and SKI.
     *
     * @param shipId the SHIP ID of the node
     * @param ski the SKI of the node's certificate

     * @return If a trust level already exists for this node, it is returned. If no trust level
     * exists for this node, the return value is 0.
     */
    virtual keo_ship::TrustLevel getTrustLevel(const std::string& shipId, const std::string& ski) const = 0;

    /**
     * Get the SHIP ID belonging to the given certificate.
     *
     * @param cert the node's certificate

     * @return The SHIP id of the node to whom the given certificate belongs. Empty string
     *         if the certificate is unknown to the trust center.
     */
    virtual std::string getId(const X509Certificate& cert) const = 0;

    /**
     * Set the trust level for the given SHIP ID, SKI, and certificate. To update the trust
     * parameters, simply call this method again.
     *
     * @param shipId the SHIP ID of the node
     * @param ski the SKI of the node's certificate
     * @param cert the node's certificate
     * @param trustLevel the trust level to set
     */
    virtual void setTrustlevel(const std::string& shipId, const std::string& ski, const X509Certificate& cert,
        const keo_ship::TrustLevel& trustLevel)
        = 0;

    /**
     * Revokes the trust for the given SHIP ID and SKI. In order to re-trust the device
     * identified by those parameters, the usual verification process must be executed.
     *
     * @param shipId the SHIP ID of the node to untrust
     * @param ski the SKI of the node to untrust
     */
    virtual void revokeTrust(const std::string& shipId, const std::string& ski) = 0;

    /**
     * Get the own certificate
     *
     * @return own certificate
     */
    virtual X509Certificate getOwnCertificate() const = 0;

    /**
     * Get the own private key
     *
     * @return own private key
     */
    virtual std::vector<unsigned char> getOwnPrivateKey() const { return std::vector<unsigned char>(); }
    
    virtual bool loadPrivateKeyAndCertificateIntoSSLCTX(SSL_CTX* ctx) const { (void) ctx; return false; }

    /**
     * Get the own SKI
     *
     * @return own SKI
     */
    virtual std::string getOwnSKI() const = 0;
};

//! typedef for non-const smart pointer type ShipSecurityHandler
typedef std::shared_ptr<ShipSecurityHandler> SecurityHandlerPtr;

//! typedef for const type ShipSecurityHandler
typedef const ShipSecurityHandler SecurityHandlerConst;

//! typedef for const smart pointer type ShipSecurityHandler
typedef std::shared_ptr<SecurityHandlerConst> SecurityHandlerConstPtr;

/** @}
 */

/** @}
 */

} /* namespace keo_ship */

#endif /* KEO_SRC_SHIPSECURITY_H_ */
