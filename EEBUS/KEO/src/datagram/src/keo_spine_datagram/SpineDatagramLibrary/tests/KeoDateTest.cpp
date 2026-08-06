/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2012
*****************************************************************************/

#include <gtest/gtest.h>

// system includes
#include "stdint.h"
#include <string>

// project includes
#include <keo_datagram/core/KeoDate.h>

using namespace keo_datagram;

/**
 * Tests the KeoDate
 */
TEST(KeoDate, Constructor)
{
    KeoDate dateEmpty;
    EXPECT_TRUE(dateEmpty.isZero());

    KeoDate date(2000, 2, 3);
    EXPECT_TRUE(date.isLeapYear());

    KeoDate date1(1, 2, 3);
    EXPECT_FALSE(date1.isZero());

    EXPECT_EQ(date1.getYear(), 1);
    EXPECT_EQ(date1.getMonth(), 2);
    EXPECT_EQ(date1.getDay(), 3);

    KeoDate date2(2002, 2, 30);
    EXPECT_EQ(date2.getYear(), 0);
    EXPECT_EQ(date2.getMonth(), 0);
    EXPECT_EQ(date2.getDay(), 0);

    KeoDate invalidDate(2002, 14, 30);
    EXPECT_FALSE(invalidDate.isValid());

    invalidDate = KeoDate(2002, 10, 66);
    EXPECT_FALSE(invalidDate.isValid());

    invalidDate = KeoDate(2002, 2, 29);
    EXPECT_FALSE(invalidDate.isValid());

    KeoDate leapDate(2016, 2, 29);
    EXPECT_TRUE(leapDate.isValid());
}
TEST(KeoDate, Plus)
{
    KeoDate date(2000, 1, 3);
    EXPECT_EQ(date.getYear(), 2000);
    EXPECT_EQ(date.getMonth(), 1);
    EXPECT_EQ(date.getDay(), 3);
    date = date.plusYears(13);
    EXPECT_EQ(date.getYear(), 2013);
    EXPECT_EQ(date.getMonth(), 1);
    EXPECT_EQ(date.getDay(), 3);
    date = date.plusMonths(13);
    EXPECT_EQ(date.getYear(), 2014);
    EXPECT_EQ(date.getMonth(), 2);
    EXPECT_EQ(date.getDay(), 3);
    date = date.plusDays(43);
    EXPECT_EQ(date.getYear(), 2014);
    EXPECT_EQ(date.getMonth(), 3);
    EXPECT_EQ(date.getDay(), 18);
}
TEST(KeoDate, Minus)
{
    KeoDate date(2000, 1, 3);
    EXPECT_EQ(date.getYear(), 2000);
    EXPECT_EQ(date.getMonth(), 1);
    EXPECT_EQ(date.getDay(), 3);
    date = date.plusYears(-13);
    EXPECT_EQ(date.getYear(), 1987);
    EXPECT_EQ(date.getMonth(), 1);
    EXPECT_EQ(date.getDay(), 3);
    date = date.plusMonths(-13);
    EXPECT_EQ(date.getYear(), 1985);
    EXPECT_EQ(date.getMonth(), 12);
    EXPECT_EQ(date.getDay(), 3);
    date = date.plusDays(-43);
    EXPECT_EQ(date.getYear(), 1985);
    EXPECT_EQ(date.getMonth(), 10);
    EXPECT_EQ(date.getDay(), 21);
}
TEST(KeoDate, Parsing)
{
    KeoDate date(2000, 1, 3);
    std::string dateString = date.toString();
    KeoDate dateParsed = KeoDate::parse(dateString);
    EXPECT_EQ(date, dateParsed);
}
TEST(KeoDate, seconds)
{
    KeoDate date = KeoDate::nowUTC();
    int64_t seconds = date.toSeconds();
    KeoDate dateSec = KeoDate::ofEpochSeconds(seconds);
    EXPECT_EQ(date.toString(), dateSec.toString());
}

TEST(KeoDate, testRelationOperators)
{
    KeoDate date1(2000, 1, 1);
    KeoDate date2(2000, 1, 1);
    KeoDate date3(2000, 1, 2);
    KeoDate date4(2001, 1, 11);
    EXPECT_TRUE(date1 <= date2);
    EXPECT_TRUE(date1 >= date2);
    EXPECT_TRUE(date1 < date3);
    EXPECT_TRUE(date1 <= date3);
    EXPECT_TRUE(date4 >= date1);
}
