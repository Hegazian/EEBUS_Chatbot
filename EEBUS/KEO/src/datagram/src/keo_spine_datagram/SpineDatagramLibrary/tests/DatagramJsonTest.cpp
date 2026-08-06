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
 *  @brief Tests for generation of datagrams from and to JSON
 *
 *  @par    Module description
 *          JSON transformation
 *
 */
#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <keo_datagram/actuator/Actuator_All.h>
#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/core/DatagramParserException.h>
#include <keo_datagram/core/SpineResultErrors.h>
#include <keo_datagram/deviceconfiguration/DeviceConfiguration_All.h>
#include <keo_datagram/devicediagnosis/DeviceDiagnosis_All.h>
#include <keo_datagram/hvac/HVAC_All.h>
#include <keo_datagram/incentivetable/IncentiveTable_All.h>
#include <keo_datagram/measurement/Measurement_All.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPs_All.h>
#include <keo_datagram/timeinformation/TimeInformation_All.h>

#include <string>

using namespace keo_datagram;

void removeWhiteSpaces(std::string& s)
{
    s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
}

TEST(DatagramJsonTest, testNegativeAsUint)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_n:systemtest_node_2\"},{\"entity\":[1]},{\"feature\":1}]},{"
                           "\"addressDestination\":[{\"device\":\"d:_n:systemtest_node_1\"},{\"entity\":[1]},{"
                           "\"feature\":1}]},{\"msgCounter\":-12},{\"cmdClassifier\":"
                           "\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"measurementListData\":[{\"measurementData\":[[{"
                           "\"value\":[{\"number\":4200000},{\"scale\":9}]}]]}]}]]}]}]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, testScaleOverflow)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_n:systemtest_node_2\"},{\"entity\":[1]},{\"feature\":1}]},{"
                           "\"addressDestination\":[{\"device\":\"d:_n:systemtest_node_1\"},{\"entity\":[1]},{"
                           "\"feature\":1}]},{\"msgCounter\":12},{\"cmdClassifier\":"
                           "\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"measurementListData\":[{\"measurementData\":[[{"
                           "\"value\":[{\"number\":4200000},{\"scale\":99999999}]}]]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_THROW(datagram.parsePayloadThrows(), DatagramParserException);
}

TEST(DatagramJsonTest, SetPayloadOnUnparsedDatagram)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_n:systemtest_node_2\"},{\"entity\":[1]},{\"feature\":1}]},{"
                           "\"addressDestination\":[{\"device\":\"d:_n:systemtest_node_1\"},{\"entity\":[1]},{"
                           "\"feature\":1}]},{\"msgCounter\":12},{\"msgCounterReference\":6},{\"cmdClassifier\":"
                           "\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"measurementListData\":[{\"measurementData\":[[{"
                           "\"value\":[{\"number\":42000000000000},{\"scale\":-12}]}]]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_TRUE(datagram.isHeaderValid());
    ASSERT_FALSE(datagram.isPayloadParsed());

    std::vector<Cmd> cmds = { Cmd(std::make_shared<MeasurementListData>()) };
    Payload payload = Payload(cmds);
    datagram.setPayload(payload);

    ASSERT_TRUE(datagram.isPayloadParsed());
    ASSERT_TRUE(datagram.parsePayload());
}

TEST(DatagramJsonTest, readNumber)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_n:systemtest_node_2\"},{\"entity\":[1]},{\"feature\":1}]},{"
                           "\"addressDestination\":[{\"device\":\"d:_n:systemtest_node_1\"},{\"entity\":[1]},{"
                           "\"feature\":1}]},{\"msgCounter\":12},{\"msgCounterReference\":6},{\"cmdClassifier\":"
                           "\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"measurementListData\":[{\"measurementData\":[[{"
                           "\"value\":[{\"number\":42000000000000},{\"scale\":-12}]}]]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_TRUE(datagram.parsePayload());
    ASSERT_EQ(testJson, datagram.toJson());

    std::shared_ptr<const keo_datagram::MeasurementListData> p
        = std::static_pointer_cast<const keo_datagram::MeasurementListData>(datagram.getCmdData());

    ASSERT_EQ(42000000000000, p->getMeasurementData()[0].getValue().getNumber());
    ASSERT_EQ(-12, p->getMeasurementData()[0].getValue().getScale());
}

TEST(DatagramJsonTest, readNumberNegative)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_n:systemtest_node_2\"},{\"entity\":[1]},{\"feature\":1}]},{"
                           "\"addressDestination\":[{\"device\":\"d:_n:systemtest_node_1\"},{\"entity\":[1]},{"
                           "\"feature\":1}]},{\"msgCounter\":12},{\"msgCounterReference\":6},{\"cmdClassifier\":"
                           "\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"measurementListData\":[{\"measurementData\":[[{"
                           "\"value\":[{\"number\":-42000000000000},{\"scale\":-12}]}]]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_TRUE(datagram.parsePayload());
    ASSERT_EQ(testJson, datagram.toJson());

    std::shared_ptr<const keo_datagram::MeasurementListData> p
        = std::static_pointer_cast<const keo_datagram::MeasurementListData>(datagram.getCmdData());

    ASSERT_EQ(-42000000000000, p->getMeasurementData()[0].getValue().getNumber());
    ASSERT_EQ(-12, p->getMeasurementData()[0].getValue().getScale());
}

TEST(DatagramJsonTest, testMissingMandatoryFields)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
          "\"device\":\"d:_i:1234_EMS\"},{\"entity\":[2]},{\"feature\":1}]},{\"entity\":[0]},{\"feature\":2}]},{"
          "\"msgCounterReference\":11},{\"msgCounter\":33}]},{"
          "\"payload\":[{\"cmd\":[[{\"deviceDiagnosisHeartbeatData\":[{\"timestamp\":\"2017-12-07T11:"
          "39:26Z\"},{\"heartbeatCounter\":1},{\"heartbeatTimeout\":\"PT4S\"}]}]]}]}]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, testPayloadBeforeHeader)
{
    std::string testJson
        = "{\"datagram\": [{\"payload\": [{\"cmd\": [[{\"deviceDiagnosisHeartbeatData\": [{\"timestamp\": "
          "\"2017-12-07T11:39:26Z\"},{\"heartbeatCounter\": 1},{\"heartbeatTimeout\": \"PT4S\"}]}]]}]},{\"header\": "
          "[{\"specificationVersion\": \"1.1.0\"},{\"addressSource\": [{\"device\": \"d:_i:1234_EMS\"},{\"entity\": "
          "[2]},{\"feature\": 1}]},{\"addressDestination\": [{\"device\": \"d:_i:4711_Mennekes\"},{\"entity\": "
          "[0]},{\"feature\": 2}]},{\"msgCounter\": 33}]}]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, testWrongOrderInHeader)
{
    // MsgCounterReference before MsgCounter
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_i:1234_EMS\"},{\"entity\":[2]},{\"feature\":1}]},{\"addressDestination\":[{"
                           "\"device\":\"d:_i:4711_Mennekes\"},{\"entity\":[0]},{\"feature\":2}]},{"
                           "\"msgCounterReference\":11},{\"msgCounter\":33}]},{"
                           "\"payload\":[{\"cmd\":[[{\"deviceDiagnosisHeartbeatData\":[{\"timestamp\":\"2017-12-07T11:"
                           "39:26Z\"},{\"heartbeatCounter\":1},{\"heartbeatTimeout\":\"PT4S\"}]}]]}]}]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, doNotParseInvalidTimeFromJsonInPayload)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.1\"},{\"addressSource\":[{\"device\":\"d:_i:"
          "12345_SourceDevice\"},"
          "{\"entity\":[1,2]},{\"feature\":1}]},{\"addressDestination\":[{\"device\":\"d:_i:12345_DestinationDevice\"},"
          "{\"entity\":[1,2]},{\"feature\":1}]},{\"msgCounter\":123},{\"msgCounterReference\":11},{\"cmdClassifier\":"
          "\"read\"},"
          "{\"ackRequest\":true}]},{\"payload\":[{\"cmd\":[[{\"deviceConfigurationKeyValueListData\":"
          "[{\"deviceConfigurationKeyValueData\":[[{\"keyId\":1050645299},{\"value\":[{\"boolean\":false},"
          "{\"date\":\"2017-10-19\"},{\"dateTime\":\"2017-10-19T26:50:57Z\"},{\"duration\":\"P1Y2M3DT1H10M0S\"},"
          "{\"string\":\"dummyString\"},{\"time\":\"21:16:45\"},{\"scaledNumber\":[{\"number\":2127705051},"
          "{\"scale\":15}]}]},{\"isValueChangeable\":true}]]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_THROW(datagram.parsePayloadThrows(), DatagramParserException);
}

TEST(DatagramJsonTest, parseResultData)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.1\"},{\"addressSource\":[{"
                           "\"device\":\"dummyString\"},{\"entity\":[1079338857,1481727868,2037494070,1594635255]},{"
                           "\"feature\":1886739004}]},{\"addressDestination\":[{\"device\":\"dummyString\"},{"
                           "\"entity\":[2009123195,1618202624,2102535068,626219048]},{\"feature\":1612775356}]},{"
                           "\"addressOriginator\":[{\"device\":\"dummyString\"},{\"entity\":[789059093,848637832,"
                           "375324788]},{\"feature\":1336778938}]},{\"msgCounter\":4512},{\"msgCounterReference\":"
                           "16678774"
                           "},{\"cmdClassifier\":\"reply\"},{\"ackRequest\":false}]},{\"payload\":[{\"cmd\":[[{"
                           "\"resultData\":[{\"errorNumber\":"
                           "734983252},{\"description\":\"dummyString\"}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_TRUE(datagram.parsePayload());
    ASSERT_EQ(testJson, datagram.toJson());
}

TEST(DatagramJsonTest, testParseRead)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:SHIP_test_1\"},{\"entity\":[1]},{\"feature\":4}]},{\"addressDestination\":[{"
                           "\"device\":\"d:EEBusTestClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":185},{"
                           "\"msgCounterReference\":28},"
                           "{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
                           "\"deviceDiagnosisServiceData\":[]}]]}]}]}";
    Datagram d = Datagram::fromJsonThrows(testJson);
    d.parsePayloadThrows();
    ASSERT_TRUE(d.isHeaderValid());
    ASSERT_TRUE(d.isPayloadValid());
}

TEST(DatagramJsonTest, doNotParseStringsAsNumberInHeader)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:SHIP_test_1\"},{\"entity\":[1]},{\"feature\":4}]},{\"addressDestination\":[{"
                           "\"device\":\"d:EEBusTestClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":185},{"
                           "\"msgCounterReference\":\"28\"},"
                           "{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
                           "\"deviceDiagnosisServiceData\":[]}]]}]}]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, doNotParseBoolAsNumberInHeader)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:SHIP_test_1\"},{\"entity\":[1]},{\"feature\":4}]},{\"addressDestination\":[{"
                           "\"device\":\"d:EEBusTestClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":185},{"
                           "\"msgCounterReference\":false},"
                           "{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
                           "\"deviceDiagnosisServiceData\":[]}]]}]}]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, doNotParseListBoolAsNumberInHeader)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:SHIP_test_1\"},{\"entity\":[1]},{\"feature\":4}]},{\"addressDestination\":[{"
                           "\"device\":\"d:EEBusTestClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":185},{"
                           "\"msgCounterReference\":[]},"
                           "{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
                           "\"deviceDiagnosisServiceData\":[]}]]}]}]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

// reuse header
TEST(DatagramJsonTest, doubleList)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},"
          "{\"addressSource\":[{\"device\":\"d:_i:4711_Mennekes\"},{\"entity\":[1,1]},{\"feature\":4}]},"
          "{\"addressDestination\":[{\"device\":\"d:_i:4711_ems-client\"},{\"entity\":[2]},{\"feature\":1}]},"
          "{\"msgCounter\":86},"
          "{\"msgCounterReference\":32},"
          "{\"cmdClassifier\":\"reply\"}]},"
          "{\"payload\":[{\"cmd\":[["
          "{\"electricalConnectionPermittedValueSetListData\":["
          "{\"electricalConnectionPermittedValueSetData\":[["
          "{\"electricalConnectionId\":1},{\"parameterId\":3},"
          "{\"permittedValueSet\":[[{\"value\":[[{\"number\":0},{\"scale\":0}]]},"
          "{\"range\":[[{\"min\":[{\"number\":600},{\"scale\":-2}]},{\"max\":[{\"number\":2200},{\"scale\":-2}]}]]}]]}]"
          "]}]}]]}]}]}";

    Datagram datagram = Datagram::fromJsonThrows(testJson);

    keo_datagram::Header replyHeader(datagram.getHeader());
    replyHeader.changeToResponse(CmdClassifier::Value::REPLY);
    ASSERT_TRUE(datagram.parsePayload());
    keo_datagram::Cmd replyCmd = datagram.getCmd();
    Datagram datagramReply(replyHeader, replyCmd);

    ASSERT_TRUE(datagramReply.isHeaderValid());
    ASSERT_TRUE(datagramReply.isReply());
    ASSERT_TRUE(datagram.isHeaderValid());
}

TEST(DatagramJsonTest, emptyOptionGroup)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:SHIP_test_1\"},{\"entity\":[1]},{\"feature\":4}]},{\"addressDestination\":[{"
                           "\"device\":\"d:EEBusTestClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":185},{"
                           "\"msgCounterReference\":28},{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
                           "\"deviceDiagnosisServiceData\":[]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_TRUE(datagram.parsePayload());

    keo_datagram::Header replyHeader(datagram.getHeader());
    replyHeader.changeToResponse(CmdClassifier::Value::REPLY);
    keo_datagram::Cmd replyCmd = datagram.getCmd();
    Datagram datagramReply(replyHeader, replyCmd);
    std::string jsonString = datagramReply.toJson();
    ASSERT_TRUE(datagramReply.isHeaderValid());
    ASSERT_TRUE(datagramReply.isReply());
    ASSERT_TRUE(datagram.isHeaderValid());
}

TEST(DatagramJsonTest, emptyClassTest)
{
    std::string jsonIn = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                         "\"device\":\"d:SHIP_test_1\"},{\"entity\":[1]},{\"feature\":4}]},{\"addressDestination\":[{"
                         "\"device\":\"d:EEBusTestClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":185},{"
                         "\"msgCounterReference\":28},{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
                         "\"deviceDiagnosisServiceData\":[]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(jsonIn);
    ASSERT_TRUE(datagram.isHeaderValid());
    ASSERT_TRUE(datagram.parsePayload());
    ASSERT_TRUE(datagram.isPayloadValid());
    std::string jsonOut = datagram.toJson();
    removeWhiteSpaces(jsonOut);
    removeWhiteSpaces(jsonIn);
    ASSERT_EQ(jsonIn, jsonOut);
}

TEST(DatagramJsonTest, justHeaderParsingTest)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:SHIP_test_2\"},{\"entity\":[1]},{\"feature\":4}]},{\"addressDestination\":[{"
                           "\"device\":\"d:EEBusTestClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":79},{"
                           "\"msgCounterReference\":80},{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
                           "\"hvacSystemFunctionSetpointRelationListData\":[{"
                           "\"hvacSystemFunctionSetpointRelationData\":[]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_TRUE(datagram.isHeaderValid());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(jsonString, testJson);
}

TEST(DatagramJsonTest, additionalListTest)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:SHIP_test_2\"},{\"entity\":[1]},{\"feature\":4}]},{\"addressDestination\":[{"
                           "\"device\":\"d:EEBusTestClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":79},{"
                           "\"msgCounterReference\":80},{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
                           "\"hvacSystemFunctionSetpointRelationListData\":[{"
                           "\"hvacSystemFunctionSetpointRelationData\":[]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_TRUE(datagram.isHeaderValid());
    datagram.parsePayloadThrows();
    ASSERT_TRUE(datagram.isPayloadValid());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(jsonString, testJson);
}

TEST(DatagramJsonTest, valueTest)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
          "\"device\":\"d:server_08_00_27_a7_1e_b9\"},{\"entity\":[1]},{\"feature\":1}]},{"
          "\"addressDestination\":[{\"device\":\"d:client1_eclipse\"},{\"entity\":[1]},{\"feature\":1}"
          "]},{\"msgCounter\":233},{\"msgCounterReference\":9},{\"cmdClassifier\":\"reply\"}]},{"
          "\"payload\":[{\"cmd\":[[{\"measurementListData\":[{\"measurementData\":[[{\"measurementId\":1},{\"value\":[{"
          "\"number\":5800},{\"scale\":-2}]}]]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.parsePayload());

    std::string actualJson = datagram.toJson();
    removeWhiteSpaces(actualJson);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(testJson, actualJson);
}

TEST(DatagramJsonTest, bb)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[ {\"specificationVersion\":\"1.0.0\"}, {\"addressSource\":[ {\"entity\":[0]}, "
          "{\"feature\":0} ]}, {\"addressDestination\":[ {\"device\":\"d:hlemClient\"}, {\"entity\":[0]}, "
          "{\"feature\":0} ]}, {\"msgCounter\":12}, {\"msgCounterReference\":2}, {\"cmdClassifier\":\"reply\"} "
          "]},{\"payload\":[{\"cmd\":[[{\"nodeManagementDetailedDiscoveryData\": "
          "[{\"specificationVersionList\":[{\"specificationVersion\":[\"1.0.0\" ]} "
          "]},{\"deviceInformation\":[{\"description\":[{\"deviceAddress\":[{\"device\":\"d:MieleWasher\"} "
          "]},{\"deviceType\":\"Washer\"},{\"networkFeatureSet\":\"simple\"} ]} "
          "]},{\"entityInformation\":[[{\"description\":[{\"entityAddress\":[ {\"entity\":[0]} "
          "]},{\"entityType\":\"DeviceInformation\"} ]} ],[{\"description\":[{\"entityAddress\":[ {\"entity\":[1]} "
          "]},{\"entityType\":\"Washer\"} ]} ] ]},{\"featureInformation\":[[{\"description\":[{\"featureAddress\":[ "
          "{\"entity\":[0]}, {\"feature\":0} "
          "]},{\"featureType\":\"NodeManagement\"},{\"role\":\"special\"},{\"supportedFunction\":[[{\"function\":"
          "\"nodeManagementDetailedDiscoveryData\"},{\"possibleOperations\":[{\"read\":[]}]} ] ]} ]} "
          "],[{\"description\":[{\"featureAddress\":[ {\"entity\":[0]}, {\"feature\":1} "
          "]},{\"featureType\":\"DeviceClassification\"},{\"role\":\"server\"},{\"supportedFunction\":[[{\"function\":"
          "\"deviceClassificationManufacturerData\"},{\"possibleOperations\":[{\"read\":[]}]} ] ]} ]} "
          "],[{\"description\":[{\"featureAddress\":[ {\"entity\":[1]}, {\"feature\":1} "
          "]},{\"featureType\":\"SmartEnergyManagementPs\"},{\"role\":\"server\"},{\"supportedFunction\":[[{"
          "\"function\":\"smartEnergyManagementPsData\"},{\"possibleOperations\":[{\"write\":[]}]} ] ]} ]} ] ]} ]} "
          "]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(jsonString, testJson);
}

TEST(DatagramJsonTest, parseFilters)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[ {\"specificationVersion\":\"1.0.0\"}, {\"addressSource\":[ "
          "{\"device\":\"d:MieleWasher\"}, {\"entity\":[1]}, {\"feature\":1} ]}, {\"addressDestination\":[ "
          "{\"device\":\"d:hlemClient\"}, {\"entity\":[1]}, {\"feature\":1} ]}, {\"msgCounter\":43}, "
          "{\"cmdClassifier\":\"notify\"} ]},{\"payload\":[{\"cmd\":[[{\"function\": "
          "\"smartEnergyManagementPsData\"},{\"filter\":[[ "
          "{\"smartEnergyManagementPsDataSelectors\":[{\"powerSequenceDescription\":[{\"sequenceId\":23} ]} "
          "]},{\"smartEnergyManagementPsDataElements\":[{\"alternatives\":[{\"powerSequence\":[{\"state\":[{\"state\":["
          "]},{\"activeSlotNumber\":[]},{\"elapsedSlotTime\": []},{\"remainingSlotTime\":[]} ]} ]} ]} "
          "]}]]},{\"smartEnergyManagementPsData\" : [{\"alternatives\":[[{\"powerSequence\": "
          "[[{\"description\":[{\"sequenceId\":23} ]},{\"state\":[{\"state\":\"completed\"} ]} ] ]} ] ]} ]} ]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.parsePayload());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(testJson, jsonString);
}

TEST(DatagramJsonTest, smartEnergyManagementPs)
{
    // filter
    Filter cmdFilterType;
    {

        // smartEnergyManagementPsDataSelectors
        SmartEnergyManagementPsDataSelectorsPtr smartEnergyManagementPsDataSelectorsPtr;
        smartEnergyManagementPsDataSelectorsPtr
            = SmartEnergyManagementPsDataSelectorsPtr(new SmartEnergyManagementPsDataSelectors);

        // powerSequenceDescription
        PowerSequenceDescriptionListDataSelectors powerSequenceDescriptionListDataSelectors;
        powerSequenceDescriptionListDataSelectors.setSequenceId(1);

        smartEnergyManagementPsDataSelectorsPtr->setPowerSequenceDescription(powerSequenceDescriptionListDataSelectors);

        // smartEnergyManagementPsDataElements
        SmartEnergyManagementPsDataElementsPtr smartEnergyManagementPsDataElementsPtr;
        smartEnergyManagementPsDataElementsPtr
            = SmartEnergyManagementPsDataElementsPtr(new SmartEnergyManagementPsDataElements);

        // alternatives
        SmartEnergyManagementPsAlternativesElements smartEnergyManagementPsAlternativesElements;

        // powerSequence
        SmartEnergyManagementPsPowerSequenceElements smartEnergyManagementPsPowerSequenceElements;

        // state
        PowerSequenceStateDataElements powerSequenceStateDataElements;
        powerSequenceStateDataElements.setState();
        powerSequenceStateDataElements.setActiveSlotNumber();
        powerSequenceStateDataElements.setElapsedSlotTime();
        powerSequenceStateDataElements.setRemainingSlotTime();

        smartEnergyManagementPsPowerSequenceElements.setState(powerSequenceStateDataElements);
        smartEnergyManagementPsAlternativesElements.setPowerSequence(smartEnergyManagementPsPowerSequenceElements);
        smartEnergyManagementPsDataElementsPtr->setAlternatives(smartEnergyManagementPsAlternativesElements);

        cmdFilterType.setDataElements(smartEnergyManagementPsDataElementsPtr);

        cmdFilterType.setDataSelectors({ smartEnergyManagementPsDataSelectorsPtr });
    }

    // smartEnergyManagementPsData
    SmartEnergyManagementPsDataPtr pData;
    {
        pData = SmartEnergyManagementPsDataPtr(new (SmartEnergyManagementPsData));
        SmartEnergyManagementPsAlternatives smartEnergyManagementPsAlternatives;

        SmartEnergyManagementPsPowerSequence smartEnergyManagementPsPowerSequence;
        PowerSequenceDescriptionData powerSequenceDescriptionData;
        powerSequenceDescriptionData.setSequenceId(1);
        smartEnergyManagementPsPowerSequence.setDescription(powerSequenceDescriptionData);
        PowerSequenceStateData powerSequenceStateData;

        powerSequenceStateData.setState(PowerSequenceState(PowerSequenceState::Value::COMPLETED));
        smartEnergyManagementPsPowerSequence.setState(powerSequenceStateData);

        std::vector<SmartEnergyManagementPsPowerSequence> smartEnergyManagementPsPowerSequenceVector;
        smartEnergyManagementPsPowerSequenceVector.push_back(smartEnergyManagementPsPowerSequence);
        smartEnergyManagementPsAlternatives.setPowerSequence(smartEnergyManagementPsPowerSequenceVector);

        std::vector<SmartEnergyManagementPsAlternatives> SmartEnergyManagementPsAlternativesVector;
        SmartEnergyManagementPsAlternativesVector.push_back(smartEnergyManagementPsAlternatives);
        pData->setAlternatives(SmartEnergyManagementPsAlternativesVector);
    }

    Cmd cmd;
    cmd.setFunction(Function::Value::SMART_ENERGY_MANAGEMENT_PS_DATA);
    cmd.setFilter({ cmdFilterType });
    cmd.setCmdData(pData);

    Header header = Header(FeatureAddress("e", 0, 0), FeatureAddress("f", 2, 3), CmdClassifier::Value::NOTIFY);

    Datagram programmaticDatagram;
    programmaticDatagram.setCmd(cmd);
    programmaticDatagram.setHeader(header);
    std::string jsonStringOne = programmaticDatagram.toJson();
    Datagram datagramFromJson = Datagram::fromJsonThrows(jsonStringOne);
    ASSERT_FALSE(datagramFromJson.isEmpty());
    std::string jsonStringTwo = datagramFromJson.toJson();
    removeWhiteSpaces(jsonStringOne);
    removeWhiteSpaces(jsonStringTwo);
    ASSERT_EQ(jsonStringOne, jsonStringTwo);
}

TEST(DatagramJsonTest, CreateDatagramProgramatically)
{
    FeatureAddress destination = FeatureAddress("d:N1", 2, 3);
    FeatureAddress sourceAddress = FeatureAddress("d:N2", 5, 6);
    Header header = Header(sourceAddress, destination, CmdClassifier::Value::READ);
    Datagram datagram(header, Cmd(CmdData::Type::ACTUATOR_SWITCH_DATA_TYPE));
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.isHeaderValid());
    ASSERT_TRUE(datagram.isPayloadValid());
}

TEST(DatagramJsonTest, bshStuff)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:"
          "myFancyEEBusDevice\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:"
          "myOtherFancyEEBusDevice\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":12},{\"msgCounterReference\":"
          "2},{\"cmdClassifier\":\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"nodeManagementDetailedDiscoveryData\":[{"
          "\"specificationVersionList\":[{\"specificationVersion\":[\"1.0.0\"]}]},{\"deviceInformation\":[{"
          "\"description\":[{\"deviceAddress\":[{\"device\":\"d:myFancyEEBusDevice\"}]},{\"deviceType\":"
          "\"HVACController\"},{\"networkFeatureSet\":\"smart\"}]}]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(testJson, jsonString);
}

TEST(DatagramJsonTest, partialCmd)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
          "\"device\":\"d:myFancyEEBusDevice\"},{\"entity\":[1]},{\"feature\":0}]},{"
          "\"addressDestination\":[{\"device\":\"d:myOtherFancyEEBusDevice\"},{\"entity\":[2,1,1]},{"
          "\"feature\":4}]},{\"msgCounter\":12},{\"cmdClassifier\":\"write\"}]},{\"payload\":[{"
          "\"cmd\":[[{\"function\":\"hvacSystemFunctionListData\"},{\"filter\":[[{\"filterId\":1},{\"cmdControl\":[{"
          "\"partial\":[]}]}]]},{\"hvacSystemFunctionListData\":[{\"hvacSystemFunctionData\":[[{"
          "\"systemFunctionId\":1},{\"currentOperationModeId\":1}]]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.parsePayload());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(testJson, jsonString);
}

TEST(DatagramJsonTest, emptyArray)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:N1\"},{\"entity\":[2]},{\"feature\":3}]},{\"addressDestination\":[{"
                           "\"device\":\"d:N2\"},{\"entity\":[3]},{\"feature\":4}]},{\"msgCounter\":6},{"
                           "\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{\"actuatorSwitchData\":[]},{"
                           "\"manufacturerSpecificExtension\":\"abcdef\"},{\"lastUpdateAt\":\"2016-02-29T6:31:22.33Z\"}"
                           "]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(jsonString, testJson);
}

TEST(DatagramJsonTest, bshCmd)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:N1\"},{\"entity\":[2]},{\"feature\":3}]},{\"addressDestination\":[{"
                           "\"device\":\"d:N2\"},{\"entity\":[3]},{\"feature\":4}]},{\"msgCounter\":5},{"
                           "\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{\"actuatorSwitchData\":[]},{"
                           "\"manufacturerSpecificExtension\":\"abcdef\"},{\"lastUpdateAt\":\"2016-02-29T06:31:22."
                           "033Z\"}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.parsePayload());
    ASSERT_EQ(datagram.getCmd().getManufacturerSpecificExtension().toString(), "abcdef");
    ASSERT_EQ(datagram.getCmd().getLastUpdateAt().toString(), "2016-02-29T06:31:22.033Z");
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(jsonString, testJson);
}

TEST(DatagramJsonTest, bshCmdList)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"SHIP_DEVICE_001\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":"
                           "[{\"device\":\"SHIP_CLIENT_002\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":6},{"
                           "\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{\"actuatorSwitchData\":[]}],[{"
                           "\"actuatorSwitchData\":[]},{\"manufacturerSpecificExtension\":\"abcdef\"},{"
                           "\"lastUpdateAt\":\"2016-02-29T6:31:22.33Z\"}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(jsonString, testJson);
}

TEST(DatagramJsonTest, detailedDiscoveryRead)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"entity\":[0]},{\"feature\":0}"
                           "]},{\"msgCounter\":2},{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
                           "\"nodeManagementDetailedDiscoveryData\":[]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(jsonString, testJson);
}

TEST(DatagramJsonTest, detailedDiscoveryReply)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:"
          "exampleServer\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:"
          "exampleClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":25},{\"msgCounterReference\":2},{"
          "\"cmdClassifier\":\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"nodeManagementDetailedDiscoveryData\":[{"
          "\"specificationVersionList\":[{\"specificationVersion\":[\"1.0.0\"]}]},{\"deviceInformation\":[{"
          "\"description\":[{\"deviceAddress\":[{\"device\":\"d:myFancyEEBusDevice\"}]},{\"deviceType\":"
          "\"HVACController\"},{\"networkFeatureSet\":\"smart\"}]}]},{\"entityInformation\":[[{\"description\":[{"
          "\"entityAddress\":[{\"entity\":[0]}]},{\"entityType\":\"DeviceInformation\"}]}],[{\"description\":[{"
          "\"entityAddress\":[{\"entity\":[1]}]},{\"entityType\":\"HVACController\"}]}]]},{\"featureInformation\":[[{"
          "\"description\":[{\"featureAddress\":[{\"entity\":[0]},{\"feature\":0}]},{\"featureType\":"
          "\"NodeManagement\"},{\"role\":\"special\"},{\"supportedFunction\":[[{\"function\":"
          "\"nodeManagementDetailedDiscoveryData\"},{\"possibleOperations\":[{\"read\":[]}]}],[{\"function\":"
          "\"nodeManagementDestinationListData\"},{\"possibleOperations\":[{\"read\":[]}]}]]}]}],[{\"description\":[{"
          "\"featureAddress\":[{\"entity\":[0]},{\"feature\":1}]},{\"featureType\":\"DeviceClassification\"},{\"role\":"
          "\"server\"},{\"supportedFunction\":[[{\"function\":\"deviceClassificationManufacturerData\"},{"
          "\"possibleOperations\":[{\"read\":[]}]}]]}]}],[{\"description\":[{\"featureAddress\":[{\"entity\":[1]},{"
          "\"feature\":3}]},{\"featureType\":\"HVAC\"},{\"specificUsage\":[\"Overrun\"]},{\"role\":\"server\"},{"
          "\"supportedFunction\":[[{\"function\":\"hvacOverrunDescriptionListData\"},{\"possibleOperations\":[{"
          "\"read\":[]}]}],[{\"function\":\"hvacOverrunListData\"},{\"possibleOperations\":[{\"read\":[{\"partial\":[]}"
          "]}]}]]}]}],[{\"description\":[{\"featureAddress\":[{\"entity\":[1]},{\"feature\":4}]},{\"featureType\":"
          "\"DeviceDiagnosis\"},{\"role\":\"server\"},{\"supportedFunction\":[[{\"function\":"
          "\"deviceDiagnosisStateData\"},{\"possibleOperations\":[{\"read\":[]}]}]]}]}]]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(jsonString, testJson);
}

TEST(DatagramJsonTest, hvacSystemFunctionOperationModeRelationListData)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:2\"},{\"entity\":[2,1,1]},{\"feature\":4}]},{\"addressDestination\":[{"
                           "\"device\":\"d:SHM\"},{\"entity\":[1]},{\"feature\":1}]},{\"msgCounter\":21},{"
                           "\"msgCounterReference\":14},{\"cmdClassifier\":\"reply\"}]},{\"payload\":[{\"cmd\":[[{"
                           "\"hvacSystemFunctionOperationModeRelationListData\":[{"
                           "\"hvacSystemFunctionOperationModeRelationData\":[[{\"systemFunctionId\":1},{"
                           "\"operationModeId\":[1,2]}]]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(jsonString, testJson);
}
TEST(DatagramJsonTest, toJSon)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[ {\"specificationVersion\":\"1.0.0\"}, {\"addressSource\":[ {\"entity\":[0]}, "
          "{\"feature\":0} ]}, {\"addressDestination\":[ {\"device\":\"d:SHIP_42332_1\"}, {\"entity\":[0]}, "
          "{\"feature\":0} ]}, {\"msgCounter\":5}, {\"msgCounterReference\":2}, {\"cmdClassifier\":\"reply\"} "
          "]},{\"payload\":[{\"cmd\":[[{\"nodeManagementDetailedDiscoveryData\": "
          "[{\"specificationVersionList\":[{\"specificationVersion\":[\"1.0.0\"]}]},{\"deviceInformation\":[{"
          "\"description\":[{\"deviceAddress\":[{\"device\":\"d:QClient\"} "
          "]},{\"deviceType\":\"HVACClient\"},{\"networkFeatureSet\":\"smart\"},{\"label\":\"HVACClient "
          "(Device)\"},{\"description\":\"HVAC client (Device)\"} ]} "
          "]},{\"entityInformation\":[[{\"description\":[{\"entityAddress\":[ {\"entity\":[0]} "
          "]},{\"entityType\":\"DeviceInformation\"} ]} "
          "]]},{\"featureInformation\":[[{\"description\":[{\"featureAddress\":[ {\"entity\":[0]}, {\"feature\":0} "
          "]},{\"featureType\":\"NodeManagement\"},{\"role\":\"special\"} ]} ]]} ]} ]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    std::string jsonString = datagram.toJson();
    removeWhiteSpaces(jsonString);
    removeWhiteSpaces(testJson);
    ASSERT_EQ(jsonString, testJson);
}

TEST(DatagramJsonTest, FullCmd)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:N1\"},{\"entity\":[2]},{\"feature\":3}]},{\"addressDestination\":[{"
                           "\"device\":\"d:N2\"},{\"entity\":[3]},{\"feature\":4}]},{\"msgCounter\":3},{"
                           "\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{\"actuatorSwitchData\":[]},{"
                           "\"manufacturerSpecificExtension\":\"abcdef\"},{\"lastUpdateAt\":\"2016-02-29T6:31:22.33Z\"}"
                           "]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.parsePayload());
    ASSERT_EQ(datagram.getCmd().getManufacturerSpecificExtension().toString(), "abcdef");
    ASSERT_EQ(datagram.getCmd().getLastUpdateAt().toString(), "2016-02-29T06:31:22.033Z");
}

TEST(DatagramJsonTest, ProgramaticallyCreateThenDeserializeThenSerialize)
{
    Header header = Header(FeatureAddress("d:N1", 2, 3), FeatureAddress("d:N2", 3, 4));
    header.setCmdClassifier(CmdClassifier::Value::REPLY);
    TimeDistributorDataPtr timeDistributorData = TimeDistributorDataPtr(new TimeDistributorData(false, 3));
    Cmd cmd = Cmd(timeDistributorData);
    Datagram pDatagram(header, cmd);
    ASSERT_TRUE(pDatagram.isHeaderValid());
    ASSERT_TRUE(pDatagram.isPayloadValid());
    std::string jsonString = pDatagram.toJson();
    ASSERT_FALSE(jsonString.empty());
    Datagram datagram = Datagram::fromJsonThrows(jsonString);
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.parsePayload());
    std::string jsonStringAgain = datagram.toJson();
    ASSERT_EQ(jsonString, jsonStringAgain);
}

TEST(DatagramJsonTest, AckResult)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:N1\"},{\"entity\":[2]},{\"feature\":3}]},{\"addressDestination\":[{"
                           "\"device\":\"d:N2\"},{\"entity\":[3]},{\"feature\":4}]},{\"msgCounter\":3},{"
                           "\"cmdClassifier\":\"read\"},{\"ackRequest\":true}]},{\"payload\":[{\"cmd\":[[{"
                           "\"actuatorSwitchData\":[]},{\"manufacturerSpecificExtension\":\"abcdef\"},{"
                           "\"lastUpdateAt\":\"2016-02-29T06:31:22.033Z\"}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.parsePayload());
    std::string jsonStringAgain = datagram.toJson();
    removeWhiteSpaces(jsonStringAgain);
    ASSERT_EQ(testJson, jsonStringAgain);
}

TEST(DatagramJsonTest, NotJson)
{
    std::string testJson = "Dies ist ein Test";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, simpleArray)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:_i:"
          "42332_3\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:_i:4711_Tester_1\"},{"
          "\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":43},{\"msgCounterReference\":9},{\"cmdClassifier\":"
          "\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"nodeManagementDetailedDiscoveryData\":[{"
          "\"specificationVersionList\":[{\"specificationVersion\":[\"1.0.0\"]}]},{\"deviceInformation\":[{"
          "\"description\":[{\"deviceAddress\":[{\"device\":\"d:_i:42332_3\"}]},{\"deviceType\":\"HeatSinkSystem\"},{"
          "\"networkFeatureSet\":\"gateway\"},{\"lastStateChange\":\"added\"}]}]},{\"entityInformation\":[[{"
          "\"description\":[{\"entityAddress\":[{\"entity\":[0]}]},{\"entityType\":\"DeviceInformation\"}]}],[{"
          "\"description\":[{\"entityAddress\":[{\"entity\":[1]}]},{\"entityType\":\"DHWCircuit\"}]}],[{"
          "\"description\":[{\"entityAddress\":[{\"entity\":[2]}]},{\"entityType\":\"HeatingCircuit\"}]}],[{"
          "\"description\":[{\"entityAddress\":[{\"entity\":[2,1]}]},{\"entityType\":\"HeatingZone\"}]}],[{"
          "\"description\":[{\"entityAddress\":[{\"entity\":[2,1,2]}]},{\"entityType\":\"HVACRoom\"}]}]]},{"
          "\"featureInformation\":[[{\"description\":[{\"featureAddress\":[{\"device\":\"d:_i:42332_3\"},{\"entity\":["
          "0]},{\"feature\":0}]},{\"featureType\":\"NodeManagement\"},{\"role\":\"special\"},{\"supportedFunction\":[[{"
          "\"function\":\"nodeManagementDetailedDiscoveryData\"},{\"possibleOperations\":[{\"read\":[{\"partial\":[]}]}"
          "]}],[{\"function\":\"nodeManagementDestinationListData\"},{\"possibleOperations\":[{\"read\":[{\"partial\":["
          "]}]}]}],[{\"function\":\"subscriptionManagementEntryListData\"},{\"possibleOperations\":[{\"read\":[{"
          "\"partial\":[]}]}]}],[{\"function\":\"bindingManagementEntryListData\"},{\"possibleOperations\":[{\"read\":["
          "{\"partial\":[]}]}]}],[{\"function\":\"nodeManagementSubscriptionRequestCall\"},{\"possibleOperations\":[]}]"
          ",[{\"function\":\"nodeManagementSubscriptionDeleteCall\"},{\"possibleOperations\":[]}],[{\"function\":"
          "\"nodeManagementBindingRequestCall\"},{\"possibleOperations\":[]}],[{\"function\":"
          "\"nodeManagementBindingDeleteCall\"},{\"possibleOperations\":[]}]]},{\"description\":\"d:_i:42332_3\"}]}],[{"
          "\"description\":[{\"featureAddress\":[{\"device\":\"d:_i:42332_3\"},{\"entity\":[0]},{\"feature\":1}]},{"
          "\"featureType\":\"DeviceClassification\"},{\"role\":\"server\"},{\"supportedFunction\":[[{\"function\":"
          "\"deviceClassificationManufacturerData\"},{\"possibleOperations\":[{\"read\":[]}]}]]}]}],[{\"description\":["
          "{\"featureAddress\":[{\"device\":\"d:_i:42332_3\"},{\"entity\":[1]},{\"feature\":1}]},{\"featureType\":"
          "\"DeviceClassification\"},{\"role\":\"server\"},{\"supportedFunction\":[[{\"function\":"
          "\"deviceClassificationManufacturerData\"},{\"possibleOperations\":[{\"read\":[]}]}]]}]}],[{\"description\":["
          "{\"featureAddress\":[{\"device\":\"d:_i:42332_3\"},{\"entity\":[1]},{\"feature\":2}]},{\"featureType\":"
          "\"Measurement\"},{\"specificUsage\":[\"Temperature\"]},{\"role\":\"server\"},{\"supportedFunction\":[[{"
          "\"function\":\"measurementDescriptionListData\"},{\"possibleOperations\":[{\"read\":[]}]}],[{\"function\":"
          "\"measurementListData\"},{\"possibleOperations\":[{\"read\":[]}]}],[{\"function\":"
          "\"measurementConstraintsListData\"},{\"possibleOperations\":[{\"read\":[]}]}]]}]}],[{\"description\":[{"
          "\"featureAddress\":[{\"device\":\"d:_i:42332_3\"},{\"entity\":[1]},{\"feature\":3}]},{\"featureType\":"
          "\"Setpoint\"},{\"specificUsage\":[\"Temperature\"]},{\"role\":\"server\"},{\"supportedFunction\":[[{"
          "\"function\":\"setpointDescriptionListData\"},{\"possibleOperations\":[{\"read\":[{\"partial\":[]}]},{"
          "\"write\":[{\"partial\":[]}]}]}],[{\"function\":\"setpointListData\"},{\"possibleOperations\":[]}],[{"
          "\"function\":\"setpointConstraintsListData\"},{\"possibleOperations\":[{\"read\":[{\"partial\":[]}]},{"
          "\"write\":[{\"partial\":[]}]}]}]]}]}],[{\"description\":[{\"featureAddress\":[{\"device\":\"d:_i:42332_3\"},"
          "{\"entity\":[1]},{\"feature\":4}]},{\"featureType\":\"HVAC\"},{\"specificUsage\":[\"OperationMode\","
          "\"Overrun\"]},{\"role\":\"server\"},{\"supportedFunction\":[[{\"function\":"
          "\"hvacSystemFunctionDescriptionListData\"},{\"possibleOperations\":[{\"read\":[{\"partial\":[]}]},{"
          "\"write\":[{\"partial\":[]}]}]}],[{\"function\":\"hvacSystemFunctionOperationModeRelationListData\"},{"
          "\"possibleOperations\":[{\"read\":[{\"partial\":[]}]},{\"write\":[{\"partial\":[]}]}]}],[{\"function\":"
          "\"hvacSystemFunctionSetpointRelationListData\"},{\"possibleOperations\":[{\"read\":[{\"partial\":[]}]},{"
          "\"write\":[{\"partial\":[]}]}]}],[{\"function\":\"hvacSystemFunctionListData\"},{\"possibleOperations\":[]}]"
          ",[{\"function\":\"hvacOperationModeDescriptionListData\"},{\"possibleOperations\":[{\"read\":[{\"partial\":["
          "]}]},{\"write\":[{\"partial\":[]}]}]}],[{\"function\":\"hvacOverrunDescriptionListData\"},{"
          "\"possibleOperations\":[{\"read\":[{\"partial\":[]}]},{\"write\":[{\"partial\":[]}]}]}],[{\"function\":"
          "\"hvacOverrunListData\"},{\"possibleOperations\":[{\"read\":[{\"partial\":[]}]},{\"write\":[{\"partial\":[]}"
          "]}]}]]}]}]]}]}]]}]}]}";
    // index 3356
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.parsePayload());
    std::string jsonStringAgain = datagram.toJson();
    removeWhiteSpaces(jsonStringAgain);
    ASSERT_EQ(testJson, jsonStringAgain);
}

TEST(DatagramJsonTest, complexNotify)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:_n:"
          "DEVICE_SOURCE\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:_n:DEVICE_"
          "DESTINATION\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":6},{\"cmdClassifier\":\"notify\"}]},{"
          "\"payload\":[{\"cmd\":[[{\"function\":\"nodeManagementDestinationListData\"},{\"filter\":[[{\"cmdControl\":["
          "{\"delete\":[]}]},{\"nodeManagementDestinationListDataSelectors\":[{\"deviceDescription\":[{"
          "\"deviceAddress\":[{\"device\":\"d:_n:DEVICE_REMOVED\"}]}]}]}],[{\"cmdControl\":[{\"partial\":[]}]}]]},{"
          "\"nodeManagementDestinationListData\":[{\"nodeManagementDestinationData\":[[{\"deviceDescription\":[{"
          "\"deviceAddress\":[{\"device\":\"d:_n:DEVICE_MODIFIED\"}]},{\"lastStateChange\":\"modified\"}]}],[{"
          "\"deviceDescription\":[{\"deviceAddress\":[{\"device\":\"d:_n:DEVICE_ADDED\"}]},{\"networkFeatureSet\":"
          "\"simple\"},{\"lastStateChange\":\"added\"}]}]]}]}]]}]}]}";
    // index 3356
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.parsePayload());
    std::string jsonStringAgain = datagram.toJson();
    removeWhiteSpaces(jsonStringAgain);
    ASSERT_EQ(testJson, jsonStringAgain);
}

TEST(DatagramJsonTest, utf8Test)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:"
          "myFancyEEBusDevice\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:"
          "myOtherFancyEEBusDevice\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":12},{\"msgCounterReference\":"
          "2},{\"cmdClassifier\":\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"actuatorSwitchDescriptionData\":[{"
          "\"label\":\"ShortLabel\xE0\xA4\xAE\xE0\xA4\xB9\xE0\xA4\xB8\xE0\xA5\x81\xE0\xA4\xB8UTF8\"},{\"description\":"
          "\"ShortLabel\xE0\xA4\xAE\xE0\xA4\xB9\xE0\xA4\xB8\xE0\xA5\x81\xE0\xA4\xB8UTF8\"}]}]]}]}]}";
    Datagram datagram = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(datagram.isEmpty());
    ASSERT_TRUE(datagram.parsePayload());
    std::string jsonStringAgain = datagram.toJson();
    removeWhiteSpaces(jsonStringAgain);
    ASSERT_EQ(testJson, jsonStringAgain);
}

TEST(DatagramJsonTest, copyConstructorParsedPayload)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:"
          "myFancyEEBusDevice\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:"
          "myOtherFancyEEBusDevice\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":12},{\"msgCounterReference\":"
          "2},{\"cmdClassifier\":\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"actuatorSwitchDescriptionData\":[{"
          "\"label\":\"ShortLabel\xE0\xA4\xAE\xE0\xA4\xB9\xE0\xA4\xB8\xE0\xA5\x81\xE0\xA4\xB8UTF8\"},{\"description\":"
          "\"ShortLabel\xE0\xA4\xAE\xE0\xA4\xB9\xE0\xA4\xB8\xE0\xA5\x81\xE0\xA4\xB8UTF8\"}]}]]}]}]}";

    Datagram datagram = Datagram::fromJsonThrows(testJson);
    datagram.parsePayloadThrows();
    Datagram copy(datagram);

    std::string jsonDatagram = datagram.toJson();
    std::string jsonCopy = copy.toJson();

    ASSERT_EQ(jsonDatagram, jsonCopy);
}

TEST(DatagramJsonTest, copyConstructorUnparsedPayload)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:"
          "myFancyEEBusDevice\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:"
          "myOtherFancyEEBusDevice\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":12},{\"msgCounterReference\":"
          "2},{\"cmdClassifier\":\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"actuatorSwitchDescriptionData\":[{"
          "\"label\":\"ShortLabel\xE0\xA4\xAE\xE0\xA4\xB9\xE0\xA4\xB8\xE0\xA5\x81\xE0\xA4\xB8UTF8\"},{\"description\":"
          "\"ShortLabel\xE0\xA4\xAE\xE0\xA4\xB9\xE0\xA4\xB8\xE0\xA5\x81\xE0\xA4\xB8UTF8\"}]}]]}]}]}";

    Datagram datagram = Datagram::fromJsonThrows(testJson);
    Datagram copy(datagram);

    std::string jsonDatagram = datagram.toJson();
    std::string jsonCopy = copy.toJson();

    ASSERT_EQ(jsonDatagram, jsonCopy);
}

TEST(DatagramJsonTest, copyConstructorUnparsedPayloadParseSource)
{
    std::string testJson
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:"
          "myFancyEEBusDevice\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:"
          "myOtherFancyEEBusDevice\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":12},{\"msgCounterReference\":"
          "2},{\"cmdClassifier\":\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"actuatorSwitchDescriptionData\":[{"
          "\"label\":\"label\"},{\"description\":"
          "\"desc\"}]}]]}]}]}";
    Datagram source = Datagram::fromJsonThrows(testJson);
    Datagram copy(source);

    ASSERT_TRUE(source.parsePayload()); // this clears the unparsed payload in the source
    ASSERT_TRUE(copy.parsePayload()); // this fails when they both use the same unparsed payload ptr
    ASSERT_EQ(source.toJson(), copy.toJson());
}

TEST(DatagramJsonTest, EmptyDatagram)
{
    std::string testJson = "{\"datagram\":[]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, NoDatagram)
{
    std::string testJson = "{\"hi\":[]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, NoPayload)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_n:systemtest_node_2\"},{\"entity\":[1]},{\"feature\":1}]},{"
                           "\"addressDestination\":[{\"device\":\"d:_n:systemtest_node_1\"},{\"entity\":[1]},{"
                           "\"feature\":1}]},{\"msgCounter\":-12},{\"cmdClassifier\":"
                           "\"reply\"}]}]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, failToReadEmptyAbsoluteTime)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_n:systemtest_node_2\"},{\"entity\":[1]},{\"feature\":1}]},{"
                           "\"addressDestination\":[{\"device\":\"d:_n:systemtest_node_1\"},{\"entity\":[1]},{"
                           "\"feature\":1}]},{\"msgCounter\":12},{\"msgCounterReference\":6},{\"cmdClassifier\":"
                           "\"reply\"},{\"timestamp\":\"\"}]},{\"payload\":[{\"cmd\":[[{\"measurementListData\":[{"
                           "\"measurementData\":[[{"
                           "\"value\":[{\"number\":-42000000000000},{\"scale\":-12}]}]]}]}]]}]}]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, failOnMissingMsgCounter)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_n:systemtest_node_2\"},{\"entity\":[1]},{\"feature\":1}]},{"
                           "\"addressDestination\":[{\"device\":\"d:_n:systemtest_node_1\"},{\"entity\":[1]},{"
                           "\"feature\":1}]},{\"msgCounterReference\":6},{\"cmdClassifier\":"
                           "\"reply\"},{\"timestamp\":\"\"}]},{\"payload\":[{\"cmd\":[[{\"measurementListData\":[{"
                           "\"measurementData\":[[{"
                           "\"value\":[{\"number\":-42000000000000},{\"scale\":-12}]}]]}]}]]}]}]}";
    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, copyCmdDataWhenCopyingDatagram)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_n:systemtest_node_2\"},{\"entity\":[1]},{\"feature\":1}]},{"
                           "\"addressDestination\":[{\"device\":\"d:_n:systemtest_node_1\"},{\"entity\":[1]},{"
                           "\"feature\":1}]},{\"msgCounter\":12},{\"cmdClassifier\":"
                           "\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"measurementListData\":[{\"measurementData\":[[{"
                           "\"value\":[{\"number\":4200000},{\"scale\":9}]}]]}]}]]}]}]}";
    Datagram source = Datagram::fromJsonThrows(testJson);
    ASSERT_TRUE(source.parsePayload());

    Datagram copy(source);

    MeasurementListDataPtr dataSource = std::static_pointer_cast<MeasurementListData>(source.getCmdData());
    MeasurementListDataPtr dataCopy = std::static_pointer_cast<MeasurementListData>(copy.getCmdData());

    ASSERT_EQ(*(dataSource.get()), *(dataCopy.get()));
    dataSource->cleanMeasurementData();
    ASSERT_NE(*(dataSource.get()), *(dataCopy.get()));
}

TEST(DatagramJsonTest, syntacticallyCorrectJsonButIncorrectSPINE)
{
    // Element "description" in the "entityInformation" should be wrapped in another array
    std::string testJson
        = R"({"datagram":[{"header":[{"specificationVersion":"1.1.0"},{"addressSource":[{"device":"d:_i:1234_EVSE"},{"entity":[0]},{"feature":0}]},{"addressDestination":[{"device":"d:_i:47859_sempshipgw"},{"entity":[0]},{"feature":0}]},{"msgCounter":2},{"msgCounterReference":48},{"cmdClassifier":"reply"}]},{"payload":[{"cmd":[[{"nodeManagementDetailedDiscoveryData":[{"specificationVersionList":[{"specificationVersion":["1.1.0"]}]},{"deviceInformation":[{"description":[{"deviceAddress":[{"device":"d:_i:1234_EVSE"}]},{"deviceType":"Generic"},{"networkFeatureSet":"smart"},{"lastStateChange":"added"}]}]},{"entityInformation":[{"description":[{"entityAddress":[{"entity":[0]}]},{"entityType":"DeviceInformation"}]},{"description":[{"entityAddress":[{"entity":[1]}]},{"entityType":"EVSE"}]}]},{"featureInformation":[[{"description":[{"featureAddress":[{"entity":[0]},{"feature":0}]},{"featureType":"NodeManagement"},{"role":"special"},{"description":"Description of the feature"},{"supportedFunction":[[{"function":"nodeManagementSubscriptionRequestCall"},{"possibleOperations":[]}],[{"function":"nodeManagementUseCaseData"},{"possibleOperations":[{"read":[]}]}],[{"function":"nodeManagementDetailedDiscoveryData"},{"possibleOperations":[{"read":[]}]}],[{"function":"nodeManagementSubscriptionDeleteCall"},{"possibleOperations":[]}]]}]}],[{"description":[{"featureAddress":[{"entity":[0]},{"feature":1}]},{"featureType":"Generic"},{"role":"client"},{"description":"UseCase Client feature"},{"supportedFunction":[]}]}]]}]}]]}]}]})";

    Datagram d = Datagram::fromJsonThrows(testJson);
    ASSERT_THROW(d.parsePayloadThrows(), DatagramParserException);
}

TEST(DatagramJsonTest, testArrayInsteadOfObject)
{
    // Element "number" in the ScaledNumber "value" is an array instead of an object
    std::string testJson
        = R"({"datagram":[{"header":[{"specificationVersion":"1.1.0"},{"addressSource":[{"device":"d:_n:systemtest_node_2"},{"entity":[1]},{"feature":1}]},{"addressDestination":[{"device":"d:_n:systemtest_node_1"},{"entity":[1]},{"feature":1}]},{"msgCounter": 12},{"cmdClassifier":"reply"}]},{"payload":[{"cmd":[[{"measurementListData":[{"measurementData":[[{"value":[["number"],{"scale":9}]}]]}]}]]}]}]})";

    Datagram d = Datagram::fromJsonThrows(testJson);
    ASSERT_THROW(d.parsePayloadThrows(), DatagramParserException);
}

TEST(DatagramJsonTest, testObjectInsteadOfArray)
{
    // The entity part of the source address is an object instead of an array
    std::string testJson
        = R"({"datagram":[{"header":[{"specificationVersion":"1.1.0"},{"addressSource":[{"device":"d:_n:systemtest_node_2"},{"entity":{1:1}},{"feature":1}]},{"addressDestination":[{"device":"d:_n:systemtest_node_1"},{"entity":[1]},{"feature":1}]},{"msgCounter": 12},{"cmdClassifier":"reply"}]},{"payload":[{"cmd":[[{"measurementListData":[{"measurementData":[[{"value":[{"number":4200000},{"scale":9}]}]]}]}]]}]}]})";

    ASSERT_THROW(Datagram::fromJsonThrows(testJson), DatagramParserException);
}

TEST(DatagramJsonTest, testWrongOrderInCmd)
{
    // Wrong order in ScaledNumber "value"
    std::string testJson
        = R"({"datagram":[{"header":[{"specificationVersion":"1.1.0"},{"addressSource":[{"device":"d:_n:systemtest_node_2"},{"entity":[1]},{"feature":1}]},{"addressDestination":[{"device":"d:_n:systemtest_node_1"},{"entity":[1]},{"feature":1}]},{"msgCounter":12},{"cmdClassifier":"reply"}]},{"payload":[{"cmd":[[{"measurementListData":[{"measurementData":[[{"value":[{"scale":9},{"number":4200000}]}]]}]}]]}]}]})";

    Datagram d = Datagram::fromJsonThrows(testJson);
    ASSERT_THROW(d.parsePayloadThrows(), DatagramParserException);
}

TEST(DatagramJsonTest, testNoCmd1)
{
    std::string testJson
        = R"({"datagram":[{"header":[{"specificationVersion":"1.1.0"},{"addressSource":[{"device":"d:_i:1234_EVSE"},{"entity":[1,0]},{"feature":4}]},{"addressDestination":[{"device":"d:_i:36013_3000220573"},{"entity":[2]},{"feature":2}]},{"msgCounter":201},{"msgCounterReference":58},{"cmdClassifier":"reply"}]},{"payload":[{"cmd":[[]]}]}]})";

    Datagram d = Datagram::fromJsonThrows(testJson);
    ASSERT_THROW(d.parsePayloadThrows(), DatagramParserException);
}

TEST(DatagramJsonTest, testNoCmd2)
{
    std::string testJson
        = R"({"datagram":[{"header":[{"specificationVersion":"1.1.0"},{"addressSource":[{"device":"d:_i:1234_EVSE"},{"entity":[1,0]},{"feature":4}]},{"addressDestination":[{"device":"d:_i:36013_3000220573"},{"entity":[2]},{"feature":2}]},{"msgCounter":201},{"msgCounterReference":58},{"cmdClassifier":"reply"}]},{"payload":[{"cmd":[]}]}]})";

    Datagram d = Datagram::fromJsonThrows(testJson);
    ASSERT_THROW(d.parsePayloadThrows(), DatagramParserException);
}

TEST(DatagramJsonTest, testNoCmd3)
{
    std::string testJson
        = R"({"datagram":[{"header":[{"specificationVersion":"1.1.0"},{"addressSource":[{"device":"d:_i:1234_EVSE"},{"entity":[1,0]},{"feature":4}]},{"addressDestination":[{"device":"d:_i:36013_3000220573"},{"entity":[2]},{"feature":2}]},{"msgCounter":201},{"msgCounterReference":58},{"cmdClassifier":"reply"}]},{"payload":[{"cmd":[1]}]}]})";

    Datagram d = Datagram::fromJsonThrows(testJson);
    ASSERT_THROW(d.parsePayloadThrows(), DatagramParserException);
}

TEST(DatagramJsonTest, testAcceptAdditionalFieldInHeader)
{
    std::string testJson
        = R"({"datagram":[{"header":[{"specificationVersion":"1.2.0"},{"addressSource":[{"device":"d:_i:1234_EVSE"},{"entity":[0]},{"feature":0}]},{"addressDestination":[{"device":"d:_i:47859_sempshipgw"},{"entity":[0]},{"feature":0}]},{"msgCounter":2},{"msgCounterReference":1},{"cmdClassifier":"reply"},{"testCmd":"test"}]},{"payload":[{"cmd":[[{"nodeManagementDetailedDiscoveryData":[{"specificationVersionList":[{"specificationVersion":["1.1.0"]}]},{"deviceInformation":[{"description":[{"deviceAddress":[{"device":"d:_i:1234_EVSE"}]},{"deviceType":"Generic"},{"networkFeatureSet":"smart"},{"lastStateChange":"added"}]}]},{"entityInformation":[[{"description":[{"entityAddress":[{"entity":[0]}]},{"entityType":"DeviceInformation"}]}],[{"description":[{"entityAddress":[{"entity":[1]}]},{"entityType":"EVSE"}]}]]},{"featureInformation":[[{"description":[{"featureAddress":[{"entity":[0]},{"feature":0}]},{"featureType":"NodeManagement"},{"role":"special"},{"supportedFunction":[[{"function":"nodeManagementSubscriptionRequestCall"},{"possibleOperations":[]}],[{"function":"nodeManagementUseCaseData"},{"possibleOperations":[{"read":[]}]}],[{"function":"nodeManagementDetailedDiscoveryData"},{"possibleOperations":[{"read":[]}]}],[{"function":"nodeManagementSubscriptionDeleteCall"},{"possibleOperations":[]}]]},{"description":"Description of the feature"}]}],[{"description":[{"featureAddress":[{"entity":[0]},{"feature":1}]},{"featureType":"Generic"},{"role":"client"},{"supportedFunction":[]},{"description":"UseCase Client feature"}]}],[{"description":[{"featureAddress":[{"entity":[1]},{"feature":0}]},{"featureType":"DeviceDiagnosis"},{"role":"server"},{"supportedFunction":[[{"function":"deviceDiagnosisStateData"},{"possibleOperations":[{"read":[]}]}]]},{"description":"Description of the feature"}]}]]}]}]]}]}]})";

    Datagram d = Datagram::fromJsonThrows(testJson);
    ASSERT_TRUE(d.parsePayload());
}

TEST(DatagramJsonTest, testAcceptAdditionalFieldInCmd)
{
    std::string testJson
        = R"({"datagram":[{"header":[{"specificationVersion":"1.2.0"},{"addressSource":[{"device":"d:_i:1234_EVSE"},{"entity":[0]},{"feature":0}]},{"addressDestination":[{"device":"d:_i:47859_sempshipgw"},{"entity":[0]},{"feature":0}]},{"msgCounter":2},{"msgCounterReference":1},{"cmdClassifier":"reply"}]},{"payload":[{"cmd":[[{"nodeManagementDetailedDiscoveryData":[{"specificationVersionList":[{"specificationVersion":["1.1.0"]}]},{"deviceInformation":[{"description":[{"deviceAddress":[{"device":"d:_i:1234_EVSE"}]},{"deviceType":"Generic"},{"networkFeatureSet":"smart"},{"lastStateChange":"added"}]}]},{"entityInformation":[[{"description":[{"entityAddress":[{"entity":[0]}]},{"entityType":"DeviceInformation"}]}],[{"description":[{"entityAddress":[{"entity":[1]}]},{"entityType":"EVSE"}]}]]},{"featureInformation":[[{"description":[{"featureAddress":[{"entity":[0]},{"feature":0}]},{"featureType":"NodeManagement"},{"role":"special"},{"supportedFunction":[[{"function":"nodeManagementSubscriptionRequestCall"},{"possibleOperations":[]}],[{"function":"nodeManagementUseCaseData"},{"possibleOperations":[{"read":[]}]}],[{"function":"nodeManagementDetailedDiscoveryData"},{"possibleOperations":[{"read":[]}]}],[{"function":"nodeManagementSubscriptionDeleteCall"},{"possibleOperations":[]}]]},{"description":"Description of the feature"}]}],[{"description":[{"featureAddress":[{"entity":[0]},{"feature":1}]},{"featureType":"Generic"},{"role":"client"},{"supportedFunction":[]},{"description":"UseCase Client feature"}]}],[{"description":[{"featureAddress":[{"entity":[1]},{"feature":0}]},{"featureType":"DeviceDiagnosis"},{"role":"server"},{"supportedFunction":[[{"function":"deviceDiagnosisStateData"},{"possibleOperations":[{"read":[]}]}]]},{"description":"Description of the feature"},{"testCmd":"test"}]}]]}]}]]}]}]})";

    Datagram d = Datagram::fromJsonThrows(testJson);
    ASSERT_TRUE(d.parsePayload());
}

TEST(DatagramJsonTest, testRejectWrongOrderInCmd)
{
    // role and featureType and swapped in Feature 1/0
    std::string testJson
        = R"({"datagram":[{"header":[{"specificationVersion":"1.2.0"},{"addressSource":[{"device":"d:_i:1234_EVSE"},{"entity":[0]},{"feature":0}]},{"addressDestination":[{"device":"d:_i:47859_sempshipgw"},{"entity":[0]},{"feature":0}]},{"msgCounter":2},{"msgCounterReference":1},{"cmdClassifier":"reply"},{"testCmd":"test"}]},{"payload":[{"cmd":[[{"nodeManagementDetailedDiscoveryData":[{"specificationVersionList":[{"specificationVersion":["1.1.0"]}]},{"deviceInformation":[{"description":[{"deviceAddress":[{"device":"d:_i:1234_EVSE"}]},{"deviceType":"Generic"},{"networkFeatureSet":"smart"},{"lastStateChange":"added"}]}]},{"entityInformation":[[{"description":[{"entityAddress":[{"entity":[0]}]},{"entityType":"DeviceInformation"}]}],[{"description":[{"entityAddress":[{"entity":[1]}]},{"entityType":"EVSE"}]}]]},{"featureInformation":[[{"description":[{"featureAddress":[{"entity":[0]},{"feature":0}]},{"featureType":"NodeManagement"},{"role":"special"},{"supportedFunction":[[{"function":"nodeManagementSubscriptionRequestCall"},{"possibleOperations":[]}],[{"function":"nodeManagementUseCaseData"},{"possibleOperations":[{"read":[]}]}],[{"function":"nodeManagementDetailedDiscoveryData"},{"possibleOperations":[{"read":[]}]}],[{"function":"nodeManagementSubscriptionDeleteCall"},{"possibleOperations":[]}]]},{"description":"Description of the feature"}]}],[{"description":[{"featureAddress":[{"entity":[0]},{"feature":1}]},{"featureType":"Generic"},{"role":"client"},{"supportedFunction":[]},{"description":"UseCase Client feature"}]}],[{"description":[{"featureAddress":[{"entity":[1]},{"feature":0}]},{"role":"server"},{"featureType":"DeviceDiagnosis"},{"supportedFunction":[[{"function":"deviceDiagnosisStateData"},{"possibleOperations":[{"read":[]}]}]]},{"description":"Description of the feature"}]}]]}]}]]}]}]})";

    Datagram d = Datagram::fromJsonThrows(testJson);
    ASSERT_FALSE(d.parsePayload());
}

TEST(DatagramJsonTest, testMultipleSelectors)
{
    auto s1 = std::make_shared<MeasurementListDataSelectors>();
    s1->setMeasurementId(1);
    auto s2 = std::make_shared<MeasurementListDataSelectors>();
    s2->setMeasurementId(2);

    Filter filter;
    filter.setDataSelectors({ s1, s2 });

    Cmd cmd;
    cmd.setFilter({ filter });
    cmd.setCmdData(std::make_shared<MeasurementListData>());

    Header header = Header(FeatureAddress("d:N1", 2, 3), FeatureAddress("d:N2", 3, 4));
    header.setCmdClassifier(CmdClassifier::Value::REPLY);
    Datagram datagramProgrammatic(header, cmd);

    std::string datagramToJson = datagramProgrammatic.toJson();

    Datagram datagramFromJson = Datagram::fromJson(datagramToJson);
    ASSERT_TRUE(datagramFromJson.parsePayload());

    ASSERT_EQ(datagramFromJson.toJson().c_str(), datagramToJson);
}

TEST(DatagramJsonTest, testAcceptAdditionalFieldInPayload)
{
    std::string testJson = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{"
                           "\"device\":\"d:_n:systemtest_node_2\"},{\"entity\":[1]},{\"feature\":1}]},{"
                           "\"addressDestination\":[{\"device\":\"d:_n:systemtest_node_1\"},{\"entity\":[1]},{"
                           "\"feature\":1}]},{\"msgCounter\":12},{\"cmdClassifier\":"
                           "\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"measurementListData\":[{\"measurementData\":[[{"
                           "\"measurementId\":1},{\"additionalField\":0}]]}]}]]}]}]}";
    Datagram datagram = Datagram::fromJson(testJson);
    ASSERT_TRUE(datagram.parsePayload());

    auto mld = std::static_pointer_cast<const keo_datagram::MeasurementListData>(datagram.getCmdData());
    ASSERT_TRUE(mld->getMeasurementDataIsSet());
    ASSERT_EQ(1U, mld->getMeasurementData().size());
    ASSERT_TRUE(mld->getMeasurementData()[0].getMeasurementIdIsSet());
    ASSERT_EQ(1U, mld->getMeasurementData()[0].getMeasurementId());
    ASSERT_FALSE(mld->getMeasurementData()[0].getValueIsSet());
    ASSERT_FALSE(mld->getMeasurementData()[0].getEvaluationPeriodIsSet());
    ASSERT_FALSE(mld->getMeasurementData()[0].getTimestampIsSet());
    ASSERT_FALSE(mld->getMeasurementData()[0].getValueSourceIsSet());
    ASSERT_FALSE(mld->getMeasurementData()[0].getValueStateIsSet());
    ASSERT_FALSE(mld->getMeasurementData()[0].getValueTendencyIsSet());
    ASSERT_FALSE(mld->getMeasurementData()[0].getValueTypeIsSet());
}
