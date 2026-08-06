/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2012
*****************************************************************************/

#include <gtest/gtest.h>

// system includes
#include "stdint.h"
#include <string>

// project includes
#include <keo_datagram/core/KeoTime.h>

using namespace keo_datagram;

/**
 * Tests the KeoTime
 */
TEST(KeoTime, Constructor)
{
    KeoTime timeEmpty;
    EXPECT_FALSE(timeEmpty.isValid());
    EXPECT_TRUE(timeEmpty.isZero());

    KeoTime time(13, 2, 3, 50);
    EXPECT_TRUE(time.isValid());
    EXPECT_FALSE(time.isZero());
    EXPECT_EQ(time.getHour(), 13);
    EXPECT_EQ(time.getMinute(), 2);
    EXPECT_EQ(time.getSecond(), 3);
    EXPECT_EQ(time.getMilliSecond(), 50);

    KeoTime time2(25, 62, 63, 2000);
    EXPECT_FALSE(time2.isValid());
    EXPECT_TRUE(time2.isZero());
}
TEST(KeoTime, Plus)
{
    KeoTime time(13, 2, 3, 50);
    EXPECT_TRUE(time.isValid());
    EXPECT_EQ(time.getHour(), 13);
    EXPECT_EQ(time.getMinute(), 2);
    EXPECT_EQ(time.getSecond(), 3);
    EXPECT_EQ(time.getMilliSecond(), 50);
    time = time.plusHours(6);
    EXPECT_TRUE(time.isValid());
    EXPECT_EQ(time.getHour(), 19);
    EXPECT_EQ(time.getMinute(), 2);
    EXPECT_EQ(time.getSecond(), 3);
    EXPECT_EQ(time.getMilliSecond(), 50);
    time = time.plusMinutes(59);
    EXPECT_TRUE(time.isValid());
    EXPECT_EQ(time.getHour(), 20);
    EXPECT_EQ(time.getMinute(), 1);
    EXPECT_EQ(time.getSecond(), 3);
    EXPECT_EQ(time.getMilliSecond(), 50);
    time = time.plusSeconds(58);
    EXPECT_TRUE(time.isValid());
    EXPECT_EQ(time.getHour(), 20);
    EXPECT_EQ(time.getMinute(), 2);
    EXPECT_EQ(time.getSecond(), 1);
    EXPECT_EQ(time.getMilliSecond(), 50);
    time = time.plusHours(6);
    EXPECT_TRUE(time.isValid());
    EXPECT_EQ(time.getHour(), 2);
    EXPECT_EQ(time.getMinute(), 2);
    EXPECT_EQ(time.getSecond(), 1);
    EXPECT_EQ(time.getMilliSecond(), 50);
}
TEST(KeoTime, Minus)
{
    KeoTime time(13, 2, 3, 50);
    EXPECT_EQ(time.getHour(), 13);
    EXPECT_EQ(time.getMinute(), 2);
    EXPECT_EQ(time.getSecond(), 3);
    EXPECT_EQ(time.getMilliSecond(), 50);
    time = time.plusHours(-13);
    EXPECT_EQ(time.getHour(), 0);
    EXPECT_EQ(time.getMinute(), 2);
    EXPECT_EQ(time.getSecond(), 3);
    EXPECT_EQ(time.getMilliSecond(), 50);
    time = time.plusMinutes(-13);
    EXPECT_EQ(time.getHour(), 23);
    EXPECT_EQ(time.getMinute(), 49);
    EXPECT_EQ(time.getSecond(), 3);
    EXPECT_EQ(time.getMilliSecond(), 50);
    time = time.plusSeconds(-43);
    EXPECT_EQ(time.getHour(), 23);
    EXPECT_EQ(time.getMinute(), 48);
    EXPECT_EQ(time.getSecond(), 20);
    EXPECT_EQ(time.getMilliSecond(), 50);
    time = time.plusHours(-10);
    EXPECT_TRUE(time.isValid());
}
TEST(KeoTime, Parsing)
{
    {
        KeoTime time(13, 2, 3, 50);
        std::string timeString = time.toString();
        KeoTime timeParsed = KeoTime::parse(timeString);
        EXPECT_EQ(time, timeParsed);
    }

    {
        KeoTime time(13, 2, 0, 0);
        std::string timeString = time.toString();
        EXPECT_EQ(timeString, "13:02:00Z");
    }
    {
        KeoTime time(13, 2, 0, 50);
        std::string timeString = time.toString();
        EXPECT_EQ(timeString, "13:02:00.050Z");
    }
}
TEST(KeoTime, seconds)
{
    KeoTime time = KeoTime::now();
    long seconds = time.toSeconds();
    uint16_t milliSeconds = time.getMilliSecond();
    KeoTime timeSec = KeoTime::ofMilliSecondOfDay(seconds * 1000 + milliSeconds);
    EXPECT_EQ(time, timeSec);
}
TEST(KeoTime, MilliSecondOfDay)
{
    KeoTime time = KeoTime::ofMilliSecondOfDay(123456789);
    EXPECT_EQ(time.getHour(), 10);
    EXPECT_EQ(time.getMinute(), 17);
    EXPECT_EQ(time.getSecond(), 36);
    EXPECT_EQ(time.getMilliSecond(), 789);
}
TEST(KeoTime, ToSecondOfDay)
{
    KeoTime testTime = KeoTime(10, 3, 51, 9);
    EXPECT_EQ(testTime.toSeconds(), 36231u);
    KeoTime testTime2 = KeoTime::ofMilliSecondOfDay(36231009);
    EXPECT_EQ(testTime, testTime2);
}

TEST(KeoTime, fromString)
{
    KeoTime time = KeoTime::parse(
        "20:00:00"); // Absolute times shall always be stated as UTC-Time ("Z" at the end of the time information).
    EXPECT_FALSE(time.isValid());

    time = KeoTime::parse("30:00:00Z");
    EXPECT_FALSE(time.isValid());

    time = KeoTime::parse("20:66:00Z");
    EXPECT_FALSE(time.isValid());

    time = KeoTime::parse("20:10:99Z");
    EXPECT_FALSE(time.isValid());
}

TEST(KeoTime, testRelationOperators)
{
    KeoTime time1(1, 0, 0, 00);
    KeoTime time2(1, 0, 0, 00);
    KeoTime time3(1, 0, 0, 01);
    KeoTime time4(4, 0, 0, 00);
    EXPECT_TRUE(time1 <= time2);
    EXPECT_TRUE(time1 >= time2);
    EXPECT_TRUE(time1 < time3);
    EXPECT_TRUE(time1 <= time3);
    EXPECT_TRUE(time4 >= time1);
}
