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
 *     @brief      Unit Tests for class Uri
 *
 *     @par        Module description
 *                 Unit Tests for class Uri
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include "gtest/gtest.h"
#include <regex>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_ship/Uri.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */
#define LOG(x) std::cout << x << std::endl
#define LOG_ERROR(x) std::cout << "\033[1;31m" << x << "\033[0m" << std::endl

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

using namespace keo_ship;

/**
 * Test for valid URI's
 */
TEST(UriTest, uriValidTest)
{
    static char const* arrayValidUri[]
        = { "http://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal",
            "https://example.org/absolute/URI/with/absolute/path/to/resource.txt", "ftp://example.org/resource.txt",
            "wss://127.0.0.1/resource.txt", "wss://abi-vm.local/resource.txt",
            "http://user:password@www.ics.uci.edu/pub/ietf/uri", "http://user@www.ics.uci.edu/pub/ietf/uri",
            "http://:user@www.ics.uci.edu:233/pub/ietf/uri/",
            "file:///C:/Users/Benutzer/Desktop/Uniform%20Resource%20Identifier.html",
            "http://[fe80::428d:5cff:fe79:8b9f]:64/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal",
            "http://[::1]:128/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal",
            "http://192.168.22.102:64/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal",
            "http://127.0.0:128/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal" };

    for (size_t i = 0; i < (sizeof(arrayValidUri) / sizeof(char*)); i++)
    {
        std::string uri = arrayValidUri[i];
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(uri == u.getUri());
    }
}

TEST(UriTest, IPv4)
{
    EXPECT_TRUE(Uri::isValidIpv4("127.0.0.1"));
    EXPECT_TRUE(Uri::isValidIpv4("192.168.100.112"));
    EXPECT_FALSE(Uri::isValidIpv4("192.168.100.1123"));
    EXPECT_FALSE(Uri::isValidIpv4("192.168.100."));
    EXPECT_FALSE(Uri::isValidIpv4("192.168.000.1123"));
}

TEST(UriTest, uriIPv4)
{
    {
        std::string uri("http://192.168.22.102:64/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "192.168.22.102");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeIPv4Address);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == 64);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("http://192.168.22.102/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "192.168.22.102");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeIPv4Address);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("http://192.168.22./path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "192.168.22.");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("http://192000.168.22.127/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "192000.168.22.127");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("http://192.168.0.1279/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "192.168.0.1279");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("http://192..0.1279/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "192..0.1279");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri() == uri);
    }
}

TEST(UriTest, uriIPv6)
{
    {
        std::string uri("http://[::2899]/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "::2899");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeIPv6Address);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("http://[fe80::a00:27ff:fe6a:2899]:64/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "fe80::a00:27ff:fe6a:2899");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeIPv6Address);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == 64);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("http://[fe80::a00:27ff:fe6a:2899]/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "fe80::a00:27ff:fe6a:2899");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeIPv6Address);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        // This one will fail, because prefix length information is not allowed
        std::string uri("http://[fe80::a00:27ff:fe6a:2899/128]/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_FALSE(u.getHost() == "fe80::a00:27ff:fe6a:2899");
        EXPECT_FALSE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeIPv6Address);
        EXPECT_FALSE(u.getPath() == "/path");
        EXPECT_FALSE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri() == uri); // however, this is true
    }

    {
        std::string scheme = "wss";
        std::string host = "fe80::a00:27ff:febc:9797%eth0";
        unsigned short port = 4711;
        std::string path = "/ship";
        std::string uri = "wss://[fe80::a00:27ff:febc:9797%25eth0]:4711/ship";
        {
            std::cout << std::endl << "Given uri: " << uri << std::endl;
            Uri u(uri);
            std::cout << u.log() << std::endl;
            EXPECT_TRUE(scheme == u.getScheme());
            EXPECT_TRUE(host == u.getHost());
            EXPECT_TRUE(port == u.getPort());
            EXPECT_TRUE(path == u.getPath());
            EXPECT_TRUE(u.isValid());
            EXPECT_TRUE(uri == u.getUri());
        }
        {
            Uri u("");
            u.setScheme(scheme);
            u.setHost(host);
            u.setPort(port);
            u.setPath(path);
            std::cout << std::endl << "Created uri: " << uri << std::endl;
            std::cout << u.log() << std::endl;
            EXPECT_TRUE(u.isValid());
            EXPECT_TRUE(uri == u.getUri());
            EXPECT_TRUE(scheme == u.getScheme());
            EXPECT_TRUE(host == u.getHost());
            EXPECT_TRUE(port == u.getPort());
            EXPECT_TRUE(path == u.getPath());
        }
    }
}

TEST(UriTest, uriRegisteredName)
{
    {
        std::string uri("http://www.google.com/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "www.google.com");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("http://www.google.com:8080/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "http");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "www.google.com");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/path");
        EXPECT_TRUE(u.getPort() == 8080);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("https://de.wikipedia.org/wiki/IPv6#URL-Notation_von_IPv6-Adressen");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "https");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "de.wikipedia.org");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/wiki/IPv6");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_FALSE(u.getUri() == uri); // because the fragment part is missing!
    }
}

TEST(UriTest, uriUserInformation)
{
    {
        std::string uri("https://user:password@de.wikipedia.org/wiki/IPv6");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "https");
        EXPECT_TRUE(u.getUserInfo() == "user:password");
        EXPECT_TRUE(u.getHost() == "de.wikipedia.org");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/wiki/IPv6");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("https://user:password@de.wikipedia.org:12345/wiki/IPv6");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "https");
        EXPECT_TRUE(u.getUserInfo() == "user:password");
        EXPECT_TRUE(u.getHost() == "de.wikipedia.org");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/wiki/IPv6");
        EXPECT_TRUE(u.getPort() == 12345);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("https://user@de.wikipedia.org:12345/wiki/IPv6");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "https");
        EXPECT_TRUE(u.getUserInfo() == "user");
        EXPECT_TRUE(u.getHost() == "de.wikipedia.org");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/wiki/IPv6");
        EXPECT_TRUE(u.getPort() == 12345);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("https://user:@de.wikipedia.org:12345/wiki/IPv6");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "https");
        EXPECT_TRUE(u.getUserInfo() == "user:");
        EXPECT_TRUE(u.getHost() == "de.wikipedia.org");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/wiki/IPv6");
        EXPECT_TRUE(u.getPort() == 12345);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("https://:password@de.wikipedia.org:12345/wiki/IPv6");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "https");
        EXPECT_TRUE(u.getUserInfo() == ":password");
        EXPECT_TRUE(u.getHost() == "de.wikipedia.org");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/wiki/IPv6");
        EXPECT_TRUE(u.getPort() == 12345);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("https://:@de.wikipedia.org:12345/wiki/IPv6");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "https");
        EXPECT_TRUE(u.getUserInfo() == ":");
        EXPECT_TRUE(u.getHost() == "de.wikipedia.org");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/wiki/IPv6");
        EXPECT_TRUE(u.getPort() == 12345);
        EXPECT_TRUE(u.getUri() == uri);
    }
}

TEST(UriTest, uriInvalid)
{
    {
        std::string uri(":@de.wikipedia.org:12345");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_FALSE(u.isValid());
    }

    {
        std::string uri("de.wikipedia.org/");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_FALSE(u.isValid());
    }

    {
        std::string uri("de.wikipedia.org");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_FALSE(u.isValid());
    }

    {
        std::string uri("/path");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_FALSE(u.isValid());
    }
}

TEST(UriTest, uriOther)
{
    {
        std::string uri("wss://127.0.0.1:18888/path/resource.txt");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "wss");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "127.0.0.1");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeIPv4Address);
        EXPECT_TRUE(u.getPath() == "/path/resource.txt");
        EXPECT_TRUE(u.getPort() == 18888);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        std::string uri("wss://abi-vm.local:18888/path/resource.txt");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "wss");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "abi-vm.local");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeRegisteredName);
        EXPECT_TRUE(u.getPath() == "/path/resource.txt");
        EXPECT_TRUE(u.getPort() == 18888);
        EXPECT_TRUE(u.getUri() == uri);
    }

    {
        // std::string uri("urn:ISSN:1535–3613");    // unsupported character
        std::string uri("urn:ISSN:1535-3613");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "urn");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeUnknown);
        // EXPECT_TRUE(u.getPath() == "ISSN:1535–3613");
        EXPECT_TRUE(u.getPath() == "ISSN:1535-3613");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri("") == uri);
    }

    {
        std::string uri("urn:oasis:names:specification:docbook:dtd:xml:4.1.2");
        std::cout << std::endl << "Given uri: " << uri << std::endl;
        Uri u(uri);
        std::cout << u.log() << std::endl;
        EXPECT_TRUE(u.isValid());
        EXPECT_TRUE(u.getScheme() == "urn");
        EXPECT_TRUE(u.getUserInfo() == "");
        EXPECT_TRUE(u.getHost() == "");
        EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
            == Uri::literal::HostTypeUnknown);
        EXPECT_TRUE(u.getPath() == "oasis:names:specification:docbook:dtd:xml:4.1.2");
        EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
        EXPECT_TRUE(u.getUri("") == uri);
    }

    {
        std::string uri = "file:///C:/Users/Benutzer/Desktop/Uniform%20Resource%20Identifier.html";
        std::string scheme = "file";
        std::string path = "/C:/Users/Benutzer/Desktop/Uniform Resource Identifier.html";
        {
            std::cout << std::endl << "Given uri: " << uri << std::endl;
            Uri u(uri);
            std::cout << u.log() << std::endl;
            EXPECT_TRUE(u.isValid());
            EXPECT_TRUE(u.getScheme() == scheme);
            EXPECT_TRUE(u.getUserInfo() == "");
            EXPECT_TRUE(u.getHost() == "");
            EXPECT_TRUE(Uri::getHostTypeStr(Uri::getHostType(u.getHost()))
                == Uri::literal::HostTypeUnknown);
            EXPECT_TRUE(u.getPath() == path);
            EXPECT_TRUE(u.getPort() == Uri::DefaultPortNumber);
            EXPECT_TRUE(u.getUri() == uri);
        }
        {
            Uri u("");
            u.setScheme(scheme);
            u.setPath(path);
            std::cout << std::endl << "Created uri: " << uri << std::endl;
            std::cout << u.log() << std::endl;
            EXPECT_TRUE(u.isValid());
            EXPECT_TRUE(u.getUri() == uri);
            EXPECT_TRUE(scheme == u.getScheme());
            EXPECT_TRUE(path == u.getPath());
        }
    }
}

TEST(UriTest, percentEncode)
{
    std::string input;
    std::string expected;
    std::string output;

    input = "fe80::a00:27ff:febc:9797%eth0";
    expected = "fe80::a00:27ff:febc:9797%25eth0";
    output = Uri::percentEncode(input, false);
    EXPECT_TRUE(expected == output);

    std::ostringstream ss;
    for (int i = 0x00; i <= 0xFF; i++)
    {
        ss << static_cast<unsigned char>(i);
    }
    input = ss.str();
    output = Uri::percentEncode(input, false);
    expected = "%00%01%02%03%04%05%06%07%08%09%0A%0B%0C%0D%0E%0F%10%11%12%13%14%15%16%17%18%19%1A%1B%1C%1D%1E%1F%20!%"
               "22#$%25&'()*+,-./"
               "0123456789:;%3C=%3E?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[%5C]%5E_%60abcdefghijklmnopqrstuvwxyz%7B%7C%7D~%7F%80%"
               "81%82%83%84%85%86%87%88%89%8A%8B%8C%8D%8E%8F%90%91%92%93%94%95%96%97%98%99%9A%9B%9C%9D%9E%9F%A0%A1%A2%"
               "A3%A4%A5%A6%A7%A8%A9%AA%AB%AC%AD%AE%AF%B0%B1%B2%B3%B4%B5%B6%B7%B8%B9%BA%BB%BC%BD%BE%BF%C0%C1%C2%C3%C4%"
               "C5%C6%C7%C8%C9%CA%CB%CC%CD%CE%CF%D0%D1%D2%D3%D4%D5%D6%D7%D8%D9%DA%DB%DC%DD%DE%DF%E0%E1%E2%E3%E4%E5%E6%"
               "E7%E8%E9%EA%EB%EC%ED%EE%EF%F0%F1%F2%F3%F4%F5%F6%F7%F8%F9%FA%FB%FC%FD%FE%FF";
    EXPECT_TRUE(expected == output);

    output = Uri::percentEncode(input, true);
    expected = "%00%01%02%03%04%05%06%07%08%09%0A%0B%0C%0D%0E%0F%10%11%12%13%14%15%16%17%18%19%1A%1B%1C%1D%1E%1F%20%21%"
               "22%23%24%25%26%27%28%29%2A%2B%2C-.%2F0123456789%3A%3B%3C%3D%3E%3F%40ABCDEFGHIJKLMNOPQRSTUVWXYZ%5B%5C%"
               "5D%5E_%60abcdefghijklmnopqrstuvwxyz%7B%7C%7D~%7F%80%81%82%83%84%85%86%87%88%89%8A%8B%8C%8D%8E%8F%90%91%"
               "92%93%94%95%96%97%98%99%9A%9B%9C%9D%9E%9F%A0%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC%AD%AE%AF%B0%B1%B2%B3%"
               "B4%B5%B6%B7%B8%B9%BA%BB%BC%BD%BE%BF%C0%C1%C2%C3%C4%C5%C6%C7%C8%C9%CA%CB%CC%CD%CE%CF%D0%D1%D2%D3%D4%D5%"
               "D6%D7%D8%D9%DA%DB%DC%DD%DE%DF%E0%E1%E2%E3%E4%E5%E6%E7%E8%E9%EA%EB%EC%ED%EE%EF%F0%F1%F2%F3%F4%F5%F6%F7%"
               "F8%F9%FA%FB%FC%FD%FE%FF";
    EXPECT_TRUE(expected == output);
}

TEST(UriTest, percentDecode)
{
    std::string input;
    std::string expected;
    std::string output;

    input = "fe80::a00:27ff:febc:9797%25eth0";
    expected = "fe80::a00:27ff:febc:9797%eth0";
    output = Uri::percentDecode(input);
    EXPECT_TRUE(expected == output);

    std::ostringstream ss;
    for (int i = 0x00; i <= 0xFF; i++)
    {
        ss << static_cast<unsigned char>(i);
    }
    expected = ss.str();
    input = "%00%01%02%03%04%05%06%07%08%09%0A%0B%0C%0D%0E%0F%10%11%12%13%14%15%16%17%18%19%1A%1B%1C%1D%1E%1F%20!%22#$%"
            "25&'()*+,-./"
            "0123456789:;%3C=%3E?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[%5C]%5E_%60abcdefghijklmnopqrstuvwxyz%7B%7C%7D~%7F%80%81%"
            "82%83%84%85%86%87%88%89%8A%8B%8C%8D%8E%8F%90%91%92%93%94%95%96%97%98%99%9A%9B%9C%9D%9E%9F%A0%A1%A2%A3%A4%"
            "A5%A6%A7%A8%A9%AA%AB%AC%AD%AE%AF%B0%B1%B2%B3%B4%B5%B6%B7%B8%B9%BA%BB%BC%BD%BE%BF%C0%C1%C2%C3%C4%C5%C6%C7%"
            "C8%C9%CA%CB%CC%CD%CE%CF%D0%D1%D2%D3%D4%D5%D6%D7%D8%D9%DA%DB%DC%DD%DE%DF%E0%E1%E2%E3%E4%E5%E6%E7%E8%E9%EA%"
            "EB%EC%ED%EE%EF%F0%F1%F2%F3%F4%F5%F6%F7%F8%F9%FA%FB%FC%FD%FE%FF";
    output = Uri::percentDecode(input);
    EXPECT_TRUE(expected == output);
    input = "%00%01%02%03%04%05%06%07%08%09%0A%0B%0C%0D%0E%0F%10%11%12%13%14%15%16%17%18%19%1A%1B%1C%1D%1E%1F%20%21%22%"
            "23%24%25%26%27%28%29%2A%2B%2C-.%2F0123456789%3A%3B%3C%3D%3E%3F%40ABCDEFGHIJKLMNOPQRSTUVWXYZ%5B%5C%5D%5E_%"
            "60abcdefghijklmnopqrstuvwxyz%7B%7C%7D~%7F%80%81%82%83%84%85%86%87%88%89%8A%8B%8C%8D%8E%8F%90%91%92%93%94%"
            "95%96%97%98%99%9A%9B%9C%9D%9E%9F%A0%A1%A2%A3%A4%A5%A6%A7%A8%A9%AA%AB%AC%AD%AE%AF%B0%B1%B2%B3%B4%B5%B6%B7%"
            "B8%B9%BA%BB%BC%BD%BE%BF%C0%C1%C2%C3%C4%C5%C6%C7%C8%C9%CA%CB%CC%CD%CE%CF%D0%D1%D2%D3%D4%D5%D6%D7%D8%D9%DA%"
            "DB%DC%DD%DE%DF%E0%E1%E2%E3%E4%E5%E6%E7%E8%E9%EA%EB%EC%ED%EE%EF%F0%F1%F2%F3%F4%F5%F6%F7%F8%F9%FA%FB%FC%FD%"
            "FE%FF";
    output = Uri::percentDecode(input);
    EXPECT_TRUE(expected == output);

    expected = "0815";
    input = "%30%38%31%35";
    output = Uri::percentDecode(input);
    EXPECT_TRUE(expected == output);
    input = "0%38%315";
    output = Uri::percentDecode(input);
    EXPECT_TRUE(expected == output);

    expected = "*+";
    input = "%2a%2B";
    output = Uri::percentDecode(input);
    EXPECT_TRUE(expected == output);

    /* malformed encoded strings */
    expected = ""; // empty string used as error indication
    input = "%30%3";
    output = Uri::percentDecode(input);
    EXPECT_TRUE(expected == output);
    input = "%30%";
    output = Uri::percentDecode(input);
    EXPECT_TRUE(expected == output);
    input = "%3";
    output = Uri::percentDecode(input);
    EXPECT_TRUE(expected == output);
    input = "%";
    output = Uri::percentDecode(input);
    EXPECT_TRUE(expected == output);
}
