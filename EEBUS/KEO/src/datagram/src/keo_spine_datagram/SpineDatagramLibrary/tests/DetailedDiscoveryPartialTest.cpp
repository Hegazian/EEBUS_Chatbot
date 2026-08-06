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
#include <keo_datagram/core/SpineDatagram.h>
#include <keo_spine_datagramVersion.h>

#include <keo_datagram/core/DetailedDiscovery.h>

// module to test
#include <keo_datagram/core/DetailedDiscoveryPartial.h>

/* ************************************************************************** *
 *  defines                                                                   *
 * ************************************************************************** */
//#define PRINT_DETAILED_DISCOVERY

/* ************************************************************************** *
 *  types                                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  definition                                                                *
 * ************************************************************************** */
static const std::string spineSourceDeviceAddr("d:myFancyEEBusDevice");
static const std::string spineDestinationAddr("d:myOtherFancyEEBusDevice");

// flooding the global namespace ....
using namespace keo_datagram;

#ifdef PRINT_DETAILED_DISCOVERY
std::string datagramToPrettyString(SpineDatagramPtr datagram);

void printDetailedDiscovery(const std::string description,
                            const NodeManagementDetailedDiscoveryData& detailedDiscoveryData)
{
    NodeManagementDetailedDiscoveryDataPtr pData
        = NodeManagementDetailedDiscoveryDataPtr(new NodeManagementDetailedDiscoveryData(detailedDiscoveryData));

    FeatureAddress sourceAddress(spineSourceDeviceAddr, 0, 0);
    FeatureAddress destinationAddress(spineDestinationAddr, 0, 0);
    HeaderPtr header = HeaderPtr(new Header(sourceAddress, destinationAddress, keo_datagram::CmdClassifier::Value::NOTIFY));

    keo_datagram::CmdPtr cmdPtr(new Cmd(pData));
    SpineDatagramPtr pDatagram = SpineDatagramPtr(new SpineDatagram(header, cmdPtr));
    std::cout << description << std::endl;
    std::cout << datagramToPrettyString(pDatagram) << std::endl;
}

void printDetailedDiscoveryPartial(const std::string description,
                                   const DetailedDiscoveryPartial& detailedDiscoveryPartial)
{
    FeatureAddress sourceAddress(spineSourceDeviceAddr, 0, 0);
    FeatureAddress destinationAddress(spineDestinationAddr, 0, 0);
    HeaderPtr pHeader = HeaderPtr(new Header(sourceAddress, destinationAddress, keo_datagram::CmdClassifier::Value::NOTIFY));
    std::cout << description << std::endl;
    std::cout << datagramToPrettyString(detailedDiscoveryPartial.getPartialDetailedDiscoveryDatagram(pHeader))
              << std::endl;
}
#else
void printDetailedDiscovery(const std::string description,
                            const NodeManagementDetailedDiscoveryData& detailedDiscoveryData)
{
    (void)spineSourceDeviceAddr;
    (void)spineDestinationAddr;

    (void)description;
    (void)detailedDiscoveryData;
}

void printDetailedDiscoveryPartial(const std::string description,
                                   const DetailedDiscoveryPartial& detailedDiscoveryPartial)
{
    (void)spineSourceDeviceAddr;
    (void)spineDestinationAddr;

    (void)description;
    (void)detailedDiscoveryPartial;
}
#endif /* PRINT_DETAILED_DISCOVERY */

NodeManagementDetailedDiscoveryData createBaseDetailedDiscoveryForCompare()
{
    NodeManagementDetailedDiscoveryData detailedDiscoveryData;

    std::vector<xs_unsignedInt> addr0;
    addr0.push_back(0);

    NodeManagementSpecificationVersionList nodeManagementSpecificationVersionList;
    std::vector<xs_string> specificationVersionList;
    specificationVersionList.push_back(SPINE_VERSION_STRING);
    nodeManagementSpecificationVersionList.setSpecificationVersion(specificationVersionList);
    detailedDiscoveryData.setSpecificationVersionList(nodeManagementSpecificationVersionList);

    {
        NetworkManagementDeviceDescriptionData deviceDescriptionData;
        deviceDescriptionData.setDeviceAddress(DeviceAddress(spineSourceDeviceAddr));
        deviceDescriptionData.setNetworkFeatureSet(NetworkManagementFeatureSet(NetworkManagementFeatureSet::Value::SMART));
        deviceDescriptionData.setDeviceType(DeviceType(DeviceType::Value::WASHER));

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
            entityDescription.setEntityType(EntityType(EntityType::Value::DEVICE_INFORMATION));

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
            featureDescription.setFeatureType(FeatureType(FeatureType::Value::NODE_MANAGEMENT));

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
            featureDescription.setSupportedFunction(functionVector);

            NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
            featureInformation.setDescription(featureDescription);
            // featureInformation.setNodeDescription(nodeDescriptionData);
            featureInformationList.push_back(featureInformation);
        }

        detailedDiscoveryData.setFeatureInformation(featureInformationList);
    }

    return detailedDiscoveryData;
}

bool addEntity(DetailedDiscovery& detailedDiscovery, const xs_unsignedInt entityAddr, EntityType entityType)
{
    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryData;
    pDetailedDiscoveryData = detailedDiscovery.getDetailedDiscoveryDataPtr();
    std::vector<NodeManagementDetailedDiscoveryEntityInformation> entityInformationList
        = pDetailedDiscoveryData->getEntityInformation();

    pDetailedDiscoveryData->getDeviceInformation().getDescription().getDeviceAddress();

    NetworkManagementEntityDescriptionData entityDescription;
    std::vector<xs_unsignedInt> addr;
    addr.push_back(entityAddr);
    EntityAddress entityAddress(addr);
    entityDescription.setEntityAddress(entityAddress);
    entityDescription.setEntityType(EntityType(entityType));

    NodeManagementDetailedDiscoveryEntityInformation entityInformation;
    entityInformation.setDescription(entityDescription);
    entityInformationList.push_back(entityInformation);

    pDetailedDiscoveryData->setEntityInformation(entityInformationList);
    return detailedDiscovery.setDetailedDiscoveryData(*pDetailedDiscoveryData);
}

bool addFeature(DetailedDiscovery& detailedDiscovery, const xs_unsignedInt entityAddr, const xs_unsignedInt featureAddr,
                Role role, FeatureType featureType, Function function, bool possibleOperationRead,
                bool possibleOperationWrite)
{
    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryData;
    pDetailedDiscoveryData = detailedDiscovery.getDetailedDiscoveryDataPtr();
    std::vector<NodeManagementDetailedDiscoveryFeatureInformation> featureInformationList;
    if (pDetailedDiscoveryData->getFeatureInformationIsSet())
    {
        featureInformationList = pDetailedDiscoveryData->getFeatureInformation();
    }

    std::vector<xs_unsignedInt> entityAddress;
    entityAddress.push_back(entityAddr);
    FeatureAddress featureAddress;
    featureAddress.setEntity(entityAddress);
    featureAddress.setFeature(featureAddr);
    NetworkManagementFeatureDescriptionData featureDescription;
    featureDescription.setFeatureAddress(featureAddress);
    featureDescription.setRole(Role(role));
    featureDescription.setFeatureType(FeatureType(featureType));

    std::vector<FunctionProperty> functionPropertyVector;
    FunctionProperty functionProperty;
    functionProperty.setFunction(function);
    PossibleOperations possibleOperations;
    if (possibleOperationRead)
    {
        PossibleOperationsRead possibleOperationsRead;
        possibleOperations.setRead(possibleOperationsRead);
    }
    if (possibleOperationWrite)
    {
        PossibleOperationsWrite possibleOperationsWrite;
        possibleOperations.setWrite(possibleOperationsWrite);
    }
    functionProperty.setPossibleOperations(possibleOperations);
    functionPropertyVector.push_back(functionProperty);
    featureDescription.setSupportedFunction(functionPropertyVector);

    NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
    featureInformation.setDescription(featureDescription);
    featureInformationList.push_back(featureInformation);
    pDetailedDiscoveryData->setFeatureInformation(featureInformationList);

    return detailedDiscovery.setDetailedDiscoveryData(*pDetailedDiscoveryData);
}

NodeManagementDetailedDiscoveryEntityInformation
createEntityOne(const EntityType& entityType, const NetworkManagementStateChange* stateChange = nullptr)
{
    NodeManagementDetailedDiscoveryEntityInformation entityInformation;
    NetworkManagementEntityDescriptionData entityDescription;
    std::vector<xs_unsignedInt> addr;
    addr.push_back(1);
    EntityAddress entityAddress(addr);
    entityDescription.setEntityAddress(entityAddress);

    if (stateChange == nullptr || *stateChange != NetworkManagementStateChange::Value::REMOVED)
    {
        entityDescription.setEntityType(EntityType(entityType));
    }

    if (stateChange != nullptr)
    {
        entityDescription.setLastStateChange(*stateChange);
    }

    entityInformation.setDescription(entityDescription);
    return entityInformation;
}

NodeManagementDetailedDiscoveryFeatureInformation
createFeatureOneForEntityOne(const NetworkManagementStateChange* stateChange = nullptr)
{

    NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
    NetworkManagementFeatureDescriptionData featureDescription;

    std::vector<xs_unsignedInt> entityAddress;
    entityAddress.push_back(1);
    FeatureAddress featureAddress;
    featureAddress.setEntity(entityAddress);
    featureAddress.setFeature(1);
    featureDescription.setFeatureAddress(featureAddress);

    if (stateChange == nullptr || *stateChange == NetworkManagementStateChange::Value::ADDED
        || *stateChange == NetworkManagementStateChange::Value::MODIFIED)
    {
        featureDescription.setRole(Role(Role::Value::SERVER));
        featureDescription.setFeatureType(FeatureType(FeatureType::Value::DEVICE_DIAGNOSIS));

        std::vector<FunctionProperty> functionPropertyVector;
        FunctionProperty functionProperty;
        functionProperty.setFunction(Function(Function::Value::DEVICE_DIAGNOSIS_STATE_DATA));
        PossibleOperations possibleOperations;
        PossibleOperationsRead possibleOperationsRead;
        possibleOperations.setRead(possibleOperationsRead);
        functionProperty.setPossibleOperations(possibleOperations);
        functionPropertyVector.push_back(functionProperty);
        featureDescription.setSupportedFunction(functionPropertyVector);
    }

    if (stateChange != nullptr)
    {
        featureDescription.setLastStateChange(*stateChange);
    }

    featureInformation.setDescription(featureDescription);
    return featureInformation;
}

bool testIsEntityModified(const DetailedDiscoveryPartial& detailedDiscoveryPartial,
                          const std::vector<std::vector<xs_unsignedInt> >& entitiesVector)
{
    bool modified = true;

    for (auto entityIter = entitiesVector.begin(); entityIter != entitiesVector.end(); entityIter++)
    {
        modified &= detailedDiscoveryPartial.isEntityModified(EntityAddress(*entityIter));
    }
    return modified;
}

bool testIsEntityRemoved(const DetailedDiscoveryPartial& detailedDiscoveryPartial,
                         const std::vector<std::vector<xs_unsignedInt> >& entitiesVector)
{
    bool removed = true;

    for (auto entityIter = entitiesVector.begin(); entityIter != entitiesVector.end(); entityIter++)
    {
        removed &= detailedDiscoveryPartial.isEntityModified(EntityAddress(*entityIter));
    }
    return removed;
}

void cleanLastStateChange(NodeManagementDetailedDiscoveryEntityInformation& entityInformation)
{
    NetworkManagementEntityDescriptionData stateCleanedDescription = entityInformation.getDescription();
    stateCleanedDescription.cleanLastStateChange();
    entityInformation.setDescription(stateCleanedDescription);
}

void cleanLastStateChange(NodeManagementDetailedDiscoveryFeatureInformation& featureInformation)
{
    NetworkManagementFeatureDescriptionData stateCleanedDescription = featureInformation.getDescription();
    stateCleanedDescription.cleanLastStateChange();
    featureInformation.setDescription(stateCleanedDescription);
}

TEST(DetailedDiscoveryPartial, diffAddedEmptyEntity)
{
    // old DD without entity 1
    DetailedDiscovery detailedDiscoveryOld;
    ASSERT_TRUE(detailedDiscoveryOld.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
    {
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryOld
            = detailedDiscoveryOld.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("old DD without entity 1", *pDetailedDiscoveryOld.get());
    }

    // new DD with empty entity 1
    DetailedDiscovery detailedDiscoveryNew = detailedDiscoveryOld;
    ASSERT_TRUE(addEntity(detailedDiscoveryNew, 1, EntityType::Value::INVERTER));
    {
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryNew
            = detailedDiscoveryNew.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("new DD w entity 1", *pDetailedDiscoveryNew);
    }

    DetailedDiscoveryPartial partialDetailedDiscovery;
    ASSERT_TRUE(partialDetailedDiscovery.setByDiffingDetailedDiscoveries(detailedDiscoveryOld, detailedDiscoveryNew));
    ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());
    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryData;
    pDetailedDiscoveryData = partialDetailedDiscovery.getDetailedDiscoveryDataPtr();

    printDetailedDiscoveryPartial("partial DD", partialDetailedDiscovery);

    ASSERT_TRUE(pDetailedDiscoveryData->getEntityInformationIsSet());
    ASSERT_FALSE(pDetailedDiscoveryData->getFeatureInformationIsSet());

    std::vector<NodeManagementDetailedDiscoveryEntityInformation> entityInformation
        = partialDetailedDiscovery.getAddedEntities();
    ASSERT_TRUE(entityInformation.size() == 1);
    for (auto entityInformationIter = entityInformation.begin(); entityInformationIter != entityInformation.end();
         entityInformationIter++)
    {
        ASSERT_TRUE(entityInformationIter->getDescriptionIsSet());
        NetworkManagementEntityDescriptionData entityDescriptionData = entityInformationIter->getDescription();
        ASSERT_TRUE(entityDescriptionData.getEntityAddressIsSet());
        ASSERT_TRUE(entityDescriptionData.getEntityAddress().toString() == "/1/");
        ASSERT_TRUE(entityDescriptionData.getEntityTypeIsSet());
        ASSERT_TRUE(entityDescriptionData.getEntityType() == EntityType(EntityType::Value::INVERTER));
        ASSERT_TRUE(entityDescriptionData.getLastStateChangeIsSet());
        ASSERT_TRUE(entityDescriptionData.getLastStateChange() == NetworkManagementStateChange::Value::ADDED);
    }

    ASSERT_FALSE(testIsEntityModified(partialDetailedDiscovery, { { 0 }, { 1 }, { 2 } }));
    ASSERT_FALSE(testIsEntityRemoved(partialDetailedDiscovery, { { 0 }, { 1 }, { 2 } }));

    ASSERT_TRUE(partialDetailedDiscovery.getModifiedEntities().empty());
    ASSERT_TRUE(partialDetailedDiscovery.getRemovedEntities().empty());

    ASSERT_TRUE(partialDetailedDiscovery.getAddedFeatures().empty());
    ASSERT_TRUE(partialDetailedDiscovery.getModifiedFeatures().empty());
    ASSERT_TRUE(partialDetailedDiscovery.getRemovedFeatures().empty());
}

TEST(DetailedDiscoveryPartial, diffAddedEntityWithFeature)
{
    // old DD without entity 1
    DetailedDiscovery detailedDiscoveryOld;
    detailedDiscoveryOld.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare());
    {
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryOld
            = detailedDiscoveryOld.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("old DD without entity 1", *pDetailedDiscoveryOld.get());
    }

    // new DD with entity 1 and feature 1
    DetailedDiscovery detailedDiscoveryNew = detailedDiscoveryOld;
    ASSERT_TRUE(addEntity(detailedDiscoveryNew, 1, EntityType::Value::INVERTER));
    ASSERT_TRUE(addFeature(detailedDiscoveryNew, 1, 1, Role::Value::SERVER, FeatureType::Value::DEVICE_DIAGNOSIS,
                           Function::Value::DEVICE_DIAGNOSIS_STATE_DATA, true, false));
    {
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryNew
            = detailedDiscoveryNew.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("new DD w entity 1 and feature 1", *pDetailedDiscoveryNew);
    }

    DetailedDiscoveryPartial partialDetailedDiscovery;
    ASSERT_TRUE(partialDetailedDiscovery.setByDiffingDetailedDiscoveries(detailedDiscoveryOld, detailedDiscoveryNew));
    ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());

    printDetailedDiscoveryPartial("partial DD", partialDetailedDiscovery);

    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryData
        = partialDetailedDiscovery.getDetailedDiscoveryDataPtr();
    ASSERT_TRUE(pDetailedDiscoveryData->getEntityInformationIsSet());
    ASSERT_TRUE(pDetailedDiscoveryData->getFeatureInformationIsSet());
    std::vector<NodeManagementDetailedDiscoveryEntityInformation> entityInformation
        = pDetailedDiscoveryData->getEntityInformation();
    ASSERT_TRUE(entityInformation.size() == 1);
    for (auto entityInformationIter = entityInformation.begin(); entityInformationIter != entityInformation.end();
         entityInformationIter++)
    {
        ASSERT_TRUE(entityInformationIter->getDescriptionIsSet());
        NetworkManagementEntityDescriptionData entityDescriptionData = entityInformationIter->getDescription();
        ASSERT_TRUE(entityDescriptionData.getEntityAddressIsSet());
        ASSERT_TRUE(entityDescriptionData.getEntityAddress().toString() == "/1/");
        ASSERT_TRUE(entityDescriptionData.getEntityTypeIsSet());
        ASSERT_TRUE(entityDescriptionData.getEntityType() == EntityType(EntityType::Value::INVERTER));
        ASSERT_TRUE(entityDescriptionData.getLastStateChangeIsSet());
        ASSERT_TRUE(entityDescriptionData.getLastStateChange() == NetworkManagementStateChange::Value::ADDED);
    }

    std::vector<NodeManagementDetailedDiscoveryFeatureInformation> featureInformationVector;
    featureInformationVector = pDetailedDiscoveryData->getFeatureInformation();
    ASSERT_TRUE(featureInformationVector.size() == 1);
    NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
    featureInformation = featureInformationVector[0];
    ASSERT_TRUE(featureInformation.getDescriptionIsSet());

    NetworkManagementFeatureDescriptionData featureDescription = featureInformation.getDescription();
    ASSERT_TRUE(featureDescription.getFeatureAddressIsSet());
    ASSERT_TRUE(featureDescription.getFeatureAddress().toString() == "/1/1");
    ASSERT_TRUE(featureDescription.getRoleIsSet());
    ASSERT_TRUE(featureDescription.getRole() == Role::Value::SERVER);
    ASSERT_TRUE(featureDescription.getFeatureTypeIsSet());
    ASSERT_TRUE(featureDescription.getFeatureType() == FeatureType(FeatureType::Value::DEVICE_DIAGNOSIS));

    ASSERT_TRUE(featureDescription.getSupportedFunctionIsSet());
    std::vector<FunctionProperty> functionPropertyVector = featureDescription.getSupportedFunction();
    ASSERT_TRUE(functionPropertyVector.size() == 1);
    FunctionProperty functionProperty = functionPropertyVector[0];

    ASSERT_TRUE(functionProperty.getFunctionIsSet());
    ASSERT_TRUE(functionProperty.getFunction() == Function(Function::Value::DEVICE_DIAGNOSIS_STATE_DATA));
}

TEST(DetailedDiscoveryPartial, diffModifiedEntity)
{
    // old DD with entity 1 type Inverter
    DetailedDiscovery detailedDiscoveryOld;
    {
        NodeManagementDetailedDiscoveryData detailedDiscoveryDataOld = createBaseDetailedDiscoveryForCompare();
        detailedDiscoveryOld.setDetailedDiscoveryData(detailedDiscoveryDataOld);
        addEntity(detailedDiscoveryOld, 1, EntityType::Value::INVERTER);
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryOld
            = detailedDiscoveryOld.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("old DD with entity 1 type Inverter", *pDetailedDiscoveryOld);
    }

    // new DD with entity 1 type
    DetailedDiscovery detailedDiscoveryNew;
    {
        NodeManagementDetailedDiscoveryData detailedDiscoveryDataNew = createBaseDetailedDiscoveryForCompare();
        detailedDiscoveryNew.setDetailedDiscoveryData(detailedDiscoveryDataNew);
        addEntity(detailedDiscoveryNew, 1, EntityType::Value::BATTERY);
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryNew
            = detailedDiscoveryNew.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("new DD with entity 1 type Battery", *pDetailedDiscoveryNew);
    }

    DetailedDiscoveryPartial partialDetailedDiscovery;
    ASSERT_TRUE(partialDetailedDiscovery.setByDiffingDetailedDiscoveries(detailedDiscoveryOld, detailedDiscoveryNew));
    ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());
    printDetailedDiscoveryPartial("partial DD", partialDetailedDiscovery);

    std::vector<NodeManagementDetailedDiscoveryEntityInformation> entityInformation
        = partialDetailedDiscovery.getModifiedEntities();
    ASSERT_TRUE(entityInformation.size() == 1);
    for (auto entityInformationIter = entityInformation.begin(); entityInformationIter != entityInformation.end();
         entityInformationIter++)
    {
        ASSERT_TRUE(entityInformationIter->getDescriptionIsSet());
        NetworkManagementEntityDescriptionData entityDescriptionData = entityInformationIter->getDescription();
        ASSERT_TRUE(entityDescriptionData.getEntityAddressIsSet());
        ASSERT_TRUE(entityDescriptionData.getEntityAddress().toString() == "/1/");
        ASSERT_TRUE(entityDescriptionData.getEntityTypeIsSet());
        ASSERT_TRUE(entityDescriptionData.getEntityType() == EntityType(EntityType::Value::BATTERY));
        ASSERT_TRUE(entityDescriptionData.getLastStateChangeIsSet());
        ASSERT_TRUE(entityDescriptionData.getLastStateChange() == NetworkManagementStateChange::Value::MODIFIED);
    }

    ASSERT_TRUE(partialDetailedDiscovery.getAddedEntities().empty());
    ASSERT_TRUE(partialDetailedDiscovery.getRemovedEntities().empty());

    ASSERT_TRUE(partialDetailedDiscovery.getAddedFeatures().empty());
    ASSERT_TRUE(partialDetailedDiscovery.getModifiedFeatures().empty());
    ASSERT_TRUE(partialDetailedDiscovery.getRemovedFeatures().empty());
}

TEST(DetailedDiscoveryPartial, diffRemoveEntity)
{
    // old DD with entity 1
    DetailedDiscovery detailedDiscoveryOld;
    NodeManagementDetailedDiscoveryData detailedDiscoveryDataOld = createBaseDetailedDiscoveryForCompare();
    detailedDiscoveryOld.setDetailedDiscoveryData(detailedDiscoveryDataOld);

    addEntity(detailedDiscoveryOld, 1, EntityType::Value::INVERTER);

    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryOld = detailedDiscoveryOld.getDetailedDiscoveryDataPtr();
    printDetailedDiscovery("old DD with entity 1", *pDetailedDiscoveryOld);

    // new DD without entity 1
    DetailedDiscovery detailedDiscoveryNew;
    detailedDiscoveryNew.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare());
    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryNew = detailedDiscoveryNew.getDetailedDiscoveryDataPtr();

    printDetailedDiscovery("new DD without entity 1", *pDetailedDiscoveryNew);

    DetailedDiscoveryPartial partialDetailedDiscovery;
    ASSERT_TRUE(partialDetailedDiscovery.setByDiffingDetailedDiscoveries(detailedDiscoveryOld, detailedDiscoveryNew));
    ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());
    printDetailedDiscoveryPartial("partial DD", partialDetailedDiscovery);

    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscovery = partialDetailedDiscovery.getDetailedDiscoveryDataPtr();

    ASSERT_FALSE(pDetailedDiscovery->getFeatureInformationIsSet());
    ASSERT_TRUE(pDetailedDiscovery->getEntityInformationIsSet());

    std::vector<NodeManagementDetailedDiscoveryEntityInformation> entityInformation
        = pDetailedDiscovery->getEntityInformation();
    ASSERT_TRUE(entityInformation[0].getDescriptionIsSet());
    NetworkManagementEntityDescriptionData entityDescriptionData = entityInformation[0].getDescription();
    ASSERT_TRUE(entityDescriptionData.getEntityAddressIsSet());
    ASSERT_TRUE(entityDescriptionData.getEntityAddress().toString() == "/1/");
    ASSERT_FALSE(entityDescriptionData.getEntityTypeIsSet());
    ASSERT_TRUE(entityDescriptionData.getLastStateChangeIsSet());
    ASSERT_TRUE(entityDescriptionData.getLastStateChange() == NetworkManagementStateChange::Value::REMOVED);
}

TEST(DetailedDiscoveryPartial, diffRemoveEntityWithFeature)
{
    // old DD with entity 1
    DetailedDiscovery detailedDiscoveryOld;
    NodeManagementDetailedDiscoveryData detailedDiscoveryDataOld = createBaseDetailedDiscoveryForCompare();
    detailedDiscoveryOld.setDetailedDiscoveryData(detailedDiscoveryDataOld);

    addEntity(detailedDiscoveryOld, 1, EntityType::Value::INVERTER);
    addFeature(detailedDiscoveryOld, 1, 1, Role::Value::SERVER, FeatureType::Value::DEVICE_DIAGNOSIS,
               Function::Value::DEVICE_DIAGNOSIS_STATE_DATA, true, false);

    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryOld = detailedDiscoveryOld.getDetailedDiscoveryDataPtr();

    // new DD without entity 1
    DetailedDiscovery detailedDiscoveryNew;
    detailedDiscoveryNew.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare());
    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryNew = detailedDiscoveryNew.getDetailedDiscoveryDataPtr();

    DetailedDiscoveryPartial partialDetailedDiscovery;
    ASSERT_TRUE(partialDetailedDiscovery.setByDiffingDetailedDiscoveries(detailedDiscoveryOld, detailedDiscoveryNew));

    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscovery = partialDetailedDiscovery.getDetailedDiscoveryDataPtr();

    ASSERT_FALSE(pDetailedDiscovery->getFeatureInformationIsSet());
    ASSERT_TRUE(pDetailedDiscovery->getEntityInformationIsSet());
}


TEST(DetailedDiscoveryPartial, diffAddedFeature)
{
    DetailedDiscovery detailedDiscoveryOld;
    ASSERT_TRUE(detailedDiscoveryOld.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
    ASSERT_TRUE(addEntity(detailedDiscoveryOld, 1, EntityType::Value::INVERTER));
    {
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryOld
            = detailedDiscoveryOld.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("old DD with empty entity 1", *pDetailedDiscoveryOld);
    }

    DetailedDiscovery detailedDiscoveryNew = detailedDiscoveryOld;
    addFeature(detailedDiscoveryNew, 1, 1, Role::Value::SERVER, FeatureType::Value::DEVICE_DIAGNOSIS,
               Function::Value::DEVICE_DIAGNOSIS_STATE_DATA, true, false);
    {
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryNew
            = detailedDiscoveryNew.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("new DD with added feature 1 in entity 1", *pDetailedDiscoveryNew);
    }

    DetailedDiscoveryPartial partialDetailedDiscovery;
    ASSERT_TRUE(partialDetailedDiscovery.setByDiffingDetailedDiscoveries(detailedDiscoveryOld, detailedDiscoveryNew));
    ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());
    printDetailedDiscoveryPartial("partial DD", partialDetailedDiscovery);

    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscovery = partialDetailedDiscovery.getDetailedDiscoveryDataPtr();

    ASSERT_TRUE(pDetailedDiscovery->getFeatureInformationIsSet());
    std::vector<NodeManagementDetailedDiscoveryFeatureInformation> featureInformation
        = pDetailedDiscovery->getFeatureInformation();
    ASSERT_TRUE(1 == featureInformation.size());
    NetworkManagementFeatureDescriptionData featureDescription = featureInformation[0].getDescription();
    ASSERT_TRUE(featureDescription.getFeatureAddressIsSet());
    ASSERT_TRUE(featureDescription.getFeatureAddress().toString() == "/1/1");
    ASSERT_TRUE(featureDescription.getRoleIsSet());
    ASSERT_TRUE(featureDescription.getRole() == Role::Value::SERVER);
    ASSERT_TRUE(featureDescription.getFeatureTypeIsSet());
    ASSERT_TRUE(featureDescription.getFeatureType() == FeatureType(FeatureType::Value::DEVICE_DIAGNOSIS));
    ASSERT_TRUE(featureDescription.getLastStateChangeIsSet());
    ASSERT_TRUE(featureDescription.getLastStateChange() == NetworkManagementStateChange::Value::ADDED);

    ASSERT_TRUE(featureDescription.getSupportedFunctionIsSet());
    std::vector<FunctionProperty> functionPropertyVector = featureDescription.getSupportedFunction();
    ASSERT_TRUE(functionPropertyVector.size() == 1);
    FunctionProperty functionProperty = functionPropertyVector[0];

    ASSERT_TRUE(functionProperty.getFunctionIsSet());
    ASSERT_TRUE(functionProperty.getFunction() == Function(Function::Value::DEVICE_DIAGNOSIS_STATE_DATA));
}

TEST(DetailedDiscoveryPartial, diffRemovedFeature)
{
    // old DD with feature 1 in entity 1
    DetailedDiscovery detailedDiscoveryOld;
    ASSERT_TRUE(detailedDiscoveryOld.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
    ASSERT_TRUE(addEntity(detailedDiscoveryOld, 1, EntityType::Value::INVERTER));
    ASSERT_TRUE(addFeature(detailedDiscoveryOld, 1, 1, Role::Value::SERVER, FeatureType::Value::DEVICE_DIAGNOSIS,
                           Function::Value::DEVICE_DIAGNOSIS_STATE_DATA, true, false));
    {
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryOld
            = detailedDiscoveryOld.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("old DD with feature 1 in entity 1", *pDetailedDiscoveryOld);
    }

    // new DD with empty entity 1 (removed feature 1)
    DetailedDiscovery detailedDiscoveryNew;
    ASSERT_TRUE(detailedDiscoveryNew.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
    ASSERT_TRUE(addEntity(detailedDiscoveryNew, 1, EntityType::Value::INVERTER));
    {
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryNew
            = detailedDiscoveryNew.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("new DD with empty entity 1 (removed feature 1)", *pDetailedDiscoveryNew);
    }

    DetailedDiscoveryPartial partialDetailedDiscovery;
    ASSERT_TRUE(partialDetailedDiscovery.setByDiffingDetailedDiscoveries(detailedDiscoveryOld, detailedDiscoveryNew));
    ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());
    printDetailedDiscoveryPartial("partial DD", partialDetailedDiscovery);

    // check
    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscovery = partialDetailedDiscovery.getDetailedDiscoveryDataPtr();
    ASSERT_FALSE(pDetailedDiscovery->getEntityInformationIsSet());

    ASSERT_TRUE(pDetailedDiscovery->getFeatureInformationIsSet());
    std::vector<NodeManagementDetailedDiscoveryFeatureInformation> featureInformation
        = pDetailedDiscovery->getFeatureInformation();
    ASSERT_TRUE(1 == featureInformation.size());
    NetworkManagementFeatureDescriptionData featureDescription = featureInformation[0].getDescription();
    ASSERT_TRUE(featureDescription.getFeatureAddressIsSet());
    ASSERT_TRUE(featureDescription.getFeatureAddress().toString() == "/1/1");
    ASSERT_FALSE(featureDescription.getRoleIsSet());
    ASSERT_FALSE(featureDescription.getFeatureTypeIsSet());
    ASSERT_TRUE(featureDescription.getLastStateChangeIsSet());
    ASSERT_TRUE(featureDescription.getLastStateChange() == NetworkManagementStateChange::Value::REMOVED);
    ASSERT_FALSE(featureDescription.getSupportedFunctionIsSet());
}

TEST(DetailedDiscoveryPartial, diffModifiedFeature)
{
    // old DD with feature 1 (in entity 1 ) with possibleOperationRead set
    DetailedDiscovery detailedDiscoveryOld;
    ASSERT_TRUE(detailedDiscoveryOld.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
    ASSERT_TRUE(addEntity(detailedDiscoveryOld, 1, EntityType::Value::INVERTER));
    ASSERT_TRUE(addFeature(detailedDiscoveryOld, 1, 1, Role::Value::SERVER, FeatureType::Value::DEVICE_DIAGNOSIS,
                           Function::Value::DEVICE_DIAGNOSIS_STATE_DATA, true, false));
    {
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryOld
            = detailedDiscoveryOld.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("old DD with feature 1 (in entity 1 ) with possibleOperationRead set",
                               *pDetailedDiscoveryOld);
    }

    // new DD with feature 1 (in entity 1 ) with possibleOperationRead unset
    DetailedDiscovery detailedDiscoveryNew;
    ASSERT_TRUE(detailedDiscoveryNew.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
    ASSERT_TRUE(addEntity(detailedDiscoveryNew, 1, EntityType::Value::INVERTER));
    ASSERT_TRUE(addFeature(detailedDiscoveryNew, 1, 1, Role::Value::SERVER, FeatureType::Value::DEVICE_DIAGNOSIS,
                           Function::Value::DEVICE_DIAGNOSIS_STATE_DATA, false, false));
    {
        NodeManagementDetailedDiscoveryDataPtr pDetailedDiscoveryNew
            = detailedDiscoveryNew.getDetailedDiscoveryDataPtr();
        printDetailedDiscovery("new DD with feature 1 (in entity 1 ) with possibleOperationRead unset",
                               *pDetailedDiscoveryNew);
    }

    DetailedDiscoveryPartial partialDetailedDiscovery;
    ASSERT_TRUE(partialDetailedDiscovery.setByDiffingDetailedDiscoveries(detailedDiscoveryOld, detailedDiscoveryNew));
    ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());
    printDetailedDiscoveryPartial("partial DD", partialDetailedDiscovery);

    NodeManagementDetailedDiscoveryDataPtr pDetailedDiscovery = partialDetailedDiscovery.getDetailedDiscoveryDataPtr();

    ASSERT_TRUE(pDetailedDiscovery->getFeatureInformationIsSet());

    std::vector<NodeManagementDetailedDiscoveryFeatureInformation> featureInformation
        = partialDetailedDiscovery.getModifiedFeatures();
    ASSERT_TRUE(1 == featureInformation.size());
    NetworkManagementFeatureDescriptionData featureDescription = featureInformation[0].getDescription();
    ASSERT_TRUE(featureDescription.getFeatureAddressIsSet());
    ASSERT_TRUE(featureDescription.getFeatureAddress().toString() == "/1/1");
    ASSERT_TRUE(featureDescription.getRoleIsSet());
    ASSERT_TRUE(featureDescription.getRole() == Role::Value::SERVER);
    ASSERT_TRUE(featureDescription.getFeatureTypeIsSet());
    ASSERT_TRUE(featureDescription.getFeatureType() == FeatureType(FeatureType::Value::DEVICE_DIAGNOSIS));
    ASSERT_TRUE(featureDescription.getLastStateChangeIsSet());
    ASSERT_TRUE(featureDescription.getLastStateChange() == NetworkManagementStateChange::Value::MODIFIED);

    ASSERT_FALSE(partialDetailedDiscovery.isEntityModified(EntityAddress(std::vector<xs_unsignedInt>({ 0 }))));
    ASSERT_FALSE(partialDetailedDiscovery.isEntityModified(EntityAddress(std::vector<xs_unsignedInt>({ 1 }))));
    ASSERT_FALSE(partialDetailedDiscovery.isEntityRemoved(EntityAddress(std::vector<xs_unsignedInt>({ 0 }))));
    ASSERT_FALSE(partialDetailedDiscovery.isEntityRemoved(EntityAddress(std::vector<xs_unsignedInt>({ 1 }))));

    ASSERT_TRUE(featureDescription.getSupportedFunctionIsSet());
    std::vector<FunctionProperty> functionPropertyVector = featureDescription.getSupportedFunction();
    ASSERT_TRUE(functionPropertyVector.size() == 1);
    FunctionProperty functionProperty = functionPropertyVector[0];

    ASSERT_TRUE(functionProperty.getPossibleOperationsIsSet());
    ASSERT_FALSE(functionProperty.getPossibleOperations().getReadIsSet());
    ASSERT_FALSE(functionProperty.getPossibleOperations().getWriteIsSet());

    ASSERT_TRUE(functionProperty.getFunctionIsSet());
    ASSERT_TRUE(functionProperty.getFunction() == Function(Function::Value::DEVICE_DIAGNOSIS_STATE_DATA));

    ASSERT_TRUE(partialDetailedDiscovery.isFeatureModified(FeatureAddress("", 1, 1)));
    ASSERT_FALSE(partialDetailedDiscovery.isFeatureModified(FeatureAddress("", 0, 0)));
    ASSERT_FALSE(partialDetailedDiscovery.isFeatureRemoved(FeatureAddress("", 1, 1)));
    ASSERT_FALSE(partialDetailedDiscovery.isFeatureRemoved(FeatureAddress("", 0, 0)));
}

TEST(DetailedDiscoveryPartial, mergeAddedEmptyEntity)
{
    DetailedDiscovery detailedDiscovery;
    ASSERT_TRUE(detailedDiscovery.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));

    printDetailedDiscovery("Old detailed discovery:", *detailedDiscovery.getDetailedDiscoveryDataPtr());

    // create partial DD with empty entity 1 added
    DetailedDiscoveryPartial partialDetailedDiscovery;
    NodeManagementDetailedDiscoveryEntityInformation partialEntityInformation;

    NetworkManagementStateChange stateChange = NetworkManagementStateChange::Value::ADDED;
    partialEntityInformation = createEntityOne(EntityType::Value::INVERTER, &stateChange);
    {
        std::vector<NodeManagementDetailedDiscoveryEntityInformation> entityInformationVector;
        entityInformationVector.push_back(partialEntityInformation);
        NodeManagementDetailedDiscoveryData partialDetailedDiscoveryData;
        partialDetailedDiscoveryData.setEntityInformation(entityInformationVector);
        ASSERT_TRUE(partialDetailedDiscovery.setDetailedDiscoveryData(partialDetailedDiscoveryData));
        ASSERT_FALSE(partialDetailedDiscovery.getDeviceNameIsSet());
        partialDetailedDiscovery.setDeviceName(spineSourceDeviceAddr);
        ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());
        printDetailedDiscoveryPartial("Partial detailed discovery: ", partialDetailedDiscovery);
    }

    DetailedDiscovery detailedDiscoveryMerged;
    bool success;
    detailedDiscoveryMerged = partialDetailedDiscovery.getMergedDetailedDiscovery(detailedDiscovery, &success);
    ASSERT_TRUE(success);

    printDetailedDiscovery("New detailed discovery:", *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());

    NodeManagementDetailedDiscoveryDataPtr pExpectedDetailedDiscoveryData
        = detailedDiscovery.getDetailedDiscoveryDataPtr();
    {
        ASSERT_TRUE(pExpectedDetailedDiscoveryData->getEntityInformationIsSet());
        std::vector<NodeManagementDetailedDiscoveryEntityInformation> expectedEntityInformationVector
            = pExpectedDetailedDiscoveryData->getEntityInformation();
        cleanLastStateChange(partialEntityInformation);
        expectedEntityInformationVector.push_back(partialEntityInformation);
        pExpectedDetailedDiscoveryData->setEntityInformation(expectedEntityInformationVector);

        printDetailedDiscovery("Expected detailed discovery:", *pExpectedDetailedDiscoveryData);
    }
    ASSERT_EQ(*pExpectedDetailedDiscoveryData, *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
}

TEST(DetailedDiscoveryPartial, mergeAddedEntityWithFeature)
{
    DetailedDiscovery detailedDiscovery;
    ASSERT_TRUE(detailedDiscovery.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));

    printDetailedDiscovery("Old detailed discovery:", *detailedDiscovery.getDetailedDiscoveryDataPtr());

    // create partial DD with entity 1 containing feature 1 added
    DetailedDiscoveryPartial partialDetailedDiscovery;
    NodeManagementDetailedDiscoveryEntityInformation partialEntityInformation;
    NetworkManagementStateChange stateChange = NetworkManagementStateChange::Value::ADDED;
    partialEntityInformation = createEntityOne(EntityType::Value::INVERTER, &stateChange);

    NodeManagementDetailedDiscoveryFeatureInformation partialFeatureInformation;
    partialFeatureInformation = createFeatureOneForEntityOne();
    {
        NodeManagementDetailedDiscoveryData partialDetailedDiscoveryData;

        std::vector<NodeManagementDetailedDiscoveryEntityInformation> entityInformationVector;
        entityInformationVector.push_back(partialEntityInformation);
        partialDetailedDiscoveryData.setEntityInformation(entityInformationVector);

        std::vector<NodeManagementDetailedDiscoveryFeatureInformation> featureInformationVector;
        featureInformationVector.push_back(partialFeatureInformation);
        partialDetailedDiscoveryData.setFeatureInformation(featureInformationVector);

        ASSERT_TRUE(partialDetailedDiscovery.setDetailedDiscoveryData(partialDetailedDiscoveryData));
        ASSERT_FALSE(partialDetailedDiscovery.getDeviceNameIsSet());
        partialDetailedDiscovery.setDeviceName(spineSourceDeviceAddr);
        ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());

        printDetailedDiscoveryPartial("Partial detailed discovery: ", partialDetailedDiscovery);
    }

    DetailedDiscovery detailedDiscoveryMerged;
    bool success;
    detailedDiscoveryMerged = partialDetailedDiscovery.getMergedDetailedDiscovery(detailedDiscovery, &success);
    ASSERT_TRUE(success);

    printDetailedDiscovery("New detailed discovery:", *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());

    // expected new detailed discovery
    NodeManagementDetailedDiscoveryDataPtr pExpectedDetailedDiscoveryData
        = detailedDiscovery.getDetailedDiscoveryDataPtr();
    {
        ASSERT_TRUE(pExpectedDetailedDiscoveryData->getEntityInformationIsSet());
        std::vector<NodeManagementDetailedDiscoveryEntityInformation> expectedEntityInformationVector
            = pExpectedDetailedDiscoveryData->getEntityInformation();
        cleanLastStateChange(partialEntityInformation);
        expectedEntityInformationVector.push_back(partialEntityInformation);
        pExpectedDetailedDiscoveryData->setEntityInformation(expectedEntityInformationVector);

        ASSERT_TRUE(pExpectedDetailedDiscoveryData->getFeatureInformationIsSet());
        std::vector<NodeManagementDetailedDiscoveryFeatureInformation> expectedFeatureInformationVector
            = pExpectedDetailedDiscoveryData->getFeatureInformation();
        expectedFeatureInformationVector.push_back(partialFeatureInformation);
        pExpectedDetailedDiscoveryData->setFeatureInformation(expectedFeatureInformationVector);

        printDetailedDiscovery("Expected detailed discovery:", *pExpectedDetailedDiscoveryData);
    }
    ASSERT_EQ(*pExpectedDetailedDiscoveryData, *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
}

TEST(DetailedDiscoveryPartial, mergeModifiedEntity)
{
    DetailedDiscovery detailedDiscoveryOld;
    {
        ASSERT_TRUE(detailedDiscoveryOld.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
        ASSERT_TRUE(detailedDiscoveryOld.addDetailedDiscoveryEntityInformation(createEntityOne(EntityType::Value::INVERTER)));
        printDetailedDiscovery("Old detailed discovery:", *detailedDiscoveryOld.getDetailedDiscoveryDataPtr());
    }

    DetailedDiscoveryPartial detailedDiscoveryPartial;
    {
        NetworkManagementStateChange stateChange = NetworkManagementStateChange::Value::MODIFIED;
        ASSERT_TRUE(detailedDiscoveryPartial.addDetailedDiscoveryEntityInformation(
            createEntityOne(EntityType::Value::BATTERY, &stateChange)));
        ASSERT_FALSE(detailedDiscoveryPartial.getDeviceNameIsSet());
        detailedDiscoveryPartial.setDeviceName(spineSourceDeviceAddr);
        ASSERT_TRUE(detailedDiscoveryPartial.getDeviceNameIsSet());
        printDetailedDiscoveryPartial("Partial detailed discovery:", detailedDiscoveryPartial);
    }

    DetailedDiscovery detailedDiscoveryExpected;
    {
        ASSERT_TRUE(detailedDiscoveryExpected.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
        ASSERT_TRUE(
            detailedDiscoveryExpected.addDetailedDiscoveryEntityInformation(createEntityOne(EntityType::Value::BATTERY)));
        printDetailedDiscovery("Expected detailed discovery:",
                               *detailedDiscoveryExpected.getDetailedDiscoveryDataPtr());
    }

    DetailedDiscovery detailedDiscoveryMerged;
    {
        bool success;
        detailedDiscoveryMerged = detailedDiscoveryPartial.getMergedDetailedDiscovery(detailedDiscoveryOld, &success);
        ASSERT_TRUE(success);

        printDetailedDiscovery("New merged detailed discovery:",
                               *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
    }

    ASSERT_EQ(*detailedDiscoveryExpected.getDetailedDiscoveryDataPtr(),
        *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
}

TEST(DetailedDiscoveryPartial, mergeRemovedEntity)
{
    DetailedDiscovery detailedDiscovery;
    {
        ASSERT_TRUE(detailedDiscovery.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
        ASSERT_TRUE(detailedDiscovery.addDetailedDiscoveryEntityInformation(createEntityOne(EntityType::Value::INVERTER)));

        printDetailedDiscovery("Old detailed discovery:", *detailedDiscovery.getDetailedDiscoveryDataPtr());
    }

    DetailedDiscoveryPartial partialDetailedDiscovery;
    {
        NetworkManagementStateChange stateChange = NetworkManagementStateChange::Value::REMOVED;
        ASSERT_TRUE(partialDetailedDiscovery.addDetailedDiscoveryEntityInformation(
            createEntityOne(EntityType::Value::INVERTER, &stateChange)));
        ASSERT_FALSE(partialDetailedDiscovery.getDeviceNameIsSet());
        partialDetailedDiscovery.setDeviceName(spineSourceDeviceAddr);
        ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());

        printDetailedDiscoveryPartial("Partial detailed discovery: ", partialDetailedDiscovery);
    }

    DetailedDiscovery detailedDiscoveryExpected;
    {
        ASSERT_TRUE(detailedDiscoveryExpected.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));

        printDetailedDiscovery("Expected detailed discovery:",
                               *detailedDiscoveryExpected.getDetailedDiscoveryDataPtr());
    }

    DetailedDiscovery detailedDiscoveryMerged;
    {
        bool success;
        detailedDiscoveryMerged = partialDetailedDiscovery.getMergedDetailedDiscovery(detailedDiscovery, &success);
        ASSERT_TRUE(success);

        printDetailedDiscovery("New detailed discovery:", *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
    }

    ASSERT_EQ(*detailedDiscoveryExpected.getDetailedDiscoveryDataPtr(),
        *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
}

TEST(DetailedDiscoveryPartial, mergeRemovedEntityWithFeature)
{
    DetailedDiscovery detailedDiscovery;
    {
        ASSERT_TRUE(detailedDiscovery.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
        ASSERT_TRUE(detailedDiscovery.addDetailedDiscoveryEntityInformation(createEntityOne(EntityType::Value::INVERTER)));
        ASSERT_TRUE(detailedDiscovery.addDetailedDiscoveryFeatureInformation(createFeatureOneForEntityOne()));

        printDetailedDiscovery("Old detailed discovery:", *detailedDiscovery.getDetailedDiscoveryDataPtr());
    }

    DetailedDiscoveryPartial partialDetailedDiscovery;
    {
        NetworkManagementStateChange stateChange = NetworkManagementStateChange::Value::REMOVED;
        ASSERT_TRUE(partialDetailedDiscovery.addDetailedDiscoveryEntityInformation(
            createEntityOne(EntityType::Value::INVERTER, &stateChange)));
        ASSERT_FALSE(partialDetailedDiscovery.getDeviceNameIsSet());
        partialDetailedDiscovery.setDeviceName(spineSourceDeviceAddr);
        ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());

        printDetailedDiscoveryPartial("Partial detailed discovery: ", partialDetailedDiscovery);
    }

    DetailedDiscovery detailedDiscoveryExpected;
    {
        ASSERT_TRUE(detailedDiscoveryExpected.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));

        printDetailedDiscovery("Expected detailed discovery:",
                               *detailedDiscoveryExpected.getDetailedDiscoveryDataPtr());
    }

    DetailedDiscovery detailedDiscoveryMerged;
    {
        bool success;
        detailedDiscoveryMerged = partialDetailedDiscovery.getMergedDetailedDiscovery(detailedDiscovery, &success);
        ASSERT_TRUE(success);

        printDetailedDiscovery("New detailed discovery:", *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
    }

    ASSERT_EQ(*detailedDiscoveryExpected.getDetailedDiscoveryDataPtr(),
        *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
}

TEST(DetailedDiscoveryPartial, mergeAddedFeature)
{
    DetailedDiscovery detailedDiscovery;
    {
        ASSERT_TRUE(detailedDiscovery.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
        ASSERT_TRUE(detailedDiscovery.addDetailedDiscoveryEntityInformation(createEntityOne(EntityType::Value::INVERTER)));

        printDetailedDiscovery("Old detailed discovery:", *detailedDiscovery.getDetailedDiscoveryDataPtr());
    }

    DetailedDiscoveryPartial partialDetailedDiscovery;
    {
        NetworkManagementStateChange stateChangeFeature = NetworkManagementStateChange::Value::ADDED;
        ASSERT_TRUE(partialDetailedDiscovery.addDetailedDiscoveryFeatureInformation(
            createFeatureOneForEntityOne(&stateChangeFeature)));
        ASSERT_FALSE(partialDetailedDiscovery.getDeviceNameIsSet());
        partialDetailedDiscovery.setDeviceName(spineSourceDeviceAddr);
        ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());

        printDetailedDiscoveryPartial("Partial detailed discovery: ", partialDetailedDiscovery);
    }

    DetailedDiscovery detailedDiscoveryExpected;
    {
        ASSERT_TRUE(detailedDiscoveryExpected.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
        NodeManagementDetailedDiscoveryEntityInformation entityInformation = createEntityOne(EntityType::Value::INVERTER);
        detailedDiscoveryExpected.addDetailedDiscoveryEntityInformation(entityInformation);

        detailedDiscoveryExpected.addDetailedDiscoveryFeatureInformation(createFeatureOneForEntityOne());

        printDetailedDiscovery("Expected detailed discovery:",
                               *detailedDiscoveryExpected.getDetailedDiscoveryDataPtr());
    }

    DetailedDiscovery detailedDiscoveryMerged;
    {
        bool success;
        detailedDiscoveryMerged = partialDetailedDiscovery.getMergedDetailedDiscovery(detailedDiscovery, &success);
        ASSERT_TRUE(success);

        printDetailedDiscovery("New detailed discovery:", *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
    }

    ASSERT_EQ(*detailedDiscoveryExpected.getDetailedDiscoveryDataPtr(),
        *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
}

TEST(DetailedDiscoveryPartial, mergeModifiedFeature)
{
    DetailedDiscovery detailedDiscovery;
    ASSERT_TRUE(detailedDiscovery.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
    ASSERT_TRUE(detailedDiscovery.addDetailedDiscoveryEntityInformation(createEntityOne(EntityType::Value::INVERTER)));
    ASSERT_TRUE(detailedDiscovery.addDetailedDiscoveryFeatureInformation(createFeatureOneForEntityOne()));

    printDetailedDiscovery("Old detailed discovery:", *detailedDiscovery.getDetailedDiscoveryDataPtr());

    DetailedDiscovery detailedDiscoveryExpected;
    ASSERT_TRUE(detailedDiscoveryExpected.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));

    DetailedDiscoveryPartial partialDetailedDiscovery;

    NetworkManagementStateChange stateChange = NetworkManagementStateChange::Value::MODIFIED;
    ASSERT_TRUE(partialDetailedDiscovery.addDetailedDiscoveryEntityInformation(
        createEntityOne(EntityType::Value::INVERTER, &stateChange)));

    NodeManagementDetailedDiscoveryFeatureInformation partialFeatureInformation
        = createFeatureOneForEntityOne(&stateChange);
    NetworkManagementFeatureDescriptionData featureDescription = partialFeatureInformation.getDescription();
    std::vector<FunctionProperty> supportedFunctions = featureDescription.getSupportedFunction();
    ASSERT_TRUE(supportedFunctions.size() == 1);
    supportedFunctions[0].setPossibleOperations(PossibleOperations());
    featureDescription.setSupportedFunction(supportedFunctions);
    partialFeatureInformation.setDescription(featureDescription);
    ASSERT_TRUE(partialDetailedDiscovery.addDetailedDiscoveryFeatureInformation(partialFeatureInformation));
    ASSERT_FALSE(partialDetailedDiscovery.getDeviceNameIsSet());
    partialDetailedDiscovery.setDeviceName(spineSourceDeviceAddr);
    ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());

    printDetailedDiscoveryPartial("Partial detailed discovery: ", partialDetailedDiscovery);

    detailedDiscoveryExpected.addDetailedDiscoveryEntityInformation(createEntityOne(EntityType::Value::INVERTER));
    cleanLastStateChange(partialFeatureInformation);
    detailedDiscoveryExpected.addDetailedDiscoveryFeatureInformation(partialFeatureInformation);

    printDetailedDiscovery("Expected detailed discovery:", *detailedDiscoveryExpected.getDetailedDiscoveryDataPtr());

    // new (merged) DD
    DetailedDiscovery detailedDiscoveryMerged;
    bool success;
    detailedDiscoveryMerged = partialDetailedDiscovery.getMergedDetailedDiscovery(detailedDiscovery, &success);
    ASSERT_TRUE(success);

    printDetailedDiscovery("New detailed discovery:", *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());

    ASSERT_EQ(*detailedDiscoveryExpected.getDetailedDiscoveryDataPtr(),
        *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
}

TEST(DetailedDiscoveryPartial, mergeRemovedFeature)
{
    DetailedDiscovery detailedDiscovery;
    {
        ASSERT_TRUE(detailedDiscovery.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
        ASSERT_TRUE(detailedDiscovery.addDetailedDiscoveryEntityInformation(createEntityOne(EntityType::Value::INVERTER)));
        ASSERT_TRUE(detailedDiscovery.addDetailedDiscoveryFeatureInformation(createFeatureOneForEntityOne()));

        printDetailedDiscovery("Old detailed discovery:", *detailedDiscovery.getDetailedDiscoveryDataPtr());
    }

    DetailedDiscoveryPartial partialDetailedDiscovery;
    {
        ASSERT_TRUE(
            partialDetailedDiscovery.addDetailedDiscoveryEntityInformation(createEntityOne(EntityType::Value::INVERTER)));

        NetworkManagementStateChange stateChangeFeature = NetworkManagementStateChange::Value::REMOVED;
        ASSERT_TRUE(partialDetailedDiscovery.addDetailedDiscoveryFeatureInformation(
            createFeatureOneForEntityOne(&stateChangeFeature)));
        ASSERT_FALSE(partialDetailedDiscovery.getDeviceNameIsSet());
        partialDetailedDiscovery.setDeviceName(spineSourceDeviceAddr);
        ASSERT_TRUE(partialDetailedDiscovery.getDeviceNameIsSet());

        printDetailedDiscoveryPartial("Partial detailed discovery:", partialDetailedDiscovery);
    }

    DetailedDiscovery detailedDiscoveryExpected;
    {
        ASSERT_TRUE(detailedDiscoveryExpected.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare()));
        NodeManagementDetailedDiscoveryEntityInformation entityInformation = createEntityOne(EntityType::Value::INVERTER);
        detailedDiscoveryExpected.addDetailedDiscoveryEntityInformation(entityInformation);

        printDetailedDiscovery("Expected detailed discovery:",
                               *detailedDiscoveryExpected.getDetailedDiscoveryDataPtr());
    }

    DetailedDiscovery detailedDiscoveryMerged;
    {
        bool success;
        detailedDiscoveryMerged = partialDetailedDiscovery.getMergedDetailedDiscovery(detailedDiscovery, &success);
        ASSERT_TRUE(success);

        printDetailedDiscovery("New detailed discovery:", *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
    }

    ASSERT_EQ(*detailedDiscoveryExpected.getDetailedDiscoveryDataPtr(),
        *detailedDiscoveryMerged.getDetailedDiscoveryDataPtr());
}

TEST(DetailedDiscoveryPartial, diffSameDD)
{
    DetailedDiscovery detailedDiscovery1;
    detailedDiscovery1.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare());

    DetailedDiscovery detailedDiscovery2;
    detailedDiscovery2.setDetailedDiscoveryData(createBaseDetailedDiscoveryForCompare());

    DetailedDiscoveryPartial partialDetailedDiscovery;
    ASSERT_TRUE(partialDetailedDiscovery.setByDiffingDetailedDiscoveries(detailedDiscovery1, detailedDiscovery2));
    ASSERT_TRUE(partialDetailedDiscovery.isEmpty());
}
