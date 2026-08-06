/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2012
*****************************************************************************/

#include <gtest/gtest.h>

// system includes
#include "stdint.h"
#include <string>

// project includes
#include <keo_datagram/core/KeoByteArray.h>

using namespace keo_datagram;

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, Constructor_std_string)
{
    std::string s("test");
    KeoByteArray ba(s);

    EXPECT_EQ(ba.length(), s.length());
    EXPECT_EQ(ba.toHex(), "74657374");
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, Constructor_char_ptr)
{
    char s[] = "test";
    KeoByteArray ba(s);

    EXPECT_EQ(ba.length(), strlen(s));
    EXPECT_EQ(ba.toHex(), "74657374");
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, Constructor_char_ptr_size)
{
    char s[] = "test";
    KeoByteArray ba(s, sizeof(s));

    EXPECT_EQ(ba.length(), sizeof(s));
    EXPECT_EQ(ba.toHex(), "7465737400");
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, Constructor_vector_char)
{
    char s[] = "test";
    std::vector<char> v(s, s + sizeof(s));

    KeoByteArray ba(v);

    EXPECT_EQ(ba.length(), sizeof(s));
    EXPECT_EQ(ba.toHex(), "7465737400");
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, Constructor_vector_uchar)
{
    char s[] = "test";
    std::vector<unsigned char> v(s, s + sizeof(s));

    KeoByteArray ba(v);

    EXPECT_EQ(ba.length(), sizeof(s));
    EXPECT_EQ(ba.toHex(), "7465737400");
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, Constructor_fill_char)
{
    char s[] = "test";
    std::vector<unsigned char> v(s, s + sizeof(s));

    KeoByteArray ba(10, 't');

    EXPECT_EQ(ba.length(), 10U);
    EXPECT_EQ(ba.toHex(), "74747474747474747474");
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, to_from_hex)
{
    char s[] = "7400650073007400";
    KeoByteArray ba = KeoByteArray::fromHex(s);

    EXPECT_EQ(ba.length(), sizeof(s) / 2);
    EXPECT_EQ(ba.toHex(), "7400650073007400");
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, to_string)
{
    char s[] = "Das ist ein test";
    KeoByteArray ba(s);

    EXPECT_EQ(ba.length(), strlen(s));
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, set_content)
{
    char s[] = "Das ist ein test";
    KeoByteArray ba;
    ba.setContent(s, strlen(s));

    EXPECT_EQ(ba.length(), strlen(s));
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, set)
{
    char s[] = "Das ist ein test";
    KeoByteArray ba;
    ba.setContent(s, strlen(s));
    ba.set(3, '-');
    s[3] = '-';

    EXPECT_EQ(ba.length(), strlen(s));
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, fill)
{
    char s[] = "11111";
    KeoByteArray ba;
    ba.fill(5, '1');

    EXPECT_EQ(ba.length(), strlen(s));
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, test)
{
    char s1[] = "1234567890";
    KeoByteArray ba1(s1);

    char s2[] = "abcdefgh";
    KeoByteArray ba2(s2);

    char s3[] = "1234567890";
    KeoByteArray ba3(s3);

    EXPECT_TRUE(ba1.equals(ba3));
    EXPECT_FALSE(ba1.equals(ba2));
    EXPECT_TRUE(ba1 == ba3);
    EXPECT_FALSE(ba1 == ba2);
    EXPECT_TRUE(ba1 != ba2);
    EXPECT_FALSE(ba1 != ba3);
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, assignment)
{
    char s1[] = "1234567890";
    KeoByteArray ba1(s1);
    KeoByteArray ba2 = ba1;

    EXPECT_TRUE(ba1.equals(ba2));
}

/**
 * Tests the KeoByteArray
 */
TEST(KeoByteArray, const_data)
{
    char s1[] = "1234567890";
    KeoByteArray ba1(s1);
    EXPECT_TRUE(strncmp(s1, ba1.constData(), ba1.length()) == 0);
}
