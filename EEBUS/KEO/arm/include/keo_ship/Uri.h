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

#ifndef KEO_SHIP_STACK_INCLUDE_URI_H_
#define KEO_SHIP_STACK_INCLUDE_URI_H_

/* ****************************************************************************** *
*  standard header files                                                         *
* ****************************************************************************** */
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

namespace keo_ship
{
/**
 * @addtogroup ship
 * @{
 */

class UriInternal;

/**
* Uri handles URIs and provides some convenience methods.
*
*/
class Uri
{
public:
    enum HostType
    {
        HOST_TYPE_UNKNOWN,
        HOST_TYPE_IPv4,
        HOST_TYPE_IPv6,
        HOST_TYPE_REGISTERED_NAME
    };

    struct literal
    {
        static char const* HostTypeIPv4Address;
        static char const* HostTypeIPv6Address;
        static char const* HostTypeRegisteredName;
        static char const* HostTypeUnknown;
    };

    /**
     * The default port value (returned by getPort() if no port-part
     * was found in constructors URI string).
     */
    static unsigned short const DefaultPortNumber = 0;

    /**
     * Retrieve the given host type from given string.
     * @param host
     *        String to be verified.
     * @return
     *        Host type.
     */
    static HostType getHostType(std::string const& host);

    /**
     * Retrieve the given host type as string.
     * @param hostType
     * @return
     *        Host type as string
     */
    static std::string getHostTypeStr(HostType hostType);

    /**
     * Check, if the given string is a valid IPv4 address
     * (concerning URI definition).
     * @param ipv4
     *        The desired string to verify.
     * @return
     *        True if IPv4 verification is successful, else false.
     */
    static bool isValidIpv4(std::string const& ipv4);

    /**
     * Check, if the given string is a valid IPv6 address
     * (concerning URI definition).
     * @param ipv6
     *        The desired string to verify. MUST be enclosed by
     *        square brackets ('[', ']').
     * @return
     *        True if IPv6 verification is successful, else false.
     */
    static bool isValidIpv6(std::string const& ipv6);

    /**
     * Check, if the given string is a valid registered name
     * (concerning URI definition).
     * @param regname
     *        The desired string to verify.
     * @return
     *        True if registered name verification is successful, else false.
     */
    static bool isValidRegisteredName(std::string const& regname);

    /**
     * Percent-encode given string according to RFC 3986
     * @param str
     *        The desired string to encode.
     * @param encodeReserved
     *        Encode reserved characters (section 2.2) if set to true.
     * @return
     *        The encoded percent-encoded string.
     */
    static std::string percentEncode(std::string const& str, bool encodeReserved = false);

    /**
     * Decode given percent-encoded string (RFC 3986)
     * @param str
     *        The desired string to decode.
     * @return
     *        The decoded string, empty string on error.
     */
    static std::string percentDecode(std::string const& str);

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
    explicit Uri(const std::string& uri);
    Uri(const Uri& uri);
    Uri& operator=(const Uri& rhs);

    /**
     * Creates a URI from internal members. If the object is not valid,
     * an empty string is returned.
     * @param leadingAuthoritySlashes
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
      * Note: For IPv6 enclosing square brackets are removed.
      * @return
      *        The host part (e.g. '127.0.0.1', 'fe80::a00:27ff:fe6a:2899', 'www.example.com').
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
     * @param userinfo
     */
    void setUserInfo(std::string const& userinfo);

    /**
     * Set the host part (without port number).
     * Note: For IPv6 enclosing square brackets are not required.
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

    ~Uri();

private:
    UriInternal* d;
};

/** @}
* end of file
*/
}

#endif /* KEO_SHIP_STACK_INCLUDE_URI_H_ */
