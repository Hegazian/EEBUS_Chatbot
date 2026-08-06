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

#include "DeviceTransportIdHandler.h"

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

TEST(DeviceTransportIdHandlerTest, Add)
{
    DeviceTransportIdHandler handler;

    handler.addDirectlyConnectedDevice("d:directly_1", "ship_1");
    handler.addDirectlyConnectedDevice("d:directly_2", "ship_2");
    handler.addDevice("d:indirectly_1", "ship_1");
    handler.addDevice("d:indirectly_2", "ship_2");

    ASSERT_TRUE(handler.containsTransportIdForDevice("d:directly_1"));
    ASSERT_TRUE(handler.containsTransportIdForDevice("d:directly_2"));
    ASSERT_TRUE(handler.containsTransportIdForDevice("d:indirectly_1"));
    ASSERT_TRUE(handler.containsTransportIdForDevice("d:indirectly_2"));

    ASSERT_EQ("ship_1", handler.getTransportIdForDevice("d:directly_1"));
    ASSERT_EQ("ship_2", handler.getTransportIdForDevice("d:directly_2"));
    ASSERT_EQ("ship_1", handler.getTransportIdForDevice("d:indirectly_1"));
    ASSERT_EQ("ship_2", handler.getTransportIdForDevice("d:indirectly_2"));
}

TEST(DeviceTransportIdHandlerTest, Remove)
{
    DeviceTransportIdHandler handler;

    handler.addDirectlyConnectedDevice("d:directly_1", "ship_1");
    handler.addDirectlyConnectedDevice("d:directly_2", "ship_2");
    handler.addDirectlyConnectedDevice("d:directly_3", "ship_3");
    handler.addDevice("d:indirectly_1", "ship_1");
    handler.addDevice("d:indirectly_2", "ship_2");
    handler.addDevice("d:indirectly_3", "ship_3");

    // This removes nothing because removeDevice cannot be used for directly connected devices
    handler.removeDevice("d:directly_1", "ship_1");
    ASSERT_TRUE(handler.containsTransportIdForDevice("d:directly_1"));
    ASSERT_TRUE(handler.containsTransportIdForDevice("d:indirectly_1"));

    handler.removeTransportId("ship_2");
    ASSERT_FALSE(handler.containsTransportIdForDevice("d:directly_2"));
    ASSERT_FALSE(handler.containsTransportIdForDevice("d:indirectly_2"));

    handler.removeDevice("d:indirectly_3", "ship_3");
    ASSERT_TRUE(handler.containsTransportIdForDevice("d:directly_3"));
    ASSERT_FALSE(handler.containsTransportIdForDevice("d:indirectly_2"));
}

TEST(DeviceTransportIdHandlerTest, RemoveWhenMultipleConnectionsForSingleDevice)
{
    DeviceTransportIdHandler handler;

    handler.addDirectlyConnectedDevice("d:directly_1", "ship_1");
    handler.addDirectlyConnectedDevice("d:directly_2", "ship_2");
    handler.addDevice("d:indirectly", "ship_1");
    handler.addDevice("d:indirectly", "ship_2");

    handler.removeTransportId("ship_2");
    ASSERT_FALSE(handler.containsTransportIdForDevice("d:directly_2"));
    ASSERT_TRUE(handler.containsTransportIdForDevice("d:directly_1"));
    ASSERT_TRUE(handler.containsTransportIdForDevice("d:indirectly"));

    handler.removeTransportId("ship_1");
    ASSERT_FALSE(handler.containsTransportIdForDevice("d:directly_3"));
    ASSERT_FALSE(handler.containsTransportIdForDevice("d:directly_1"));
    ASSERT_FALSE(handler.containsTransportIdForDevice("d:indirectly_2"));
}
