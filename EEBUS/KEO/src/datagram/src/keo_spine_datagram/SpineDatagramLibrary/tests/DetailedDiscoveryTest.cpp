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
#include <keo_datagram/core/Datagram.h>
#include <keo_spine_datagramVersion.h>

// module to test
#include <keo_datagram/core/DetailedDiscovery.h>

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

void addTab(std::string& string, int numberOfTabs)
{
    for (int i = 0; i < numberOfTabs; ++i)
    {
        string += "   ";
    }
}

DatagramPtr createDetailedDiscovery()
{
    NodeManagementDetailedDiscoveryData detailedDiscoveryData;

    std::vector<xs_unsignedInt> addr0;
    addr0.push_back(0);

    std::vector<xs_unsignedInt> addr1;
    addr1.push_back(1);

    NodeManagementSpecificationVersionList nodeManagementSpecificationVersionList;
    std::vector<xs_string> specificationVersionList;
    specificationVersionList.push_back(SPINE_VERSION_STRING);
    nodeManagementSpecificationVersionList.setSpecificationVersion(specificationVersionList);
    detailedDiscoveryData.setSpecificationVersionList(nodeManagementSpecificationVersionList);

    {
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:myFancyEEBusDevice"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SMART));
        deviceDescriptionData.setDeviceType(DeviceType::Value::WASHER);

        detailedDiscoveryData.setDeviceInformation(
            NodeManagementDetailedDiscoveryDeviceInformation(deviceDescriptionData));
    }

    {
        // entity information
        std::vector<NodeManagementDetailedDiscoveryEntityInformation> entityInformationList;
        {
            // entity 0
            NetworkManagementEntityDescriptionData entityDescription;

            EntityAddress entityAddress(addr0);
            entityDescription.setEntityAddress(entityAddress);
            entityDescription.setEntityType(EntityType::Value::DEVICE_INFORMATION);

            NodeManagementDetailedDiscoveryEntityInformation entityInformation;
            entityInformation.setDescription(entityDescription);
            entityInformationList.push_back(entityInformation);
        }

        {
            // entity 1
            NetworkManagementEntityDescriptionData entityDescription;

            EntityAddress entityAddress(addr1);
            entityDescription.setEntityAddress(entityAddress);
            entityDescription.setEntityType(EntityType::Value::INVERTER); // Inverter;Control

            NodeManagementDetailedDiscoveryEntityInformation entityInformation;
            entityInformation.setDescription(entityDescription);
            entityInformationList.push_back(entityInformation);
        }

        detailedDiscoveryData.setEntityInformation(entityInformationList);
    }

    {
        // feature information
        std::vector<NodeManagementDetailedDiscoveryFeatureInformation> featureInformationList;

        {
            // entity 0 feature 0
            NetworkManagementFeatureDescriptionData featureDescription;
            // NetworkManagementNodeDescriptionData nodeDescriptionData;

            FeatureAddress featureAddress;
            featureAddress.setEntity(addr0);
            featureAddress.setFeature(0);
            featureDescription.setFeatureAddress(featureAddress);
            featureDescription.setRole(Role(Role::Value::SPECIAL));
            featureDescription.setFeatureType(FeatureType::Value::NODE_MANAGEMENT);

            std::vector<FunctionProperty> functionVector;
            {
                FunctionProperty functionProperty;
                Function function("nodeManagementDetailedDiscoveryData");
                functionProperty.setFunction(function);
                PossibleOperations possibleOperations;
                PossibleOperationsRead possibleOperationsRead;
                possibleOperations.setRead(possibleOperationsRead);
                functionProperty.setPossibleOperations(possibleOperations);
                functionVector.push_back(functionProperty);
            }
            {
                FunctionProperty functionProperty;
                Function function("nodeManagementDestinationListData");
                functionProperty.setFunction(function);
                PossibleOperations possibleOperations;
                PossibleOperationsRead possibleOperationsRead;
                possibleOperations.setRead(possibleOperationsRead);
                functionProperty.setPossibleOperations(possibleOperations);
                functionVector.push_back(functionProperty);
            }
            featureDescription.setSupportedFunction(functionVector);

            NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
            featureInformation.setDescription(featureDescription);
            // featureInformation.setNodeDescription(nodeDescriptionData);
            featureInformationList.push_back(featureInformation);
        }

        {
            // entity 1 feature 1
            NetworkManagementFeatureDescriptionData featureDescription;
            // NetworkManagementNodeDescriptionData nodeDescriptionData;

            FeatureAddress featureAddress;
            featureAddress.setEntity(addr1);
            featureAddress.setFeature(1);
            featureDescription.setFeatureAddress(featureAddress);
            featureDescription.setRole(Role(Role::Value::SERVER));
            featureDescription.setFeatureType(FeatureType::Value::DEVICE_DIAGNOSIS);

            std::vector<FunctionProperty> functionVector;
            {
                FunctionProperty functionProperty;
                Function function(Function::Value::DEVICE_DIAGNOSIS_STATE_DATA);
                functionProperty.setFunction(function);
                PossibleOperations possibleOperations;
                PossibleOperationsRead possibleOperationsRead;
                possibleOperations.setRead(possibleOperationsRead);
                functionProperty.setPossibleOperations(possibleOperations);
                functionVector.push_back(functionProperty);
            }
            featureDescription.setSupportedFunction(functionVector);

            NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
            featureInformation.setDescription(featureDescription);
            // featureInformation.setNodeDescription(nodeDescriptionData);
            featureInformationList.push_back(featureInformation);
        }

        {
            // entity 1 feature 2
            NetworkManagementFeatureDescriptionData featureDescription;
            // NetworkManagementNodeDescriptionData nodeDescriptionData;

            FeatureAddress featureAddress;
            featureAddress.setEntity(addr1);
            featureAddress.setFeature(2);
            featureDescription.setFeatureAddress(featureAddress);
            featureDescription.setRole(Role(Role::Value::SERVER));
            featureDescription.setFeatureType(FeatureType::Value::ELECTRICAL_CONNECTION);

            NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
            featureInformation.setDescription(featureDescription);
            // featureInformation.setNodeDescription(nodeDescriptionData);
            featureInformationList.push_back(featureInformation);
        }

        {
            // entity 1 feature 3
            NetworkManagementFeatureDescriptionData featureDescription;
            // NetworkManagementNodeDescriptionData nodeDescriptionData;

            FeatureAddress featureAddress;
            featureAddress.setEntity(addr1);
            featureAddress.setFeature(3);
            featureDescription.setFeatureAddress(featureAddress);
            featureDescription.setRole(Role(Role::Value::SERVER));
            featureDescription.setFeatureType(FeatureType::Value::MEASUREMENT);

            NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
            featureInformation.setDescription(featureDescription);
            // featureInformation.setNodeDescription(nodeDescriptionData);
            featureInformationList.push_back(featureInformation);
        }

        {
            // entity 1 feature 4
            NetworkManagementFeatureDescriptionData featureDescription;
            // NetworkManagementNodeDescriptionData nodeDescriptionData;

            FeatureAddress featureAddress;
            featureAddress.setEntity(addr1);
            featureAddress.setFeature(4);
            featureDescription.setFeatureAddress(featureAddress);
            featureDescription.setRole(Role(Role::Value::SERVER));
            featureDescription.setFeatureType(FeatureType::Value::SETPOINT);

            NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
            featureInformation.setDescription(featureDescription);
            // featureInformation.setNodeDescription(nodeDescriptionData);
            featureInformationList.push_back(featureInformation);
        }

        detailedDiscoveryData.setFeatureInformation(featureInformationList);
    }

    NodeManagementDetailedDiscoveryDataPtr pData
        = NodeManagementDetailedDiscoveryDataPtr(new NodeManagementDetailedDiscoveryData(detailedDiscoveryData));

    FeatureAddress sourceAddress("d:myFancyEEBusDevice", 0, 0);
    FeatureAddress destinationAddress("d:myOtherFancyEEBusDevice", 0, 0);
    Header header = Header(sourceAddress, destinationAddress, CmdClassifier::Value::NOTIFY);
    DatagramPtr pDatagram = DatagramPtr(new Datagram(header, Cmd(pData)));

    return pDatagram;
}

TEST(DetailedDiscoverySF, memoryLeak)
{
    DetailedDiscovery detailedDiscovery;

    EXPECT_TRUE(true);
}

TEST(DetailedDiscoverySF, EmptyDetailedDiscoveryIsEmpty)
{
    const DetailedDiscovery dd;
    // Redmine #2285: this will not compile until isEmpty() is made const.
    ASSERT_TRUE(dd.isEmpty());
}

TEST(DetailedDiscoverySF, createFromDatagram)
{

    DatagramPtr datagram = createDetailedDiscovery();

    DetailedDiscovery detailedDiscovery;

    ASSERT_TRUE(detailedDiscovery.setDiscoveryInformationFromCmd(datagram->getCmd()));

    std::vector<xs_unsignedInt> addr0;
    addr0.push_back(0);

    std::vector<xs_unsignedInt> addr1;
    addr1.push_back(1);

    ASSERT_TRUE(detailedDiscovery.containsEntityAddress(addr0));
    ASSERT_TRUE(detailedDiscovery.containsEntityType("DeviceInformation"));
    ASSERT_TRUE(detailedDiscovery.containsEntityType("Inverter"));
    ASSERT_TRUE(detailedDiscovery.containsFeatureIdOnEntity(addr0, 0));
    ASSERT_FALSE(detailedDiscovery.containsFeatureIdOnEntity(addr0, 1));
    ASSERT_FALSE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 0));
    ASSERT_TRUE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 1));
    ASSERT_TRUE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 2));
    ASSERT_TRUE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 3));
    ASSERT_TRUE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 4));
    ASSERT_FALSE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 5));
    ASSERT_TRUE(detailedDiscovery.containsFeatureType("NodeManagement"));
    ASSERT_TRUE(detailedDiscovery.containsFeatureType("DeviceDiagnosis"));
    ASSERT_TRUE(detailedDiscovery.containsFeatureType("ElectricalConnection"));
    ASSERT_TRUE(detailedDiscovery.containsFeatureType("Setpoint"));
    ASSERT_TRUE(detailedDiscovery.containsFeatureType("Measurement"));
    ASSERT_TRUE(detailedDiscovery.containsFeatureTypeOnEntity(addr0, "NodeManagement"));
    ASSERT_FALSE(detailedDiscovery.containsFeatureTypeOnEntity(addr0, "InverterControl"));
    ASSERT_TRUE(detailedDiscovery.containsFeatureTypeOnEntity(addr1, "ElectricalConnection"));
    ASSERT_TRUE(detailedDiscovery.containsFeatureTypeOnEntity(addr1, "Setpoint"));
    ASSERT_TRUE(detailedDiscovery.containsFeatureTypeOnEntity(addr1, "Measurement"));

    ASSERT_TRUE(2 == detailedDiscovery.getEntities().size());
    ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByEntityType("Inverter").size());
    ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByFeatureType("DeviceDiagnosis").size());
    ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByFeatureType("ElectricalConnection").size());
    ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByFeatureType("Measurement").size());
    ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByFeatureType("Setpoint").size());

    ASSERT_TRUE(1 == detailedDiscovery.getFeatures(addr0).size());
    ASSERT_TRUE(4 == detailedDiscovery.getFeatures(addr1).size());
    ASSERT_TRUE(1 == detailedDiscovery.getFeaturesByFeatureType(addr1, "DeviceDiagnosis").size());
    ASSERT_TRUE(1 == detailedDiscovery.getFeaturesByFeatureType(addr1, "ElectricalConnection").size());
    ASSERT_TRUE(1 == detailedDiscovery.getFeaturesByFeatureType(addr1, "Measurement").size());
    ASSERT_TRUE(1 == detailedDiscovery.getFeaturesByFeatureType(addr1, "Setpoint").size());
    ASSERT_TRUE(0 == detailedDiscovery.getFeaturesByFeatureType(addr1, "unknownProcessId").size());
}

TEST(DetailedDiscoverySF, createFromSetter)
{
    DetailedDiscovery detailedDiscovery;

    std::vector<xs_unsignedInt> addr0;
    addr0.push_back(0);

    std::vector<xs_unsignedInt> addr1;
    addr1.push_back(1);

    NodeManagementSpecificationVersionList specificationVersionList;
    std::vector<xs_string> list;
    list.push_back(SPINE_VERSION_STRING);
    specificationVersionList.setSpecificationVersion(list);
    detailedDiscovery.setSpecificationVersionList(specificationVersionList);

    {
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress("d:myFancyEEBusDevice"));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SMART));
        deviceDescriptionData.setDeviceType(DeviceType::Value::DRYER);

        detailedDiscovery.setDeviceDescription(deviceDescriptionData);
    }

    { // entity information
      { // entity 0
          NetworkManagementEntityDescriptionData entityDescription;
    // NetworkManagementNodeDescriptionData nodeDescriptionData;

    EntityAddress entityAddress(addr0);
    entityDescription.setEntityAddress(entityAddress);
    entityDescription.setEntityType(EntityType::Value::DEVICE_INFORMATION);

    NodeManagementDetailedDiscoveryEntityInformation entityInformation;
    entityInformation.setDescription(entityDescription);

    detailedDiscovery.addDetailedDiscoveryEntityInformation(entityInformation);
}

{
    // entity 1
    NetworkManagementEntityDescriptionData entityDescription;
    // NetworkManagementNodeDescriptionData nodeDescriptionData;

    EntityAddress entityAddress(addr1);
    entityDescription.setEntityAddress(entityAddress);
    entityDescription.setEntityType(EntityType::Value::INVERTER); // Inverter;Control

    NodeManagementDetailedDiscoveryEntityInformation entityInformation;
    entityInformation.setDescription(entityDescription);

    detailedDiscovery.addDetailedDiscoveryEntityInformation(entityInformation);
}
}

{
    // feature information
    {
        // entity 0 feature 0
        NetworkManagementFeatureDescriptionData featureDescription;
        // NetworkManagementNodeDescriptionData nodeDescriptionData;

        FeatureAddress featureAddress;
        featureAddress.setEntity(addr0);
        featureAddress.setFeature(0);
        featureDescription.setFeatureAddress(featureAddress);
        featureDescription.setRole(Role(Role::Value::SPECIAL));
        featureDescription.setFeatureType(FeatureType::Value::NODE_MANAGEMENT);

        std::vector<FunctionProperty> functionVector;
        {
            FunctionProperty functionProperty;
            Function function("nodeManagementDetailedDiscoveryData");
            functionProperty.setFunction(function);
            PossibleOperations possibleOperations;
            PossibleOperationsRead possibleOperationsRead;
            possibleOperations.setRead(possibleOperationsRead);
            functionProperty.setPossibleOperations(possibleOperations);
            functionVector.push_back(functionProperty);
        }
        {
            FunctionProperty functionProperty;
            Function function("nodeManagementDestinationListData");
            functionProperty.setFunction(function);
            PossibleOperations possibleOperations;
            PossibleOperationsRead possibleOperationsRead;
            possibleOperations.setRead(possibleOperationsRead);
            functionProperty.setPossibleOperations(possibleOperations);
            functionVector.push_back(functionProperty);
        }
        featureDescription.setSupportedFunction(functionVector);

        NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
        featureInformation.setDescription(featureDescription);
        // featureInformation.setNodeDescription(nodeDescriptionData);

        detailedDiscovery.addDetailedDiscoveryFeatureInformation(featureInformation);
    }

    {
        // entity 1 feature 1
        NetworkManagementFeatureDescriptionData featureDescription;
        // NetworkManagementNodeDescriptionData nodeDescriptionData;

        FeatureAddress featureAddress;
        featureAddress.setEntity(addr1);
        featureAddress.setFeature(1);
        featureDescription.setFeatureAddress(featureAddress);
        featureDescription.setRole(Role(Role::Value::SERVER));
        featureDescription.setFeatureType(FeatureType::Value::DEVICE_DIAGNOSIS);

        std::vector<FunctionProperty> functionVector;
        {
            FunctionProperty functionProperty;
            Function function(Function::Value::DEVICE_DIAGNOSIS_STATE_DATA);
            functionProperty.setFunction(function);
            PossibleOperations possibleOperations;
            PossibleOperationsRead possibleOperationsRead;
            possibleOperations.setRead(possibleOperationsRead);
            functionProperty.setPossibleOperations(possibleOperations);
            functionVector.push_back(functionProperty);
        }
        featureDescription.setSupportedFunction(functionVector);

        NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
        featureInformation.setDescription(featureDescription);
        // featureInformation.setNodeDescription(nodeDescriptionData);

        detailedDiscovery.addDetailedDiscoveryFeatureInformation(featureInformation);
    }

    {
        // entity 1 feature 2
        NetworkManagementFeatureDescriptionData featureDescription;
        // NetworkManagementNodeDescriptionData nodeDescriptionData;

        FeatureAddress featureAddress;
        featureAddress.setEntity(addr1);
        featureAddress.setFeature(2);
        featureDescription.setFeatureAddress(featureAddress);
        featureDescription.setRole(Role(Role::Value::SERVER));
        featureDescription.setFeatureType(FeatureType::Value::ELECTRICAL_CONNECTION);

        NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
        featureInformation.setDescription(featureDescription);
        // featureInformation.setNodeDescription(nodeDescriptionData);

        detailedDiscovery.addDetailedDiscoveryFeatureInformation(featureInformation);
    }

    {
        // entity 1 feature 3
        NetworkManagementFeatureDescriptionData featureDescription;
        // NetworkManagementNodeDescriptionData nodeDescriptionData;

        FeatureAddress featureAddress;
        featureAddress.setEntity(addr1);
        featureAddress.setFeature(3);
        featureDescription.setFeatureAddress(featureAddress);
        featureDescription.setRole(Role(Role::Value::SERVER));
        featureDescription.setFeatureType(FeatureType::Value::MEASUREMENT);

        NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
        featureInformation.setDescription(featureDescription);
        // featureInformation.setNodeDescription(nodeDescriptionData);

        detailedDiscovery.addDetailedDiscoveryFeatureInformation(featureInformation);
    }

    {
        // entity 1 feature 4
        NetworkManagementFeatureDescriptionData featureDescription;
        // NetworkManagementNodeDescriptionData nodeDescriptionData;

        FeatureAddress featureAddress;
        featureAddress.setEntity(addr1);
        featureAddress.setFeature(4);
        featureDescription.setFeatureAddress(featureAddress);
        featureDescription.setRole(Role(Role::Value::SERVER));
        featureDescription.setFeatureType(FeatureType::Value::SETPOINT);

        NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
        featureInformation.setDescription(featureDescription);
        // featureInformation.setNodeDescription(nodeDescriptionData);

        detailedDiscovery.addDetailedDiscoveryFeatureInformation(featureInformation);
    }
}

ASSERT_TRUE(detailedDiscovery.containsEntityAddress(addr0));
ASSERT_TRUE(detailedDiscovery.containsEntityType("DeviceInformation"));
ASSERT_TRUE(detailedDiscovery.containsEntityType("Inverter"));
ASSERT_TRUE(detailedDiscovery.containsFeatureIdOnEntity(addr0, 0));
ASSERT_FALSE(detailedDiscovery.containsFeatureIdOnEntity(addr0, 1));
ASSERT_FALSE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 0));
ASSERT_TRUE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 1));
ASSERT_TRUE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 2));
ASSERT_TRUE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 3));
ASSERT_TRUE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 4));
ASSERT_FALSE(detailedDiscovery.containsFeatureIdOnEntity(addr1, 5));
ASSERT_TRUE(detailedDiscovery.containsFeatureType("NodeManagement"));
ASSERT_TRUE(detailedDiscovery.containsFeatureType("DeviceDiagnosis"));
ASSERT_TRUE(detailedDiscovery.containsFeatureType("ElectricalConnection"));
ASSERT_TRUE(detailedDiscovery.containsFeatureType("Setpoint"));
ASSERT_TRUE(detailedDiscovery.containsFeatureType("Measurement"));
ASSERT_TRUE(detailedDiscovery.containsFeatureTypeOnEntity(addr0, "NodeManagement"));
ASSERT_FALSE(detailedDiscovery.containsFeatureTypeOnEntity(addr0, "InverterControl"));
ASSERT_TRUE(detailedDiscovery.containsFeatureTypeOnEntity(addr1, "ElectricalConnection"));
ASSERT_TRUE(detailedDiscovery.containsFeatureTypeOnEntity(addr1, "Setpoint"));
ASSERT_TRUE(detailedDiscovery.containsFeatureTypeOnEntity(addr1, "Measurement"));

ASSERT_TRUE(2 == detailedDiscovery.getEntities().size());
ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByEntityType("Inverter").size());
ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByFeatureType("DeviceDiagnosis").size());
ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByFeatureType("ElectricalConnection").size());
ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByFeatureType("Measurement").size());
ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByFeatureType("Setpoint").size());

ASSERT_TRUE(1 == detailedDiscovery.getFeatures(addr0).size());
ASSERT_TRUE(4 == detailedDiscovery.getFeatures(addr1).size());
ASSERT_TRUE(1 == detailedDiscovery.getFeaturesByFeatureType(addr1, "DeviceDiagnosis").size());
ASSERT_TRUE(1 == detailedDiscovery.getFeaturesByFeatureType(addr1, "ElectricalConnection").size());
ASSERT_TRUE(1 == detailedDiscovery.getFeaturesByFeatureType(addr1, "Measurement").size());
ASSERT_TRUE(1 == detailedDiscovery.getFeaturesByFeatureType(addr1, "Setpoint").size());
ASSERT_TRUE(0 == detailedDiscovery.getFeaturesByFeatureType(addr1, "unknownProcessId").size());
}

TEST(DetailedDiscoverySF, entityGetter)
{
    DetailedDiscovery detailedDiscovery;

    DatagramPtr datagram = createDetailedDiscovery();

    ASSERT_TRUE(detailedDiscovery.setDiscoveryInformationFromCmd(datagram->getCmd()));

    std::vector<xs_unsignedInt> addr0;
    addr0.push_back(0);

    std::vector<xs_unsignedInt> addr1;
    addr1.push_back(1);

    NodeManagementDetailedDiscoveryEntityInformationPtr entityPtr
        = detailedDiscovery.getDetailedDiscoveryEntityInformation(addr0);

    ASSERT_TRUE(entityPtr != nullptr);
    ASSERT_TRUE(entityPtr->getDescriptionIsSet());
    ASSERT_TRUE(EntityType::Value::DEVICE_INFORMATION == entityPtr->getDescription().getEntityType().getValue());

    entityPtr = detailedDiscovery.getDetailedDiscoveryEntityInformation(addr1);

    ASSERT_TRUE(entityPtr != nullptr);
    ASSERT_TRUE(entityPtr->getDescriptionIsSet());
    ASSERT_TRUE(EntityType::Value::INVERTER == entityPtr->getDescription().getEntityType().getValue());
}


TEST(DetailedDiscoverySF, featureGetter)
{
    DetailedDiscovery detailedDiscovery;

    DatagramPtr datagram = createDetailedDiscovery();

    ASSERT_TRUE(detailedDiscovery.setDiscoveryInformationFromCmd(datagram->getCmd()));

    std::vector<xs_unsignedInt> addr0;
    addr0.push_back(0);

    std::vector<xs_unsignedInt> addr1;
    addr1.push_back(1);

    NodeManagementDetailedDiscoveryFeatureInformationPtr featurePtr
        = detailedDiscovery.getDetailedDiscoveryFeatureInformation(addr0, 0);

    ASSERT_TRUE(featurePtr != nullptr);
    ASSERT_TRUE(featurePtr->getDescriptionIsSet());
    ASSERT_TRUE(featurePtr->getDescription().getFeatureTypeIsSet());
    ASSERT_TRUE(FeatureType::Value::NODE_MANAGEMENT == featurePtr->getDescription().getFeatureType().getValue());

    featurePtr = detailedDiscovery.getDetailedDiscoveryFeatureInformation(addr1, 2);

    ASSERT_TRUE(featurePtr != nullptr);
    ASSERT_TRUE(featurePtr->getDescriptionIsSet());
    ASSERT_TRUE(featurePtr->getDescription().getFeatureTypeIsSet());
    ASSERT_TRUE(FeatureType::Value::ELECTRICAL_CONNECTION == featurePtr->getDescription().getFeatureType().getValue());
}

TEST(DetailedDiscoverySF, discoveryGetter)
{
    DetailedDiscovery detailedDiscovery;

    DatagramPtr datagram = createDetailedDiscovery();

    ASSERT_TRUE(detailedDiscovery.setDiscoveryInformationFromCmd(datagram->getCmd()));

    NodeManagementDetailedDiscoveryDataPtr informationPtr = detailedDiscovery.getDetailedDiscoveryDataPtr();

    ASSERT_TRUE(informationPtr != nullptr);
    ASSERT_TRUE(informationPtr->getDeviceInformationIsSet());
    ASSERT_TRUE(informationPtr->getEntityInformationIsSet());
    ASSERT_TRUE(informationPtr->getFeatureInformationIsSet());
    ASSERT_TRUE(informationPtr->getSpecificationVersionListIsSet());
    ASSERT_TRUE(2 == informationPtr->getEntityInformation().size());
    ASSERT_TRUE(5 == informationPtr->getFeatureInformation().size());
}

TEST(DetailedDiscoverySF, clear)
{
    DetailedDiscovery detailedDiscovery;

    DatagramPtr datagram = createDetailedDiscovery();

    ASSERT_TRUE(detailedDiscovery.setDiscoveryInformationFromCmd(datagram->getCmd()));

    NodeManagementDetailedDiscoveryDataPtr detailedDiscoveryDataPtr = detailedDiscovery.getDetailedDiscoveryDataPtr();

    ASSERT_TRUE(detailedDiscoveryDataPtr != nullptr);
    ASSERT_TRUE(detailedDiscoveryDataPtr->getDeviceInformationIsSet());
    ASSERT_TRUE(detailedDiscoveryDataPtr->getEntityInformationIsSet());
    ASSERT_TRUE(detailedDiscoveryDataPtr->getFeatureInformationIsSet());
    ASSERT_TRUE(detailedDiscoveryDataPtr->getSpecificationVersionListIsSet());
    ASSERT_TRUE(2 == detailedDiscoveryDataPtr->getEntityInformation().size());
    ASSERT_TRUE(5 == detailedDiscoveryDataPtr->getFeatureInformation().size());

    detailedDiscovery.clear();

    ASSERT_TRUE(0 == detailedDiscovery.getEntities().size());
}

TEST(DetailedDiscoverySF, replaceEntity)
{
    DetailedDiscovery detailedDiscovery;

    DatagramPtr datagram = createDetailedDiscovery();

    ASSERT_TRUE(detailedDiscovery.setDiscoveryInformationFromCmd(datagram->getCmd()));

    ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByEntityType("Inverter").size());

    {
        // entity
        NetworkManagementEntityDescriptionData entityDescription;
        // NetworkManagementNodeDescriptionData nodeDescriptionData;

        std::vector<xs_unsignedInt> addr1;
        addr1.push_back(1);

        EntityAddress entityAddress(addr1);
        entityDescription.setEntityAddress(entityAddress);
        entityDescription.setEntityType(EntityType::Value::DHW_STORAGE); // Inverter;Control

        NodeManagementDetailedDiscoveryEntityInformation entityInformation;
        entityInformation.setDescription(entityDescription);

        detailedDiscovery.addDetailedDiscoveryEntityInformation(entityInformation);
    }
    ASSERT_TRUE(0 == detailedDiscovery.getEntitiesByEntityType(EntityType::Value::INVERTER).size());
    ASSERT_TRUE(1 == detailedDiscovery.getEntitiesByEntityType(EntityType::Value::DHW_STORAGE).size());
    ASSERT_TRUE(2 == detailedDiscovery.getEntities().size());
}

TEST(DetailedDiscoverySF, replaceFeature)
{
    DetailedDiscovery detailedDiscovery;

    DatagramPtr datagram = createDetailedDiscovery();

    ASSERT_TRUE(detailedDiscovery.setDiscoveryInformationFromCmd(datagram->getCmd()));

    std::vector<xs_unsignedInt> addr1;
    addr1.push_back(1);

    ASSERT_TRUE(1 == detailedDiscovery.getFeaturesByFeatureType(addr1, "DeviceDiagnosis").size());

    {
        // entity 1 feature 1
        NetworkManagementFeatureDescriptionData featureDescription;
        // NetworkManagementNodeDescriptionData nodeDescriptionData;

        FeatureAddress featureAddress;
        featureAddress.setEntity(addr1);
        featureAddress.setFeature(1);
        featureDescription.setFeatureAddress(featureAddress);
        featureDescription.setRole(Role(Role::Value::SERVER));
        featureDescription.setFeatureType(FeatureType::Value::DATA_TUNNELING);

        std::vector<FunctionProperty> functionVector;
        {
            FunctionProperty functionProperty;
            Function function(Function::Value::DEVICE_DIAGNOSIS_STATE_DATA);
            functionProperty.setFunction(function);
            PossibleOperations possibleOperations;
            PossibleOperationsRead possibleOperationsRead;
            possibleOperations.setRead(possibleOperationsRead);
            functionProperty.setPossibleOperations(possibleOperations);
            functionVector.push_back(functionProperty);
        }
        featureDescription.setSupportedFunction(functionVector);

        NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
        featureInformation.setDescription(featureDescription);
        detailedDiscovery.addDetailedDiscoveryFeatureInformation(featureInformation);
    }

    ASSERT_TRUE(0 == detailedDiscovery.getFeaturesByFeatureType(addr1, "DeviceDiagnosis").size());
    ASSERT_TRUE(1 == detailedDiscovery.getFeaturesByFeatureType(addr1, "DataTunneling").size());
    ASSERT_TRUE(4 == detailedDiscovery.getFeatures(addr1).size());
}

TEST(DetailedDiscoverySF, CustomEntityTypeCanBePutAndRetrieved_Redmine2284)
{
    DetailedDiscovery detailedDiscovery;

    // Create a custom entity type
    EntityType type = EntityType::fromString("_i:34863_AnalogInput");

    // Put an entity of that type into the detailed discovery
    NetworkManagementEntityDescriptionData description;
    description.setEntityAddress(EntityAddress({ 1 }));
    description.setEntityType(type);
    detailedDiscovery.addDetailedDiscoveryEntityInformation(
        NodeManagementDetailedDiscoveryEntityInformation(description));

    // Assert that it can be found and is the right one
    auto entities = detailedDiscovery.getEntitiesByEntityType(type);
    ASSERT_EQ(1U, entities.size());
    ASSERT_EQ(1U, entities[0].size());
    ASSERT_EQ(1U, entities[0][0]);

    // Second part: use two different individual types
    EntityType type2 = EntityType::fromString("_i:12345_CustomEntity");

    // Put an entity of that type into the detailed discovery
    description.setEntityAddress(EntityAddress({ 2 }));
    description.setEntityType(type2);
    detailedDiscovery.addDetailedDiscoveryEntityInformation(
        NodeManagementDetailedDiscoveryEntityInformation(description));

    // Assert that it can be found and is the right one
    entities = detailedDiscovery.getEntitiesByEntityType(type2);
    ASSERT_EQ(1U, entities.size());
    ASSERT_EQ(1U, entities[0].size());
    ASSERT_EQ(2U, entities[0][0]);
}
