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

#ifndef KEO_SHIP_STACK_UTIL_SRC_URI_INTERNAL_H_
#define KEO_SHIP_STACK_UTIL_SRC_URI_INTERNAL_H_

// TODO
/** @ingroup KEToolsLibrary
* @{
*/

/* ****************************************************************************** *
*  standard header files                                                         *
* ****************************************************************************** */
#include <string>
#include <regex.h>

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

namespace keo_ship
{

extern char const* pattern_Uri;
extern char const* pattern_IPv6address;
extern char const* pattern_IPv4address;
extern char const* pattern_reg_name;
extern int const pattern_reg_name_groupCnt;

/**
* Handling of IP addresses
*
*/
class UriInternal
{

public:
    /**
     * Constructor for absolute URI.
     *
     * Fills the internal members according to the following scheme (see RFC3968):
     *  URI example:
     * @n
     * \code{.unparsed}
        https://max:muster@www.example.com:8080/index.html
        \___/   \_/ \____/ \_____________/ \__/\_________/
          |      |    |           |         |       |
        scheme   |   password    host      port    path
                user
                \________/
                    |
                   user-information
                \_____________________________/
                                |
                            authority
     * \endcode
     * @n
     * Notes:
     * (taken from https://de.wikipedia.org/wiki/Uniform_Resource_Identifier
     * and https://en.wikipedia.org/wiki/Uniform_Resource_Identifier)
     *
     * - A valid URI consists at least of scheme and path.
     * - An authority part comprises
     *    + an optional user-information part
     *      (which is a user-name and optional password, separated by colon,
     *      delimited by '@' character)
     *    + a host part (see below)
     *    + an optional port number, separated from the host part by a colon.
     *    + follows two slashes ("//") and is delimited by a slash ('/'), a
     *      question mark ('?'), a hash ('#') or the end of the URI.
     *  - The host part consists of either a registered name (including but
     *    not limited to a hostname), or an IP address. IPv4 addresses must
     *    be in dot-decimal notation, and IPv6 addresses must be enclosed in
     *    brackets ([ ]).
     * - The 'path' must begin with a single slash (/) if an authority part was present,
     *   and may also if one was not. If authority part is not present, 'path' must not
     *   begin with a double slash.
     *   The 'path' is delimited by '/', '?', '#' character or end of the string.
     * - A leading fragment part is ignored.
     * - Parts are extracted using POSIX regular expressions.
     *
     * Important: According to the definitions above IPv6 addresses MUST NOT
     *            contain a prefix length information (e.g. "/64"), because
     *            this generates ambiguity concerning the authority delimiter.
     *
     * @param uri
     *        A string (expected according to above description).
     */
    explicit UriInternal(std::string uri);

    /**
     * Creates a URI from internal members. If the object is not valid,
     * an empty string is returned.
     * @param leadingAuthority
     *        Substring that is placed between the scheme- and authority part.
     *        The colon after the scheme part is added automatically.
     * @return
     *        URI or empty string.
     */
    std::string getUri(std::string leadingAuthoritySlashes = "//") const;

    /**
     * Check current object for validity. The object is valid in case
     * a scheme and path is given.
     * @return
     *        True if valid, else false.
     */
    bool isValid() const;

    /**
     * Retrieve the scheme part.
     * @return
     *        The scheme part (without '://', e.g. 'http', 'wss')
     */
    std::string const& getScheme() const;

    /**
     * Retrieve the user info part.
     * @return
     *        The scheme part (e.g. 'max:muster').
     */
    std::string const& getUserInfo() const;

    /**
      * Retrieve the host part. The host part may consist of an IPv4, IPv6 or regular-name.
      * @return
      *        The host part (e.g. '127.0.0.1', '[fe80::a00:27ff:fe6a:2899]', 'www.example.com').
      */
    std::string getHost() const;

    /**
     * Retrieve the port number.
     * @return
     *        The port number (e.g. 8080).
     *        Return value is DefaultPortNumber if no port is assigned.
     */
    unsigned short getPort() const;

    /**
     * Retrieve the path part.
     * @return
     *        The host part (e.g. '/index.html').
     */
    std::string const& getPath() const;

    /**
     * Set the scheme part ('http')
     * @param scheme
     */
    void setScheme(std::string const& scheme);

    /**
     * Set the user info part (format: <user:password>).
     * @param user
     */
    void setUserInfo(std::string const& userinfo);

    /**
     * Set the host part (without port number)
     * @param host
     */
    void setHost(std::string const& host);

    /**
     * Set the path part (including leading slashes!)
     * @param path
     */
    void setPath(std::string const& path);

    /**
     * Set the port part.
     * @param port
     */
    void setPort(unsigned short port);

    /**
     * Retrieve log information of the current object
     * @return
     *        A string containing log information
     */
    std::string log() const;

    void validateAndSetScheme(std::string const& str);
    void validateAndSetAuthority(std::string const& str);
    void validateAndSetPath(std::string const& str);
    void validateAndSetHost(std::string const& str);

    static bool regex_compile(regex_t& regex, char const* pattern);
    static bool regex_execute(regex_t& regex, char const* str, regmatch_t* matches, size_t sizeMatches);

    static std::string addOuterSquareBrackets(std::string const& str);
    static std::string removeOuterSquareBrackets(std::string const& str);

private:
    std::string m_uri;
    std::string m_scheme;
    std::string m_userinfo;
    std::string m_host;
    std::string m_port;
    std::string m_path;
};
}

/** @}
* end of file
*/

#endif /* KEO_SHIP_STACK_UTIL_SRC_URI_INTERNAL_H_ */
