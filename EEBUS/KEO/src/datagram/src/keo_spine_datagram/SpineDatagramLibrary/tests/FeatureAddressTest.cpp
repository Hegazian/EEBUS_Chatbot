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

/**
 *  @brief SPINE Datagram
 *
 *  @par    Module description
 *          All generated datagrams are derived from this base class
 *
 */
#include <gtest/gtest.h>


#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/EntityAddress.h>

using namespace keo_datagram;


TEST(FeatureAddressTest, Constructor)
{
    {
        FeatureAddress address = FeatureAddress();
        ASSERT_TRUE(address.isEmpty());
    }
    {
        FeatureAddress address = FeatureAddress("d:N1", 2, 3);
        ASSERT_TRUE(!address.isEmpty());
    }
    {
        FeatureAddress address = FeatureAddress("d:N1", 2, 3);
        ASSERT_TRUE(!address.isEmpty());
        ASSERT_EQ("d:N1", address.getDevice());
        std::vector<xs_unsignedInt> entityList;
        entityList.push_back(2);
        ASSERT_EQ(entityList, address.getEntity());
        ASSERT_EQ(3U, address.getFeature());
    }
}
TEST(FeatureAddressTest, Operator)
{
    {
        FeatureAddress addressL = FeatureAddress("d:N1", 2, 3);
        FeatureAddress addressR = FeatureAddress();
        ASSERT_FALSE(addressL == addressR);
    }
    {
        FeatureAddress addressL = FeatureAddress("d:N1", 2, 3);
        FeatureAddress addressR = FeatureAddress("d:N1", 2, 3);
        ASSERT_TRUE(addressL == addressR);
    }
    {
        FeatureAddress addressL = FeatureAddress("d:N1", 2, 3);
        FeatureAddress addressR = FeatureAddress("d:N1", 3, 3);
        ASSERT_TRUE(addressL != addressR);
    }
    {
        FeatureAddress addressL = FeatureAddress("d:N1", 2, 3);
        FeatureAddress addressR = FeatureAddress("d:N1", 3, 3);
        ASSERT_TRUE(addressL < addressR);
        ASSERT_FALSE(addressL > addressR);
        ASSERT_FALSE(addressL == addressR);
    }
    {
        FeatureAddress addressL = FeatureAddress("d:N1", 3, 3);
        FeatureAddress addressR = FeatureAddress("d:N1", 2, 3);
        ASSERT_TRUE(addressL > addressR);
        ASSERT_FALSE(addressL < addressR);
        ASSERT_FALSE(addressL == addressR);
    }
    {
        FeatureAddress addressL = FeatureAddress("d:N1", 2, 3);
        FeatureAddress addressR = FeatureAddress("d:N2", 2, 3);
        ASSERT_TRUE(addressL < addressR);
        ASSERT_FALSE(addressL > addressR);
        ASSERT_FALSE(addressL == addressR);
    }
    {
        FeatureAddress addressL = FeatureAddress("d:N1", 2, 3);
        FeatureAddress addressR = FeatureAddress("d:N1", 2, 4);
        ASSERT_TRUE(addressL < addressR);
        ASSERT_FALSE(addressL > addressR);
        ASSERT_FALSE(addressL == addressR);
    }
    {
        FeatureAddress addressL = FeatureAddress("d:N1", 1, 1);
        FeatureAddress addressR = FeatureAddress("d:N1", 1, 1);
        ASSERT_FALSE(addressL < addressR);
        ASSERT_FALSE(addressL > addressR);
        ASSERT_TRUE(addressL == addressR);
    }
    {
        std::vector<xs_unsignedInt> entity1;
        entity1.push_back(1);
        entity1.push_back(2);
        std::vector<xs_unsignedInt> entity2;
        entity2.push_back(1);
        entity2.push_back(2);
        FeatureAddress addressL = FeatureAddress("d:N1", entity1, 1);
        FeatureAddress addressR = FeatureAddress("d:N1", entity2, 1);
        ASSERT_FALSE(addressL < addressR);
        ASSERT_FALSE(addressL > addressR);
        ASSERT_TRUE(addressL == addressR);
        std::vector<xs_unsignedInt> entity3;
        entity3.push_back(1);
        entity3.push_back(3);
        FeatureAddress addressR2 = FeatureAddress("d:N1", entity3, 1);
        ASSERT_TRUE(addressL < addressR2);
        ASSERT_FALSE(addressL > addressR2);
        ASSERT_TRUE(addressL != addressR2);
        std::vector<xs_unsignedInt> entity4;
        entity3.push_back(2);
        entity3.push_back(1);
        FeatureAddress addressR3 = FeatureAddress("d:N1", entity3, 1);
        ASSERT_TRUE(addressL != addressR3);
        ASSERT_TRUE(addressL < addressR3);
        ASSERT_FALSE(addressL > addressR3);
    }
}
TEST(FeatureAddressTest, OperatorExtended)
{
    {
        std::vector<xs_unsignedInt> entityList;
        entityList.push_back(2);
        entityList.push_back(3);
        entityList.push_back(4);
        FeatureAddress addressL = FeatureAddress("d:N1", entityList, 5);
        FeatureAddress addressR = FeatureAddress();
        ASSERT_FALSE(addressL == addressR);
    }
    {
        std::vector<xs_unsignedInt> entityList;
        entityList.push_back(2);
        entityList.push_back(3);
        entityList.push_back(4);
        FeatureAddress addressL = FeatureAddress("d:N1", entityList, 5);
        FeatureAddress addressR = FeatureAddress("d:N1", entityList, 5);
        ASSERT_TRUE(addressL == addressR);
    }
    {
        std::vector<xs_unsignedInt> entityList;
        entityList.push_back(2);
        entityList.push_back(3);
        entityList.push_back(4);
        FeatureAddress addressL = FeatureAddress("d:N1", entityList, 5);
        FeatureAddress addressR = FeatureAddress("d:N1", entityList, 6);
        ASSERT_TRUE(addressL != addressR);
    }
    {
        std::vector<xs_unsignedInt> entityList1;
        entityList1.push_back(2);
        entityList1.push_back(3);
        entityList1.push_back(4);
        std::vector<xs_unsignedInt> entityList2;
        entityList2.push_back(2);
        entityList2.push_back(3);
        entityList2.push_back(6);
        FeatureAddress addressL = FeatureAddress("d:N1", entityList1, 5);
        FeatureAddress addressR = FeatureAddress("d:N1", entityList2, 5);
        ASSERT_TRUE(addressL != addressR);
    }
    {
        std::vector<xs_unsignedInt> entityList1;
        entityList1.push_back(2);
        entityList1.push_back(3);
        entityList1.push_back(4);
        std::vector<xs_unsignedInt> entityList2;
        entityList2.push_back(2);
        entityList2.push_back(3);
        entityList2.push_back(6);
        FeatureAddress addressL = FeatureAddress("d:N1", entityList1, 5);
        FeatureAddress addressR = FeatureAddress("d:N1", entityList2, 5);
        ASSERT_TRUE(addressL < addressR);
        ASSERT_FALSE(addressL > addressR);
        ASSERT_FALSE(addressL == addressR);
    }
    {
        std::vector<xs_unsignedInt> entityList1;
        entityList1.push_back(2);
        entityList1.push_back(3);
        entityList1.push_back(6);
        std::vector<xs_unsignedInt> entityList2;
        entityList2.push_back(2);
        entityList2.push_back(3);
        entityList2.push_back(4);
        FeatureAddress addressL = FeatureAddress("d:N1", entityList1, 5);
        FeatureAddress addressR = FeatureAddress("d:N1", entityList2, 5);
        ASSERT_TRUE(addressL > addressR);
        ASSERT_FALSE(addressL < addressR);
        ASSERT_FALSE(addressL == addressR);
    }
    {
        std::vector<xs_unsignedInt> entityList1;
        entityList1.push_back(2);
        entityList1.push_back(3);
        std::vector<xs_unsignedInt> entityList2;
        entityList2.push_back(2);
        entityList2.push_back(3);
        entityList2.push_back(4);
        FeatureAddress addressL = FeatureAddress("d:N1", entityList1, 5);
        FeatureAddress addressR = FeatureAddress("d:N1", entityList2, 5);
        ASSERT_TRUE(addressL < addressR);
        ASSERT_FALSE(addressL > addressR);
        ASSERT_FALSE(addressL == addressR);
    }
}
TEST(FeatureAddressTest, StringOutAndIn)
{
    {
        std::vector<xs_unsignedInt> entityList;
        entityList.push_back(2);
        entityList.push_back(3);
        entityList.push_back(4);
        FeatureAddress address = FeatureAddress("d:N1", entityList, 5);
        std::string out = address.toString();
        FeatureAddress addressIn;
        addressIn.fromString(out);
        ASSERT_TRUE(address == addressIn);
    }
}
TEST(FeatureAddressTest, EntityStringOutAndIn)
{
    {
        std::vector<xs_unsignedInt> entityList;
        entityList.push_back(2);
        entityList.push_back(3);
        entityList.push_back(4);
        EntityAddress address = EntityAddress("d:N1", entityList);
        std::string out = address.toString();
        EntityAddress addressIn;
        addressIn.fromString(out);
        ASSERT_TRUE(address == addressIn);
    }
}
