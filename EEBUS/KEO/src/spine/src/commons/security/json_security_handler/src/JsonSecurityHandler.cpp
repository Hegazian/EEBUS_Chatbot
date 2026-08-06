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

#include <keo_json_security_handler/JsonSecurityHandler.h>

#include <keo_util/KELogging.h>

#include "JsonTrustStore.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <fstream>
#include <openssl/x509.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_json_security_handler
{

JsonSecurityHandler::JsonSecurityHandler()
    : trustStore(nullptr)
    , ownCertificate()
    , ownPrivateKey()
{
}

JsonSecurityHandler::~JsonSecurityHandler()
{
    delete trustStore;
}

bool JsonSecurityHandler::init(const std::string& certificateFullFilename, const std::string& privateKeyFullFilename,
    const std::string& truststoreFullFilename)
{

    // Load certificate and private key
    if (!(initOwnSecurityData(certificateFullFilename, privateKeyFullFilename)))
    {
        LOG_ERROR() << "Reading own certificate and key failed.";
        return false;
    }

    // Initialize the trust store
    trustStore = new JsonTrustStore(truststoreFullFilename);
    if (!trustStore->init())
    {
        LOG_ERROR() << "Failed to initialize the trust store.";
        return false;
    }

    return true;
}

keo_ship::X509Certificate JsonSecurityHandler::getCertificate(
    const std::string& shipId, const std::string& ski) const
{
    return trustStore->getCertificate(createTruststoreEntryId(shipId, ski));
}

keo_ship::TrustLevel JsonSecurityHandler::getTrustLevel(const std::string& shipId, const std::string& ski) const
{
    return trustStore->getTrustLevel(createTruststoreEntryId(shipId, ski));
}

std::string JsonSecurityHandler::getId(const keo_ship::X509Certificate& cert) const
{
    std::string id;
    std::string entryId = trustStore->getKeyByCertificate(cert);
    if (!entryId.empty())
    {
        std::size_t pos = entryId.find(".");
        if (pos != std::string::npos)
        {
            id = entryId.substr(0, pos);
            DEBUG_INFO() << "Got entry ID '" << entryId << "' from the trust store, which results in SHIP ID '" << id
                         << "'.";
        }
    }
    return id;
}

void JsonSecurityHandler::setTrustlevel(const std::string& shipId, const std::string& ski,
    const keo_ship::X509Certificate& cert, const keo_ship::TrustLevel& trustlevel)
{
    std::string entryId = createTruststoreEntryId(shipId, ski);
    trustStore->setTrustLevel(entryId, cert, trustlevel);
}

void JsonSecurityHandler::revokeTrust(const std::string& shipId, const std::string& ski)
{
    std::string entryId = createTruststoreEntryId(shipId, ski);
    trustStore->revokeTrust(entryId);
}

std::string JsonSecurityHandler::getOwnSKI() const
{
    return ownCertificate.getSki();
}

keo_ship::X509Certificate JsonSecurityHandler::getOwnCertificate() const
{
    return ownCertificate;
    // FIXME return (const) reference?
}

std::vector<unsigned char> JsonSecurityHandler::getOwnPrivateKey() const
{
    return ownPrivateKey;
    // FIXME return (const) reference?
}

std::string JsonSecurityHandler::createTruststoreEntryId(const std::string& id, const std::string& ski) const
{
    return id + "." + ski;
}

bool JsonSecurityHandler::initOwnSecurityData(
    const std::string& certificateFullFilename, const std::string& privateKeyFullFilename)
{
    DEBUG_FUNC();

    DEBUG_INFO() << "Attempting to read certificate from file '" << certificateFullFilename << "'.";
    std::ifstream inputCert(certificateFullFilename, std::ios::in | std::ios::binary);
    if (inputCert.is_open())
    {
        std::vector<unsigned char> bufferCert(
            (std::istreambuf_iterator<char>(inputCert)), (std::istreambuf_iterator<char>()));
        ownCertificate.setData(bufferCert);
        inputCert.close();
    }
    else
    {
        LOG_ERROR() << "Unable to read certificate from file '" << certificateFullFilename << "'.";
        return false;
    }

    DEBUG_INFO() << "Attempting to read private key from file '" << privateKeyFullFilename << "'.";
    std::ifstream inputPrivateKey(privateKeyFullFilename, std::ios::in | std::ios::binary);
    if (inputPrivateKey.is_open())
    {
        std::vector<unsigned char> bufferKey(
            (std::istreambuf_iterator<char>(inputPrivateKey)), (std::istreambuf_iterator<char>()));
        ownPrivateKey = bufferKey;
        inputPrivateKey.close();
    }
    else
    {
        LOG_ERROR() << "Unable to read private key from file '" << privateKeyFullFilename << "'.";
        return false;
    }

    return true;
}

} /* namespace keo_json_security_handler */
