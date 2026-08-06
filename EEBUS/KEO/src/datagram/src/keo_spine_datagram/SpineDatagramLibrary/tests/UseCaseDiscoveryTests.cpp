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

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <algorithm>
#include <iostream>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <gtest/gtest.h>
#include <keo_datagram/core/NodeManagementUseCaseData.h>
#include <keo_datagram/core/UseCaseDiscovery.h>
#include <keo_datagram/core/UseCaseInformationData.h>
#include <keo_datagram/core/UseCaseSupport.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

#include <gtest/gtest.h>

using namespace keo_datagram;

UseCaseSupport createUseCaseSupport(std::string const& name, std::string const& version = "",
    bool useCaseAvailable = true, std::vector<xs_unsignedInt> scenarios = {})
{
    UseCaseSupport u;
    if (!name.empty())
    {
        u.setUseCaseName(name);
    }
    if (!version.empty())
    {
        u.setUseCaseVersion(version);
    }
    if (!useCaseAvailable)
    {
        u.setUseCaseAvailable(false);
    }
    if (!scenarios.empty())
    {
        u.setScenarioSupport(scenarios);
    }
    return u;
}

NodeManagementUseCaseData createUseCaseData1()
{
    UseCaseSupport s1_1 = createUseCaseSupport("UseCase1", "Version1", true, { 1, 2, 3 });
    UseCaseSupport s1_2 = createUseCaseSupport("UseCase2", "Version1", true, { 1, 2 });
    UseCaseSupport s1_3 = createUseCaseSupport("UseCase3", "Version1", false);

    UseCaseInformationData i1;
    i1.setActor("Actor1");
    i1.setAddress(FeatureAddress(1, 1));
    i1.setUseCaseSupport({ s1_1, s1_2, s1_3 });

    UseCaseSupport s2_1 = createUseCaseSupport("UseCase1", "Version2");
    UseCaseSupport s2_2 = createUseCaseSupport("UseCase2", "Version1", true, { 1 });

    UseCaseInformationData i2;
    i2.setActor("Actor2");
    i2.setAddress(FeatureAddress(1, 2));
    i2.setUseCaseSupport({ s2_1, s2_2 });

    return NodeManagementUseCaseData({ i1, i2 });
}

NodeManagementUseCaseData createUseCaseData2()
{
    UseCaseSupport s1_1 = createUseCaseSupport("UseCase1", "Version1");
    UseCaseSupport s1_2 = createUseCaseSupport("UseCase2", "Version2", false);
    UseCaseSupport s1_3 = createUseCaseSupport("UseCase3", "Version1");

    UseCaseInformationData i1;
    i1.setActor("Actor3");
    i1.setAddress(FeatureAddress(1, 1));
    i1.setUseCaseSupport({ s1_1, s1_2, s1_3 });

    UseCaseSupport s2_1 = createUseCaseSupport("UseCase1", "Version2");
    UseCaseSupport s2_2 = createUseCaseSupport("UseCase1", "", true, { 1, 2, 3 });

    UseCaseInformationData i2;
    i2.setActor("Actor2");
    i2.setAddress(FeatureAddress(1, 1));
    i2.setUseCaseSupport({ s2_1, s2_2 });

    return NodeManagementUseCaseData({ i1, i2 });
}

NodeManagementUseCaseData createUseCaseData3()
{
    UseCaseSupport s1_1 = createUseCaseSupport("UseCase1", "Version1", true, { 1, 2 });
    UseCaseSupport s1_2 = createUseCaseSupport("UseCase2", "Version1", true);
    UseCaseSupport s1_3 = createUseCaseSupport("UseCase3", "Version1", false);

    UseCaseInformationData i1;
    i1.setActor("Actor5");
    i1.setAddress(FeatureAddress(1, 1));
    i1.setUseCaseSupport({ s1_1, s1_2, s1_3 });

    UseCaseSupport s2_1 = createUseCaseSupport("UseCase1", "Version2", { 1 });
    UseCaseSupport s2_2 = createUseCaseSupport("UseCase2", "Version1", true, { 1 });

    UseCaseInformationData i2;
    i2.setActor("Actor6");
    i2.setAddress(FeatureAddress(1, 2));
    i2.setUseCaseSupport({ s2_1, s2_2 });

    return NodeManagementUseCaseData({ i1, i2 });
}

TEST(UseCaseDiscoveryTests, testGetFeatures)
{
    UseCaseDiscovery useCaseDiscovery(createUseCaseData1(), NodeManagementUseCaseData());

    std::vector<FeatureAddress> features = useCaseDiscovery.getOwnAddressesSupporting("UseCase1");
    ASSERT_EQ(2U, features.size());
    ASSERT_NE(features.end(), std::find(features.begin(), features.end(), FeatureAddress(1, 1)));
    ASSERT_NE(features.end(), std::find(features.begin(), features.end(), FeatureAddress(1, 2)));

    features = useCaseDiscovery.getOwnAddressesSupporting("UseCase1", "Version1");
    ASSERT_EQ(1U, features.size());
    ASSERT_NE(features.end(), std::find(features.begin(), features.end(), FeatureAddress(1, 1)));

    features = useCaseDiscovery.getOwnAddressesSupporting("", "", {}, "Actor1");
    ASSERT_EQ(1U, features.size());
    ASSERT_NE(features.end(), std::find(features.begin(), features.end(), FeatureAddress(1, 1)));

    features = useCaseDiscovery.getOwnAddressesSupporting("UseCase2", "", { 1 });
    ASSERT_EQ(2U, features.size());
    ASSERT_NE(features.end(), std::find(features.begin(), features.end(), FeatureAddress(1, 2)));

    features = useCaseDiscovery.getOwnAddressesSupporting("UseCase3");
    ASSERT_EQ(0U, features.size());

    features = useCaseDiscovery.getOwnAddressesSupporting("UseCase4");
    ASSERT_EQ(0U, features.size());

    features = useCaseDiscovery.getOwnAddressesSupporting();
    ASSERT_EQ(2U, features.size());
    ASSERT_NE(features.end(), std::find(features.begin(), features.end(), FeatureAddress(1, 1)));
    ASSERT_NE(features.end(), std::find(features.begin(), features.end(), FeatureAddress(1, 2)));
}

TEST(UseCaseDiscoveryTests, testSingleMatching)
{
    UseCaseDiscovery useCaseDiscovery(createUseCaseData1(), createUseCaseData2());

    std::vector<UseCaseSupport> matching = useCaseDiscovery.getMatchingUseCases();
    ASSERT_EQ(1U, matching.size());
    ASSERT_EQ("UseCase1", matching[0].getUseCaseName());
    ASSERT_EQ("Version1", matching[0].getUseCaseVersion());
    ASSERT_FALSE(matching[0].getUseCaseAvailableIsSet()); // means that the use case is available
}

TEST(UseCaseDiscoveryTests, testMultipleMatching)
{
    UseCaseDiscovery useCaseDiscovery(createUseCaseData1(), createUseCaseData3());
    std::vector<UseCaseSupport> matching = useCaseDiscovery.getMatchingUseCases();
    ASSERT_EQ(4U, matching.size());
}

TEST(UseCaseDiscoveryTests, testRemoteSupports)
{
    UseCaseDiscovery useCaseDiscovery(createUseCaseData1(), createUseCaseData2());

    ASSERT_TRUE(useCaseDiscovery.remoteSupports("", "", {}, "Actor3"));
    ASSERT_TRUE(useCaseDiscovery.remoteSupports("UseCase1", "", {}, "Actor3"));
    ASSERT_TRUE(useCaseDiscovery.remoteSupports("UseCase1", "Version1", {}, "Actor3"));
    ASSERT_TRUE(useCaseDiscovery.remoteSupports("UseCase1", "Version1", { 1 }, "Actor3"));

    ASSERT_FALSE(useCaseDiscovery.remoteSupports("UseCase1", "Version2", {}, "Actor3"));
}
