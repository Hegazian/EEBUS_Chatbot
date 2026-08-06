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
#include "TestClientFeature.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_spine/Entity.h>

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */

#include "gtest/gtest.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <string>

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

TEST(EntityTest, ConstructorTest)
{
    std::vector<keo_datagram::xs_unsignedInt> entityAddr;
    entityAddr.push_back(1);
    keo_datagram::EntityType entityType(keo_datagram::EntityType::Value::WASHER);
    keo_spine::Entity entity1(entityAddr, entityType);

    keo_datagram::NetworkManagementEntityDescriptionData entityDescription;
    entityDescription.setEntityAddress(keo_datagram::EntityAddress("", 1));
    entityDescription.setEntityType(keo_datagram::EntityType(keo_datagram::EntityType::Value::WASHER));
    keo_spine::Entity entity2(entityDescription);

    keo_datagram::NetworkManagementEntityDescriptionData entity1DescriptionRead = entity1.getEntityDescription();
    keo_datagram::NetworkManagementEntityDescriptionData entity2DescriptionRead = entity2.getEntityDescription();

    ASSERT_EQ(keo_datagram::EntityType(keo_datagram::EntityType::Value::WASHER), entity1DescriptionRead.getEntityType());
    ASSERT_EQ(entity1DescriptionRead.getEntityType(), entity2DescriptionRead.getEntityType());
    ASSERT_EQ(keo_datagram::EntityAddress("", 1), entity1DescriptionRead.getEntityAddress());
    ASSERT_EQ(entity1DescriptionRead.getEntityAddress(), entity2DescriptionRead.getEntityAddress());
}

TEST(EntityTest, getNetworkManagementEntityDescriptionData)
{
    keo_datagram::NetworkManagementEntityDescriptionData entityDescription;
    entityDescription.setDescription("myDescription");
    entityDescription.setEntityAddress(keo_datagram::EntityAddress("myDevice", 2));
    entityDescription.setEntityType(keo_datagram::EntityType(keo_datagram::EntityType::Value::GENERIC));
    entityDescription.setLabel("myLabel");
    entityDescription.setLastStateChange(keo_datagram::NetworkManagementStateChange::Value::MODIFIED);
    entityDescription.setMinimumTrustLevel("myMinimumTrustLevel");

    keo_spine::Entity entity(entityDescription);
    keo_datagram::NetworkManagementEntityDescriptionData entityDescriptionRead = entity.getEntityDescription();

    ASSERT_TRUE(entityDescriptionRead.getDescriptionIsSet());
    ASSERT_STREQ("myDescription", entityDescriptionRead.getDescription().c_str());

    ASSERT_TRUE(entityDescriptionRead.getEntityAddressIsSet());
    ASSERT_EQ(keo_datagram::EntityAddress("myDevice", 2), entityDescriptionRead.getEntityAddress());

    ASSERT_TRUE(entityDescriptionRead.getEntityTypeIsSet());
    ASSERT_EQ(keo_datagram::EntityType(keo_datagram::EntityType::Value::GENERIC), entityDescriptionRead.getEntityType());

    ASSERT_TRUE(entityDescriptionRead.getLabelIsSet());
    ASSERT_STREQ("myLabel", entityDescriptionRead.getLabel().c_str());

    ASSERT_TRUE(entityDescriptionRead.getLastStateChangeIsSet());
    ASSERT_EQ(keo_datagram::NetworkManagementStateChange(keo_datagram::NetworkManagementStateChange::Value::MODIFIED),
        entityDescriptionRead.getLastStateChange());
    ASSERT_NE(keo_datagram::NetworkManagementStateChange(keo_datagram::NetworkManagementStateChange::Value::REMOVED),
        entityDescriptionRead.getLastStateChange());

    ASSERT_TRUE(entityDescriptionRead.getDescriptionIsSet());
    ASSERT_STREQ("myMinimumTrustLevel", entityDescriptionRead.getMinimumTrustLevel().c_str());
}

TEST(EntityTest, getEntity)
{
    std::vector<keo_datagram::xs_unsignedInt> entityAddr;
    entityAddr.push_back(2);
    entityAddr.push_back(3);
    entityAddr.push_back(4);
    keo_datagram::EntityType entityType(keo_datagram::EntityType::Value::GENERIC);
    keo_spine::Entity entity(entityAddr, entityType);

    std::vector<keo_datagram::xs_unsignedInt> entityRead = entity.getEntity();
    ASSERT_EQ(2U, entityRead[0]);
    ASSERT_EQ(3U, entityRead[1]);
    ASSERT_EQ(4U, entityRead[2]);
}

TEST(EntityTest, featureAddGetRemoveTest)
{
    std::vector<keo_datagram::xs_unsignedInt> entityAddr;
    entityAddr.push_back(0);
    keo_datagram::EntityType entityType(keo_datagram::EntityType::Value::DEVICE_INFORMATION);

    keo_spine::Entity entity(entityAddr, entityType);

    // no feature set
    std::vector<FeaturePtr> featureList = entity.getFeatures();
    ASSERT_EQ(0U, featureList.size());

    // add feature 0
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription0;
    featureDescription0.setFeatureAddress(keo_datagram::FeatureAddress("myDevice", 0, 0));
    featureDescription0.setFeatureType(keo_datagram::FeatureType(keo_datagram::FeatureType::Value::GENERIC));
    featureDescription0.setRole(keo_datagram::Role::Value::CLIENT);
    keo_spine::FeaturePtr pFeature0 = keo_spine::FeaturePtr(new keo_spine::TestClientFeature(featureDescription0));
    entity.addFeature(pFeature0);

    // check for feature 0 in list
    featureList = entity.getFeatures();
    ASSERT_EQ(1U, featureList.size());

    bool featureInList0 = false;
    for (auto iter = featureList.begin(); iter != featureList.end(); ++iter)
    {
        if (*iter == pFeature0)
        {
            featureInList0 = true;
            break;
        }
    }
    ASSERT_TRUE(featureInList0);

    // add feature 1
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription1;
    featureDescription1.setFeatureAddress(keo_datagram::FeatureAddress("myDevice", 0, 1));
    featureDescription1.setFeatureType(keo_datagram::FeatureType(keo_datagram::FeatureType::Value::GENERIC));
    featureDescription1.setRole(keo_datagram::Role::Value::CLIENT);
    keo_spine::TestFeaturePtr pFeature1 = TestFeaturePtr(new keo_spine::TestClientFeature(featureDescription1));
    ASSERT_TRUE(entity.addFeature(pFeature1));
    ASSERT_TRUE(entity.validate());
    featureList = entity.getFeatures();
    ASSERT_EQ(2U, featureList.size());

    // check for feature 1 in list
    bool featureInList1 = false;
    for (auto iter = featureList.begin(); iter != featureList.end(); ++iter)
    {
        if (*iter == pFeature1)
        {
            featureInList1 = true;
            break;
        }
    }
    ASSERT_TRUE(featureInList1);

    // Check if the entity is set correctly in the added feature
    ASSERT_EQ(entityAddr, pFeature1->getFeatureDescription().getFeatureAddress().getEntity());
    ASSERT_EQ(entity.getEntityDescription().getEntityAddress().getEntity(), entityAddr);

    // test getFeature()
    keo_spine::FeaturePtr pFeatureRead;
    pFeatureRead = entity.getFeature(0);
    ASSERT_EQ(pFeature0, pFeatureRead);
    pFeatureRead = entity.getFeature(1);
    ASSERT_EQ(pFeature1, pFeatureRead);
    pFeatureRead = entity.getFeature(2);
    ASSERT_FALSE(pFeatureRead);

    // remove feature 1
    ASSERT_TRUE(entity.removeFeature(1));
    ASSERT_FALSE(entity.removeFeature(1));
    featureList = entity.getFeatures();
    ASSERT_EQ(1U, featureList.size());

    // only feature 0 should be left
    auto iter = featureList.begin();
    ASSERT_EQ(pFeature0, *iter);

    // remove feature 0
    ASSERT_TRUE(entity.removeFeature(0));
    ASSERT_FALSE(entity.removeFeature(0));
    featureList = entity.getFeatures();
    ASSERT_EQ(0U, featureList.size());
}

TEST(EntityTest, entityToString)
{
    keo_datagram::NetworkManagementEntityDescriptionData description;
    std::vector<keo_datagram::xs_unsignedInt> entityList;

    entityList.push_back(0);
    description.setEntityAddress(keo_datagram::EntityAddress(std::string(), entityList));
    keo_spine::EntityPtr entity = keo_spine::EntityPtr(new keo_spine::Entity(description));
    EXPECT_STREQ("/0/", entity->addressToString().c_str());

    entityList.push_back(1);
    description.setEntityAddress(keo_datagram::EntityAddress(std::string(), entityList));
    entity = keo_spine::EntityPtr(new keo_spine::Entity(description));
    EXPECT_STREQ("/0/1/", entity->addressToString().c_str());

    entityList.push_back(10);
    description.setEntityAddress(keo_datagram::EntityAddress(std::string(), entityList));
    entity = keo_spine::EntityPtr(new keo_spine::Entity(description));
    EXPECT_STREQ("/0/1/10/", entity->addressToString().c_str());

    entityList.push_back(100);
    description.setEntityAddress(keo_datagram::EntityAddress(std::string(), entityList));
    entity = keo_spine::EntityPtr(new keo_spine::Entity(description));
    EXPECT_STREQ("/0/1/10/100/", entity->addressToString().c_str());

    entityList.push_back(1000);
    description.setEntityAddress(keo_datagram::EntityAddress(std::string(), entityList));
    entity = keo_spine::EntityPtr(new keo_spine::Entity(description));
    EXPECT_STREQ("/0/1/10/100/1000/", entity->addressToString().c_str());
}
TEST(EntityTest, ValidationOfEntity)
{
    std::vector<keo_datagram::xs_unsignedInt> entityAddr;
    entityAddr.push_back(1);
    keo_datagram::EntityType entityType(keo_datagram::EntityType::Value::DEVICE_INFORMATION);

    keo_spine::Entity entity(entityAddr, entityType);

    // no feature set
    std::vector<FeaturePtr> featureList = entity.getFeatures();
    ASSERT_EQ(0U, featureList.size());

    // add feature 0
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription0;
    featureDescription0.setFeatureAddress(keo_datagram::FeatureAddress("myDevice", 1, 0));
    featureDescription0.setFeatureType(keo_datagram::FeatureType(keo_datagram::FeatureType::Value::GENERIC));
    featureDescription0.setRole(keo_datagram::Role::Value::CLIENT);
    keo_spine::FeaturePtr pFeature0 = keo_spine::FeaturePtr(new keo_spine::TestClientFeature(featureDescription0));
    entity.addFeature(pFeature0);
    ASSERT_TRUE(entity.validate());

    // add feature 1 but to entity 2 instead of entity 1
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription1;
    featureDescription1.setFeatureAddress(keo_datagram::FeatureAddress("myDevice", 2, 1));
    featureDescription1.setFeatureType(keo_datagram::FeatureType(keo_datagram::FeatureType::Value::GENERIC));
    featureDescription1.setRole(keo_datagram::Role::Value::CLIENT);
    keo_spine::FeaturePtr pFeature1 = keo_spine::FeaturePtr(new keo_spine::TestClientFeature(featureDescription1));
    entity.addFeature(pFeature1);

    ASSERT_FALSE(entity.validate());
    featureList = entity.getFeatures();
    ASSERT_EQ(2U, featureList.size());
}

