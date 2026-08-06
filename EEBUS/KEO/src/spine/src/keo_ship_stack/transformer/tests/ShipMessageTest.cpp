/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2014
*****************************************************************************/

#define DBG_MODUL_NAME "ShipDataTransformer Test"
#include <gtest/gtest.h>
// ASSERT_TRUE
// ASSERT_EQ

#include "ShipDataTransformer.h"

const std::string testShipMessageConst = "{\"data\":[{\"header\":[{\"protocolId\":\"ee1.0\"}]},{\"payload\":EEBUS_"
                                         "PAYLOAD_REPLACE},{\"extension\":[{\"extensionId\":\"extensionId\"},{"
                                         "\"binary\":\"12345678\"},{\"string\":\"extensionString\"}]}]}";
const std::string testSpineDatagramConst2
    = "{\"datagram\":[{\"header\":[{\"specificationVersion\":[{\"major\":1},{\"minor\":0},{\"revision\":7}]},{"
      "\"addressSource\":[{\"device\":\"d:device0\"},{\"entity\":[1]},{\"feature\":2}]},{\"addressDestination\":[{"
      "\"device\":\"d:device1\"},{\"entity\":[3]},{\"feature\":4}]},{\"datagramIdSource\":\"9339acbc-c8c7-40cc-9921-"
      "92a648bbcd76\"},{\"cmdClassifier\":\"write\"},{\"timestamp\":\"P1Y2M3DT1H10M0S\"}]},{\"payload\":[{"
      "\"payloadType\":\"cmd\"},{\"actuatorLevelData\":[{\"function\":\"absolute\"},{\"value\":0}]}]}]}";
const std::string testSpineDatagramConst
    = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"entity\":[0]},{"
      "\"feature\":0}]},{\"addressDestination\":[{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":2},{"
      "\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{\"nodeManagementDetailedDiscoveryData\":[]}]]}]}]}";
const std::string testSpineDatagramComplexConst
    = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:"
      "exampleServer\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:exampleClient\"},{"
      "\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":25},{\"msgCounterReference\":2},{\"cmdClassifier\":\"reply\"}]"
      "},{\"payload\":[{\"cmd\":[[{\"nodeManagementDetailedDiscoveryData\":[{\"specificationVersionListData\":[\"1.0."
      "0\"]},{\"deviceInformation\":[{\"deviceDescription\":[{\"deviceAddress\":\"d:myFancyEEBusDevice\"},{"
      "\"networkFeatureSet\":\"smart\"}]}]},{\"entityInformation\":[[{\"entityDescription\":[{\"entityAddress\":[{"
      "\"device\":\"\"},{\"entity\":[0]}]},{\"entityType\":\"DeviceInformation\"}]}],[{\"entityDescription\":[{"
      "\"entityAddress\":[{\"device\":\"\"},{\"entity\":[1]}]},{\"entityType\":\"MeasurementExample\"}]}]]},{"
      "\"featureInformation\":[[{\"featureDescription\":[{\"featureAddress\":[{\"entity\":[0]},{\"feature\":0}]},{"
      "\"featureType\":\"NodeManagement\"},{\"role\":\"special\"},{\"supportedFunction\":[[{\"function\":"
      "\"nodeManagementDetailedDiscoveryData\"},{\"possibleOperations\":\"readOnly\"}]]}]}],[{\"featureDescription\":[{"
      "\"featureAddress\":[{\"entity\":[0]},{\"feature\":1}]},{\"featureType\":\"DeviceClassification\"},{\"role\":"
      "\"server\"},{\"supportedFunction\":[[{\"function\":\"deviceClassificationManufacturerData\"},{"
      "\"possibleOperations\":\"readOnly\"}]]}]}],[{\"featureDescription\":[{\"featureAddress\":[{\"entity\":[1]},{"
      "\"feature\":1}]},{\"featureType\":\"Measurement\"},{\"role\":\"server\"},{\"supportedFunction\":[[{\"function\":"
      "\"measurementListData\"},{\"possibleOperations\":\"readOnly\"}]]}]}]]}]}]]}]}]}";

TEST(ShipDataTransformerTest, testShipMessage)
{
    std::vector<char> testJsonArray = std::vector<char>();
    testJsonArray.push_back(2);
    int foundIndex = testShipMessageConst.find("EEBUS_PAYLOAD_REPLACE");
    std::string testShipMessage = testShipMessageConst;
    std::string testMessage = testShipMessage.replace(foundIndex, 21, testSpineDatagramConst);
    std::copy(testMessage.begin(), testMessage.end(), std::back_inserter(testJsonArray));

    keo_ship::Data* pDataClass = keo_ship::ShipDataTransformer::createShipDataMessageFromJson(testJsonArray);

    std::vector<char> returnJsonArray;
    ASSERT_TRUE(keo_ship::ShipDataTransformer::getJsonFromMessageData(*pDataClass, returnJsonArray));
    ASSERT_TRUE(returnJsonArray.size() > 0);
    std::string returnTestMessage(returnJsonArray.begin() + 1, returnJsonArray.end());
    ASSERT_EQ(returnTestMessage, testMessage);
}
TEST(ShipDataTransformerTest, testShipMessageComplex)
{
    std::vector<char> testJsonArray = std::vector<char>();
    testJsonArray.push_back(2);
    int foundIndex = testShipMessageConst.find("EEBUS_PAYLOAD_REPLACE");
    std::string testShipMessage = testShipMessageConst;
    std::string testMessage = testShipMessage.replace(foundIndex, 21, testSpineDatagramComplexConst);
    std::copy(testMessage.begin(), testMessage.end(), std::back_inserter(testJsonArray));

    keo_ship::Data* pDataClass = keo_ship::ShipDataTransformer::createShipDataMessageFromJson(testJsonArray);

    std::vector<char> returnJsonArray;
    ASSERT_TRUE(keo_ship::ShipDataTransformer::getJsonFromMessageData(*pDataClass, returnJsonArray));
    ASSERT_TRUE(returnJsonArray.size() > 0);
    std::string returnTestMessage(returnJsonArray.begin() + 1, returnJsonArray.end());
    ASSERT_EQ(returnTestMessage, testMessage);
}
