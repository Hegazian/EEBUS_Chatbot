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
 *     @brief      Unit Tests for class KEDevicAddress
 *
 *     @par        Module description
 *                 Unit Tests for class KEDevicAddress
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include "gtest/gtest.h"

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_util/KEDeviceAddress.h>

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

using namespace keo_util;

/**
 * Test for valid SPINE address device parts.
 */
TEST(KEDeviceAddressTest, isValid)
{
    static char const* arrayValidDevicePart[] = { "d:_i:12345678_vendor-wide-unique-address",
        "d:_i:1_vendor-wide-unique-address", "d:_n:1_vendor-wide-unique-address", "d:_n:a_vendor-wide-unique-address",
        "d:_n:Z_vendor-wide-unique-address", "d:_i:46925_I-5-32\\.1\\*5" };

    for (size_t i = 0; i < (sizeof(arrayValidDevicePart) / sizeof(char*)); i++)
    {
        std::string str = arrayValidDevicePart[i];
        std::cout << std::endl << "Given device part: " << str << std::endl;
        EXPECT_TRUE(keo_util::KEDeviceAddress::isValid(str));
    }
}

/**
 * Test for valid SPINE address device parts.
 */
TEST(KEDeviceAddressTest, isInValid)
{
    static char const* arrayInvalidDevicePart[]
        = { "d:_i:_vendor-wide-unique-address", "d:__vendor-wide-unique-address", "d:vendor-wide-unique-address",
            "_i:1_vendor-wide-unique-address", "_i1_vendor-wide-unique-address", "d:_i1_vendor-wide-unique-address",
            "d:_i1_:vendor-wide-unique-address", "vendor-wide-unique-address", "d:_n:_vendor-wide-unique-address",
            "d:vendor-wide-unique-address", "_n:1_vendor-wide-unique-address", "_n1_vendor-wide-unique-address",
            "d:_n1_vendor-wide-unique-address", "d:_n1_:vendor-wide-unique-address" };

    for (size_t i = 0; i < (sizeof(arrayInvalidDevicePart) / sizeof(char*)); i++)
    {
        std::string str = arrayInvalidDevicePart[i];
        std::cout << std::endl << "Given device part: " << str << std::endl;
        EXPECT_FALSE(keo_util::KEDeviceAddress::isValid(str));
    }
}

/**
 * Retrieve the vendor specific extension part from a given device address
 */
TEST(KEDeviceAddressTest, getVendorSpecificExtension)
{
    {
        std::string devicePart = "d:_i:12345678_vendor-wide-unique-address";
        EXPECT_STREQ("i:12345678", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:1_vendor-wide-unique-address";
        EXPECT_STREQ("i:1", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_n:1_vendor-wide-unique-address";
        EXPECT_STREQ("n:1", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_n:a_vendor-wide-unique-address";
        EXPECT_STREQ("n:a", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_n:Z_vendor-wide-unique-address";
        EXPECT_STREQ("n:Z", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:46925_I-5-32\\.1\\*5";
        EXPECT_STREQ("i:46925", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:46925_ABCabc-123";
        EXPECT_STREQ("i:46925", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:46925_0123456789";
        EXPECT_STREQ("i:46925", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:46925_I-5-32\\.1\\*5";
        EXPECT_STREQ("i:46925", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:-5-32\\.1\\*5";
        EXPECT_STREQ("", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i_-5-32\\.1\\*5";
        EXPECT_STREQ("", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:_-5-32\\.1\\*5";
        EXPECT_STREQ("", keo_util::KEDeviceAddress::getVendorSpecificExtension(devicePart).c_str());
    }
}

/**
 * Retrieve the vendor-wide unique identifier from a given device address
 */
TEST(KEDeviceAddressTest, getVendorWideUniqueIdentifier)
{
    {
        std::string devicePart = "d:_i:12345678_vendor-wide-unique-address";
        EXPECT_STREQ("vendor-wide-unique-address", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:1_vendor-wide-unique-address";
        EXPECT_STREQ("vendor-wide-unique-address", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_n:1_vendor-wide-unique-address";
        EXPECT_STREQ("vendor-wide-unique-address", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_n:a_vendor-wide-unique-address";
        EXPECT_STREQ("vendor-wide-unique-address", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_n:Z_vendor-wide-unique-address";
        EXPECT_STREQ("vendor-wide-unique-address", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:46925_I-5-32\\.1\\*5";
        EXPECT_STREQ("I-5-32", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:46925_ABCabc-123";
        EXPECT_STREQ("ABCabc-123", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:46925_0123456789";
        EXPECT_STREQ("0123456789", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }

    {
        std::string devicePart = "d:-5-32\\.1\\*5"; // invalid string (missing vendor specific extension)
        EXPECT_STREQ("", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i_-5-32\\.1\\*5"; // invalid string (missing vendor specific extension)
        EXPECT_STREQ("", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }

    {
        std::string devicePart = "d:_i:_-5-32\\.1\\*5"; // invalid string (missing vendor specific extension)
        EXPECT_STREQ("", keo_util::KEDeviceAddress::getUniqueAddress(devicePart).c_str());
    }
}
