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

#ifndef KEO_TRUSTCENTER_SRC_TRUSTSTORE_H_
#define KEO_TRUSTCENTER_SRC_TRUSTSTORE_H_

/** @addtogroup examples_security
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <mutex>
#include <string>
/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "json/json.h"

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

namespace keo_json_security_handler
{

/**
 * This class represents a JSON-based trust store. It is implemented as a key-value
 * store. Keys take the form "SHIPId.ski". The entries contain the certificate and
 * the trust level of the respective peer. The trust store is written to and read
 * from the file system.
 */
class JsonTrustStore
{
public:
    /**
     * Constructor
     *
     * @param fileName the full path to the file holding the trust store
     */
    JsonTrustStore(const std::string& fileName);

    /**
     * Destructor
     */
    ~JsonTrustStore();

    /**
     * Initialize the trust store. This includes a check whether the given file exists
     * and the attempt to create it if it does not. Initialization fails as well if the
     * file exists but does not contain parseable JSON.
     *
     * @return true if initialization succeeded, false otherwise.
     */
    bool init();

    /**
     * Get the trust level for the trust store entry identified by entryId.
     *
     * @param key the key of the desired trust store entry.
     *
     * @return the trust level for the given entry ID. 0 for each member, if not found.
     */
    keo_ship::TrustLevel getTrustLevel(const std::string& key) const;

    /**
     * Retrieve the certificate for the given entry ID.
     *
     * @param key the key of the desired entry
     *
     * @return the X509 certificate for the given key
     */
    keo_ship::X509Certificate getCertificate(const std::string& key) const;

    /**
     * Retrieve the key under which the given certificate is stored.
     * If the same certificate exists in the trust store for different
     * keys, the behaviour is undefined. (You might get a different
     * key than expected)
     *
     * @param certificate the certificate to determine the entry ID for
     *
     * @return the key, empty string if no matching entry is found.
     */
    std::string getKeyByCertificate(const keo_ship::X509Certificate& certificate) const;

    /**
     * Set the trust level for the given entry ID. This stores the given
     * certificate in the trust store, along with the given trust level.
     *
     * @param key the key under which to store the trust parameters
     * @param cert the certificate to store
     * @param trustLevel the trust level to store
     */
    void setTrustLevel(
        const std::string& key, const keo_ship::X509Certificate& cert, const keo_ship::TrustLevel& trustlevel);

    /**
     * Revoke trust for the given entry ID. This removes the stored certificate from the
     * trust store, along with the stored trust level.
     *
     * @param key the key to remove the stored values
     */
    void revokeTrust(const std::string& key);

private:
    /**
     * Write the trust store to the given file.
     *
     * @return true if the file was successfully written, false otherwise.
     */
    bool write() const;

private:
    mutable std::recursive_mutex mutex;

    std::string fileName;
    KEJson::Value trustEntries;
};

} /* namespace keo_json_security_handler */

/** @}
 * end of file
 */

#endif /* KEO_TRUSTCENTER_SRC_TRUSTSTORE_H_ */
