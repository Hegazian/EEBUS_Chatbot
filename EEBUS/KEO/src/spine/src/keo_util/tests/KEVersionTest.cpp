/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2012
*****************************************************************************/

#define DBG_MODUL_NAME "KEToolsLib Test"
#include <gtest/gtest.h>

// system includes
#include "stdint.h"
#include <regex.h>
#include <string>

// project includes
#include <keo_util/KEVersion.h>

using namespace keo_util;

/**
 * Tests the KEVersion
 */
TEST(KEVersion, constructor_with_init)
{
    keo_util::KEVersion versionInfo("#module\n");
    std::string s1(versionInfo.getVersionInfo());

    ASSERT_TRUE(s1.find("spine") != std::string::npos);
}

/**
 * Tests the KEVersion
 */
TEST(KEVersion, module_version)
{

    keo_util::KEVersion versionInfo("Test-#module\n");
    std::string s1(versionInfo.getModuleVersionInfo("spine"));
    std::string s2("Test-spine\n");
    ASSERT_EQ(s1, s2);
}

TEST(KEVersion, version_string)
{
    char const* pattern = "^spine-[0-9]+\\.[0-9]+\\.[0-9]+-[0-9]*-.*-[a-zA-Z0-9-]+";
    keo_util::KEVersion versionInfo("#module-#version-#build-#tag-#hash");
    std::string s1(versionInfo.getModuleVersionInfo("spine"));

    regex_t regex;
    int errorCode = regcomp(&regex, pattern, REG_ICASE | REG_EXTENDED);
    ASSERT_EQ(errorCode, 0);
    errorCode = regexec(&regex, s1.c_str(), 0, NULL, 0);
    ASSERT_EQ(errorCode, 0);
    regfree(&regex);
}
