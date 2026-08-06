/*
 *     Copyright KEO GmbH 2015 - All rights reserved!
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
#include <keo_datagram/core/DestinationList.h>

/* ************************************************************************** *
 *  defines                                                                   *
 * ************************************************************************** */

/* ************************************************************************** *
 *  types                                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  definition                                                                *
 * ************************************************************************** */

// flooding the global namespace ....
using namespace keo_datagram;

NodeManagementDestinationListDataPtr createDestinationList()
{
    std::vector<NodeManagementDestinationData> list;

    {
        // simple device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_A"));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    {
        // simple device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_B"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SIMPLE));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    {
        // smart device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_C"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SMART));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    {
        // gateway device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_D"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::GATEWAY));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    {
        // router device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_E"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::ROUTER));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    NodeManagementDestinationListDataPtr destinationListInformation
        = NodeManagementDestinationListDataPtr(new NodeManagementDestinationListData);
    destinationListInformation->setNodeManagementDestinationData(list);

    return destinationListInformation;
}

TEST(DestinationListSF, memoryLeak)
{
    DestinationList DestinationList;

    EXPECT_TRUE(true);
}

TEST(DestinationListSF, insertList)
{
    DestinationList destinationList;

    destinationList.insertDestinationListInformation(createDestinationList());

    ASSERT_TRUE(5 == destinationList.getListOfDestinations().size());
    ASSERT_TRUE(3 == destinationList.getListOfSmartDestinations().size());
    ASSERT_TRUE(0 == destinationList.getNumberOfModifiedDevices());
    ASSERT_TRUE(5 == destinationList.getNumberOfAddedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfRemovedDevices());
    ASSERT_TRUE(0 == destinationList.getModifiedDevicesList().size());
    ASSERT_TRUE(5 == destinationList.getAddedDevicesList().size());
    ASSERT_TRUE(0 == destinationList.getRemovedDevicesList().size());

    destinationList.commit();

    ASSERT_TRUE(5 == destinationList.getListOfDestinations().size());
    ASSERT_TRUE(3 == destinationList.getListOfSmartDestinations().size());
    ASSERT_TRUE(0 == destinationList.getNumberOfModifiedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfAddedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfRemovedDevices());
    ASSERT_TRUE(0 == destinationList.getModifiedDevicesList().size());
    ASSERT_TRUE(0 == destinationList.getAddedDevicesList().size());
    ASSERT_TRUE(0 == destinationList.getRemovedDevicesList().size());

    destinationList.clear();

    ASSERT_TRUE(0 == destinationList.getListOfDestinations().size());
    ASSERT_TRUE(0 == destinationList.getListOfSmartDestinations().size());
    ASSERT_TRUE(0 == destinationList.getNumberOfModifiedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfAddedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfRemovedDevices());
    ASSERT_TRUE(0 == destinationList.getModifiedDevicesList().size());
    ASSERT_TRUE(0 == destinationList.getAddedDevicesList().size());
    ASSERT_TRUE(0 == destinationList.getRemovedDevicesList().size());
}

TEST(DestinationListSF, unite)
{
    DestinationList destinationList;

    destinationList.insertDestinationListInformation(createDestinationList());

    ASSERT_TRUE(5 == destinationList.getListOfDestinations().size());
    ASSERT_TRUE(3 == destinationList.getListOfSmartDestinations().size());
    ASSERT_TRUE(0 == destinationList.getNumberOfModifiedDevices());
    ASSERT_TRUE(5 == destinationList.getNumberOfAddedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfRemovedDevices());

    destinationList.commit();

    ASSERT_TRUE(0 == destinationList.getNumberOfAddedDevices());

    std::vector<NodeManagementDestinationData> list;

    {
        // simple device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_A"));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    {
        // simple device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_5000"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SIMPLE));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    {
        // smart device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_C"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SMART));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    DestinationList destinationListOther;

    NodeManagementDestinationListDataPtr destinationListInformation
        = NodeManagementDestinationListDataPtr(new NodeManagementDestinationListData());
    destinationListInformation->setNodeManagementDestinationData(list);

    destinationListOther.insertDestinationListInformation(destinationListInformation);
    destinationListOther.commit();
    ASSERT_TRUE(3 == destinationListOther.getListOfDestinations().size());

    destinationList.unite(destinationListOther);

    ASSERT_TRUE(6 == destinationList.getListOfDestinations().size());
    ASSERT_TRUE(3 == destinationList.getListOfSmartDestinations().size());
    ASSERT_TRUE(0 == destinationList.getNumberOfModifiedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfAddedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfRemovedDevices());
}

TEST(DestinationListSF, subtract)
{
    DestinationList destinationList;

    destinationList.insertDestinationListInformation(createDestinationList());

    ASSERT_TRUE(5 == destinationList.getListOfDestinations().size());
    ASSERT_TRUE(3 == destinationList.getListOfSmartDestinations().size());
    ASSERT_TRUE(0 == destinationList.getNumberOfModifiedDevices());
    ASSERT_TRUE(5 == destinationList.getNumberOfAddedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfRemovedDevices());
    ASSERT_TRUE(0 == destinationList.getModifiedDevicesList().size());
    ASSERT_TRUE(5 == destinationList.getAddedDevicesList().size());
    ASSERT_TRUE(0 == destinationList.getRemovedDevicesList().size());

    destinationList.commit();

    std::vector<NodeManagementDestinationData> list;

    {
        // simple device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_A"));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    {
        // simple device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_5000"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SIMPLE));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }
    {
        // smart device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_C"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SMART));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    DestinationList destinationListOther;

    NodeManagementDestinationListDataPtr destinationListInformation
        = NodeManagementDestinationListDataPtr(new NodeManagementDestinationListData());
    destinationListInformation->setNodeManagementDestinationData(list);

    destinationListOther.insertDestinationListInformation(destinationListInformation);
    destinationListOther.commit();
    ASSERT_TRUE(3 == destinationListOther.getListOfDestinations().size());

    destinationList.subtract(destinationListOther);

    ASSERT_TRUE(3 == destinationList.getListOfDestinations().size());
    ASSERT_TRUE(2 == destinationList.getListOfSmartDestinations().size());
    ASSERT_TRUE(0 == destinationList.getNumberOfModifiedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfAddedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfRemovedDevices());
    ASSERT_TRUE(0 == destinationList.getModifiedDevicesList().size());
    ASSERT_TRUE(0 == destinationList.getAddedDevicesList().size());
    ASSERT_TRUE(0 == destinationList.getRemovedDevicesList().size());
}

TEST(DestinationListSF, insert)
{
    DestinationList destinationList;

    destinationList.insertDestinationListInformation(createDestinationList());

    ASSERT_TRUE(5 == destinationList.getListOfDestinations().size());
    ASSERT_TRUE(3 == destinationList.getListOfSmartDestinations().size());
    ASSERT_TRUE(0 == destinationList.getNumberOfModifiedDevices());
    ASSERT_TRUE(5 == destinationList.getNumberOfAddedDevices());
    ASSERT_TRUE(0 == destinationList.getNumberOfRemovedDevices());
    ASSERT_TRUE(0 == destinationList.getModifiedDevicesList().size());
    ASSERT_TRUE(5 == destinationList.getAddedDevicesList().size());
    ASSERT_TRUE(0 == destinationList.getRemovedDevicesList().size());

    destinationList.commit();

    std::vector<NodeManagementDestinationData> list;

    {
        // simple device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_A"));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    {
        // simple device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        FeatureAddress address;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_5000"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SIMPLE));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    {
        // smart device
        NodeManagementDestinationData destinationInformation;
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:device_C"));
        deviceDescriptionData.setLastStateChange(NetworkManagementStateChange::Value::REMOVED);
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SMART));
        destinationInformation.setDeviceDescription(deviceDescriptionData);

        list.push_back(destinationInformation);
    }

    NodeManagementDestinationListDataPtr destinationListInformation
        = NodeManagementDestinationListDataPtr(new NodeManagementDestinationListData());
    destinationListInformation->setNodeManagementDestinationData(list);
    destinationList.insertDestinationListInformation(destinationListInformation);

    ASSERT_TRUE(5 == destinationList.getListOfDestinations().size());
    ASSERT_TRUE(2 == destinationList.getListOfSmartDestinations().size());
    ASSERT_TRUE(1 == destinationList.getNumberOfModifiedDevices());
    ASSERT_TRUE(1 == destinationList.getNumberOfAddedDevices());
    ASSERT_TRUE(1 == destinationList.getNumberOfRemovedDevices());
    ASSERT_TRUE(1 == destinationList.getModifiedDevicesList().size());
    ASSERT_TRUE(1 == destinationList.getAddedDevicesList().size());
    ASSERT_TRUE(1 == destinationList.getRemovedDevicesList().size());

    auto removedList = destinationList.getRemovedDevicesList();
    ASSERT_TRUE(1 == removedList.size());
    NodeManagementDestinationData removedData = destinationList.getDestinationInformationFromRemoved(removedList.front());
    ASSERT_TRUE(removedData.getDeviceDescriptionIsSet());
    ASSERT_TRUE(removedData.getDeviceDescription().getLastStateChangeIsSet());
    ASSERT_TRUE(
        NetworkManagementStateChange::Value::REMOVED == removedData.getDeviceDescription().getLastStateChange().getValue());

    auto modifiedList = destinationList.getModifiedDevicesList();

    ASSERT_TRUE(1 == modifiedList.size());

    auto addedList = destinationList.getAddedDevicesList();

    ASSERT_TRUE(1 == addedList.size());

    auto allList = destinationList.getListOfDestinations();

    ASSERT_TRUE(5 == allList.size());

    NodeManagementDestinationListDataPtr update = destinationList.getDestinationListInformationUpdate("");

    ASSERT_TRUE(update->getNodeManagementDestinationDataIsSet());
    ASSERT_TRUE(3 == update->getNodeManagementDestinationData().size());
}
