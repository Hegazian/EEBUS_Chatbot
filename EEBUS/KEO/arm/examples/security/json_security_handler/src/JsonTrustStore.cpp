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
 *  standard header files                                                         *
 * ****************************************************************************** */
#include "JsonTrustStore.h"
#include "KEByteArray.h"

#include <fstream>
#include <sys/stat.h>

/* ****************************************************************************** *
 *  project header files                                                          *
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

namespace keo_json_security_handler
{

static const char* TRUST_ENTRY_ATTRIBUTE_USER_TRUSTLEVEL = "UserTrust";
static const char* TRUST_ENTRY_ATTRIBUTE_SECOND_FACTOR_TRUSTLEVEL = "SecondFactorTrust";
static const char* TRUST_ENTRY_ATTRIBUTE_PKI_TRUSTLEVEL = "PKITrust";

static const char* TRUST_ENTRY_ATTRIBUTE_CERTIFICATE = "Certificate";

static int checkFile(const std::string& filename, struct stat& st)
{
    int result = stat(filename.c_str(), &st);
    if (result == -1)
    {
        DEBUG_INFO() << "stat failed for '" << filename << "'.";
    }
    return result;
}

static bool isRegular(const std::string& filename)
{
    struct stat st;
    checkFile(filename, st);
    return S_ISREG(st.st_mode);
}

static bool exists(const std::string& filename)
{
    struct stat st;
    return (checkFile(filename, st) == 0);
}

JsonTrustStore::JsonTrustStore(const std::string& fileName)
    : mutex()
    , fileName(fileName)
    , trustEntries(KEJson::objectValue)
{
}

JsonTrustStore::~JsonTrustStore()
{
}

bool JsonTrustStore::init()
{
    std::lock_guard<std::recursive_mutex> locker(mutex);

    DEBUG_FUNC();

    DEBUG_INFO() << "Attempting to initialize the trust store using file name '" << fileName << "'.";

    if (!exists(fileName))
    {
        LOG_INFO() << "File '" << fileName << "' does not exist. Attempting to create the file.";
        if (!write())
        {
            LOG_ERROR() << "Failed to create file '" << fileName << "'.";
            return false;
        }
        else
        {
            LOG_INFO() << "File '" << fileName << "' created.";
        }
    }

    if (!isRegular(fileName))
    {
        LOG_ERROR() << "File '" << fileName << "' is not a regular file. Cannot read the trust store from there.";
        return false;
    }

    // open for input
    std::ifstream ifs(fileName.c_str(), std::ios::in);
    if (!ifs.good())
    {
        LOG_ERROR() << "Error opening trust store file '" << fileName << "' for reading.";
        return false;
    }

    KEJson::Reader reader;
    if (!reader.parse(ifs, trustEntries))
    {
        LOG_ERROR() << "Error parsing trust store file '" << fileName << "': " << reader.getFormattedErrorMessages();
        return false;
    }

    ifs.close();
    return true;
}

bool JsonTrustStore::write() const
{
    std::lock_guard<std::recursive_mutex> locker(mutex);

    DEBUG_FUNC();

    KEJson::StyledWriter writer;
    std::ofstream os(fileName, std::ios_base::trunc);
    if (!os.good())
    {
        LOG_ERROR() << "Error opening trust store '" << fileName << "' for writing.";
        return false;
    }

    os << writer.write(trustEntries);
    os.close();

    return true;
}

keo_ship::TrustLevel JsonTrustStore::getTrustLevel(const std::string& key) const
{
    std::lock_guard<std::recursive_mutex> locker(mutex);

    DEBUG_FUNC();

    keo_ship::TrustLevel trustLevel;

    KEJson::Value entry = trustEntries[key];
    if (entry == KEJson::nullValue)
    {
        LOG_WARN() << "No trust store entry for '" << key << "' found. Returning trust level 0.";
        return trustLevel;
    }

    KEJson::Value userTrustLevel = entry[TRUST_ENTRY_ATTRIBUTE_USER_TRUSTLEVEL];
    if (userTrustLevel == KEJson::nullValue)
    {
        LOG_WARN() << "Trust store entry for '" << key << "' exists, but contains no user trust level.";
    }
    else
    {
        trustLevel.setUserTrust(userTrustLevel.asInt());
    }

    KEJson::Value secondFactorTrustLevel = entry[TRUST_ENTRY_ATTRIBUTE_SECOND_FACTOR_TRUSTLEVEL];
    if (secondFactorTrustLevel == KEJson::nullValue)
    {
        LOG_WARN() << "Trust store entry for '" << key << "' exists, but contains no second factor trust level.";
    }
    else
    {
        trustLevel.setSecondFactorTrust(secondFactorTrustLevel.asInt());
    }

    KEJson::Value pkiTrustLevel = entry[TRUST_ENTRY_ATTRIBUTE_PKI_TRUSTLEVEL];
    if (pkiTrustLevel == KEJson::nullValue)
    {
        LOG_WARN() << "Trust store entry for '" << key << "' exists, but contains no PKI trust level.";
    }
    else
    {
        trustLevel.setPkiTrust(pkiTrustLevel.asInt());
    }

    return trustLevel;
}

keo_ship::X509Certificate JsonTrustStore::getCertificate(const std::string& key) const
{
    std::lock_guard<std::recursive_mutex> locker(mutex);

    DEBUG_FUNC();

    keo_ship::X509Certificate crt;

    KEJson::Value entry = trustEntries[key];
    if (entry == KEJson::nullValue)
    {
        LOG_WARN() << "No trust store entry for '" << key << "' found. Returning empty certificate.";
    }
    else
    {
        std::string certificate = entry[TRUST_ENTRY_ATTRIBUTE_CERTIFICATE].asString();
        if (certificate.empty())
        {
            LOG_WARN() << "Trust store entry for '" << key
                       << "' exists, but it contains no certificate. Returning empty certificate.";
        }
        else
        {
            // parse the stored hex string back to a vector
            std::vector<unsigned char> certVector = KEByteArray::fromHex(certificate).toVectorUnsigned();

            // set it
            crt.setData(certVector);
        }
    }

    return crt;
}

std::string JsonTrustStore::getKeyByCertificate(const keo_ship::X509Certificate& certificate) const
{
    std::lock_guard<std::recursive_mutex> locker(mutex);

    DEBUG_FUNC();

    std::string key;

    if (trustEntries.empty())
    {
        DEBUG_INFO() << "Trust store is empty. Returning empty key.";
    }
    else
    {
        bool found = false;
        std::string certificateToLookFor = KEByteArray(certificate.getData()).toHex();

        KEJson::Value::Members members = trustEntries.getMemberNames();
        for (std::vector<std::string>::iterator it = members.begin(); it != members.end(); it++)
        {
            KEJson::Value entry = trustEntries[*it];
            std::string memberCertificate = entry[TRUST_ENTRY_ATTRIBUTE_CERTIFICATE].asString();
            if (memberCertificate == certificateToLookFor)
            {
                key = *it;
                found = true;
                break;
            }
        }

        if (found)
        {
            DEBUG_INFO() << "Matching key '" << key << "' found in trust store for the given certificate.";
        }
        else
        {
            LOG_INFO() << "No matching key found in the trust store for the given certificate with SKI "
                       << certificate.getSki() << " . Returning empty key.";
        }
    }

    return key;
}

void JsonTrustStore::setTrustLevel(
    const std::string& key, const keo_ship::X509Certificate& cert, const keo_ship::TrustLevel& trustlevel)
{
    std::lock_guard<std::recursive_mutex> locker(mutex);

    DEBUG_FUNC();

    // check for existing entry, just for logging purposes
    if (trustEntries.isMember(key))
    {
        LOG_WARN() << "Trust store entry for '" << key
                   << "' already exists. Entry will be overwritten with new values.";
    }

    // create the new trust store entry
    KEJson::Value entry(KEJson::objectValue);

    // transform the certificate
    std::string certificate = KEByteArray(cert.getData()).toHex();

    // verify (and correct, if required) the trust levels.
    // the limits are defined in the SHIP specification.
    unsigned short userTrustLevelToSet = trustlevel.getUserTrust();
    if (userTrustLevelToSet > keo_ship::TrustLevel::TRUST_VALUE_USER_COMMISSIONED_MAX)
    {
        LOG_ERROR() << "User trust level " << userTrustLevelToSet << " is illegal. It can at most take the value "
                    << keo_ship::TrustLevel::TRUST_VALUE_USER_COMMISSIONED_MAX << ". Changing the value to 0.";
        userTrustLevelToSet = 0;
    }

    unsigned short pkiTrustLevelToSet = trustlevel.getPkiTrust();
    // FIXME redundant. As long as the type is unsigned short, the value cannot exceed 0xFFFF.
    // TODO use portable data types that guarantee the size of the value
    //    if (pkiTrustLevelToSet > 0xFFFF)
    //    {
    //        DEBUG_INFO() << "PKI trustlevel " << pkiTrustLevelToSet << " is illegal. Changing the value to 0.";
    //        pkiTrustLevelToSet = 0;
    //    }

    unsigned short secondFactorTrustLevelToSet = trustlevel.getSecondFactorTrust();
    if (secondFactorTrustLevelToSet > keo_ship::TrustLevel::TRUST_VALUE_2NDFACTOR_PIN_SPECIAL)
    {
        LOG_ERROR() << "Second factor trustlevel " << secondFactorTrustLevelToSet
                    << " is illegal. It can at most take the value "
                    << keo_ship::TrustLevel::TRUST_VALUE_2NDFACTOR_PIN_SPECIAL << ". Changing the value to 0.";
        secondFactorTrustLevelToSet = 0;
    }

    LOG_INFO() << "Storing trust parameters for '" << key << "'. Trust levels: user = " << userTrustLevelToSet
               << ", pki = " << pkiTrustLevelToSet << ", second factor = " << secondFactorTrustLevelToSet
               << ". Certificate=0x[" << certificate << "]";

    // set the values
    entry[TRUST_ENTRY_ATTRIBUTE_CERTIFICATE] = certificate;
    entry[TRUST_ENTRY_ATTRIBUTE_USER_TRUSTLEVEL] = userTrustLevelToSet;
    entry[TRUST_ENTRY_ATTRIBUTE_PKI_TRUSTLEVEL] = pkiTrustLevelToSet;
    entry[TRUST_ENTRY_ATTRIBUTE_SECOND_FACTOR_TRUSTLEVEL] = secondFactorTrustLevelToSet;

    // store the entry
    trustEntries[key] = entry;

    // save to disk
    write();
}

void JsonTrustStore::revokeTrust(const std::string& key)
{
    std::lock_guard<std::recursive_mutex> locker(mutex);

    DEBUG_FUNC();

    // check for existing entry, just for logging purposes
    if (!trustEntries.isMember(key))
    {
        LOG_WARN() << "Trust store entry for '" << key << "' does not exist. No trust to remove.";
        return;
    }

    LOG_INFO() << "Removing trust parameters for '" << key << "'.";

    trustEntries.removeMember(key);

    // save to disk
    write();
}

} /* namespace keo_json_security_handler */
