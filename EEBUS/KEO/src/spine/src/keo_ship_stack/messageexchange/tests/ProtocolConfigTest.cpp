/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2014
*****************************************************************************/

#define DBG_MODUL_NAME "ProtocolConfig Test"
#include <gtest/gtest.h>
// ASSERT_TRUE
// ASSERT_EQ

#include <keo_ship/ShipStack.h>

using namespace keo_ship;

TEST(ProtocolConfigTest, tooEarlyVersionIsInvalid)
{
    // anything lower than 1.0 should be invalid
    ASSERT_FALSE(ProtocolConfig::isVersionValid(0, 9));
    ASSERT_FALSE(ProtocolConfig::isVersionValid(0, 1));
}

TEST(ProtocolConfigTest, futureVersionIsInvalid)
{
    // anything above 1.0 should be invalid
    ASSERT_FALSE(ProtocolConfig::isVersionValid(1, 1));
    ASSERT_FALSE(ProtocolConfig::isVersionValid(4, 2));
}

TEST(ProtocolConfigTest, currentVersionIsValid)
{
    // 1.0 is fine
    ASSERT_TRUE(ProtocolConfig::isVersionValid(1, 0));
}
