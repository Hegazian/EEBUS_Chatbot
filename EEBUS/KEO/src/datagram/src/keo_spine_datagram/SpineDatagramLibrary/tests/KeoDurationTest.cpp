/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2012
*****************************************************************************/

#include <gtest/gtest.h>

// system includes
#include "stdint.h"
#include <string>

// project includes
#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoDuration.h>

using namespace keo_datagram;

/**
 * Tests the KeoDuration
 */
TEST(KeoDuration, Constructor)
{
    KeoDuration durationEmpty;
    EXPECT_TRUE(durationEmpty.isZero());

    KeoDuration duration(13, 2, 3, 0, 0, 20, 10);
    EXPECT_FALSE(duration.isZero());

    EXPECT_EQ(duration.getYears(), 13U);
    EXPECT_EQ(duration.getMonths(), 2U);
    EXPECT_EQ(duration.getDays(), 3U);
    EXPECT_EQ(duration.getSeconds(), 20U);
    EXPECT_EQ(duration.getMilliSeconds(), 10U);

    KeoDuration duration2(13, 2, 3, 0, 0, 34550, 10);
    EXPECT_EQ(duration2.getYears(), 13U);
    EXPECT_EQ(duration2.getMonths(), 2U);
    EXPECT_EQ(duration2.getDays(), 3U);
    EXPECT_EQ(duration2.getSeconds(), 34550U);
    EXPECT_EQ(duration2.getMilliSeconds(), 10U);

    KeoDuration duration3(13, 2, 3, 0, 0, 164550, 10);
    EXPECT_EQ(duration3.getYears(), 13U);
    EXPECT_EQ(duration3.getMonths(), 2U);
    EXPECT_EQ(duration3.getDays(), 4U);
    EXPECT_EQ(duration3.getSeconds(), 78150U);
    EXPECT_EQ(duration3.getMilliSeconds(), 10U);

    KeoDuration duration4(0, 0, 1, 26, 70, 80, 10);
    EXPECT_EQ(duration4.getYears(), 0U);
    EXPECT_EQ(duration4.getMonths(), 0U);
    EXPECT_EQ(duration4.getDays(), 2U);
    EXPECT_EQ(duration4.getSeconds(), 11480U);
    EXPECT_EQ(duration4.getMilliSeconds(), 10U);
}
TEST(KeoDuration, Plus)
{
    KeoDuration duration(13, 2, 3, 0, 0, 20, 10);
    EXPECT_EQ(duration.getYears(), 13U);
    EXPECT_EQ(duration.getMonths(), 2U);
    EXPECT_EQ(duration.getDays(), 3U);
    EXPECT_EQ(duration.getSeconds(), 20U);
    EXPECT_EQ(duration.getMilliSeconds(), 10U);
    duration = duration.plusDays(13);
    EXPECT_EQ(duration.getYears(), 13U);
    EXPECT_EQ(duration.getMonths(), 2U);
    EXPECT_EQ(duration.getDays(), 16U);
    EXPECT_EQ(duration.getSeconds(), 20U);
    EXPECT_EQ(duration.getMilliSeconds(), 10U);
    duration = duration.plusHours(13);
    EXPECT_EQ(duration.getYears(), 13U);
    EXPECT_EQ(duration.getMonths(), 2U);
    EXPECT_EQ(duration.getDays(), 16U);
    EXPECT_EQ(duration.getSeconds(), 46820U);
    EXPECT_EQ(duration.getMilliSeconds(), 10U);
    duration = duration.plusMinutes(59);
    EXPECT_EQ(duration.getYears(), 13U);
    EXPECT_EQ(duration.getMonths(), 2U);
    EXPECT_EQ(duration.getDays(), 16U);
    EXPECT_EQ(duration.getSeconds(), 50360U);
    EXPECT_EQ(duration.getMilliSeconds(), 10U);
    duration = duration.plusSeconds(58);
    EXPECT_EQ(duration.getYears(), 13U);
    EXPECT_EQ(duration.getMonths(), 2U);
    EXPECT_EQ(duration.getDays(), 16U);
    EXPECT_EQ(duration.getSeconds(), 50418U);
    EXPECT_EQ(duration.getMilliSeconds(), 10U);
    duration = duration.plusMilliSeconds(58);
    EXPECT_EQ(duration.getYears(), 13U);
    EXPECT_EQ(duration.getMonths(), 2U);
    EXPECT_EQ(duration.getDays(), 16U);
    EXPECT_EQ(duration.getSeconds(), 50418U);
    EXPECT_EQ(duration.getMilliSeconds(), 68U);
}
TEST(KeoDuration, PlusExtra)
{
    {
        KeoDuration duration(13, 2, 3, 0, 0, 20, 10);
        duration = duration.plus(2, -100);
        std::string durationString = duration.toString();
        EXPECT_EQ(duration.toString(), "P13Y2M3DT21.91S");
    }
    {
        KeoDuration duration(13, 2, 3, 0, 0, 20, 10);
        duration = duration.plus(-32, 100);
        std::string durationString = duration.toString();
        EXPECT_EQ(duration.toString(), "P13Y2M2DT23H59M48.11S");
    }
    {
        KeoDuration duration(0, 0, 3, 0, 0, 20, 10);
        duration = duration.plus(-320000, -100);
        std::string durationString = duration.toString();
        EXPECT_EQ(duration.toString(), "-PT16H53M1.91S");
    }
}
TEST(KeoDuration, Parsing)
{
    KeoDuration duration(13, 2, 3, 0, 0, 34550, 10);
    std::string durationString = duration.toString();
    KeoDuration durationParsed = KeoDuration::parse(durationString);
    EXPECT_EQ(duration, durationParsed);
}
TEST(KeoDuration, seconds)
{
    long seconds = 2334550;
    KeoDuration durationSec = KeoDuration::ofSeconds(seconds);
    EXPECT_FALSE(durationSec.isZero());
}

TEST(KeoDuration, parse)
{
    KeoDuration d("P2Y8M15DT7H32M17S");
    EXPECT_TRUE(d.isValid());
    KeoDuration e = d.parse("2Y8M15DT7H32M17S");
    EXPECT_FALSE(e.isValid());
}

TEST(KeoDuration, toString)
{
    {
        KeoDuration d;
        EXPECT_FALSE(d.isValid());
        EXPECT_TRUE(d.isZero());
        EXPECT_EQ(d.toString(), "");
    }

    {
        KeoDuration d("PT0S");
        EXPECT_TRUE(d.isValid());
        EXPECT_TRUE(d.isZero());
        EXPECT_EQ(d.toString(), "PT0S");
    }

    {
        KeoDuration d("PT23H");
        EXPECT_TRUE(d.isValid());
        EXPECT_FALSE(d.isZero());
        EXPECT_EQ(d.toString(), "PT23H");
    }

    {
        KeoDuration d;
        KeoDuration d2 = d.plusSeconds(0);
        EXPECT_FALSE(d.isValid());
        EXPECT_FALSE(d2.isValid());
    }

    {
        KeoDuration d(0);
        KeoDuration d2 = d.plusHours(24);
        EXPECT_TRUE(d.isValid());
        EXPECT_TRUE(d2.isValid());
        EXPECT_EQ(d2.toString(), "P1D");
        d2 = d2.minusHours(1);
        EXPECT_EQ(d2.toString(), "PT23H");
        d2 = d2.minusHours(1);
        EXPECT_EQ(d2.toString(), "PT22H");
    }
}
TEST(KeoDuration, absoluteTimestamp)
{
    KeoDuration d("P1M");
    EXPECT_TRUE(d.isValid());
    KeoDateTime date1(2000, 2, 28, 12, 0, 0, 0);
    KeoDateTime date2(2001, 2, 28, 12, 0, 0, 0);
    d.setAbsoluteUTCTimestamp(date1.toSeconds());
    int64_t seconds1 = d.getAbsoluteSecondsSinceInternalTimestamp();
    d.setAbsoluteUTCTimestamp(date2.toSeconds());
    int64_t seconds2 = d.getAbsoluteSecondsSinceInternalTimestamp();
    EXPECT_EQ(seconds1 - seconds2, 86400); // 1 day more
}

TEST(KeoDuration, absoluteTimestampMilliseconds)
{
    KeoDuration duration = KeoDuration::ofSeconds(0, 50);
    ASSERT_EQ(50, duration.getAbsoluteMilliSeconds(KeoDateTime::now()));

    duration = KeoDuration::ofSeconds(5, 50);
    ASSERT_EQ(5 * 1000 + 50, duration.getAbsoluteMilliSeconds(KeoDateTime::now()));

    duration = KeoDuration(0, 0, 0, 2, 0, 0, 0, false);
    ASSERT_EQ(2LL * 60LL * 60LL * 1000LL, duration.getAbsoluteMilliSeconds(KeoDateTime::now()));

    duration = KeoDuration(0, 1, 0, 0, 0, 0, 0, false);
    // January 2017 has 31 days
    ASSERT_EQ(31LL * 24LL * 60LL * 60LL * 1000LL, duration.getAbsoluteMilliSeconds(KeoDateTime(2017, 1, 1, 0, 0, 0, 0)));
}

TEST(KeoDuration, stringOut)
{
    {
        KeoDuration duration(2016, 11, 29, 0, 0, 0, 200);
        EXPECT_EQ(duration.toString(), "P2016Y11M29DT0.2S");
    }
    {
        KeoDuration duration(2016, 11, 29, 0, 0, 0, 200, true);
        EXPECT_EQ(duration.toString(), "-P2016Y11M29DT0.2S");
        KeoDuration durationParsed = KeoDuration::parse("-P2016Y11M29DT0.2S");
        EXPECT_EQ(duration, durationParsed);
    }
}

TEST(KeoDuration, notValid)
{
    KeoDuration duration = KeoDuration::parse("PT3600");
    EXPECT_FALSE(duration.isValid());
}
