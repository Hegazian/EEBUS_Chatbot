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

#include <gtest/gtest.h>
#include <keo_datagram/core/Core_All.h>

using namespace keo_datagram;

TEST(CmdTest, testCopyEmptyCmdData1)
{
    Cmd cmd = Cmd(CmdData::Type::UNDEFINED);
    ASSERT_FALSE(cmd.getCmdDataIsSet());
    Cmd copy = cmd;
    ASSERT_FALSE(copy.getCmdDataIsSet());
}

TEST(CmdTest, testCopyEmptyCmdData2)
{
    Cmd cmd = Cmd(CmdDataPtr());
    ASSERT_FALSE(cmd.getCmdDataIsSet());
    Cmd copy = cmd;
    ASSERT_FALSE(copy.getCmdDataIsSet());
}

TEST(CmdTest, testCopyEmptyCmdData3)
{
    Cmd cmd;
    cmd.setCmdData(CmdDataPtr());
    ASSERT_FALSE(cmd.getCmdDataIsSet());
    Cmd copy = cmd;
    ASSERT_FALSE(copy.getCmdDataIsSet());
}

TEST(CmdTest, testOverrideOwnStateOnAssign)
{
    Cmd empty = Cmd(CmdDataPtr());
    Cmd cmd(std::make_shared<NodeManagementDetailedDiscoveryData>());
    cmd = empty;
    ASSERT_FALSE(cmd.getCmdDataIsSet());
}
