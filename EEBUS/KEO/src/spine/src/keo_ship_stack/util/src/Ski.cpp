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

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <algorithm>
#include <iomanip>

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

static std::string toLower(const std::string& in)
{
    std::string result;
    result.resize(in.size());
    std::transform(in.begin(), in.end(), result.begin(), ::tolower);
    return result;
}

static std::string toHEX(const char* data, size_t len)
{
    std::string retVal;
    char buf[3];
    for (size_t i = 0; i < len; i++)
    {
        sprintf(buf, "%02x", static_cast<std::uint8_t>(data[i]));
        retVal.append(buf);
    }
    return retVal;
}

std::string Ski::fromRaw(const char* data, size_t size)
{
    return (NULL != data && size == 20) ? toLower(toHEX(data, size)) : std::string();
}

std::string Ski::normalize(const std::string& ski)
{
    std::string str(toLower(ski));
    return validate(str) ? str : std::string();
}

bool Ski::validate(const std::string& ski)
{
    bool failed = ski.size() != 40;
    if (!failed)
        for (std::string::const_iterator iter = ski.begin(); !failed && iter != ski.end(); ++iter)
        {
            failed = !((*iter >= 'a' && *iter <= 'f') || (*iter >= '0' && *iter <= '9'));
        }
    return !failed;
}

int Ski::compare(const std::string& skiA, const std::string& skiB)
{
    return normalize(skiA).compare(normalize(skiB));
}

} // namespace keo_ship
