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

#include <keo_spine/DeviceDefinition.h>
#include <keo_spine/PrimaryNodeManagementFeature.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */

#include "TestPrimaryNodeManagementFeature.h"
#include "TestSendService.h"
#include "gtest/gtest.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <string>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

using namespace keo_spine;
using namespace keo_datagram;

class PrimaryNodeManagementInterfaceImpl : public PrimaryNodeManagementInterface
{

public:
    bool addSubscription(
        unsigned int subscriptionId, const keo_datagram::SubscriptionManagementRequestCall& subscriptionCall) override
    {
        Association assoc;
        assoc.id = subscriptionId;
        assoc.clientAddress = subscriptionCall.getClientAddress();
        subscriptions[subscriptionCall.getServerAddress()].push_back(assoc);
        return true;
    }

    bool removeSubscription(const keo_datagram::SubscriptionManagementDeleteCall& deleteCall) override
    {
        (void)deleteCall;
        return true;
    }

    bool addBinding(unsigned int bindingId, const keo_datagram::BindingManagementRequestCall& bindingCall) override
    {
        Association assoc;
        assoc.id = bindingId;
        assoc.clientAddress = bindingCall.getClientAddress();
        bindings[bindingCall.getServerAddress()].push_back(assoc);
        return true;
    }

    bool removeBinding(const keo_datagram::BindingManagementDeleteCall& deleteCall) override
    {
        (void)deleteCall;
        return true;
    }

    void onNewDevices(const std::vector<std::string>& devices, const TransportId& transportId) override
    {
        newDevices.insert(std::pair<TransportId, std::vector<std::string>>(transportId, devices));
        transportIds.push_back(transportId);
    }

    void onRemovedDevices(const std::vector<std::string>& devices, const TransportId& transportId) override
    {
        removedDevices.insert(std::pair<TransportId, std::vector<std::string>>(transportId, devices));
        transportIds.push_back(transportId);
    }

    void onDetailedDiscovery(
        const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery) override
    {
        (void)deviceName;
        (void)detailedDiscovery;
    }

    void onDetailedDiscoveryPartial(
        const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial) override
    {
        (void)deviceName;
        (void)detailedDiscoveryPartial;
    }

    void onUseCaseDiscovery(
        const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery) override
    {
        useCaseDiscoveries.insert(std::pair<std::string, keo_datagram::UseCaseDiscovery>(deviceName, useCaseDiscovery));
    }

    const std::map<keo_datagram::FeatureAddress, std::vector<Association>> getBindings() const override
    {
        return bindings;
    }

    const std::map<keo_datagram::FeatureAddress, std::vector<Association>> getSubscriptions() const override
    {
        return subscriptions;
    }

    std::vector<TransportId> transportIds;
    std::map<TransportId, std::vector<std::string>> newDevices;
    std::map<TransportId, std::vector<std::string>> removedDevices;
    std::map<std::string, UseCaseDiscovery> useCaseDiscoveries;
    std::map<keo_datagram::FeatureAddress, std::vector<Association>> subscriptions;
    std::map<keo_datagram::FeatureAddress, std::vector<Association>> bindings;
};

NetworkManagementFeatureDescriptionData getNetworkManagementFeatureDescriptionData()
{
    NetworkManagementFeatureDescriptionData featureDescription;
    std::vector<FunctionProperty> supportedFunction;
    { // NodeManagement
        featureDescription.setFeatureAddress(FeatureAddress("", 0, 0));
        featureDescription.setFeatureType(DeviceDefinition::EntityZeroFeatureZeroType);
        featureDescription.setRole(Role::Value::SERVER);
        PossibleOperations possibleOperationsReadOnly;
        possibleOperationsReadOnly.setRead(PossibleOperationsRead());
        FunctionProperty functionPropertyDetailedDiscovery(
            Function(Function::Value::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA), possibleOperationsReadOnly);
        supportedFunction.push_back(functionPropertyDetailedDiscovery);
    }
    { // DeviceClassification
        featureDescription.setFeatureAddress(FeatureAddress("", 1, 0));
        featureDescription.setFeatureType(DeviceDefinition::EntityZeroFeatureOneType);
        featureDescription.setRole(Role::Value::SERVER);
        PossibleOperations possibleOperationsReadOnly;
        possibleOperationsReadOnly.setRead(PossibleOperationsRead());
        FunctionProperty functionPropertyDetailedDiscovery(
            Function(Function::Value::DEVICE_CLASSIFICATION_MANUFACTURER_DATA), possibleOperationsReadOnly);
        supportedFunction.push_back(functionPropertyDetailedDiscovery);
    }
    featureDescription.setSupportedFunction(supportedFunction);
    return featureDescription;
}

Datagram datagramFromJson(std::string& json)
{
    auto datagram = Datagram::fromJson(json);
    datagram.parsePayload();
    return datagram;
}

DetailedDiscovery detailedDiscoveryFromJson(std::string& json)
{
    Datagram datagram = datagramFromJson(json);
    DetailedDiscovery dd;
    dd.setDiscoveryInformationFromCmd(datagram.getCmd());
    return dd;
}

TEST(PrimaryNodeManagementFeatureTest, HandleDestinationListNotification)
{
    std::string jsonDestinationListNotify
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
    Datagram datagram = datagramFromJson(jsonDestinationListNotify);

    PrimaryNodeManagementInterfaceImpl primaryNodeManagementInterface;
    PrimaryNodeManagementFeaturePtr nodeManagementFeature
        = PrimaryNodeManagementFeature::createBasicNodeManagementFeature(true, false);
    nodeManagementFeature->setPrimaryNodeManagementInterface(&primaryNodeManagementInterface);

    DatagramRecord datagramRecord = DatagramRecord(datagram, "TransportId");
    nodeManagementFeature->handleDatagram(datagramRecord);
    ASSERT_EQ("TransportId", primaryNodeManagementInterface.transportIds.front());
    auto allNewDevices = primaryNodeManagementInterface.newDevices.find("TransportId");

    ASSERT_EQ(1U, allNewDevices->second.size());
    ASSERT_EQ("d:_n:DEVICE_ADDED", allNewDevices->second.front());
    auto allRemovedDevices = primaryNodeManagementInterface.removedDevices.find("TransportId");
    ASSERT_EQ(1U, allRemovedDevices->second.size());
    ASSERT_EQ("d:_n:DEVICE_REMOVED", allRemovedDevices->second.front());
}

TEST(PrimaryNodeManagementFeatureTest, HandleResultOfSubscriptionRequest)
{
    std::string jsonResult
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:_n:"
          "DEVICE_SOURCE\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:_n:DEVICE_"
          "DESTINATION\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":16},{\"msgCounterReference\":6},{"
          "\"cmdClassifier\":\"result\"}]},{"
          "\"payload\":[{\"cmd\":[[{\"resultData\":[{\"errorNumber\":0}]}]]}]}]}";
    Datagram datagram = datagramFromJson(jsonResult);

    PrimaryNodeManagementInterfaceImpl primaryNodeManagementInterface;
    TestPrimaryNodeManagementFeaturePtr nodeManagementFeature
        = TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(true, false);
    nodeManagementFeature->setPrimaryNodeManagementInterface(&primaryNodeManagementInterface);

    DatagramRecord datagramRecord = DatagramRecord(datagram, "TransportId");
    keo_datagram::Header header;
    DatagramMemo memo = DatagramMemo(keo_datagram::FeatureAddress(), header.getMsgCounter() + 1,
        keo_datagram::CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE);
    ASSERT_FALSE(nodeManagementFeature->handlePendingDatagramResponsePublic(datagramRecord, memo));

    nodeManagementFeature->subscribeToPrimaryNodeManagementFeature("d:_n:DEVICE_DESTINATION");
    ASSERT_TRUE(nodeManagementFeature->handlePendingDatagramResponsePublic(datagramRecord, memo));
}

TEST(PrimaryNodeManagementFeatureTest, GetMaxResponseDelayFromDD)
{
    std::string jsonDetailedDiscovery
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:_n:"
          "ExampleClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:_n:"
          "ExampleServer\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":6},{\"msgCounterReference\":1},{"
          "\"cmdClassifier\":\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"nodeManagementDetailedDiscoveryData\":[{"
          "\"specificationVersionList\":[{\"specificationVersion\":[\"1.0.0\"]}]},{\"deviceInformation\":[{"
          "\"description\":[{\"deviceAddress\":[{\"device\":\"d:_n:ExampleClient\"}]},{\"deviceType\":\"Generic\"},{"
          "\"networkFeatureSet\":\"smart\"}]}]},{\"entityInformation\":[[{\"description\":[{\"entityAddress\":[{"
          "\"entity\":[1]}]},{\"entityType\":\"Generic\"},{\"description\":\"Measurementtestcliententity\"}]}],[{"
          "\"description\":[{\"entityAddress\":[{\"entity\":[0]}]},{\"entityType\":\"DeviceInformation\"}]}]]},{"
          "\"featureInformation\":[[{\"description\":[{\"featureAddress\":[{\"entity\":[1]},{\"feature\":2}]},{"
          "\"featureType\":\"Measurement\"},{\"role\":\"client\"},{\"description\":\"Measurementtestclientfeature\"},{"
          "\"maxResponseDelay\":\"PT10.05S\"}]}],[{\"description\":[{\"featureAddress\":[{\"entity\":[0]},{\"feature\":"
          "0}]},{\"featureType\":\"NodeManagement\"},{\"role\":\"special\"},{\"supportedFunction\":[[{\"function\":"
          "\"nodeManagementDetailedDiscoveryData\"},{\"possibleOperations\":[{\"read\":[]}]}],[{\"function\":"
          "\"nodeManagementSubscriptionRequestCall\"},{\"possibleOperations\":[]}],[{\"function\":"
          "\"nodeManagementSubscriptionDeleteCall\"},{\"possibleOperations\":[]}],[{\"function\":"
          "\"nodeManagementSubscriptionData\"},{\"possibleOperations\":[{\"read\":[]}]}],[{\"function\":"
          "\"nodeManagementBindingRequestCall\"},{\"possibleOperations\":[]}],[{\"function\":"
          "\"nodeManagementBindingDeleteCall\"},{\"possibleOperations\":[]}],[{\"function\":"
          "\"nodeManagementBindingData\"},{\"possibleOperations\":[{\"read\":[]}]}]]},{\"maxResponseDelay\":\"PT20S\"}]"
          "}],[{\"description\":[{\"featureAddress\":[{\"entity\":[0]},{\"feature\":1}]},{\"featureType\":"
          "\"DeviceClassification\"},{\"role\":\"server\"},{\"supportedFunction\":[[{\"function\":"
          "\"deviceClassificationManufacturerData\"},{\"possibleOperations\":[{\"read\":[]}]}]]},{\"maxResponseDelay\":"
          "\"PT0S\"}]}]]}]}]]}]}]}";
    DetailedDiscovery dd = detailedDiscoveryFromJson(jsonDetailedDiscovery);

    std::string sourceDevice = dd.getDeviceName();

    PrimaryNodeManagementInterfaceImpl primaryNodeManagementInterface;
    TestPrimaryNodeManagementFeaturePtr feature
        = TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(true, false);
    feature->setPrimaryNodeManagementInterface(&primaryNodeManagementInterface);

    feature->onDetailedDiscovery(sourceDevice, dd);

    // The PrimaryNodeManagementFeature in the read DetailedDiscovery has a maxReponseDelay of 20 sec
    FeatureAddress remoteFeatureAddress(sourceDevice, 0L, 0L);
    ASSERT_TRUE(feature->hasRemoteFeatureTimeout(remoteFeatureAddress));
    ASSERT_EQ(20L * 1000, feature->getRemoteFeatureTimeout(remoteFeatureAddress));

    // This feature does not exist, hence it has no maxResponseDelay
    FeatureAddress invalidFeatureAddress(sourceDevice, 1L, 1L);
    ASSERT_FALSE(feature->hasRemoteFeatureTimeout(invalidFeatureAddress));
    ASSERT_EQ(0L, feature->getRemoteFeatureTimeout(invalidFeatureAddress));

    // This feature has a maxResponseDelay in milliseconds ranges
    FeatureAddress milliFeatureAddress(sourceDevice, 1L, 2L);
    ASSERT_TRUE(feature->hasRemoteFeatureTimeout(milliFeatureAddress));
    ASSERT_EQ(10L * 1000 + 50, feature->getRemoteFeatureTimeout(milliFeatureAddress));

    // Remove the entries again
    std::vector<std::string> r = { sourceDevice };
    feature->onRemovedDevices(r);
    ASSERT_FALSE(feature->hasRemoteFeatureTimeout(remoteFeatureAddress));
    ASSERT_FALSE(feature->hasRemoteFeatureTimeout(invalidFeatureAddress));
    ASSERT_FALSE(feature->hasRemoteFeatureTimeout(milliFeatureAddress));
}

TEST(PrimaryNodeManagementFeatureTest, DeleteMaxResponseDelayByDisconnect)
{
    std::string jsonDestinationListNotify
        = "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{\"device\":\"d:_n:"
          "ExampleClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d:_n:"
          "ExampleServer\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":6},{\"msgCounterReference\":1},{"
          "\"cmdClassifier\":\"reply\"}]},{\"payload\":[{\"cmd\":[[{\"nodeManagementDetailedDiscoveryData\":[{"
          "\"specificationVersionList\":[{\"specificationVersion\":[\"1.0.0\"]}]},{\"deviceInformation\":[{"
          "\"description\":[{\"deviceAddress\":[{\"device\":\"d:_n:ExampleClient\"}]},{\"deviceType\":\"Generic\"},{"
          "\"networkFeatureSet\":\"smart\"}]}]},{\"entityInformation\":[[{\"description\":[{\"entityAddress\":[{"
          "\"entity\":[1]}]},{\"entityType\":\"Generic\"},{\"description\":\"Measurementtestcliententity\"}]}],[{"
          "\"description\":[{\"entityAddress\":[{\"entity\":[0]}]},{\"entityType\":\"DeviceInformation\"}]}]]},{"
          "\"featureInformation\":[[{\"description\":[{\"featureAddress\":[{\"entity\":[1]},{\"feature\":2}]},{"
          "\"featureType\":\"Measurement\"},{\"role\":\"client\"},{\"description\":\"Measurementtestclientfeature\"},{"
          "\"maxResponseDelay\":\"PT10.05S\"}]}],[{\"description\":[{\"featureAddress\":[{\"entity\":[0]},{\"feature\":"
          "0}]},{\"featureType\":\"NodeManagement\"},{\"role\":\"special\"},{\"supportedFunction\":[[{\"function\":"
          "\"nodeManagementDetailedDiscoveryData\"},{\"possibleOperations\":[{\"read\":[]}]}],[{\"function\":"
          "\"nodeManagementSubscriptionRequestCall\"},{\"possibleOperations\":[]}],[{\"function\":"
          "\"nodeManagementSubscriptionDeleteCall\"},{\"possibleOperations\":[]}],[{\"function\":"
          "\"nodeManagementSubscriptionData\"},{\"possibleOperations\":[{\"read\":[]}]}],[{\"function\":"
          "\"nodeManagementBindingRequestCall\"},{\"possibleOperations\":[]}],[{\"function\":"
          "\"nodeManagementBindingDeleteCall\"},{\"possibleOperations\":[]}],[{\"function\":"
          "\"nodeManagementBindingData\"},{\"possibleOperations\":[{\"read\":[]}]}]]},{\"maxResponseDelay\":\"PT20S\"}]"
          "}],[{\"description\":[{\"featureAddress\":[{\"entity\":[0]},{\"feature\":1}]},{\"featureType\":"
          "\"DeviceClassification\"},{\"role\":\"server\"},{\"supportedFunction\":[[{\"function\":"
          "\"deviceClassificationManufacturerData\"},{\"possibleOperations\":[{\"read\":[]}]}]]},{\"maxResponseDelay\":"
          "\"PT0S\"}]}]]}]}]]}]}]}";
    DetailedDiscovery dd = detailedDiscoveryFromJson(jsonDestinationListNotify);

    std::string sourceDevice = dd.getDeviceName();

    PrimaryNodeManagementInterfaceImpl primaryNodeManagementInterface;
    TestPrimaryNodeManagementFeaturePtr feature
        = TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(true, false);
    feature->setPrimaryNodeManagementInterface(&primaryNodeManagementInterface);

    feature->onDetailedDiscovery(sourceDevice, dd);

    std::vector<std::string> devices = { "test", "no_device", "no_no", "hallo", "d:_n:ExampleClient" };
    feature->onRemovedDevices(devices);

    FeatureAddress remoteFeatureAddress(sourceDevice, 0L, 0L);
    ASSERT_FALSE(feature->hasRemoteFeatureTimeout(remoteFeatureAddress));
}

TEST(PrimaryNodeManagementFeatureTest, AckSubscriptionRequest)
{
    TestSendService sendService("d");
    PrimaryNodeManagementInterfaceImpl primaryNodeManagementInterface;
    TestPrimaryNodeManagementFeaturePtr feature
        = TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false);
    feature->setPrimaryNodeManagementInterface(&primaryNodeManagementInterface);
    feature->setSendService(&sendService);

    keo_datagram::Datagram request = keo_datagram::Datagram::fromJson(
        "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{\"device\":\"d:_i:47859_"
        "KEO-SimpleDeviceClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d\""
        "},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":10},{\"cmdClassifier\":"
        "\"call\"},{\"ackRequest\":true}]},{\"payload\":[{\"cmd\":[[{\"nodeManagementSubscriptionRequestCall\":[{"
        "\"subscriptionRequest\":[{\"clientAddress\":[{\"device\":\"d:_i:47859_KEO-SimpleDeviceClient\"},{\"entity\":["
        "0]},{\"feature\":0}]},{\"serverAddress\":[{\"device\":\"d:_i:47859_KEO-SimpleDeviceServer\"},{\"entity\":[0]},"
        "{\"feature\":0}]},{\"serverFeatureType\":\"NodeManagement\"}]}]}]]}]}]}");
    ASSERT_TRUE(request.parsePayload());

    feature->handleDatagram(DatagramRecord(request));
    ASSERT_EQ(1U, sendService.getSentDatagrams().size());
    ASSERT_EQ(sendService.getSentDatagrams()[0].getDatagram().getCmdClassifier(), CmdClassifier::Value::RESULT);
}

TEST(PrimaryNodeManagementFeatureTest, DontAckSubscriptionRequest)
{
    TestSendService sendService("d");
    PrimaryNodeManagementInterfaceImpl primaryNodeManagementInterface;
    TestPrimaryNodeManagementFeaturePtr feature
        = TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false);
    feature->setPrimaryNodeManagementInterface(&primaryNodeManagementInterface);
    feature->setSendService(&sendService);

    keo_datagram::Datagram request = keo_datagram::Datagram::fromJson(
        "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{\"device\":\"d:_i:47859_"
        "KEO-SimpleDeviceClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d\""
        "},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":10},{\"cmdClassifier\":"
        "\"call\"}]},{\"payload\":[{\"cmd\":[[{\"nodeManagementSubscriptionRequestCall\":[{"
        "\"subscriptionRequest\":[{\"clientAddress\":[{\"device\":\"d:_i:47859_KEO-SimpleDeviceClient\"},{\"entity\":["
        "0]},{\"feature\":0}]},{\"serverAddress\":[{\"device\":\"d:_i:47859_KEO-SimpleDeviceServer\"},{\"entity\":[0]},"
        "{\"feature\":0}]},{\"serverFeatureType\":\"NodeManagement\"}]}]}]]}]}]}");
    ASSERT_TRUE(request.parsePayload());

    feature->handleDatagram(DatagramRecord(request));
    ASSERT_EQ(0U, sendService.getSentDatagrams().size());
}

TEST(PrimaryNodeManagementFeatureTest, ReadUseCaseInformationData)
{
    TestSendService sendService("d");
    PrimaryNodeManagementInterfaceImpl primaryNodeManagementInterface;
    TestPrimaryNodeManagementFeaturePtr feature
        = TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false);
    feature->setPrimaryNodeManagementInterface(&primaryNodeManagementInterface);
    feature->setSendService(&sendService);

    UseCaseInformationData uci;
    uci.setActor("MyFineUseCaseActor");
    uci.setAddress(FeatureAddress("d", 1, 1));
    std::vector<UseCaseInformationData> ucis = { uci };
    NodeManagementUseCaseData ucd(ucis);
    feature->setUseCaseData(ucd);

    keo_datagram::Datagram request = keo_datagram::Datagram::fromJsonThrows(
        "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
        "\"device\":\"d:SHIP_test_1\"},{\"entity\":[1]},{\"feature\":4}]},{\"addressDestination\":[{"
        "\"device\":\"d:EEBusTestClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":185},{"
        "\"msgCounterReference\":28},{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
        "\"nodeManagementUseCaseData\":[]}]]}]}]}");
    ASSERT_TRUE(request.parsePayload());

    feature->handleDatagram(DatagramRecord(request));
    ASSERT_EQ(1U, sendService.getSentDatagrams().size());
    ASSERT_EQ(sendService.getSentDatagrams()[0].getDatagram().getCmdClassifier(), CmdClassifier::Value::REPLY);
    ASSERT_EQ(sendService.getSentDatagrams()[0].getDatagram().getCmdDataType(),
        CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE);
}

TEST(PrimaryNodeManagementFeatureTest, ReadUseCaseInformationDataWhenNoneSet)
{
    TestSendService sendService("d");
    TestPrimaryNodeManagementFeaturePtr feature
        = TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false);
    feature->setSendService(&sendService);

    keo_datagram::Datagram request = keo_datagram::Datagram::fromJsonThrows(
        "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.0.0\"},{\"addressSource\":[{"
        "\"device\":\"d:SHIP_test_1\"},{\"entity\":[1]},{\"feature\":4}]},{\"addressDestination\":[{"
        "\"device\":\"d:EEBusTestClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":185},{"
        "\"msgCounterReference\":28},{\"cmdClassifier\":\"read\"}]},{\"payload\":[{\"cmd\":[[{"
        "\"nodeManagementUseCaseData\":[]}]]}]}]}");
    ASSERT_TRUE(request.parsePayload());

    feature->handleDatagram(DatagramRecord(request));
    ASSERT_EQ(0U, sendService.getSentDatagrams().size());
}

TEST(PrimaryNodeManagementFeatureTest, DistributeUseCaseDataViaInterface)
{
    PrimaryNodeManagementInterfaceImpl i;
    TestPrimaryNodeManagementFeaturePtr feature
        = TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false);
    feature->setPrimaryNodeManagementInterface(&i);

    keo_datagram::Datagram datagram = keo_datagram::Datagram::fromJsonThrows(
        R"({"datagram":[{"header":[{"specificationVersion":"1.1.0"},{"addressSource":[{"device":"UseCaseDevice"},{"entity":[0]},{"feature":0}]},{"addressDestination":[{"device":"d:_i:47859_KEO-SimpleDeviceClient"},{"entity":[0]},{"feature":0}]},{"msgCounter":14},{"cmdClassifier":"notify"}]},{"payload":[{"cmd":[[{"nodeManagementUseCaseData":[{"useCaseInformation":[[{"address":[{"entity":[1]},{"feature":1}]},{"actor":"Actor1"},{"useCaseSupport":[[{"useCaseName":"UseCase1"},{"useCaseVersion":"Version1"},{"useCaseAvailable":true},{"scenarioSupport":[1,2,3]}]]}]]}]}]]}]}]})");
    ASSERT_TRUE(datagram.parsePayload());

    feature->handleDatagram(DatagramRecord(datagram, "tid"));
    ASSERT_EQ(1U, i.useCaseDiscoveries.count("UseCaseDevice"));
    UseCaseDiscovery ucd = i.useCaseDiscoveries.find("UseCaseDevice")->second;
    ASSERT_TRUE(ucd.getMatchingUseCases().empty());
    ASSERT_EQ(1U, ucd.getRemoteUseCaseData().getUseCaseInformation().size());
    ASSERT_EQ("Actor1", ucd.getRemoteUseCaseData().getUseCaseInformation()[0].getActor());
}

TEST(PrimaryNodeManagementFeatureTest, SendFullReadOnPartialUseCaseData)
{
    TestSendService sendService("d");
    TestPrimaryNodeManagementFeaturePtr feature
        = TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false);
    feature->setSendService(&sendService);

    keo_datagram::Datagram notification = keo_datagram::Datagram::fromJsonThrows(
        R"({"datagram":[{"header":[{"specificationVersion":"1.1.0"},{"addressSource":[{"device":"UseCaseDevice"},{"entity":[0]},{"feature":0}]},{"addressDestination":[{"device":"d:_i:47859_KEO-SimpleDeviceClient"},{"entity":[0]},{"feature":0}]},{"msgCounter":14},{"cmdClassifier":"notify"}]},{"payload":[{"cmd":[[{"filter":[[{"cmdControl":[{"partial":[]}]}]]},{"nodeManagementUseCaseData":[{"useCaseInformation":[[{"address":[{"entity":[1]},{"feature":1}]},{"actor":"Actor1"},{"useCaseSupport":[[{"useCaseName":"UseCase1"},{"useCaseVersion":"Version1"},{"useCaseAvailable":true},{"scenarioSupport":[1,2,3]}]]}]]}]}]]}]}]})");
    ASSERT_TRUE(notification.parsePayload());

    feature->handleDatagram(DatagramRecord(notification, "tid"));

    ASSERT_EQ(1U, sendService.getSentDatagrams().size());
    Datagram const& response = sendService.getSentDatagrams()[0].getDatagram();
    ASSERT_TRUE(response.isRead());
    ASSERT_EQ(CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE, response.getCmdDataType());
}

TEST(PrimaryNodeManagementFeatureTest, AddMissingClientDeviceNameInSubscriptionRequest)
{
    TestSendService sendService("d");
    PrimaryNodeManagementInterface* pnmInterface = new PrimaryNodeManagementInterfaceImpl();
    TestPrimaryNodeManagementFeaturePtr pnmFeature
        = TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false);
    pnmFeature->setPrimaryNodeManagementInterface(pnmInterface);
    pnmFeature->setSendService(&sendService);

    keo_datagram::FeatureAddress serverAddress;
    serverAddress.setDevice("d");
    serverAddress.setEntity({ 0 });
    serverAddress.setFeature(0);

    keo_datagram::FeatureAddress clientAddress;
    clientAddress.setDevice("d:_i:47859_KEO-SimpleDeviceClient");
    clientAddress.setEntity({ 0 });
    clientAddress.setFeature(0);

    keo_datagram::Datagram request = keo_datagram::Datagram::fromJson(
        "{\"datagram\":[{\"header\":[{\"specificationVersion\":\"1.1.0\"},{\"addressSource\":[{\"device\":\"d:_i:47859_"
        "KEO-SimpleDeviceClient\"},{\"entity\":[0]},{\"feature\":0}]},{\"addressDestination\":[{\"device\":\"d\""
        "},{\"entity\":[0]},{\"feature\":0}]},{\"msgCounter\":10},{\"cmdClassifier\":"
        "\"call\"}]},{\"payload\":[{\"cmd\":[[{\"nodeManagementSubscriptionRequestCall\":[{"
        "\"subscriptionRequest\":[{\"clientAddress\":[{\"entity\":["
        "0]},{\"feature\":0}]},{\"serverAddress\":[{\"device\":\"d\"},{\"entity\":[0]},"
        "{\"feature\":0}]},{\"serverFeatureType\":\"NodeManagement\"}]}]}]]}]}]}");
    request.parsePayloadThrows();

    pnmFeature->handleDatagram(DatagramRecord(request));
    ASSERT_EQ(1U, pnmInterface->getSubscriptions().size());
    ASSERT_EQ(clientAddress, pnmInterface->getSubscriptions().at(serverAddress)[0].clientAddress);

    delete pnmInterface;
}
