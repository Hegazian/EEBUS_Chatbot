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

#include <gtest/gtest.h>

#include <keo_datagram/actuator/Actuator_All.h>
#include <keo_datagram/core/Core_All.h>
#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/SpineResultErrors.h>
#include <keo_datagram/measurement/Measurement_All.h>

using namespace keo_datagram;

TEST(DatagramTest, SimpleConstructor)
{
    Datagram simpleDatagram;
    ASSERT_EQ(CmdData::Type::UNDEFINED, simpleDatagram.getCmdDataType());
    ASSERT_TRUE(simpleDatagram.getHeader().getSpecificationVersionIsSet());
    ASSERT_FALSE(simpleDatagram.isHeaderValid());
    ASSERT_FALSE(simpleDatagram.isEmpty());
    ASSERT_NE(simpleDatagram.getMsgCounter(), 0U);
}

TEST(DatagramTest, TestMsgCounterAutoIncrement)
{
    Datagram d1;
    Datagram d2;
    ASSERT_TRUE(d1.getMsgCounter() < d2.getMsgCounter());
}

TEST(DatagramTest, ParsePayloadOnProgramaticallyCreatedDatagram)
{
    Datagram datagram;
    datagram.setHeader(Header(FeatureAddress(0, 0), FeatureAddress(1, 1), CmdClassifier::Value::READ));
    datagram.setCmd(Cmd(std::make_shared<MeasurementListData>()));
    ASSERT_TRUE(datagram.parsePayload());
}

TEST(DatagramTest, TestSetPayload)
{
    Datagram datagram;
    std::vector<Cmd> cmds = { Cmd(std::make_shared<MeasurementListData>()) };
    datagram.setPayload(Payload(cmds));
    ASSERT_TRUE(datagram.parsePayload());
}

TEST(DatagramTest, datagramReplyResult)
{
    Header header = Header(FeatureAddress("d:N1", 2, 3), FeatureAddress("d:N2", 3, 4), CmdClassifier::Value::READ);
    Datagram datagram = Datagram(header, Cmd(CmdData::Type::ACTUATOR_SWITCH_DATA_TYPE));

    Datagram pReply = datagram.createReply();
    ResultDataPtr pDataResult = ResultDataPtr(new (std::nothrow) ResultData(2, "RandomFehler"));
    if (pDataResult)
    {
        Datagram pReplyResult = datagram.createReply(pDataResult);
        ASSERT_EQ(pReplyResult.getCmdClassifier(), CmdClassifier::Value::REPLY);
    }
}

TEST(DatagramTest, Enumeration)
{
    EnergyDirection dir;
    ASSERT_TRUE(dir.getValue() == EnergyDirection::Value::UNDEFINED__);
    EnergyDirection dir2(EnergyDirection::Value::CONSUME);
    ASSERT_TRUE(dir2.getValue() == EnergyDirection::Value::CONSUME);
    EnergyDirection dir3("Consume");
    ASSERT_TRUE(dir3.getValue() == EnergyDirection::Value::UNDEFINED__);
    EnergyDirection dir4("consume");
    ASSERT_TRUE(dir4.getValue() == EnergyDirection::Value::CONSUME);

    EnergyDirection dirWrong;
    ASSERT_TRUE(dirWrong.setFromString("Consume"));
    ASSERT_TRUE(dirWrong.setFromString("consume"));

    ASSERT_FALSE(dir.getValue() != dir3.getValue());
}

TEST(DatagramTest, CreateDatagramProgramatically)
{
    FeatureAddress destination = FeatureAddress("d:N1", 2, 3);
    FeatureAddress sourceAddress = FeatureAddress("d:N2", 5, 6);
    Header header = Header(sourceAddress, destination, CmdClassifier::Value::READ);
    DatagramPtr datagram = std::make_shared<Datagram>(header, Cmd(CmdData::Type::ACTUATOR_SWITCH_DATA_TYPE));
    ASSERT_TRUE(datagram != NULL);
    ASSERT_TRUE(datagram->isHeaderValid());
    ASSERT_TRUE(datagram->isPayloadValid());
}

TEST(DatagramTest, changeCmdDataViaSharedPtr)
{
    FeatureAddress destination = FeatureAddress("d:N1", 2, 3);
    FeatureAddress sourceAddress = FeatureAddress("d:N2", 5, 6);
    Header header = Header(sourceAddress, destination, CmdClassifier::Value::READ);
    Datagram datagram = Datagram(header, Cmd(CmdData::Type::MEASUREMENT_LIST_DATA_TYPE));
    ASSERT_TRUE(datagram.getCmdData()->isEmpty());

    MeasurementListDataPtr cmdData = std::static_pointer_cast<MeasurementListData>(datagram.getCmdData());

    MeasurementData md;
    md.setValue(ScaledNumber(1, 2));
    cmdData->setMeasurementData({ md });

    ASSERT_FALSE(cmdData->isEmpty());
    ASSERT_FALSE(datagram.getCmdData()->isEmpty());

    MeasurementListDataPtr cmdData2 = std::static_pointer_cast<MeasurementListData>(datagram.getCmdData());
    ASSERT_EQ(1U, cmdData2->getMeasurementData().size());
}

TEST(DatagramTest, testEmptyDoesNotRequireResponse)
{
    Datagram datagram;
    ASSERT_FALSE(datagram.requiresResponse());
}

TEST(DatagramTest, testReadRequiresResponse)
{
    FeatureAddress destination = FeatureAddress("d:N1", 2, 3);
    FeatureAddress sourceAddress = FeatureAddress("d:N2", 5, 6);
    Header header = Header(sourceAddress, destination, CmdClassifier::Value::READ);
    Datagram datagram = Datagram(header, Cmd(std::make_shared<MeasurementListData>()));
    ASSERT_TRUE(datagram.requiresResponse());
}

TEST(DatagramTest, testReplyAndWriteRequireResponseOnAckRequest)
{
    FeatureAddress destination = FeatureAddress("d:N1", 2, 3);
    FeatureAddress sourceAddress = FeatureAddress("d:N2", 5, 6);
    Cmd cmd(std::make_shared<MeasurementListData>());
    Header header = Header(sourceAddress, destination, CmdClassifier::Value::REPLY);
    header.setAckRequest(true);
    Datagram datagram = Datagram(header, cmd);
    ASSERT_TRUE(datagram.requiresResponse());

    header.setCmdClassifier(keo_datagram::CmdClassifier::Value::WRITE);
    datagram = Datagram(header, cmd);
    ASSERT_TRUE(datagram.requiresResponse());

    header.setCmdClassifier(keo_datagram::CmdClassifier::Value::REPLY);
    header.setAckRequest(false);
    datagram = Datagram(header, cmd);
    ASSERT_FALSE(datagram.requiresResponse());

    header.setCmdClassifier(keo_datagram::CmdClassifier::Value::WRITE);
    datagram = Datagram(header, cmd);
    ASSERT_FALSE(datagram.requiresResponse());
}

TEST(DatagramTest, testResultDoesNotRequireResponse)
{
    FeatureAddress destination = FeatureAddress("d:N1", 2, 3);
    FeatureAddress sourceAddress = FeatureAddress("d:N2", 5, 6);
    Cmd cmd(std::make_shared<MeasurementListData>());
    Header header = Header(sourceAddress, destination, CmdClassifier::Value::RESULT);
    header.setAckRequest(true);
    Datagram datagram = Datagram(header, cmd);
    ASSERT_FALSE(datagram.requiresResponse());
}
