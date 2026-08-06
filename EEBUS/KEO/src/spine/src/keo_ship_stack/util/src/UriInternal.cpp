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
* ****************************************************************************** */
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

namespace keo_ship
{

// see RFC 3986
char const* pattern_Uri = "^(([^:\\/?#]+):)?(\\/\\/([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?";
// Group index                      12              3      4          5       6   7        8 9
int const pattern_Uri_groupCnt = 10;
/*
 * Note: The above defined pattern fails for e.g.: http://[fe80::a00:27ff:fe6a:2899/128]/path
 * Expected:
 * 1.  `http:`
 * 2.  `http`
 * 3.  `//[fe80::a00:27ff:fe6a:2899]`
 * 4.  `[fe80::a00:27ff:fe6a:2899]`
 * 5.  `/path`
 * Result:
 * 1.  `http:`
 * 2.  `http`
 * 3.  `//[fe80::a00:27ff:fe6a:2899`
 * 4.  `[fe80::a00:27ff:fe6a:2899`
 * 5.  `/128]/path`
 */

// The following patterns for regular expressions are taken from
// http://jmrware.com/articles/2009/uri_regexp/URI_regex.html.
// They are manually modified concerning escape sequences (i.e. '\' character) and spaces.
// Also the non-capturing group feature is not supported by POSIX standard,
// i.e. the "?:" character sequence is removed.
//
char const* pattern_scheme = "[A-Za-z][A-Za-z0-9+.-]*";

char const* pattern_IPv4address =
    //        "((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}" // dec-octet "." dec-octet "."
    //        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"// dec-octet "." dec-octet"
    // --> Not accurate enough (e.g. 123444.0.0.1 matches. Better solution
    // taken from https://www.safaribooksonline.com/library/view/regular-expressions-cookbook/9780596802837/ch07s16.html
    "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

char const* pattern_IPv6address = "("
                                         "(([0-9A-Fa-f]{1,4}:){6}"
                                         "|::([0-9A-Fa-f]{1,4}:){5}"
                                         "|([0-9A-Fa-f]{1,4})?::([0-9A-Fa-f]{1,4}:){4}"
                                         "|(([0-9A-Fa-f]{1,4}:){0,1} [0-9A-Fa-f]{1,4})?::([0-9A-Fa-f]{1,4}:){3}"
                                         "|(([0-9A-Fa-f]{1,4}:){0,2} [0-9A-Fa-f]{1,4})?::([0-9A-Fa-f]{1,4}:){2}"
                                         "|(([0-9A-Fa-f]{1,4}:){0,3} [0-9A-Fa-f]{1,4})?::[0-9A-Fa-f]{1,4}:"
                                         "|(([0-9A-Fa-f]{1,4}:){0,4} [0-9A-Fa-f]{1,4})?::"
                                         ")(" // ls32
                                         "[0-9A-Fa-f]{1,4}:[0-9A-Fa-f]{1,4}" // factored out
                                         "|((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}" // from first 7 lines
                                         "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)" // of ABNF rule above.
                                         ")"
                                         "|(([0-9A-Fa-f]{1,4}:){0,5} [0-9A-Fa-f]{1,4})?::[0-9A-Fa-f]{1,4}"
                                         "|(([0-9A-Fa-f]{1,4}:){0,6} [0-9A-Fa-f]{1,4})?::"
                                         ")";

char const* pattern_reg_name = "(([A-Za-z0-9\\._~!$&'()*+,;=-]|%[0-9A-Fa-f]{2})*)";

char const* pattern_userinfo = "((([A-Za-z0-9._~!$&'()*+,;=:-]|%[0-9A-Fa-f]{2}))*)@"
    // Group index
    //       123
    ;
int const pattern_userinfo_groupCnt = 4;

char const* pattern_path = { "((/([A-Za-z0-9._~!$&'()*+,;=:@-]|%[0-9A-Fa-f]{2})*)*"
                                    "|/"
                                    "(([A-Za-z0-9._~!$&'()*+,;=:@-]|%[0-9A-Fa-f]{2})+"
                                    "(/([A-Za-z0-9._~!$&'()*+,;=:@-]|%[0-9A-Fa-f]{2})*)*"
                                    ")?"
                                    "|([A-Za-z0-9._~!$&'()*+,;=@-] |%[0-9A-Fa-f]{2})+"
                                    "(/([A-Za-z0-9.~!$&'()*+,;=:@-]|%[0-9A-Fa-f]{2})*)*"
                                    "|([A-Za-z0-9.~!$&'()*+,;=:@-]|%[0-9A-Fa-f]{2})+"
                                    "(/([A-Za-z0-9.~!$&'()*+,;=:@-]|%[0-9A-Fa-f]{2})*)*"
                                    "|"
                                    ")" };


/**
 * Compile a regular expression object.
 * @param regex
 *        The regular expression object to be compiled.
 * @param pattern
 *        The pattern the regular expression is to be compiled with.
 * @return
 *        True if successful, else false.
 */
bool UriInternal::regex_compile(regex_t& regex, char const* pattern)
{
    bool ret = false;
    int errorCode = regcomp(&regex, pattern, REG_ICASE | REG_EXTENDED);
    if (errorCode == 0)
    {
        ret = true;
    }
    // enable for debug purpose
    //    else
    //    {
    //        size_t length = regerror (errorCode, const_cast<regex_t const*>(&regex), NULL, 0);
    //        char *buffer = new char[length];
    //        (void) regerror (errorCode, const_cast<regex_t const*>(&regex), buffer, length);
    //        std::cerr << "failed to compile the regular expression: " << buffer;
    //        delete [] buffer;
    //    }
    return (ret);
}

/**
 * Apply a compiled regular expression object to a given string.
 * @param regex
 *        The compiled regular expression object.
 * @param str
 *        The string to be scanned for.
 * @param matches
 *        Pointer to an array of regmatch_t objects. Each found group will
 *        be represented by an array entry.
 * @param sizeMatches
 *        Number of elements of the array.
 * @return
 *        True if successful, else false.
 *        Note: regex memory is released.
 */
bool UriInternal::regex_execute(regex_t& regex, char const* str, regmatch_t* matches, size_t sizeMatches)
{
    bool ret = false;
    int errorCode = regexec(&regex, str, sizeMatches, matches, 0);
    if (errorCode == 0)
    {
        ret = true;
    }
    // enable for debug purpose
    //    else if (errorCode != REG_NOMATCH)
    //    {
    //        size_t length = regerror (errorCode, const_cast<regex_t const*>(&regex), NULL, 0);
    //        char *buffer = new char[length];
    //        (void) regerror (errorCode, const_cast<regex_t const*>(&regex), buffer, length);
    //        std::cerr << "Failed to execute the regular expression: ErrorCode=" << errorCode << " ErrorString=" <<
    //        buffer;
    //        delete [] buffer;
    //    }
    regfree(&regex);
    return (ret);
}

UriInternal::UriInternal(std::string uri)
{
    enum
    {
        REGEX_RESULT_INDEX_SCHEMA = 2,
        REGEX_RESULT_INDEX_AUTHORITY = 4,
        REGEX_RESULT_INDEX_PATH = 5,
        REGEX_RESULT_INDEX_QUERY = 7,
        REGEX_RESULT_INDEX_FRAGMENT = 9
    };

    regex_t regex;
    if (regex_compile(regex, pattern_Uri))
    {
        regmatch_t m[pattern_Uri_groupCnt];
        if (regex_execute(regex, uri.c_str(), m, pattern_Uri_groupCnt))
        {
            for (int i = 0; i < pattern_Uri_groupCnt; i++)
            {
                if (m[i].rm_so == -1)
                {
                    // enable for debug purpose
                    // std::cout << i << ": " << std::endl;
                    continue;
                }
                // enable for debug purpose
                // std::cout << i << ": " << uri.substr(m[i].rm_so, m[i].rm_eo - m[i].rm_so) << std::endl;
                if (i == REGEX_RESULT_INDEX_SCHEMA)
                {
                    validateAndSetScheme(uri.substr(m[i].rm_so, m[i].rm_eo - m[i].rm_so));
                    continue;
                }
                if (i == REGEX_RESULT_INDEX_AUTHORITY)
                {
                    validateAndSetAuthority(uri.substr(m[i].rm_so, m[i].rm_eo - m[i].rm_so));
                    continue;
                }
                if (i == REGEX_RESULT_INDEX_PATH)
                {
                    validateAndSetPath(uri.substr(m[i].rm_so, m[i].rm_eo - m[i].rm_so));
                    continue;
                }
            }
        }
        regfree(&regex);
    }
}

std::string UriInternal::getUri(std::string leadingAuthoritySlashes) const
{
    std::string ret;
    if (isValid())
    {
        ret = m_scheme + ":" + leadingAuthoritySlashes + (!m_userinfo.empty() ? (m_userinfo + "@") : "")
            + Uri::percentEncode(m_host) + (!m_port.empty() ? (":" + m_port) : "") + Uri::percentEncode(m_path);
    }
    return (ret);
}

bool UriInternal::isValid() const
{
    return (!m_scheme.empty() && !m_path.empty());
}

std::string const& UriInternal::getScheme() const
{
    return (m_scheme);
}

std::string const& UriInternal::getUserInfo() const
{
    return (m_userinfo);
}

std::string UriInternal::getHost() const
{
    return UriInternal::removeOuterSquareBrackets(m_host);
}

unsigned short UriInternal::getPort() const
{
    unsigned short ret = Uri::DefaultPortNumber;
    if (!m_port.empty())
    {
        std::istringstream ss(m_port);
        ss >> ret;
    }
    return (ret);
}

std::string const& UriInternal::getPath() const
{
    return (m_path);
}

void UriInternal::setScheme(std::string const& scheme)
{
    regex_t regex;
    if (regex_compile(regex, pattern_scheme))
    {
        if (regex_execute(regex, scheme.c_str(), NULL, 0))
        {
            m_scheme = scheme;
        }
        regfree(&regex);
    }
}

void UriInternal::setUserInfo(std::string const& userinfo)
{
    m_userinfo = userinfo;
}

void UriInternal::setHost(std::string const& host)
{
    m_host = UriInternal::addOuterSquareBrackets(host);
}

void UriInternal::setPath(std::string const& path)
{
    validateAndSetPath(path);
}

void UriInternal::setPort(unsigned short port)
{
    m_port = static_cast<std::ostringstream*>(&(std::ostringstream() << port))->str();
}

void UriInternal::validateAndSetScheme(std::string const& str)
{
    regex_t regex;
    if (regex_compile(regex, pattern_scheme))
    {
        if (regex_execute(regex, str.c_str(), NULL, 0))
        {
            m_scheme = str;
        }
        regfree(&regex);
    }
}

void UriInternal::validateAndSetAuthority(std::string const& str)
{
    regex_t regex;
    if (regex_compile(regex, pattern_userinfo))
    {
        regmatch_t m[pattern_userinfo_groupCnt];
        if (regex_execute(regex, str.c_str(), m, pattern_userinfo_groupCnt))
        {
            // user info is located in capture group 1
            if ((m[1].rm_so != -1) && (m[1].rm_eo != -1))
            {
                m_userinfo = str.substr(m[1].rm_so, m[1].rm_eo - m[1].rm_so);
                validateAndSetHost(str.substr(m[1].rm_eo + 1));
            }
            else
            {
                validateAndSetHost(str);
            }
        }
        else
        {
            validateAndSetHost(str);
        }
    }
}

void UriInternal::validateAndSetPath(std::string const& str)
{
    regex_t regex;
    if (regex_compile(regex, pattern_path))
    {
        if (regex_execute(regex, str.c_str(), NULL, 0))
        {
            m_path = str;
        }
    }
    (void)pattern_path;
    m_path = str;
}

void UriInternal::validateAndSetHost(std::string const& str)
{
    // see RFC 3986 + port number MUST have exactly one leading colon
    // Note: Do not get mixed up with colons given in an IPv6 address!
    //       To avoid this, an IPv6 address is enclosed by '[', ']' characters.
    size_t pos = str.find_last_of(']');
    if (pos == std::string::npos)
    {
        // Assumption: no IPv6 address. Scan for the last colon.
        pos = str.find_last_of(':');
    }
    else
    {
        // Assumption: IPv6 address. Scan for the first colon behind then ']' character
        pos = str.find_first_of(':', pos);
    }

    if (pos != std::string::npos)
    {
        std::string portStr = str.substr(pos + 1);
        static char const* patternPort = "([0-9]*)";
        regex_t regex;
        if (regex_compile(regex, patternPort))
        {
            if (regex_execute(regex, portStr.c_str(), NULL, 0))
            {
                m_port = portStr;
            }
        }
        if (pos > 0)
        {
            m_host = str.substr(0, pos);
        }
    }
    else
    {
        m_host = str;
    }
}

std::string UriInternal::addOuterSquareBrackets(std::string const& str)
{
    // add [] brackets around if not there and string contains at least one colon
    std::string s = str;
    if (!s.empty())
    {
        if (s.find(":") != std::string::npos)
        {
            if (*(s.begin()) != '[' && *(s.end() - 1) != ']')
            {
                s = "[" + s + "]";
            }
        }
    }
    return s;
}

std::string UriInternal::removeOuterSquareBrackets(std::string const& str)
{
    // remove [] brackets around if there
    std::string s = str;
    if (!s.empty())
    {
        if (*(s.begin()) == '[' && *(s.end() - 1) == ']')
        {
            s = s.substr(1, s.length() - 2);
        }
    }
    return s;
}

std::string percentEncode(std::string const& str, bool encodeReserved)
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

std::string UriInternal::log() const
{
    std::stringstream s;
    s << "isValid   = " << std::boolalpha << isValid() << "\nScheme    = " << m_scheme << "\nUserinfo  = " << m_userinfo
      << "\nHost      = " << m_host << " (type=" << Uri::getHostTypeStr(Uri::getHostType(m_host)) << ")"
      << "\nPort      = " << m_port << "\nPath      = " << m_path << "\ngetUri    = " << getUri();
    return (s.str());
}

} // namespace keo_ship

