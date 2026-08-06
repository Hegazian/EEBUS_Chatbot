/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2012
*****************************************************************************/

#include <gtest/gtest.h>

// system includes
#include "stdint.h"
#include <string>

// project includes
#include <keo_datagram/core/KeoDateTime.h>

using namespace keo_datagram;

/**
 * Tests the KeoDateTime
 */
TEST(KeoDateTime, Constructor)
{
    KeoDateTime dateTimeEmpty;
    EXPECT_TRUE(dateTimeEmpty.isZero());

    KeoDateTime dateTime(5, 6, 7, 8, 9, 10, 11);
    EXPECT_FALSE(dateTime.isZero());

    EXPECT_EQ(dateTime.getYear(), 5);
    EXPECT_EQ(dateTime.getMonth(), 6);
    EXPECT_EQ(dateTime.getDay(), 7);
    EXPECT_EQ(dateTime.getHour(), 8);
    EXPECT_EQ(dateTime.getMinute(), 9);
    EXPECT_EQ(dateTime.getSecond(), 10);
    EXPECT_EQ(dateTime.getMilliSecond(), 11);

    KeoDateTime testDate = KeoDateTime::ofEpochMilliSeconds(1234567897602);
    EXPECT_EQ(testDate.getYear(), 2009);
    EXPECT_EQ(testDate.getMonth(), 2);
    EXPECT_EQ(testDate.getDay(), 13);
    EXPECT_EQ(testDate.getHour(), 23);
    EXPECT_EQ(testDate.getMinute(), 31);
    EXPECT_EQ(testDate.getSecond(), 37);
    EXPECT_EQ(testDate.getMilliSecond(), 602);

    testDate = KeoDateTime::ofEpochMilliSeconds(1500000000000);
    EXPECT_EQ(testDate.getYear(), 2017);
    EXPECT_EQ(testDate.getMonth(), 7);
    EXPECT_EQ(testDate.getDay(), 14);
    EXPECT_EQ(testDate.getHour(), 2);
    EXPECT_EQ(testDate.getMinute(), 40);
    EXPECT_EQ(testDate.getSecond(), 0);
    EXPECT_EQ(testDate.getMilliSecond(), 0);

    testDate = KeoDateTime::ofEpochMilliSeconds(1000000000000);
    EXPECT_EQ(testDate.getYear(), 2001);
    EXPECT_EQ(testDate.getMonth(), 9);
    EXPECT_EQ(testDate.getDay(), 9);
    EXPECT_EQ(testDate.getHour(), 1);
    EXPECT_EQ(testDate.getMinute(), 46);
    EXPECT_EQ(testDate.getSecond(), 40);
    EXPECT_EQ(testDate.getMilliSecond(), 0);
}
TEST(KeoDateTime, Parsing)
{
    KeoDateTime testDate = KeoDateTime::parse("2016-02-29T6:31:22.33Z");
    EXPECT_EQ(testDate.getYear(), 2016);
    EXPECT_EQ(testDate.getMonth(), 2);
    EXPECT_EQ(testDate.getDay(), 29);
    EXPECT_EQ(testDate.getHour(), 6);
    EXPECT_EQ(testDate.getMinute(), 31);
    EXPECT_EQ(testDate.getSecond(), 22);
    EXPECT_EQ(testDate.getMilliSecond(), 33);
}
TEST(KeoDateTime, Duration)
{
    KeoDateTime testDate1 = KeoDateTime::parse("2016-02-29T6:31:22.33Z");
    KeoDateTime testDate2 = KeoDateTime::parse("2016-02-29T9:21:22.23Z");
    EXPECT_TRUE(testDate1.isValid());
    EXPECT_TRUE(testDate2.isValid());
    KeoDuration duration = testDate1.getDuration(testDate2);
    EXPECT_TRUE(duration.isValid());
    EXPECT_TRUE(!duration.isZero());
}
TEST(KeoDateTime, InvalidateDateTimeIfDateOrTimeIsInvalid)
{
    KeoDateTime testDate1 = KeoDateTime::parse("2016-02-29T6:31:22.33");
    EXPECT_FALSE(testDate1.isValid());
    KeoDateTime testDate2 = KeoDateTime::parse("2016-22-29T6:31:22.33Z");
    EXPECT_FALSE(testDate2.isValid());
}
TEST(KeoDateTime, Now)
{
    KeoDateTime testDate = KeoDateTime::now();
    long milliNow = testDate.toMilliSeconds();
    KeoDateTime testDate2 = KeoDateTime::ofEpochMilliSeconds(milliNow);
    EXPECT_EQ(testDate, testDate2);
}

TEST(KeoDateTime, ToMilliSecondsSimple)
{
    KeoDateTime testDate = KeoDateTime::ofEpochMilliSeconds(197602);
    KeoDateTime testDate2 = KeoDateTime(testDate.getYear(), testDate.getMonth(), testDate.getDay(), testDate.getHour(),
        testDate.getMinute(), testDate.getSecond(), testDate.getMilliSecond());
    EXPECT_EQ(testDate2.toMilliSeconds(), 197602);
}

TEST(KeoDateTime, ToMilliSeconds)
{
    KeoDateTime testDate = KeoDateTime::ofEpochMilliSeconds(1234567897602);
    KeoDateTime testDate2 = KeoDateTime(testDate.getYear(), testDate.getMonth(), testDate.getDay(), testDate.getHour(),
        testDate.getMinute(), testDate.getSecond(), testDate.getMilliSecond());
    EXPECT_EQ(testDate2.toMilliSeconds(), 1234567897602);
}

TEST(KeoDateTime, AddDuration)
{
    KeoDateTime date1 = KeoDateTime(2003, 6, 4, 3, 20, 34, 5);
    KeoDuration duration = KeoDuration::parse("P3Y6M4DT12H30M17.457S");
    KeoDateTime date2 = date1.addDuration(duration);
    EXPECT_EQ(date2.toString(), "2006-12-08T15:50:51.462Z");
}

TEST(KeoDateTime, AddDurationNegative)
{
    KeoDateTime date1 = KeoDateTime(2003, 6, 4, 3, 20, 34, 5);
    KeoDuration duration = KeoDuration::parse("-P3Y6M4DT12H30M17.457S");
    KeoDateTime date2 = date1.addDuration(duration);
    EXPECT_EQ(date2.toString(), "1999-11-29T14:50:16.548Z");
}

TEST(KeoDateTime, GetDuration)
{
    KeoDateTime date1 = KeoDateTime(2003, 6, 4, 3, 20, 34, 5);
    KeoDateTime date2 = KeoDateTime(2006, 12, 8, 15, 50, 51, 462);
    KeoDuration duration = date1.getDuration(date2);
    EXPECT_EQ(duration.toString(), "P1283DT12H30M17.457S");
    KeoDateTime date3 = date1.addDuration(duration);
    EXPECT_EQ(date3.toString(), "2006-12-08T15:50:51.462Z");
}

TEST(KeoDateTime, GetDurationNegative)
{
    KeoDateTime date1 = KeoDateTime(2003, 6, 4, 3, 20, 34, 5);
    KeoDateTime date2 = KeoDateTime(1999, 11, 29, 14, 50, 16, 548);
    KeoDuration duration = date1.getDuration(date2);
    EXPECT_EQ(duration.toString(), "-P1282DT12H30M17.457S");
    KeoDateTime date3 = date1.addDuration(duration);
    EXPECT_EQ(date3.toString(), "1999-11-29T14:50:16.548Z");
}

TEST(KeoDateTime, testRelationOperators)
{
    KeoDateTime date1 = KeoDateTime::parse("2011-02-22T6:31:22.33Z");
    KeoDateTime date2 = KeoDateTime::parse("2011-02-22T6:31:22.33Z");
    KeoDateTime date3 = KeoDateTime::parse("2012-02-22T6:31:22.33Z");
    KeoDateTime date4 = KeoDateTime::parse("2013-02-22T6:31:22.33Z");
    ASSERT_TRUE(date1 == date2);
    ASSERT_TRUE(date1 >= date2);
    ASSERT_TRUE(date1 <= date2);
    ASSERT_TRUE(date2 <= date3);
    ASSERT_TRUE(date4 >= date3);
}
