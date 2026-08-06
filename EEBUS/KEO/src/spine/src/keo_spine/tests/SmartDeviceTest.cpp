/*
 *     Copyright KEO GmbH 2018 - All rights reserved!
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
#include "TestSendService.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_spine/SmartDevice.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <chrono>
#include <gtest/gtest.h>
#include <memory>
#include <thread>

namespace keo_smart_device_test
{

class TestSpineLinkSendService : public SpineLinkSendServiceInterface
{
public:
    bool sendDatagram(const DatagramRecord& datagramRecord) override
    {
        sentDatagrams.push_back(datagramRecord);
        return true;
    }

    std::vector<DatagramRecord> sentDatagrams;
};

SmartDevice createTestDevice()
{
    auto entity0 = PrimaryDeviceInformationEntity::createBasicDeviceInformationEntity();
    entity0->setNodeManagementFeature(PrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false));
    entity0->setDeviceClassificationFeature(DeviceClassificationFeature::createBasicDeviceClassificationFeature());
    NetworkManagementDeviceDescriptionData deviceDescription;
    deviceDescription.setDeviceAddress(DeviceAddress("DUT"));
    deviceDescription.setNetworkFeatureSet(NetworkManagementFeatureSet::Value::SMART);
    deviceDescription.setDeviceType(DeviceType::Value::GENERIC);
    SmartDevice device;
    device.setDeviceDescription(deviceDescription);
    device.setPrimaryDeviceInformationEntity(entity0);
    return device;
}

void addTransportIdMappingToDevice(SmartDevice& device, std::string const& deviceName, std::string const& tid)
{
    // A transport id mapping is created when a transport connection is added and the DD-read that is then sent on that
    // connection is replied to. Thus we have to fake and inject a DD-reply for the mapping to be added.
    Header header;
    header.setMsgCounter(0);
    header.setMsgCounterReference(3);
    header.setCmdClassifier(CmdClassifier::Value::REPLY);
    header.setAddressSource(FeatureAddress(deviceName, 0U, 0U));
    header.setAddressDestination(FeatureAddress("DUT", 0U, 0U));
    Datagram datagram;
    datagram.setHeader(header);
    auto cmdData = std::make_shared<NodeManagementDetailedDiscoveryData>();
    NodeManagementDetailedDiscoveryDeviceInformation di;
    NetworkManagementDeviceDescriptionData ddd;
    ddd.setDeviceAddress(DeviceAddress(deviceName));
    di.setDescription(ddd);
    cmdData->setDeviceInformation(di);
    cmdData->setSpecificationVersionList(NodeManagementSpecificationVersionList());
    cmdData->setEntityInformation({});
    cmdData->setFeatureInformation({});
    datagram.setCmd(Cmd(cmdData));

    if (auto rs = device.getSpineLinkReceiveService().lock())
    {
        rs->addConnection(tid);
    }

    if (auto rs = device.getSpineLinkReceiveService().lock())
    {
        DatagramRecord record(datagram, tid);
        rs->onDatagram(record);
    }
}

TEST(SmartDeviceTest, testInitializeSuccessfully)
{
    SmartDevice device = createTestDevice();

    ASSERT_TRUE(device.initialize());
    ASSERT_TRUE(device.isInitialized());
}

TEST(SmartDeviceTest, testInitializeFailsAfterSuccessfulInitialization)
{
    SmartDevice device = createTestDevice();

    ASSERT_TRUE(device.initialize());
    ASSERT_TRUE(device.isInitialized());

    device.setDeviceDescription(NetworkManagementDeviceDescriptionData()); // clear device description

    ASSERT_FALSE(device.initialize());
    ASSERT_FALSE(device.isInitialized());
}

TEST(SmartDeviceTest, testExceptionOnSendWhenUninitialized)
{
    SmartDevice device = createTestDevice();
    ASSERT_THROW(device.sendDatagram(DatagramRecord()), std::logic_error);
}

TEST(SmartDeviceTest, testExceptionOnReceiveWhenUninitialized)
{
    SmartDevice device = createTestDevice();
    if (auto receiveService = device.getSpineLinkReceiveService().lock())
    {
        DatagramRecord record;
        ASSERT_THROW(receiveService->onDatagram(record), std::logic_error);
    }
}

TEST(SmartDeviceTest, testUnknownDestinationDevice)
{
    SmartDevice device = createTestDevice();
    device.initialize();
    TestSpineLinkSendService sendService;
    device.setSpineLinkSendService(&sendService);

    std::string sourceDevice = "Device";
    std::string destinationDevice = "UNKNOWN_DEVICE";

    addTransportIdMappingToDevice(device, sourceDevice, "tid");

    Datagram datagram;
    datagram.setCmdClassifier(CmdClassifier::Value::READ);
    datagram.setSourceAddress(FeatureAddress(sourceDevice, 0U, 0U));
    datagram.setDestinationAddress(FeatureAddress(destinationDevice, 0U, 0U));
    datagram.setCmd(Cmd(std::make_shared<NodeManagementBindingData>()));

    if (auto rs = device.getSpineLinkReceiveService().lock())
    {
        DatagramRecord record(datagram, "tid");
        rs->onDatagram(record); // This will return directly and the datagram is processed in another thread
    }

    // Because the processing is asynchronous we need to sleep here
    while (sendService.sentDatagrams.size() < 2)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    ASSERT_EQ(2U, sendService.sentDatagrams.size());

    keo_datagram::Datagram const& reply = sendService.sentDatagrams.back().getDatagram();
    ASSERT_EQ("DUT", reply.getSourceAddress().getDevice());
    ASSERT_EQ(sourceDevice, reply.getDestinationAddress().getDevice());

    auto result = std::dynamic_pointer_cast<ResultData>(reply.getCmdData());
    ASSERT_TRUE(result->getErrorNumberIsSet());
    ASSERT_EQ(SpineResultErrors::DESTINATION_UNKNOWN, result->getErrorNumber());
}

TEST(SmartDeviceTest, testNoCrashOnUnknownDestinationEntity)
{
    SmartDevice device = createTestDevice();
    device.initialize();
    TestSpineLinkSendService sendService;
    device.setSpineLinkSendService(&sendService);

    addTransportIdMappingToDevice(device, "Device", "tid");

    Datagram datagram;
    datagram.setCmdClassifier(CmdClassifier::Value::READ);
    datagram.setSourceAddress(FeatureAddress("Device", 1U, 1U));
    datagram.setDestinationAddress(FeatureAddress("DUT", 2U, 0U));
    datagram.setCmd(Cmd(std::make_shared<NodeManagementBindingData>()));

    if (auto rs = device.getSpineLinkReceiveService().lock())
    {
        DatagramRecord record(datagram, "tid");
        rs->onDatagram(record); // This will return directly and the datagram is processed in another thread
    }

    // Because the processing is asynchronous we need to sleep here
    while (sendService.sentDatagrams.size() < 2)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    ASSERT_EQ(2U, sendService.sentDatagrams.size());

    auto result = std::dynamic_pointer_cast<ResultData>(sendService.sentDatagrams.back().getDatagram().getCmdData());
    ASSERT_NE(nullptr, result);
    ASSERT_TRUE(result->getErrorNumberIsSet());
    ASSERT_EQ(SpineResultErrors::DESTINATION_UNKNOWN, result->getErrorNumber());
}

TEST(SmartDeviceTest, testNoCrashOnUnknownDestinationFeature)
{
    SmartDevice device = createTestDevice();
    device.initialize();
    TestSpineLinkSendService sendService;
    device.setSpineLinkSendService(&sendService);

    addTransportIdMappingToDevice(device, "Device", "tid");

    Datagram datagram;
    datagram.setCmdClassifier(CmdClassifier::Value::READ);
    datagram.setSourceAddress(FeatureAddress("Device", 1U, 1U));
    datagram.setDestinationAddress(FeatureAddress("DUT", 0U, 99U));
    datagram.setCmd(Cmd(std::make_shared<NodeManagementBindingData>()));

    if (auto rs = device.getSpineLinkReceiveService().lock())
    {
        DatagramRecord record(datagram, "tid");
        rs->onDatagram(record); // This will return directly and the datagram is processed in another thread
    }

    // Because the processing is asynchronous we need to sleep here
    while (sendService.sentDatagrams.size() < 2)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ASSERT_EQ(2U, sendService.sentDatagrams.size());

    auto result = std::dynamic_pointer_cast<ResultData>(sendService.sentDatagrams.back().getDatagram().getCmdData());
    ASSERT_NE(nullptr, result);
    ASSERT_TRUE(result->getErrorNumberIsSet());
    ASSERT_EQ(SpineResultErrors::DESTINATION_UNKNOWN, result->getErrorNumber());
}
}
