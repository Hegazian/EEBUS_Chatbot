/*
 *     Copyright KEO GmbH 2017 - All rights reserved!
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
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_datagram/measurement/Measurement_All.h>

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */
#include "TestServerFeature.h"
#include "gtest/gtest.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */
using namespace keo_spine;
using namespace keo_datagram;

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

TEST(ServerFeatureTest, TestAddPossibleOperation)
{
    TestServerFeature feature;
    feature.addPossibleOperation(Function::Value::MEASUREMENT_LIST_DATA, ServerFeature::READ_ONLY);
    feature.addPossibleOperation(Function::Value::SETPOINT_LIST_DATA, ServerFeature::READ_PARTIAL_WRITE_PARTIAL);

    ASSERT_EQ(true, feature.getFeatureDescription().getSupportedFunctionIsSet());
    ASSERT_EQ(2U, feature.getFeatureDescription().getSupportedFunction().size());

    FunctionProperty supportedFunction = feature.getFeatureDescription().getSupportedFunction()[0];

    ASSERT_EQ(Function::Value::MEASUREMENT_LIST_DATA, supportedFunction.getFunction().getValue());
    ASSERT_TRUE(supportedFunction.getPossibleOperations().getReadIsSet());
    ASSERT_FALSE(supportedFunction.getPossibleOperations().getRead().getPartialIsSet());
    ASSERT_FALSE(supportedFunction.getPossibleOperations().getWriteIsSet());

    supportedFunction = feature.getFeatureDescription().getSupportedFunction()[1];

    ASSERT_EQ(Function::Value::SETPOINT_LIST_DATA, supportedFunction.getFunction().getValue());
    ASSERT_TRUE(supportedFunction.getPossibleOperations().getReadIsSet());
    ASSERT_TRUE(supportedFunction.getPossibleOperations().getRead().getPartialIsSet());
    ASSERT_TRUE(supportedFunction.getPossibleOperations().getWriteIsSet());
    ASSERT_TRUE(supportedFunction.getPossibleOperations().getWrite().getPartialIsSet());
}

TEST(ServerFeatureTest, TestRemoveSupportOperation)
{
    TestServerFeature f;
    f.addPossibleOperation(Function::Value::MEASUREMENT_LIST_DATA, ServerFeature::READ_ONLY);
    ASSERT_TRUE(f.isSupported(Function::Value::MEASUREMENT_LIST_DATA, CmdClassifier::Value::READ, false));
    f.removePossibleOperation(Function::Value::SETPOINT_LIST_DATA);
    ASSERT_TRUE(f.isSupported(Function::Value::MEASUREMENT_LIST_DATA, CmdClassifier::Value::READ, false));
    f.removePossibleOperation(Function::Value::MEASUREMENT_LIST_DATA);
    ASSERT_FALSE(f.isSupported(Function::Value::MEASUREMENT_LIST_DATA, CmdClassifier::Value::READ, false));
}

TEST(ServerFeatureTest, TestHasPossibleOperation)
{
    TestServerFeature feature;
    feature.addPossibleOperation(Function::Value::MEASUREMENT_LIST_DATA, ServerFeature::READ_ONLY);

    ASSERT_TRUE(feature.hasPossibleOperation(Function::Value::MEASUREMENT_LIST_DATA, ServerFeature::READ_ONLY));
    ASSERT_FALSE(feature.hasPossibleOperation(Function::Value::MEASUREMENT_LIST_DATA, ServerFeature::WRITE_ONLY));
    ASSERT_FALSE(feature.hasPossibleOperation(Function::Value::SETPOINT_LIST_DATA, ServerFeature::WRITE_ONLY));

    feature.removePossibleOperation(Function::Value::MEASUREMENT_LIST_DATA);
    ASSERT_FALSE(feature.hasPossibleOperation(Function::Value::MEASUREMENT_LIST_DATA, ServerFeature::READ_ONLY));
}

TEST(ServerFeatureTest, TestIsSupported)
{
    TestServerFeature f;
    f.addPossibleOperation(Function::Value::MEASUREMENT_LIST_DATA, ServerFeature::READ_ONLY);
    f.addPossibleOperation(Function::Value::ALARM_LIST_DATA, ServerFeature::WRITE_ONLY);

    f.addPossibleOperation(Function::Value::MEASUREMENT_DESCRIPTION_LIST_DATA, ServerFeature::READ_PARTIAL);
    f.addPossibleOperation(Function::Value::MEASUREMENT_CONSTRAINTS_LIST_DATA, ServerFeature::WRITE_PARTIAL);

    f.addPossibleOperation(Function::Value::SETPOINT_DESCRIPTION_LIST_DATA, ServerFeature::READ_WRITE);

    f.addPossibleOperation(Function::Value::BILL_CONSTRAINTS_LIST_DATA, ServerFeature::READ_PARTIAL_WRITE);
    f.addPossibleOperation(Function::Value::BILL_DESCRIPTION_LIST_DATA, ServerFeature::READ_WRITE_PARTIAL);
    f.addPossibleOperation(Function::Value::SETPOINT_LIST_DATA, ServerFeature::READ_PARTIAL_WRITE_PARTIAL);

    f.addPossibleOperation(Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL, ServerFeature::NO_OPERATIONS);

    ASSERT_TRUE(f.isSupported(Function::Value::MEASUREMENT_LIST_DATA, CmdClassifier::Value::READ, false));
    ASSERT_FALSE(f.isSupported(Function::Value::MEASUREMENT_LIST_DATA, CmdClassifier::Value::READ, true));
    ASSERT_FALSE(f.isSupported(Function::Value::MEASUREMENT_LIST_DATA, CmdClassifier::Value::WRITE, false));
    ASSERT_FALSE(f.isSupported(Function::Value::MEASUREMENT_LIST_DATA, CmdClassifier::Value::WRITE, true));

    ASSERT_FALSE(f.isSupported(Function::Value::ALARM_LIST_DATA, CmdClassifier::Value::READ, false));
    ASSERT_FALSE(f.isSupported(Function::Value::ALARM_LIST_DATA, CmdClassifier::Value::READ, true));
    ASSERT_TRUE(f.isSupported(Function::Value::ALARM_LIST_DATA, CmdClassifier::Value::WRITE, false));
    ASSERT_FALSE(f.isSupported(Function::Value::ALARM_LIST_DATA, CmdClassifier::Value::WRITE, true));

    ASSERT_TRUE(f.isSupported(Function::Value::MEASUREMENT_DESCRIPTION_LIST_DATA, CmdClassifier::Value::READ, false));
    ASSERT_TRUE(f.isSupported(Function::Value::MEASUREMENT_DESCRIPTION_LIST_DATA, CmdClassifier::Value::READ, true));
    ASSERT_FALSE(f.isSupported(Function::Value::MEASUREMENT_DESCRIPTION_LIST_DATA, CmdClassifier::Value::WRITE, false));

    ASSERT_TRUE(f.isSupported(Function::Value::MEASUREMENT_CONSTRAINTS_LIST_DATA, CmdClassifier::Value::WRITE, false));
    ASSERT_TRUE(f.isSupported(Function::Value::MEASUREMENT_CONSTRAINTS_LIST_DATA, CmdClassifier::Value::WRITE, true));
    ASSERT_FALSE(f.isSupported(Function::Value::MEASUREMENT_CONSTRAINTS_LIST_DATA, CmdClassifier::Value::READ, false));

    ASSERT_TRUE(f.isSupported(Function::Value::SETPOINT_DESCRIPTION_LIST_DATA, CmdClassifier::Value::READ, false));
    ASSERT_FALSE(f.isSupported(Function::Value::SETPOINT_DESCRIPTION_LIST_DATA, CmdClassifier::Value::READ, true));
    ASSERT_TRUE(f.isSupported(Function::Value::SETPOINT_DESCRIPTION_LIST_DATA, CmdClassifier::Value::WRITE, false));
    ASSERT_FALSE(f.isSupported(Function::Value::SETPOINT_DESCRIPTION_LIST_DATA, CmdClassifier::Value::WRITE, true));

    ASSERT_TRUE(f.isSupported(Function::Value::BILL_CONSTRAINTS_LIST_DATA, CmdClassifier::Value::READ, false));
    ASSERT_TRUE(f.isSupported(Function::Value::BILL_CONSTRAINTS_LIST_DATA, CmdClassifier::Value::READ, true));
    ASSERT_TRUE(f.isSupported(Function::Value::BILL_CONSTRAINTS_LIST_DATA, CmdClassifier::Value::WRITE, false));
    ASSERT_FALSE(f.isSupported(Function::Value::BILL_CONSTRAINTS_LIST_DATA, CmdClassifier::Value::WRITE, true));

    ASSERT_TRUE(f.isSupported(Function::Value::BILL_DESCRIPTION_LIST_DATA, CmdClassifier::Value::READ, false));
    ASSERT_FALSE(f.isSupported(Function::Value::BILL_DESCRIPTION_LIST_DATA, CmdClassifier::Value::READ, true));
    ASSERT_TRUE(f.isSupported(Function::Value::BILL_DESCRIPTION_LIST_DATA, CmdClassifier::Value::WRITE, false));
    ASSERT_TRUE(f.isSupported(Function::Value::BILL_DESCRIPTION_LIST_DATA, CmdClassifier::Value::WRITE, true));

    ASSERT_TRUE(f.isSupported(Function::Value::SETPOINT_LIST_DATA, CmdClassifier::Value::READ, false));
    ASSERT_TRUE(f.isSupported(Function::Value::SETPOINT_LIST_DATA, CmdClassifier::Value::READ, true));
    ASSERT_TRUE(f.isSupported(Function::Value::SETPOINT_LIST_DATA, CmdClassifier::Value::WRITE, false));
    ASSERT_TRUE(f.isSupported(Function::Value::SETPOINT_LIST_DATA, CmdClassifier::Value::WRITE, true));

    ASSERT_TRUE(f.isSupported(Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL, CmdClassifier::Value::CALL, false));
    ASSERT_FALSE(f.isSupported(Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL, CmdClassifier::Value::CALL, true));
    ASSERT_FALSE(f.isSupported(Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL, CmdClassifier::Value::WRITE, false));
}

TEST(ServerFeatureTest, TestIsSupportedDatagram)
{
    TestServerFeature f;
    f.addPossibleOperation(Function::Value::MEASUREMENT_LIST_DATA, ServerFeature::READ_ONLY);

    auto read = Datagram::fromJson(
        "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{\"device\":\"d:a\"},{"
        "\"entity\":[1]},{\"feature\":1}]},{\"addressDestination\":[{\"device\":\"d:a\"},{\"entity\":[1]},{\"feature\":"
        "1}]},{\"msgCounter\":1},{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{\"measurementListData\":[]}]]"
        "}]}]}");

    ASSERT_TRUE(read.parsePayload());

    auto partialRead = Datagram::fromJson(
        "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{\"device\":\"d:a\"},{"
        "\"entity\":[1]},{\"feature\":1}]},{\"addressDestination\":[{\"device\":\"d:a\"},{\"entity\":[1]},{\"feature\":"
        "1}]},{\"msgCounter\":1},{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{\"filter\":[[{"
        "\"measurementListDataSelectors\":[{\"measurementId\":5}]}]]},{\"measurementListData\":[]}]]}]}]}");

    ASSERT_TRUE(partialRead.parsePayload());

    ASSERT_TRUE(f.isSupported(read));
    ASSERT_FALSE(f.isSupported(partialRead));
}
