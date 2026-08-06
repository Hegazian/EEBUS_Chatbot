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
 *     @brief      Unit-Test for class ScaledNumberType
 *
 *     @par        Unit-Test for class ScaledNumberType
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include "gtest/gtest.h"
#include <climits>
#include <math.h>
#include <string>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_datagram/core/KeoScaledNumber.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */
using namespace keo_datagram;

/**
 * Simple tests concerning comparison of two ScaledNumberType objects
 */
TEST(KeoScaledNumberTest, scaledNumberTest_comparison)
{
    {
        KeoScaledNumber snt1(3, 0);
        KeoScaledNumber snt2(3, 0);
        EXPECT_EQ(snt1, snt2);
        EXPECT_FALSE(snt1 < snt2);
        EXPECT_FALSE(snt1 > snt2);
        EXPECT_TRUE(snt1 <= snt2);
        EXPECT_TRUE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(-3, 0);
        KeoScaledNumber snt2(-3, 0);
        EXPECT_EQ(snt1, snt2);
        EXPECT_FALSE(snt1 < snt2);
        EXPECT_FALSE(snt1 > snt2);
        EXPECT_TRUE(snt1 <= snt2);
        EXPECT_TRUE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(-3, 0);
        KeoScaledNumber snt2(3, 0);
        EXPECT_NE(snt1, snt2);
        EXPECT_TRUE(snt1 < snt2);
        EXPECT_FALSE(snt1 > snt2);
        EXPECT_TRUE(snt1 <= snt2);
        EXPECT_FALSE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(3, 0);
        KeoScaledNumber snt2(-3, 0);
        EXPECT_NE(snt1, snt2);
        EXPECT_FALSE(snt1 < snt2);
        EXPECT_TRUE(snt1 > snt2);
        EXPECT_FALSE(snt1 <= snt2);
        EXPECT_TRUE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(3000, 0);
        KeoScaledNumber snt2(30, 2);
        EXPECT_EQ(snt1, snt2);
        EXPECT_FALSE(snt1 < snt2);
        EXPECT_FALSE(snt1 > snt2);
        EXPECT_TRUE(snt1 <= snt2);
        EXPECT_TRUE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(3000, -5); // = 0.03
        KeoScaledNumber snt2(30, -3); // = 0.03
        EXPECT_EQ(snt1, snt2);
        EXPECT_FALSE(snt1 < snt2);
        EXPECT_FALSE(snt1 > snt2);
        EXPECT_TRUE(snt1 <= snt2);
        EXPECT_TRUE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(-3000, -5); // = -0.03
        KeoScaledNumber snt2(-30, -3); // = -0.03
        EXPECT_EQ(snt1, snt2);
        EXPECT_FALSE(snt1 < snt2);
        EXPECT_FALSE(snt1 > snt2);
        EXPECT_TRUE(snt1 <= snt2);
        EXPECT_TRUE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(3000, 5); // = 300000000
        KeoScaledNumber snt2(-30, -3); // = -0.03
        EXPECT_NE(snt1, snt2);
        EXPECT_FALSE(snt1 < snt2);
        EXPECT_TRUE(snt1 > snt2);
        EXPECT_FALSE(snt1 <= snt2);
        EXPECT_TRUE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(3000, 5); // = 300000000
        KeoScaledNumber snt2(-3000, 5); // = -300000000
        EXPECT_NE(snt1, snt2);
        EXPECT_FALSE(snt1 < snt2);
        EXPECT_TRUE(snt1 > snt2);
        EXPECT_FALSE(snt1 <= snt2);
        EXPECT_TRUE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(-3000, 5); // = -300000000
        KeoScaledNumber snt2(3000, 5); // = 300000000
        EXPECT_NE(snt1, snt2);
        EXPECT_TRUE(snt1 < snt2);
        EXPECT_FALSE(snt1 > snt2);
        EXPECT_TRUE(snt1 <= snt2);
        EXPECT_FALSE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(42, 0); // = 42
        KeoScaledNumber snt2(43500, -3); // = 43.5
        EXPECT_NE(snt1, snt2);
        EXPECT_TRUE(snt1 < snt2);
        EXPECT_FALSE(snt1 > snt2);
        EXPECT_TRUE(snt1 <= snt2);
        EXPECT_FALSE(snt1 >= snt2);
    }

    {
        KeoScaledNumber snt1(42, 0); // = 42
        KeoScaledNumber snt2(420000001, -7); // = 42.000000000001
        EXPECT_NE(snt1, snt2);
        EXPECT_TRUE(snt1 < snt2);
        EXPECT_FALSE(snt1 > snt2);
        EXPECT_TRUE(snt1 <= snt2);
        EXPECT_FALSE(snt1 >= snt2);
    }
}

/**
 * Tests concerning conversion from double to ScaledDataType
 */
TEST(KeoScaledNumberTest, scaledNumberTest_representation)
{
#define CHECK_EQUAL                                                                                                    \
    EXPECT_EQ(snt1, snt2);                                                                                             \
    EXPECT_FALSE(snt1 < snt2);                                                                                         \
    EXPECT_FALSE(snt1 > snt2);                                                                                         \
    EXPECT_TRUE(snt1 <= snt2);                                                                                         \
    EXPECT_TRUE(snt1 >= snt2);

    KeoScaledNumber snt1;
    KeoScaledNumber snt2;

    CHECK_EQUAL;

    snt1 = KeoScaledNumber(LONG_MAX, 0);
    snt2 = KeoScaledNumber(LONG_MAX, 0);
    CHECK_EQUAL;

    snt1 = KeoScaledNumber(LONG_MIN, 0);
    snt2 = KeoScaledNumber(LONG_MIN, 0);

    snt1 = KeoScaledNumber(1, -15);
    KeoScaledNumber::NumberTypeType numberType = snt1.getNumberType();
    KeoScaledNumber::ScaleTypeType scaleType = snt1.getScaleType();

    while (static_cast<unsigned long>(numberType) < static_cast<unsigned long>(LONG_MAX / 10))
    {
        numberType *= 10;
        scaleType--;
        snt2 = KeoScaledNumber(numberType, scaleType);
        CHECK_EQUAL;
    }

    snt1 = KeoScaledNumber(1, 0);
    numberType = snt1.getNumberType();
    scaleType = snt1.getScaleType();
    while (static_cast<unsigned long>(numberType) < static_cast<unsigned long>(LONG_MAX / 10))
    {
        numberType *= 10;
        scaleType--;
        snt2 = KeoScaledNumber(numberType, scaleType);
        CHECK_EQUAL;
    }
}

/**
 * Tests concerning conversion from double to ScaledDataType
 */
TEST(KeoScaledNumberTest, scaledNumberTest_fromDouble)
{
    double origin = 3.14159265359;

    KeoScaledNumber snt;
    snt = KeoScaledNumber::fromDouble(origin, 2);
    EXPECT_EQ(KeoScaledNumber(314, -2), snt);

    snt = KeoScaledNumber::fromDouble(origin, 5);
    EXPECT_EQ(KeoScaledNumber(314159, -5), snt);

#if defined(__LP64__)
    snt = KeoScaledNumber::fromDouble(origin, 11);
    EXPECT_EQ(KeoScaledNumber(314159265359, -11), snt);

    snt = KeoScaledNumber::fromDouble(origin, 0);
    EXPECT_EQ(KeoScaledNumber(3, 0), snt);

    snt = KeoScaledNumber::fromDouble(origin / 10, 12);
    EXPECT_EQ(KeoScaledNumber(314159265359, -12), snt);
#endif
    snt = KeoScaledNumber::fromDouble(0.0314, 2);
    EXPECT_EQ(KeoScaledNumber(3, -2), snt);

    // on a 64-bit ubuntu machine the following fails, as the origin value is internall rounded
    //    origin = 0.0000000000000001;
    //    snt.fromDouble(origin, 20);
    //    EXPECT_TRUE(ScaledNumberType(1, 16) == snt);
}

/**
 * Tests concerning conversion from ScaledDataType to string
 */
TEST(KeoScaledNumberTest, scaledNumberTest_toString)
{
    {
        KeoScaledNumber snt(1234, -6);
        std::string str = snt.toString();

        EXPECT_EQ(str, "0.001234");
    }
    {
        KeoScaledNumber snt(123456789, -6);
        std::string str = snt.toString();

        EXPECT_EQ(str, "123.456789");
    }
    {
        KeoScaledNumber snt(123456789, 0);
        std::string str = snt.toString();

        EXPECT_EQ(str, "123456789");
    }
    {
        KeoScaledNumber snt(123456789, -10);
        std::string str = snt.toString();

        EXPECT_EQ(str, "0.0123456789");
    }
    {
        KeoScaledNumber snt(123456789, 10);
        std::string str = snt.toString();

        EXPECT_EQ(str, "1234567890000000000");
    }
    {
        KeoScaledNumber snt(1, -15);
        std::string str = snt.toString();

        EXPECT_EQ(str, "0.000000000000001");
    }
    {
        KeoScaledNumber snt(-123, -3);
        std::string str = snt.toString();

        EXPECT_EQ(str, "-0.123");
    }
}

/**
 * Tests concerning conversion from string to ScaledDataType
 */
TEST(KeoScaledNumberTest, scaledNumberTest_fromString)
{
    {
        std::string origin = "0.000000000001";
        KeoScaledNumber snt = KeoScaledNumber::fromString(origin, 12);
        EXPECT_EQ(snt, KeoScaledNumber(1, -12));
    }

#if defined(__LP64__)
    {
        std::string origin = "1.000000000001";
        KeoScaledNumber snt = KeoScaledNumber::fromString(origin, 12);
        EXPECT_EQ(snt, KeoScaledNumber(1000000000001, -12));
    }
#endif

    {
        std::string origin = "2147483647"; // long max
        KeoScaledNumber snt = KeoScaledNumber::fromString(origin, 12);
        EXPECT_EQ(snt, KeoScaledNumber(2147483647, 0));
    }
}

/**
 * Tests concerning conversion operator
 */
TEST(KeoScaledNumberTest, scaledNumberTest_conversionOperator)
{
    {
        KeoScaledNumber snt(31416, -2);
        double value = static_cast<double>(snt);
        EXPECT_FLOAT_EQ(value, 314.16);
    }
}

/**
 * Tests concerning assignment operator
 */
TEST(KeoScaledNumberTest, scaledNumberTest_assignementOperator)
{
    {
        KeoScaledNumber snt;
        double value1, value2;
        value1 = 314.16; // is now 64BIT Machine: 314,16000000000003
        //        32BIT Machine: 314,16000366210938

        snt = static_cast<double>(value1);
        value1 = static_cast<double>(KeoScaledNumber(31416, -2));
        value2 = static_cast<double>(snt);

        // if we directly check the equality of both values than it will fit on 64 Bit machine but not on 32 bit.
        EXPECT_FLOAT_EQ(floor(value1 * 100), floor(value2 * 100));
    }
}

/**
 * Tests concerning assignment operator
 */
TEST(KeoScaledNumberTest, scaledNumberTest_special_case_26000000000000_minus12)
{
    {
        KeoScaledNumber snt(26000000000000, -12);
        // if we directly check the equality of both values than it will fit on 64 Bit machine but not on 32 bit.
        EXPECT_FLOAT_EQ(snt.toDouble(), 26.0);
    }
}

TEST(KeoScaledNumberTest, scaledNumberTest_normalize)
{
    // 4711 (4711, 0)
    {
        KeoScaledNumber sntNormalized = KeoScaledNumber::normalize(KeoScaledNumber(4711, 0));
        EXPECT_TRUE(sntNormalized.getNumberType() == 4711 && sntNormalized.getScaleType() == 0);
    }
    {
        KeoScaledNumber sntNormalized = KeoScaledNumber::normalize(KeoScaledNumber(4711000, -3));
        EXPECT_TRUE(sntNormalized.getNumberType() == 4711 && sntNormalized.getScaleType() == 0);
    }

    // 471,1 (4711, -1)
    {
        KeoScaledNumber sntNormalized = KeoScaledNumber::normalize(KeoScaledNumber(4711, -1));
        EXPECT_TRUE(sntNormalized.getNumberType() == 4711 && sntNormalized.getScaleType() == -1);
    }
    {
        KeoScaledNumber sntNormalized = KeoScaledNumber::normalize(KeoScaledNumber(471100000, -6));
        EXPECT_TRUE(sntNormalized.getNumberType() == 4711 && sntNormalized.getScaleType() == -1);
    }

    // -47,11 (4711, -2)
    {
        KeoScaledNumber sntNormalized = KeoScaledNumber::normalize(KeoScaledNumber(-4711, -2));
        EXPECT_TRUE(sntNormalized.getNumberType() == -4711 && sntNormalized.getScaleType() == -2);
    }
    {
        KeoScaledNumber sntNormalized = KeoScaledNumber::normalize(KeoScaledNumber(-47110000000, -9));
        EXPECT_TRUE(sntNormalized.getNumberType() == -4711 && sntNormalized.getScaleType() == -2);
    }
}

TEST(KeoScaledNumberTest, scaledNumberTest_equalizeScale)
{
    {
        KeoScaledNumber snt1(55, -1);
        KeoScaledNumber snt2(2, 1);
        KeoScaledNumber equal1;
        KeoScaledNumber equal2;

        KeoScaledNumber::equalizeScale(snt1, snt2, equal1, equal2);
        EXPECT_TRUE(equal1.getNumberType() == 55 && equal1.getScaleType() == -1);
        EXPECT_TRUE(equal2.getNumberType() == 200 && equal1.getScaleType() == -1);
    }
    {
        KeoScaledNumber snt1(20, 0);
        KeoScaledNumber snt2(55, -1);

        KeoScaledNumber equal1;
        KeoScaledNumber equal2;

        KeoScaledNumber::equalizeScale(snt1, snt2, equal1, equal2);
        EXPECT_TRUE(equal1.getNumberType() == 200 && equal1.getScaleType() == -1);
        EXPECT_TRUE(equal2.getNumberType() == 55 && equal2.getScaleType() == -1);
    }
    {
        KeoScaledNumber snt1(55, -1);
        KeoScaledNumber snt2(2000, -2);
        KeoScaledNumber equal1;
        KeoScaledNumber equal2;

        KeoScaledNumber::equalizeScale(snt1, snt2, equal1, equal2);
        EXPECT_TRUE(equal1.getNumberType() == 550 && equal1.getScaleType() == -2);
        EXPECT_TRUE(equal2.getNumberType() == 2000 && equal1.getScaleType() == -2);
    }
    {
        KeoScaledNumber snt1(2000, -2);
        KeoScaledNumber snt2(55, -1);
        KeoScaledNumber equal1;
        KeoScaledNumber equal2;

        KeoScaledNumber::equalizeScale(snt1, snt2, equal1, equal2);
        EXPECT_TRUE(equal1.getNumberType() == 2000 && equal1.getScaleType() == -2);
        EXPECT_TRUE(equal2.getNumberType() == 550 && equal2.getScaleType() == -2);
    }
    {
        KeoScaledNumber snt1(200, -1);
        KeoScaledNumber snt2(55, -1);
        KeoScaledNumber equal1;
        KeoScaledNumber equal2;

        KeoScaledNumber::equalizeScale(snt1, snt2, equal1, equal2);
        EXPECT_TRUE(equal1.getNumberType() == 200 && equal1.getScaleType() == -1);
        EXPECT_TRUE(equal2.getNumberType() == 55 && equal2.getScaleType() == -1);
    }
}

TEST(KeoScaledNumberTest, scaledNumberTest_addition)
{
    // 5,5 + 20 => 25,5 (255, -1)
    {
        KeoScaledNumber snt1(55, -1);
        KeoScaledNumber snt2(2, 1);
        KeoScaledNumber sum(KeoScaledNumber::add(snt1, snt2));
        EXPECT_TRUE(sum.getNumberType() == 255 && sum.getScaleType() == -1);
    }

    // 55 + 2 = 57 => (57, 0)
    {
        KeoScaledNumber snt1(55, 0);
        KeoScaledNumber snt2(2, 0);
        KeoScaledNumber sum(KeoScaledNumber::add(snt1, snt2));
        EXPECT_TRUE(sum.getNumberType() == 57 && sum.getScaleType() == -0);
    }

    // 550 + 0,1 = 550,1 => (5502, -1)
    {
        KeoScaledNumber snt1(55, 1);
        KeoScaledNumber snt2(2, -1);
        KeoScaledNumber sum(KeoScaledNumber::add(snt1, snt2));
        EXPECT_TRUE(sum.getNumberType() == 5502 && sum.getScaleType() == -1);
    }

    // 4711 + 0,815 = 4711,815 => (4711815, -3)
    {
        KeoScaledNumber snt1(4711, 0);
        KeoScaledNumber snt2(815, -3);
        KeoScaledNumber sum(KeoScaledNumber::add(snt1, snt2));
        EXPECT_TRUE(sum.getNumberType() == 4711815 && sum.getScaleType() == -3);
    }

    // 4711 + (-0,815) = 4710,185
    {
        KeoScaledNumber snt1(4711, 0);
        KeoScaledNumber snt2(-815, -3);
        KeoScaledNumber sum(KeoScaledNumber::add(snt1, snt2));
        EXPECT_TRUE(sum.getNumberType() == 4710185 && sum.getScaleType() == -3);
    }

    // -4711 + (-0,815) = -4711,815
    {
        KeoScaledNumber snt1(-4711, 0);
        KeoScaledNumber snt2(-815, -3);
        KeoScaledNumber sum(KeoScaledNumber::add(snt1, snt2));
        EXPECT_TRUE(sum.getNumberType() == -4711815 && sum.getScaleType() == -3);
    }
}

TEST(KeoScaledNumberTest, scaledNumberTest_subtraction)
{
    // 25,5 - 20 = 5,5
    {
        KeoScaledNumber snt1(255, -1);
        KeoScaledNumber snt2(2, 1);
        KeoScaledNumber difference(KeoScaledNumber::subtract(snt1, snt2));
        EXPECT_TRUE(difference.getNumberType() == 55 && difference.getScaleType() == -1);
    }

    // 25,5 - 5,5 = 20
    {
        KeoScaledNumber snt1(255, -1);
        KeoScaledNumber snt2(55, -1);
        KeoScaledNumber difference(KeoScaledNumber::subtract(snt1, snt2));
        EXPECT_TRUE(difference.getNumberType() == 2 && difference.getScaleType() == 1);
    }

    // 57 - 2 = 55
    {
        KeoScaledNumber snt1(57, 0);
        KeoScaledNumber snt2(2, 0);
        KeoScaledNumber difference(KeoScaledNumber::subtract(snt1, snt2));
        EXPECT_TRUE(difference.getNumberType() == 55 && difference.getScaleType() == 0);
    }

    // 572,01 - 0,374 = 571,636
    {
        KeoScaledNumber snt1(57201, -2);
        KeoScaledNumber snt2(374, -3);
        KeoScaledNumber difference(KeoScaledNumber::subtract(snt1, snt2));
        EXPECT_TRUE(difference.getNumberType() == 571636 && difference.getScaleType() == -3);
    }

    //-0,55 - 0,0125 = 0,5625
    {
        KeoScaledNumber snt1(-55, -2);
        KeoScaledNumber snt2(125, -4);
        KeoScaledNumber difference(KeoScaledNumber::subtract(snt1, snt2));
        EXPECT_TRUE(difference.getNumberType() == -5625 && difference.getScaleType() == -4);
    }

    //-0,55 - (- 0,25) = -0,3
    {
        KeoScaledNumber snt1(-55, -2);
        KeoScaledNumber snt2(-25, -2);
        KeoScaledNumber difference(KeoScaledNumber::subtract(snt1, snt2));
        EXPECT_TRUE(difference.getNumberType() == -3 && difference.getScaleType() == -1);
    }
}

TEST(KeoScaledNumberTest, scaledNumberTest_multiplication)
{
    // 4711 * 0,815 = 3839,465
    {
        KeoScaledNumber snt1(4711, 0);
        KeoScaledNumber snt2(815, -3);
        KeoScaledNumber product(KeoScaledNumber::multiply(snt1, snt2));
        EXPECT_TRUE(product.getNumberType() == 3839465 && product.getScaleType() == -3);
    }
    // -4711 * 0,815 = -3839,465
    {
        KeoScaledNumber snt1(-4711, 0);
        KeoScaledNumber snt2(815, -3);
        KeoScaledNumber product(KeoScaledNumber::multiply(snt1, snt2));
        EXPECT_TRUE(product.getNumberType() == -3839465 && product.getScaleType() == -3);
    }
    // -4711 * (-0,815) = 3839,465
    {
        KeoScaledNumber snt1(-4711, 0);
        KeoScaledNumber snt2(-815, -3);
        KeoScaledNumber product(KeoScaledNumber::multiply(snt1, snt2));
        EXPECT_TRUE(product.getNumberType() == 3839465 && product.getScaleType() == -3);
    }

    // -37275,39 * 102245 = 3811222250,55
    {
        KeoScaledNumber snt1(-3727539, -2);
        KeoScaledNumber snt2(102245, -0);
        KeoScaledNumber product(KeoScaledNumber::multiply(snt1, snt2));
        EXPECT_TRUE(product.getNumberType() == -381122225055 && product.getScaleType() == -2);
    }

    // 12345 * 0 = 0
    {
        KeoScaledNumber snt1(12345, 0);
        KeoScaledNumber snt2(0, 1);
        KeoScaledNumber product(KeoScaledNumber::multiply(snt1, snt2));
        EXPECT_TRUE(product.getNumberType() == 0 && product.getScaleType() == 0);
    }
}
