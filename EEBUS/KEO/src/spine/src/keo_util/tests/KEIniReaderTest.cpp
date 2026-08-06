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
 *     @brief      Unit Tests for class KEUri
 *
 *     @par        Module description
 *                 Unit Tests for class KEUri
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include "gtest/gtest.h"

// basic file operations
#include <fstream>
#include <iostream>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_util/KEIniReader.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */
using namespace std;

using namespace keo_util;

const char* ini_content = "dVal = 212122\n"
                          "dTrue = true\n"
                          "dFalse = false\n"
                          "dString = Hallo Welt\n"
                          "[section1]\n"
                          "s1_Val = 212122\n"
                          "s1_True = true\n"
                          "s1_False = false\n"
                          "s1_String = Hallo Welt\n"
                          "# comment"
                          "[section2]\n"
                          "s2_Val = 212122\n"
                          "s2_True = true\n"
                          "s2_False = false\n"
                          "s2_String = Hallo Welt\n";

void writeContentToFile(const char* name)
{
    ofstream file;
    file.open(name);
    file << ini_content;
    file.close();
}

/**
 * Test for valid URI's
 */
TEST(KEIniReader, uriValidTest)
{
    writeContentToFile("./__test.ini");

    KEIniReader ini;
    EXPECT_TRUE(ini.parse("./__test.ini"));
    EXPECT_FALSE(ini.hasSection("notavailablesection"));
    EXPECT_TRUE(ini.hasSection(""));
    EXPECT_TRUE(ini.hasSection("section1"));
    EXPECT_TRUE(ini.hasSection("section2"));
    EXPECT_TRUE(ini.has("", "dVal"));
    EXPECT_TRUE(ini.has("", "dTrue"));
    EXPECT_TRUE(ini.has("", "dFalse"));
    EXPECT_TRUE(ini.has("", "dString"));
    EXPECT_TRUE(ini.has("section1", "s1_Val"));
    EXPECT_TRUE(ini.has("section1", "s1_True"));
    EXPECT_TRUE(ini.has("section1", "s1_False"));
    EXPECT_TRUE(ini.has("section1", "s1_String"));
    EXPECT_TRUE(ini.has("section2", "s2_Val"));
    EXPECT_TRUE(ini.has("section2", "s2_True"));
    EXPECT_TRUE(ini.has("section2", "s2_False"));
    EXPECT_TRUE(ini.has("section2", "s2_String"));

    /* */
    EXPECT_TRUE(ini.getBool("", "dTrue", false));
    EXPECT_TRUE(ini.getBool("section1", "s1_True", false));
    EXPECT_TRUE(ini.getBool("section2", "s2_True", false));

    EXPECT_FALSE(ini.getBool("", "dFalse", true));
    EXPECT_FALSE(ini.getBool("section1", "s1_False", true));
    EXPECT_FALSE(ini.getBool("section2", "s2_False", true));

    /* default value */
    EXPECT_TRUE(ini.getBool("not_available", "not_available", true));
    EXPECT_FALSE(ini.getBool("not_available", "not_available", false));

    EXPECT_EQ(ini.get("dVal", 0), 212122);
    EXPECT_EQ(ini.get("", "dVal", 0), 212122);

    EXPECT_EQ(ini.get("s1_Val", 123), 123);
    EXPECT_EQ(ini.get("section1", "s1_Val", 0), 212122);

    EXPECT_EQ(ini.get("s2_Val", 123), 123);
    EXPECT_EQ(ini.get("section2", "s2_Val", 0), 212122);

    EXPECT_EQ(ini.get("s1_String", "123"), "123");
    EXPECT_EQ(ini.get("section1", "s1_String", ""), "Hallo Welt");

    EXPECT_EQ(ini.get("s2_String", "123"), "123");
    EXPECT_EQ(ini.get("section2", "s2_String", ""), "Hallo Welt");

    EXPECT_EQ(ini.get("dString"), "Hallo Welt");
    EXPECT_EQ(ini.get("", "dString", ""), "Hallo Welt");
}
