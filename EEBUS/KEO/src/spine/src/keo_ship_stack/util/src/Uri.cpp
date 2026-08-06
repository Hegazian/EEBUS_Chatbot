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
*     @brief      KEO URI
*
*     @par        Module description
*                 Handling of URI strings
*
*     @author     KEO GmbH 2016 @n
*                 All rights reserved !
*/

/* ****************************************************************************** *
*  standard header files                                                         *
* ****************************************************************************** */
#include <iostream>
#include <regex.h>
#include <sstream>
#include <stdlib.h>
#include <string>

#include <algorithm>
#include <iomanip>
#include <vector>

/* ****************************************************************************** *
*  project header files                                                          *
* *******************************************************************************/
#include "UriInternal.h"
#include <keo_ship/Uri.h>


/* ****************************************************************************** *
*  defines                                                                       *
* ****************************************************************************** */

/* ****************************************************************************** *
*  types                                                                         *
* ****************************************************************************** */

/* ****************************************************************************** *
*  definition                                                                    *
* ****************************************************************************** */

namespace keo_ship {

char const* Uri::literal::HostTypeIPv4Address = "IPv4";
char const* Uri::literal::HostTypeIPv6Address = "IPv6";
char const* Uri::literal::HostTypeRegisteredName = "registered-name";
char const* Uri::literal::HostTypeUnknown = "unknown";


Uri::Uri(const std::string &uri)
: d (new UriInternal(Uri::percentDecode(uri)))
{
}

Uri::Uri(const Uri &uri)
: d(new UriInternal(uri.getUri()))
{
}

Uri::~Uri()
{
    delete d;
}

Uri& Uri::operator=(const Uri& rhs)
{
    if (this != &rhs)
    {
        *d = *rhs.d;
    }
    return *this;
}

std::string Uri::getUri(std::string leadingAuthoritySlashes) const
{
    return d->getUri(leadingAuthoritySlashes);
}

bool Uri::isValid() const
{
    return d->isValid();
}

std::string const& Uri::getScheme() const
{
    return d->getScheme();
}

std::string const& Uri::getUserInfo() const
{
    return d->getUserInfo();
}

std::string Uri::getHost() const
{
    return d->getHost();
}

bool Uri::isValidIpv4(std::string const& ipv4)
{
    bool ret = false;
    if (!ipv4.empty())
    {
        regex_t regex;
        if (UriInternal::regex_compile(regex, pattern_IPv4address))
        {
            if (UriInternal::regex_execute(regex, ipv4.c_str(), NULL, 0))
            {
                ret = true;
            }
            regfree(&regex);
        }
    }
    return (ret);
}

bool Uri::isValidIpv6(std::string const& ipv6)
{
    bool ret = false;
    if (!ipv6.empty() && (*ipv6.begin() == '[') && (*(ipv6.end() - 1) == ']'))
    {
        regex_t regex;
        if (UriInternal::regex_compile(regex, pattern_IPv6address))
        {
            if (UriInternal::regex_execute(regex, ipv6.c_str(), NULL, 0))
            {
                ret = true;
            }
            regfree(&regex);
        }
    }
    return (ret);
}

bool Uri::isValidRegisteredName(std::string const& regname)
{
    bool ret = false;
    if (!regname.empty())
    {
        regex_t regex;
        static int const pattern_reg_name_groupCnt = 3;
        regmatch_t m[pattern_reg_name_groupCnt];
        if (UriInternal::regex_compile(regex, pattern_reg_name))
        {
            if (UriInternal::regex_execute(regex, regname.c_str(), m, pattern_reg_name_groupCnt))
            {
                // m[0] is expected to have the full length of m_host
                if ((m[1].rm_so == 0) && (m[1].rm_eo == static_cast<int>(regname.size())))
                {
                    ret = true;
                }
            }
            regfree(&regex);
        }
    }
    return (ret);
}

unsigned short Uri::getPort() const
{
    return d->getPort();
}

std::string const& Uri::getPath() const
{
    return d->getPath();
}

void Uri::setScheme(std::string const& scheme)
{
    d->setScheme(scheme);
}

void Uri::setUserInfo(std::string const& userinfo)
{
    d->setUserInfo(userinfo);
}

void Uri::setHost(std::string const& host)
{
    d->setHost(host);
}

void Uri::setPath(std::string const& path)
{
    d->setPath(path);
}

void Uri::setPort(unsigned short port)
{
    d->setPort(port);
}

std::string Uri::percentEncode(std::string const& str, bool encodeReserved)
{
    // RFC 3986, section 2.2
    const char reserved_characters[]
        = { ':', '/', '?', '#', '[', ']', '@', '!', '$', '&', '\'', '(', ')', '*', '+', ',', ';', '=' };
    std::vector<char> reservedCharacters;
    reservedCharacters.assign(reserved_characters, reserved_characters + sizeof(reserved_characters));

    // RFC 3986, section 2.3
    const char unreserved_characters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
        'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6',
        '7', '8', '9', '-', '.', '_', '~' };
    std::vector<char> unreservedCharacters;
    unreservedCharacters.assign(unreserved_characters, unreserved_characters + sizeof(unreserved_characters));

    std::ostringstream encoded;
    encoded << std::hex << std::setfill('0') << std::uppercase;

    for (std::string::const_iterator strIt = str.begin(); strIt != str.end(); strIt++)
    {
        std::vector<char>::iterator it;
        unsigned char c = *strIt;

        if (!encodeReserved)
        {
            it = find(reservedCharacters.begin(), reservedCharacters.end(), c);
            if (it != reservedCharacters.end())
            {
                encoded << c;
                continue;
            }
        }

        it = find(unreservedCharacters.begin(), unreservedCharacters.end(), c);
        {
            if (it != unreservedCharacters.end())
            {
                encoded << c;
            }
            else
            {
                encoded << '%' << std::setw(2) << static_cast<unsigned int>(c);
            }
        }
    }

    return encoded.str();
}

std::string Uri::percentDecode(std::string const& str)
{
    std::ostringstream decoded;

    for (std::string::const_iterator strIt = str.begin(); strIt != str.end(); strIt++)
    {
        unsigned char c = *strIt;
        if (c == '%')
        {
            if (strIt + 2 < str.end())
            {
                std::string characterEncodedStr;
                characterEncodedStr.resize(2);
                std::transform(strIt + 1, strIt + 3, characterEncodedStr.begin(), ::toupper);
                if (isxdigit(*(strIt + 1)) && isxdigit(*(strIt + 2)))
                {
                    std::stringstream ss;
                    ss << std::uppercase << std::hex << characterEncodedStr;
                    unsigned int characterDecodedInt;
                    ss >> characterDecodedInt;
                    unsigned char characterDecoded = static_cast<unsigned char>(characterDecodedInt);
                    decoded << characterDecoded;
                    strIt += 2;
                    continue;
                }
            }
            // error, return empty string
            return std::string();
        }
        else
        {
            // no percent encoded character
            decoded << c;
        }
    }
    return decoded.str();
}

Uri::HostType Uri::getHostType(std::string const& host)
{
    HostType ret = HOST_TYPE_UNKNOWN;
    if (!host.empty())
    {
        if (isValidIpv4(host))
        {
            ret = HOST_TYPE_IPv4;
        }
        else if (isValidIpv6(UriInternal::addOuterSquareBrackets(host)))
        {
            ret = HOST_TYPE_IPv6;
        }
        else if (isValidRegisteredName(host))
        {
            ret = HOST_TYPE_REGISTERED_NAME;
        }
    }
    return (ret);
}

std::string Uri::getHostTypeStr(HostType hostType)
{
    std::string ret;
    if (hostType == HOST_TYPE_IPv4)
    {
        ret = literal::HostTypeIPv4Address;
    }
    else if (hostType == HOST_TYPE_IPv6)
    {
        ret = literal::HostTypeIPv6Address;
    }
    else if (hostType == HOST_TYPE_REGISTERED_NAME)
    {
        ret = literal::HostTypeRegisteredName;
    }
    else
    {
        ret = literal::HostTypeUnknown;
    }
    return (ret);
}

std::string Uri::log() const
{
    return d->log();
}

} // namespace keo_ship
