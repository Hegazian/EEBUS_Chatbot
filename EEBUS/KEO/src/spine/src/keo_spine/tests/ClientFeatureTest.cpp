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

#include <keo_spine/Entity.h>

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

#include <string>
#include "TestClientFeature.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

/**
 * Feature constructor
 */
TEST(ClientFeatureTest, ConstructorTest)
{
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription;
    keo_spine::TestClientFeature feature(featureDescription);

    EXPECT_TRUE(feature.getDeviceName().empty());

    EXPECT_TRUE(feature.getDeviceName().empty());
    EXPECT_TRUE(feature.getFullFeatureAddress().isEmpty());
    EXPECT_TRUE(feature.getFeatureDescription().isEmpty());
}

TEST(ClientFeatureTest, NetworkManagementFeatureDescriptionDataSetterAndGetterTest)
{
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescriptionEmpty;
    keo_spine::TestClientFeature feature(featureDescriptionEmpty);
    EXPECT_TRUE(feature.getFeatureDescription().isEmpty());

    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription;
    featureDescription.setDescription("MyDescription");
    keo_datagram::FeatureAddress featureAddress("MyDevice", 1, 2);
    featureDescription.setFeatureAddress(featureAddress);
    feature.setFeatureDescription(featureDescription);

    keo_datagram::NetworkManagementFeatureDescriptionData featureDescriptionRead
        = feature.getFeatureDescription();
    keo_datagram::FeatureAddress featureAddressRead = featureDescriptionRead.getFeatureAddress();
    ASSERT_STREQ("MyDescription", featureDescriptionRead.getDescription().c_str());
    ASSERT_EQ(featureAddress, featureAddressRead);
}

TEST(ClientFeatureTest, getFullFeatureAddress)
{
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription;
    keo_datagram::FeatureAddress featureAddress("MyDevice", 1, 2);
    featureDescription.setFeatureAddress(featureAddress);

    keo_spine::TestClientFeature feature(featureDescription);

    keo_datagram::FeatureAddress featureAddressRead = feature.getFullFeatureAddress();
    ASSERT_EQ(featureAddress, featureAddressRead);
    ASSERT_STREQ("MyDevice", featureAddressRead.getDevice().c_str());
}
