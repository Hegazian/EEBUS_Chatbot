/*
 *     Copyright KEO GmbH 2018 - All rights reserved!
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
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <gtest/gtest.h>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "ShipStringUtil.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */


/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */


/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

using std::string;
using namespace keo_ship;




/**
 * Tests the string to number conversion functions (integers)
 */
TEST(ShipStringUtil, toNumber)
{
    ASSERT_TRUE(ShipStringUtil::toUint16(NULL) == 0);
    ASSERT_TRUE(ShipStringUtil::toUint16("65530") == 65530);
    ASSERT_TRUE(ShipStringUtil::toUint16("-1") == 65535);

    ASSERT_TRUE(ShipStringUtil::toUint32(NULL) == 0);
    ASSERT_TRUE(ShipStringUtil::toUint32("66000") == 66000);
    ASSERT_TRUE(ShipStringUtil::toUint32("+0") == 0);

    ASSERT_TRUE(ShipStringUtil::toInt32(NULL) == 0);
    ASSERT_TRUE(ShipStringUtil::toInt32("66100") == 66100);
    ASSERT_TRUE(ShipStringUtil::toInt32("-66000") == -66000);
    ASSERT_TRUE(ShipStringUtil::toInt32("-0") == 0);
    ASSERT_TRUE(ShipStringUtil::toInt32("+0") == 0);
    ASSERT_TRUE(ShipStringUtil::toInt32("+1") == 1);

    EXPECT_EQ(ShipStringUtil::toInt64(NULL), 0);
    EXPECT_EQ(ShipStringUtil::toInt64("2147483647"), 0x7FFFFFFFL);
    EXPECT_EQ(ShipStringUtil::toInt64("-2147483648"), -2147483648LL);
    EXPECT_EQ(ShipStringUtil::toInt64("-66000"), -66000);
    EXPECT_EQ(ShipStringUtil::toInt64("-0"), 0);
    EXPECT_EQ(ShipStringUtil::toInt64("+0"), 0);
    EXPECT_EQ(ShipStringUtil::toInt64("+1"), 1);
}


/**
 * Tests the integer to string conversion functions
 */
TEST(ShipStringUtil, integersToString)
{
    // fits in 16 bits (unumber and number get 32 bit as argument!)
    string s1 = ShipStringUtil::unumber(65530); // base 10
    string s2 = ShipStringUtil::unumber(65000, 16); // base 16
    string s3 = ShipStringUtil::number(65000); // signed long
    string s4 = ShipStringUtil::number(-32000); // signed long

    ASSERT_EQ(s1, "65530");
    ASSERT_EQ(s2, "fde8");

    ASSERT_EQ(s3, "65000");
    ASSERT_EQ(s4, "-32000");

    // fits in 32 bits

    string sb1 = ShipStringUtil::unumber(9965530); // base 10
    string sb2 = ShipStringUtil::unumber(65537, 16); // base 16
    string sb3 = ShipStringUtil::number(9965000); // signed long
    string sb4 = ShipStringUtil::number(-9932000); // signed long

    ASSERT_EQ(sb1, "9965530");
    ASSERT_EQ(sb2, "10001"); // hex

    ASSERT_EQ(sb3, "9965000");
    ASSERT_EQ(sb4, "-9932000");

    {
        // fits in 64 bits
        string s1 = ShipStringUtil::lnumber(2147483647); // signed long
        string s2 = ShipStringUtil::lnumber(-2147483648LL); // signed long long
        string s3 = ShipStringUtil::lnumber(256, 16); // signed long

        ASSERT_EQ(s1, "2147483647");
        ASSERT_EQ(s2, "-2147483648");

        ASSERT_EQ(s3, "100");
    }
}

/**
 * This test shows the general functioning of the sprintf-frontend.
 * There might be needed more test cases, but at the end only sprintf would be tested.
 *
 */
TEST(ShipStringUtil, doubleToString)
{
    // 'g' format (which is default)
    string s1 = ShipStringUtil::dnumber(123.456); // default is 'g' and precision of 6 (total digits!)
    ASSERT_EQ("123.456", s1);
    ASSERT_EQ("0", ShipStringUtil::dnumber(0));

    ASSERT_EQ("123.457", ShipStringUtil::dnumber(123.45678)); // default: 6 digits total
    ASSERT_EQ("1.45678", ShipStringUtil::dnumber(1.45678)); // default: 6 digits total
    ASSERT_EQ("12.12345678", ShipStringUtil::dnumber(12.12345678, 'g', 10)); // max. 10 digit total
    ASSERT_EQ("12.12345679", ShipStringUtil::dnumber(12.123456789, 'g', 10)); // max. 10 digit total

    ASSERT_EQ("12.1235", ShipStringUtil::dnumber(12.12345678));
    ASSERT_EQ("12.123456789", ShipStringUtil::dnumber(12.123456789, 'g', 14));

    // 'f' format
    ASSERT_EQ("-99.990000000000", ShipStringUtil::dnumber(-99.99, 'f', 12));
    ASSERT_EQ("1.00000", ShipStringUtil::dnumber(1, 'f', 5));

// 'e' format
#ifdef WIN32
    ASSERT_EQ("2.200000e+011", ShipStringUtil::dnumber(22e10, 'e', 6));
    ASSERT_EQ("-2.3000000E+011", ShipStringUtil::dnumber(-23e10, 'E', 7));
#else
    ASSERT_EQ("2.200000e+11", ShipStringUtil::dnumber(22e10, 'e', 6));
    ASSERT_EQ("-2.3000000E+11", ShipStringUtil::dnumber(-23e10, 'E', 7));
#endif
}



TEST(ShipStringUtil, stringToNumbers)
{
    double n1 = 1.5456;
    std::string s1 = "1.5456";
    unsigned int n2 = 3333333333u;
    std::string s2 = "3333333333";
    unsigned short n3 = 65535;
    std::string s3 = "65535";
    uint64_t n4 = 18446744073709551615ULL; // trailing ULL to eliminate compiler warning "integer constant is so large
                                           // that it is unsigned"
    std::string s4 = "18446744073709551615";
    int32_t n5 = -2147483647;
    std::string s5 = "-2147483647";
    int16_t n6 = -32767;
    std::string s6 = "-32767";

    double g1 = ShipStringUtil::toDouble(s1.c_str());
    unsigned int g2 = ShipStringUtil::toUint32(s2.c_str());
    unsigned short g3 = ShipStringUtil::toUint16(s3.c_str());
    uint64_t g4 = ShipStringUtil::toUint64(s4.c_str());
    int32_t g5 = ShipStringUtil::toInt32(s5.c_str());
    int16_t g6 = ShipStringUtil::toInt16(s6.c_str());

    ASSERT_DOUBLE_EQ(n1, g1);
    ASSERT_EQ(n2, g2);
    ASSERT_EQ(n3, g3);
    ASSERT_EQ(n4, g4);
    ASSERT_EQ(n5, g5);
    ASSERT_EQ(n6, g6);
}
