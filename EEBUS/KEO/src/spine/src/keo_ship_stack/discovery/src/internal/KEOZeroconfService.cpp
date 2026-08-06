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

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "KEOZeroconfService.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

KEOZeroconfService::KEOZeroconfService()
    : mPort(0)
    , mRemoved(false)
    , mOwnService(false)
    , mProtocolType(PROTOCOL_UNSPEC)
    , mInterfaceId(-1)
{
}

KEOZeroconfService::KEOZeroconfService(const std::string& name, const std::string& domain, const std::string& host,
    unsigned short port, const std::list<std::pair<std::string, std::string> >& txt, bool bRemoved)
    : mName(name)
    , mDomain(domain)
    , mHost(host)
    , mTxt(txt)
    , mPort(port)
    , mRemoved(bRemoved)
    , mOwnService(true)
    , mProtocolType(PROTOCOL_UNSPEC)
    , mInterfaceId(-1)
{
}

bool KEOZeroconfService::operator==(const KEOZeroconfService& s) const
{
    return (isEqualHeader(s) && isEqualContent(s));
}

bool KEOZeroconfService::isEqualHeader(const KEOZeroconfService& s) const
{
    return (mName == s.mName && mDomain == s.mDomain);
}

bool KEOZeroconfService::isEqualContent(const KEOZeroconfService& s) const
{
    return (mHost == s.mHost && mPort == s.mPort && mTxt == s.mTxt);
}

void KEOZeroconfService::copyContent(const KEOZeroconfService& s)
{
    mHost = s.mHost;
    mPort = s.mPort;
    mTxt = s.mTxt;
}
