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

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */

#include <gtest/gtest.h>

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */

// module to test
#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
/* ************************************************************************** *
 *  defines                                                                   *
 * ************************************************************************** */

/* ************************************************************************** *
 *  types                                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  definition                                                                *
 * ************************************************************************** */

TEST(AbsoluteOrRelativeTimeStruct, ticket1631) {
    EXPECT_EQ(
            keo_datagram::AbsoluteOrRelativeTime::fromString("PT0S").toString(),
            "PT0S");
    EXPECT_EQ(
            keo_datagram::AbsoluteOrRelativeTime::fromString("PT24H").toString(),
            "P1D");
    EXPECT_EQ(
            keo_datagram::AbsoluteOrRelativeTime::fromString("PT3.23S").toString(),
            "PT3.23S");
    EXPECT_EQ(
            keo_datagram::AbsoluteOrRelativeTime::fromString("PT3.023S").toString(),
            "PT3.023S");
}
