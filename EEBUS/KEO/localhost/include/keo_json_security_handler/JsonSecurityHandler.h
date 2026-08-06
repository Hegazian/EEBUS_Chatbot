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

#ifndef KEO_TRUSTCENTER_SRC_DEFAULTSECURITYHANDLER_H_
#define KEO_TRUSTCENTER_SRC_DEFAULTSECURITYHANDLER_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_ship/ShipSecurity.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <memory>
#include <string>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_json_security_handler
{

/** @addtogroup keo_json_security_handler
 * @{
 */

class JsonTrustStore;

/**
 * Default implementation of \ref keo_ship::ShipSecurityHandler
 *
 * This implementation uses a JSON-based on-disk trust store to remember trusted
 * peers. Own security data (certificate, private key) is read from files. There
 * is no support for a pass phrase that protects the private key. Use this example
 * implementation at your own discretion, but never in production!
 *
 * @see keo_ship::ShipSecurityHandler
 */
class JsonSecurityHandler : public keo_ship::ShipSecurityHandler
{
public:
    JsonSecurityHandler();
    virtual ~JsonSecurityHandler();

    /**
     * Initialize the security handler. The return value MUST be checked!
     *
     * @param certificateFullFilename full path to "our own" certificate
     * @param privateKeyFullFilename full path to "our own" private key
     * @param truststoreFullFilename full path to the trust store
     *
     * @return true if initialized successfully, false otherwise
     */
    virtual bool init(const std::string& certificateFullFilename, const std::string& privateKeyFullFilename,
        const std::string& truststoreFullFilename);

    // ShipSecurityHandler methods
    virtual keo_ship::X509Certificate getCertificate(const std::string& shipId, const std::string& ski) const;
    virtual keo_ship::TrustLevel getTrustLevel(const std::string& shipId, const std::string& ski) const;
    virtual std::string getId(const keo_ship::X509Certificate& cert) const;
    virtual void setTrustlevel(const std::string& shipId, const std::string& ski, const keo_ship::X509Certificate& cert,
        const keo_ship::TrustLevel& trustLevel);
    virtual void revokeTrust(const std::string& shipId, const std::string& ski);
    virtual keo_ship::X509Certificate getOwnCertificate() const;
    virtual std::vector<unsigned char> getOwnPrivateKey() const;
    virtual std::string getOwnSKI() const;

private:
    std::string createTruststoreEntryId(const std::string& id, const std::string& ski) const;
    bool initOwnSecurityData(const std::string& certificateFullFilename, const std::string& privateKeyFullFilename);

    JsonTrustStore* trustStore;

    keo_ship::X509Certificate ownCertificate;
    std::vector<unsigned char> ownPrivateKey;
};

typedef std::shared_ptr<JsonSecurityHandler> JsonSecurityHandlerPtr;

} /* namespace keo_json_security_handler */

/** @}
 * end of file
 */

#endif /* KEO_TRUSTCENTER_SRC_DEFAULTSECURITYHANDLER_H_ */
