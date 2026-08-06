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

/**
 *  @brief SPINE Datagram
 *
 *  @par    Module description
 *          All generated datagrams are derived from this base class
 *
 */

#include <gtest/gtest.h>
#include <string>

#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/devicediagnosis/DeviceDiagnosisServiceData.h>

using namespace keo_datagram;

TEST(DatagramHelperTest, getAndIs)
{
    //    SpineDataType typeActuator = ACTUATOR_SWITCH_DATA_TYPE;
    // SpineDataType typeResult = keo_datagram::RESULT_DATA_TYPE;

    // isResult
    // ASSERT_TRUE(SpineDatagramUtilities::isResult(typeResult));
}
TEST(DatagramHelperTest, getTypes)
{
    //    SpineDataType typeSystem = ACTUATOR_SWITCH_DATA_TYPE;
    // SpineDataType typeResult = RESULT_DATA_TYPE;

    // isResult
    //    ASSERT_TRUE(SpineDatagramUtilities::isResult(typeResult));
}
TEST(DatagramHelperTest, Classifier)
{
    ASSERT_EQ(CmdClassifier::fromString("result"), CmdClassifier::Value::RESULT);
    ASSERT_EQ(CmdClassifier::fromString("write"), CmdClassifier::Value::WRITE);
}
