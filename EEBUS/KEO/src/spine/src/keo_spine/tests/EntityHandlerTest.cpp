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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "EntityHandler.h"
#include "SmartDeviceHelper.h"
#include "TestSendService.h"
#include "TestClientFeature.h"
#include <keo_spine/DeviceDefinition.h>
#include <keo_spine/PrimaryDeviceInformationEntity.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */

#include "gtest/gtest.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */
using namespace keo_spine;
/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */
class EntityListener : public EntityHandler::EntityHandlerInterface
{
public:
    virtual ~EntityListener(){};

private:
    std::map<TransportId, std::vector<std::string> > newDevices;
    std::map<TransportId, std::vector<std::string> > removedDevices;
    std::map<std::string, keo_datagram::DetailedDiscovery> gotDetailedDiscovery;
    std::map<std::string, keo_datagram::DetailedDiscoveryPartial> gotDetailedDiscoveryPartial;
    std::map<std::string, keo_datagram::UseCaseDiscovery> useCaseDiscoveries;
    virtual void onNewDevices(const std::vector<std::string>& devices, const TransportId& transportId)
    {
        newDevices.insert(std::pair<TransportId, std::vector<std::string> >(transportId, devices));
    }

    virtual void onRemovedDevices(const std::vector<std::string>& devices, const TransportId& transportId)
    {
        removedDevices.insert(std::pair<TransportId, std::vector<std::string> >(transportId, devices));
    }

    virtual void onDetailedDiscovery(const std::string& deviceName,
                                     const keo_datagram::DetailedDiscovery& detailedDiscovery)
    {
        gotDetailedDiscovery.insert(
            std::pair<std::string, keo_datagram::DetailedDiscovery>(deviceName, detailedDiscovery));
    }

    virtual void onDetailedDiscoveryPartial(const std::string& deviceName,
                                            const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
    {
        gotDetailedDiscoveryPartial.insert(
            std::pair<std::string, keo_datagram::DetailedDiscoveryPartial>(deviceName, detailedDiscoveryPartial));
    }

    void onUseCaseDiscovery(const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery)
    {
        useCaseDiscoveries.insert(std::pair<std::string, keo_datagram::UseCaseDiscovery>(deviceName, useCaseDiscovery));
    }
};

TEST(EntityHandlerTest, Initialization)
{
    EntityListener parent;
    keo_spine::EntityHandler entityHandler(&parent);

    keo_datagram::NetworkManagementDeviceDescriptionData deviceDescription
        = SmartDeviceHelper::getNetworkManagementDeviceDescriptionData("TestDevice");
    ASSERT_FALSE(entityHandler.initialize(deviceDescription));

    PrimaryDeviceInformationEntityPtr entityNull = PrimaryDeviceInformationEntityPtr(
        new PrimaryDeviceInformationEntity(SmartDeviceHelper::getNetworkManagementEntityDescriptionData()));
    TestSendService testSendService("TestDevice");
    entityNull->setSendService(&testSendService);
    entityHandler.addEntity(entityNull);
    ASSERT_FALSE(entityHandler.initialize(deviceDescription));
    entityNull->setNodeManagementFeature(PrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false));
    ASSERT_TRUE(entityHandler.initialize(deviceDescription));
}

TEST(EntityHandlerTest, AddGetRemoveEntitiy)
{
    EntityListener parent;
    keo_spine::EntityHandler entityHandler(&parent);

    std::vector<keo_datagram::xs_unsignedInt> entityAddr;
    entityAddr.push_back(1);
    keo_datagram::EntityType entityType(keo_datagram::EntityType::Value::GENERIC);
    keo_spine::EntityPtr pEntity = EntityPtr(new keo_spine::Entity(entityAddr, entityType));
    ASSERT_TRUE(NULL == entityHandler.getEntity(entityAddr).get());

    // addEntity
    entityHandler.addEntity(pEntity);

    // getEntity
    keo_spine::EntityPtr pEntityRead;
    pEntityRead = entityHandler.getEntity(entityAddr);
    ASSERT_TRUE(NULL != pEntityRead.get());
    ASSERT_TRUE(pEntity.get() == pEntityRead.get());

    // removeEntity
    entityHandler.removeEntity(entityAddr);
    ASSERT_TRUE(NULL == entityHandler.getEntity(entityAddr).get());
}

TEST(EntityHandlerTest, getEntityChildren)
{
    EntityListener parent;
    keo_spine::EntityHandler entityHandler(&parent);

    std::vector<keo_datagram::xs_unsignedInt> entityAddr_1;
    entityAddr_1.push_back(1);

    std::vector<keo_datagram::xs_unsignedInt> entityAddr_1_1;
    entityAddr_1_1.push_back(1);
    entityAddr_1_1.push_back(1);

    std::vector<keo_datagram::xs_unsignedInt> entityAddr_1_2;
    entityAddr_1_2.push_back(1);
    entityAddr_1_2.push_back(2);

    keo_datagram::EntityType entityType_1(keo_datagram::EntityType::Value::SMART_ENERGY_APPLIANCE);
    keo_datagram::EntityType entityType_1_1(keo_datagram::EntityType::Value::WASHER);
    keo_datagram::EntityType entityType_1_2(keo_datagram::EntityType::Value::DISHWASHER);

    keo_spine::EntityPtr pEntity_1 = EntityPtr(new keo_spine::Entity(entityAddr_1, entityType_1));
    ASSERT_TRUE(NULL != pEntity_1.get());

    keo_spine::EntityPtr pEntity_1_1 = EntityPtr(new keo_spine::Entity(entityAddr_1_1, entityType_1_1));
    ASSERT_TRUE(NULL != pEntity_1_1.get());

    keo_spine::EntityPtr pEntity_1_2 = EntityPtr(new keo_spine::Entity(entityAddr_1_2, entityType_1_2));
    ASSERT_TRUE(NULL != pEntity_1_2.get());

    entityHandler.addEntity(pEntity_1);
    entityHandler.addEntity(pEntity_1_1);
    entityHandler.addEntity(pEntity_1_2);

    std::vector<keo_spine::EntityPtr> entityChildren = entityHandler.getEntityChildren(entityAddr_1);
    ASSERT_EQ(2U, entityChildren.size());

    for (auto iter = entityChildren.begin(); iter != entityChildren.end(); ++iter)
    {
        ASSERT_FALSE(iter->get() != pEntity_1_1.get() && iter->get() != pEntity_1_2.get());

        const keo_datagram::NetworkManagementEntityDescriptionData& descriptionData
            = iter->get()->getEntityDescription();
        ASSERT_TRUE(descriptionData.getEntityAddressIsSet());
        ASSERT_TRUE(descriptionData.getEntityAddress().getEntityIsSet());
        ASSERT_TRUE(descriptionData.getEntityTypeIsSet());

        if (iter->get() == pEntity_1_1.get())
        {
            ASSERT_EQ(entityAddr_1_1, descriptionData.getEntityAddress().getEntity());
            ASSERT_EQ(keo_datagram::EntityType(keo_datagram::EntityType::Value::WASHER),
                      descriptionData.getEntityType());
        }
        else if (iter->get() == pEntity_1_2.get())
        {
            ASSERT_EQ(entityAddr_1_2, descriptionData.getEntityAddress().getEntity());
            ASSERT_EQ(keo_datagram::EntityType(keo_datagram::EntityType::Value::DISHWASHER),
                      descriptionData.getEntityType());
        }
    }
}

TEST(EntityHandlerTest, testEntityHandler)
{
    EntityListener parent;
    keo_spine::EntityHandler entityHandler(&parent);
    keo_datagram::NetworkManagementDeviceDescriptionData deviceDescription
        = SmartDeviceHelper::getNetworkManagementDeviceDescriptionData("TestDevice");
    PrimaryDeviceInformationEntityPtr entityNull = PrimaryDeviceInformationEntityPtr(
        new PrimaryDeviceInformationEntity(SmartDeviceHelper::getNetworkManagementEntityDescriptionData()));
    TestSendService testSendService("TestDevice");
    entityNull->setSendService(&testSendService);
    entityHandler.addEntity(entityNull);
    entityNull->setNodeManagementFeature(PrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false));

    NetworkManagementEntityDescriptionData networkManagementEntityDescriptionData;
    networkManagementEntityDescriptionData.setEntityAddress(EntityAddress("SHOULD_BE_REMOVED_IN_DD", 3));
    networkManagementEntityDescriptionData.setEntityType(EntityType(EntityType::Value::GENERIC));
    EntityPtr entityClass = EntityPtr(new Entity(networkManagementEntityDescriptionData));

    TestFeaturePtr testFeature = std::make_shared<TestClientFeature>(3, 2);
    ASSERT_TRUE(entityClass->addFeature(testFeature));

    entityHandler.addEntity(entityClass);

    ASSERT_TRUE(entityHandler.initialize(deviceDescription));

    { // test detailed discovery creation (device part must not be set in entity or feature addresses)
        keo_datagram::DetailedDiscoveryConstPtr dd
            = entityHandler.getDetailedDiscovery(keo_datagram::NetworkManagementDeviceDescriptionData());

        std::vector<xs_unsignedInt> entity = {3};
        ASSERT_TRUE(dd->containsFeatureTypeOnEntity(
            entity, keo_datagram::FeatureType(keo_datagram::FeatureType::Value::GENERIC)));
        ASSERT_TRUE(dd->containsFeatureIdOnEntity(entity, 2));

        for (auto ea : dd->getEntities())
        {
            ASSERT_FALSE(
                    dd->getDetailedDiscoveryEntityInformation(ea)->getDescription().getEntityAddress().getDeviceIsSet());
            ASSERT_EQ(1UL, dd->getFeatures(ea).size()); // all entities have only one feature in this testcase
            for (auto fid : dd->getFeatures(ea))
            {
                ASSERT_FALSE(dd->getDetailedDiscoveryFeatureInformation(ea, fid)
                                 ->getDescription()
                                 .getFeatureAddress()
                                 .getDeviceIsSet());
            }
        }
    }

    { // get feature 0L,0L
        PrimaryNodeManagementFeaturePtr nodeManagementFeature = entityHandler.getNodeManagementFeature();
        ASSERT_TRUE(nodeManagementFeature != NULL);
        NetworkManagementFeatureDescriptionData featureDescription = nodeManagementFeature->getFeatureDescription();
        ASSERT_EQ(DeviceDefinition::EntityAddressZero.getEntity(), featureDescription.getFeatureAddress().getEntity());
        ASSERT_EQ(0U, featureDescription.getFeatureAddress().getFeature());
    }

    { // get feature 3L,2L
        std::vector<xs_unsignedInt> entity;
        entity.push_back(3);
        FeaturePtr featureClass = entityHandler.getFeature(entity, 2);
        ASSERT_TRUE(featureClass != NULL);
    }

    { // get feature 3L,3L
        std::vector<xs_unsignedInt> entity;
        entity.push_back(3);
        FeaturePtr featureClass = entityHandler.getFeature(entity, 3);
        ASSERT_FALSE(featureClass);
    }

    { // get feature 2L,2L
        std::vector<xs_unsignedInt> entity;
        entity.push_back(2);
        FeaturePtr featureClass = entityHandler.getFeature(entity, 2);
        ASSERT_FALSE(featureClass);
    }

    NodeManagementDetailedDiscoveryData nodeManagementDetailedDiscoveryData;
    entityHandler.addEntityAndFeatureInformation(nodeManagementDetailedDiscoveryData);

    ASSERT_TRUE(nodeManagementDetailedDiscoveryData.getEntityInformationIsSet());
    std::vector<NodeManagementDetailedDiscoveryEntityInformation> entityInformationList
        = nodeManagementDetailedDiscoveryData.getEntityInformation();
    ASSERT_TRUE(entityInformationList.size() == 2);
    {
        NodeManagementDetailedDiscoveryEntityInformation entityInformation = entityInformationList.front();
        ASSERT_EQ(DeviceDefinition::EntityAddressZero.getEntity(),
                  entityInformation.getDescription().getEntityAddress().getEntity());
    }

    ASSERT_TRUE(nodeManagementDetailedDiscoveryData.getFeatureInformationIsSet());

    std::vector<keo_datagram::xs_unsignedInt> entityAddressList;
    entityAddressList.push_back(1);
    entityAddressList.push_back(2);
    entityAddressList.push_back(3);
    EntityPtr entityClass1 = EntityPtr(new Entity(entityAddressList, EntityType(EntityType::Value::GENERIC)));
    entityHandler.addEntity(entityClass1);

    entityAddressList.clear();
    entityAddressList.push_back(1);
    entityAddressList.push_back(2);
    entityAddressList.push_back(4);
    EntityPtr entityClass2 = EntityPtr(new Entity(entityAddressList, EntityType(EntityType::Value::GENERIC)));
    entityHandler.addEntity(entityClass2);

    entityAddressList.clear();
    entityAddressList.push_back(1);
    entityAddressList.push_back(2);
    entityAddressList.push_back(5);
    EntityPtr entityClass3 = EntityPtr(new Entity(entityAddressList, EntityType(EntityType::Value::GENERIC)));
    entityHandler.addEntity(entityClass3);

    entityAddressList.clear();
    entityAddressList.push_back(1);
    entityAddressList.push_back(4);
    entityAddressList.push_back(2);
    EntityPtr entityClass4 = EntityPtr(new Entity(entityAddressList, EntityType(EntityType::Value::GENERIC)));
    entityHandler.addEntity(entityClass4);

    entityAddressList.clear();
    entityAddressList.push_back(1);
    entityAddressList.push_back(4);
    entityAddressList.push_back(1);
    EntityPtr entityClass5 = EntityPtr(new Entity(entityAddressList, EntityType(EntityType::Value::GENERIC)));
    entityHandler.addEntity(entityClass5);

    entityAddressList.clear();
    entityAddressList.push_back(1);
    std::vector<EntityPtr> entityList = entityHandler.getEntityChildren(entityAddressList);
    ASSERT_EQ(5U, entityList.size());

    entityAddressList.clear();
    entityAddressList.push_back(1);
    entityAddressList.push_back(2);
    entityList = entityHandler.getEntityChildren(entityAddressList);
    ASSERT_EQ(3U, entityList.size());

    entityAddressList.clear();
    entityAddressList.push_back(1);
    entityAddressList.push_back(4);
    entityList = entityHandler.getEntityChildren(entityAddressList);
    ASSERT_EQ(2U, entityList.size());

    entityAddressList.clear();
    entityAddressList.push_back(1);
    entityAddressList.push_back(3);
    entityList = entityHandler.getEntityChildren(entityAddressList);
    ASSERT_EQ(0U, entityList.size());
}
