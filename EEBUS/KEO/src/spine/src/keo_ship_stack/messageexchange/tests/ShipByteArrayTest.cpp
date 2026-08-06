/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2012
*****************************************************************************/


#include <gtest/gtest.h>

// system includes
#include "stdint.h"
#include <string>

// project includes
#include "ShipByteArray.h"

using namespace keo_ship;

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, Constructor_std_string)
{
    std::string s("test");
    ShipByteArray ba(s);

    EXPECT_EQ(ba.length(), s.length());
    EXPECT_EQ(ba.toHex(), "74657374");
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, Constructor_char_ptr)
{
    char s[] = "test";
    ShipByteArray ba(s);

    EXPECT_EQ(ba.length(), strlen(s));
    EXPECT_EQ(ba.toHex(), "74657374");
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, Constructor_char_ptr_size)
{
    char s[] = "test";
    ShipByteArray ba(s, sizeof(s));

    EXPECT_EQ(ba.length(), sizeof(s));
    EXPECT_EQ(ba.toHex(), "7465737400");
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, Constructor_vector_char)
{
    char s[] = "test";
    std::vector<char> v(s, s + sizeof(s));

    ShipByteArray ba(v);

    EXPECT_EQ(ba.length(), sizeof(s));
    EXPECT_EQ(ba.toHex(), "7465737400");
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, Constructor_vector_uchar)
{
    char s[] = "test";
    std::vector<unsigned char> v(s, s + sizeof(s));

    ShipByteArray ba(v);

    EXPECT_EQ(ba.length(), sizeof(s));
    EXPECT_EQ(ba.toHex(), "7465737400");
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, Constructor_fill_char)
{
    char s[] = "test";
    std::vector<unsigned char> v(s, s + sizeof(s));

    ShipByteArray ba(10, 't');

    EXPECT_EQ(ba.length(), 10U);
    EXPECT_EQ(ba.toHex(), "74747474747474747474");
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, to_from_hex)
{
    char s[] = "7400650073007400";
    ShipByteArray ba = ShipByteArray::fromHex(s);

    EXPECT_EQ(ba.length(), sizeof(s) / 2);
    EXPECT_EQ(ba.toHex(), "7400650073007400");
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, to_string)
{
    char s[] = "Das ist ein test";
    ShipByteArray ba(s);

    EXPECT_EQ(ba.length(), strlen(s));
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, set_content)
{
    char s[] = "Das ist ein test";
    ShipByteArray ba;
    ba.setContent(s, strlen(s));

    EXPECT_EQ(ba.length(), strlen(s));
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, set)
{
    char s[] = "Das ist ein test";
    ShipByteArray ba;
    ba.setContent(s, strlen(s));
    ba.set(3, '-');
    s[3] = '-';

    EXPECT_EQ(ba.length(), strlen(s));
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, fill)
{
    char s[] = "11111";
    ShipByteArray ba;
    ba.fill(5, '1');

    EXPECT_EQ(ba.length(), strlen(s));
    EXPECT_EQ(ba.toString(), s);
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, test)
{
    char s1[] = "1234567890";
    ShipByteArray ba1(s1);

    char s2[] = "abcdefgh";
    ShipByteArray ba2(s2);

    char s3[] = "1234567890";
    ShipByteArray ba3(s3);

    EXPECT_TRUE(ba1.equals(ba3));
    EXPECT_FALSE(ba1.equals(ba2));
    EXPECT_TRUE(ba1 == ba3);
    EXPECT_FALSE(ba1 == ba2);
    EXPECT_TRUE(ba1 != ba2);
    EXPECT_FALSE(ba1 != ba3);
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, assignment)
{
    char s1[] = "1234567890";
    ShipByteArray ba1(s1);
    ShipByteArray ba2 = ba1;

    EXPECT_TRUE(ba1.equals(ba2));
}

/**
 * Tests the ShipByteArray
 */
TEST(ShipByteArray, const_data)
{
    char s1[] = "1234567890";
    ShipByteArray ba1(s1);
    EXPECT_TRUE(strncmp(s1, ba1.constData(), ba1.length()) == 0);
}

/**
 * Tests the byte array handling
 */
TEST(ShipByteArray, ByteArrayBasic)
{
    // default c'tor, empty
    ShipByteArray ba1;
    ASSERT_EQ((size_t)0, ba1.length());

    // c'tor with fill
    ShipByteArray ba2(10, 'a');
    ASSERT_EQ("aaaaaaaaaa", ba2.toString());
    ASSERT_EQ((size_t)10, ba2.length());

    // copy c'tor
    ShipByteArray ba3(ba2);
    ASSERT_EQ("aaaaaaaaaa", ba3.toString());
    ASSERT_TRUE(ba3 == ba2);
    ASSERT_TRUE(ba2 == ba3);

    ba3.set(1, 'x');
    ASSERT_EQ("axaaaaaaaa", ba3.toString());
    ASSERT_FALSE(ba3 == ba2);
    ASSERT_TRUE(ba2 != ba3);

    ShipByteArray ba4("Never wanted this");
    ASSERT_EQ("Never wanted this", ba4.toString());

    ba4.clear();
    ASSERT_EQ((size_t)0, ba1.length());

    char txt[] = { 'c', 'd', 'e', '\0', '\0', 'x', 'y', 'z', 'q' }; // not a valid c-style string!
    ba4.setContent((char*)txt, 9);
    ASSERT_EQ((size_t)9, ba4.length());
    std::string sContent = ba4.toString();
    ASSERT_EQ('c', sContent.at(0));
    ASSERT_EQ('q', sContent.at(8));
    ASSERT_EQ('\0', sContent.at(4));
}

/**
 * Tests the byte array / hex conversion
 */
TEST(ShipByteArray, ByteArrayHex)
{
    // TO Hex
    ShipByteArray ba1(3, 'A');
    ASSERT_EQ("AAA", ba1.toString());
    ASSERT_EQ("414141", ba1.toHex());

    ba1.set(2, 'Z');
    ASSERT_EQ("41415a", ba1.toHex());

    char txt[] = { 'A', 'B', '\0', 'Z' }; // not a valid c-style string!
    ShipByteArray ba2;
    ba2.setContent((char*)txt, 4);
    ASSERT_EQ("4142005a", ba2.toHex());

    // FROM Hex
    ShipByteArray ba3 = ShipByteArray::fromHex("415a5A");
    ASSERT_TRUE(ba3.length() == 3);
    std::string x = ba3.toString();
    ASSERT_EQ("AZZ", x);

    ba3.set(2, 'e');
    ASSERT_EQ("AZe", ba3.toString());

    // check both directions
    std::string sOrig = "rftz497ftrgb,jhefg&436534kjddgf98uzdb dsha928#+";
    ShipByteArray ba4(sOrig);
    ASSERT_GE(ba4.length(), (size_t)20);
    std::string sAsHexString = ba4.toHex();
    ASSERT_GE(sAsHexString.size(), (size_t)40);

    ShipByteArray ba5;
    ba5 = ShipByteArray::fromHex(sAsHexString);
    ASSERT_EQ(sOrig, ba5.toString());

    // from vector <char>
    std::vector<char> vc;
    vc.push_back(0x11);
    vc.push_back(0x12);
    vc.push_back(0x13);
    vc.push_back(0x14);

    EXPECT_EQ("11121314", ShipByteArray(vc).toHex());

    // from vector <unsigned char>
    std::vector<unsigned char> vuc;
    vuc.push_back(0xf1);
    vuc.push_back(0xf2);
    vuc.push_back(0xf3);
    vuc.push_back(0xf4);

    EXPECT_EQ("f1f2f3f4", ShipByteArray(vuc).toHex());
}

