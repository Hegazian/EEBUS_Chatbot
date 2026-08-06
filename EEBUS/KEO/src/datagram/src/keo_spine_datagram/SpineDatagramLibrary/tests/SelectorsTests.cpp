/*
 *     Copyright KEO GmbH 2013 - All rights reserved!
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

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <iostream>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <gtest/gtest.h>
#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/measurement/Measurement_All.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

#include <gtest/gtest.h>

using namespace keo_datagram;

TEST(SelectorsTests, testSelectsSimple)
{
    MeasurementListDataSelectors selector;
    selector.setMeasurementId(1U);
    MeasurementData data;

    data.setMeasurementId(1U);
    ASSERT_TRUE(selector.selects(data));

    data.setValueType(MeasurementValueType::Value::AVERAGE_VALUE);
    ASSERT_TRUE(selector.selects(data));

    data.setMeasurementId(4U);
    ASSERT_FALSE(selector.selects(data));
}

TEST(SelectorsTests, testSelectsList)
{
    MeasurementThresholdRelationListDataSelectors selector;
    selector.setMeasurementId(1U);

    MeasurementThresholdRelationData data;
    data.setMeasurementId(1U);

    ASSERT_TRUE(selector.selects(data));

    selector.setThresholdId(2U);

    ASSERT_FALSE(selector.selects(data));

    data.setThresholdId({ 2U });

    ASSERT_TRUE(selector.selects(data));
}

TEST(SelectorsTests, testSelectsIntervalAbsolute)
{
    MeasurementListDataSelectors selector;
    AbsoluteOrRelativeTime start;
    start.setDateTime(KeoDateTime(1991, 10, 24, 0, 0, 0, 0));

    AbsoluteOrRelativeTime end;
    end.setDateTime(KeoDateTime(1991, 10, 25, 0, 0, 0, 0));

    TimestampInterval interval(start, end);
    selector.setTimestampInterval(interval);

    AbsoluteOrRelativeTime time;
    time.setDateTime(KeoDateTime(1991, 10, 24, 10, 0, 0, 0));
    MeasurementData data;
    data.setTimestamp(time);

    time.setDateTime(KeoDateTime(1992, 10, 24, 10, 0, 0, 0));
    data.setTimestamp(time);

    ASSERT_FALSE(selector.selects(data));
}

TEST(SelectorsTests, testSelectsIntervalRelative)
{
    MeasurementListDataSelectors selector;
    AbsoluteOrRelativeTime start;
    start.setDuration(KeoDuration(100, 0));

    AbsoluteOrRelativeTime end;
    end.setDuration(KeoDuration(200, 0));

    TimestampInterval interval(start, end);
    selector.setTimestampInterval(interval);

    AbsoluteOrRelativeTime time;
    time.setDuration(KeoDuration(150, 0));
    MeasurementData data;
    data.setTimestamp(time);

    time.setDuration(KeoDuration(250, 0));
    data.setTimestamp(time);

    ASSERT_FALSE(selector.selects(data));
}
