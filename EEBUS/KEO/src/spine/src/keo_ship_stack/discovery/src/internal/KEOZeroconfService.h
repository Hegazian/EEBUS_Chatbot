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
 *     @brief      KEOZeroconfService
 *
 *     @par        Represents a KEOZeroconfService
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_ZEROCONF_INCLUDE_KEOZEROCONFSERVICE_H_
#define KEO_ZEROCONF_INCLUDE_KEOZEROCONFSERVICE_H_

/** @addtogroup TODO use doxygen group
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <list>
#include <string>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

class KEOZeroconfService
{
public:
    enum ProtocolType
    {
        PROTOCOL_IPV4,
        PROTOCOL_IPV6,
        PROTOCOL_UNSPEC
    };

    /** Creates an empty ZeroconfService object */
    KEOZeroconfService();

    /** Creates a ZeroconfService object */
    /** @param name */
    /**  Name of service */
    /** @param domain */
    /**  Domain of service */
    /** @param host */
    /**  Hostname or IP address of service */
    /** @param port */
    /**  Port number of service */
    /** @param txt */
    /**  TXT record of service */
    /** @param bRemoved */
    /**  Indicates whether this service has been removed */
    KEOZeroconfService(const std::string& name, const std::string& domain, const std::string& host, unsigned short port,
        const std::list<std::pair<std::string, std::string> >& txt, bool bRemoved = false);

    bool operator==(const KEOZeroconfService& s) const;

    bool isEqualHeader(const KEOZeroconfService& s) const;
    bool isEqualContent(const KEOZeroconfService& s) const;
    void copyContent(const KEOZeroconfService& s);

    /** Name of service */
    std::string mName;

    /** Domain of service */
    std::string mDomain;

    /** Hostname or IP address of service */
    std::string mHost;

    /** IP Address of service */
    std::string mAddress;

    /** TXT record of service */
    std::list<std::pair<std::string, std::string> > mTxt;

    /** Port number of service */
    unsigned short mPort;

    /** Indicates whether this service has been removed */
    bool mRemoved;

    bool mOwnService;

    ProtocolType mProtocolType;

    int mInterfaceId;
};

/** @}
 * end of file
 */

#endif /* KEO_ZEROCONF_INCLUDE_KEOZEROCONFSERVICE_H_ */
