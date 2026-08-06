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

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include "ConnectionStateHandlerTest.h"
#include "ActionState.h"
#include "StateHandler.h"
#include "keo_ship/ShipHeader.h"

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */

#include "gtest/gtest.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <vector>
/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */
using namespace keo_ship;

ConnectionStateHandlerTest::ConnectionStateHandlerTest()
    : m_pConnectionStateHandler(NULL)
    , m_pNodeInfo(NULL)
    , m_pStateInfo(NULL)
{
}

void ConnectionStateHandlerTest::SetUp()
{
    m_pNodeInfo = new NodeInfo();
    initJustNodeInfo();
    m_pConnectionStateHandler = new ConnectionStateHandlerExtend(
        "ID", *m_pNodeInfo, true, &m_connectionStateHandlerListener, "wss://hostname:12345/ship/");

    delete m_pNodeInfo;
    m_pNodeInfo = m_pConnectionStateHandler->getNodeInfo();
    m_pStateInfo = m_pConnectionStateHandler->getStateInfo();
}
void ConnectionStateHandlerTest::initJustNodeInfo()
{
    m_pNodeInfo->setConnected(true);
    m_pNodeInfo->setEnabledDataExchange(false);
    m_pNodeInfo->setNeedUnrestrictedAccess(true);
    m_pNodeInfo->setPinOwnRequirement(PinRequirement::PIN_NONE);
    TrustLevel trustLevel;
    m_pNodeInfo->setTrustLevel(trustLevel);
    m_pNodeInfo->setShipVersionMajor(1);
    m_pNodeInfo->setShipVersionMinor(0);
    m_pNodeInfo->setShipFormat("");
}
void ConnectionStateHandlerTest::initNodeInfo(bool isClient)
{
    initJustNodeInfo();
    m_pStateInfo->setInitialized(true);
    m_pStateInfo->setClient(isClient);
    m_pStateInfo->setPartnerIsHelloReady(false);
    m_pStateInfo->setAcceptProlongationRequest(true);
    m_pStateInfo->setPinOk(false);
    m_pStateInfo->setPartnerIsPinOk(false);
    m_pStateInfo->setNumberOfAcceptedProlongationRequests((short)0);
    m_pStateInfo->setError((short)0);
    m_pStateInfo->setState(SmeConnectionState::CMI_INIT_STATE);
    m_pStateInfo->setPinState(SmeConnectionState::STATE_UNDEFINED);
    m_pStateInfo->setTimerMain(0);
    m_pStateInfo->setTimerSendProlongationRequest(0);
    m_pStateInfo->setLastWaitingReceived(0);
    m_pStateInfo->setTimerProlongationRequestReply(0);
    m_pStateInfo->setTimerPin(0);
    m_pStateInfo->setTimerPinRecall(0);
}
void ConnectionStateHandlerTest::resetNodeInfo(bool isClient)
{
    m_pNodeInfo = new NodeInfo();
    m_pStateInfo = new StateInfo();
    initNodeInfo(isClient);
}

TEST_F(ConnectionStateHandlerTest, testInitState_CMIState)
{
    { // client role
        initNodeInfo(true);
        keo_ship::ActionState action = StateHandler::initState(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_CLIENT_SEND_CMI_MESSAGE_AND_START_CMI_TIMER);
        m_pConnectionStateHandler->doAction(action);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::CMI_STATE_CLIENT_WAIT);
        ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutCmi());
        std::vector<std::vector<char> > sentData = m_connectionStateHandlerListener.getSentData();
        ASSERT_TRUE(sentData.size() == 1);
        ASSERT_TRUE(sentData[0].size() == 2);
        ASSERT_TRUE(sentData[0][0] == 0);
        ASSERT_TRUE(sentData[0][1] == 0);
        // wait timeout
        m_pStateInfo->setTimerMain(0);
        action = StateHandler::getStateFromTimeout(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_CLOSE_CONNECTION);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::STATE_WAIT_CLOSE_CONNECTION);
    }
    { // server role
        initNodeInfo(false);
        m_connectionStateHandlerListener.clear();
        ActionState action = StateHandler::initState(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_SERVER_START_CMI_TIMER);
        m_pConnectionStateHandler->doAction(action);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::CMI_STATE_SERVER_WAIT);
        ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutCmi());
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentData().size() == 0);
        // wait timeout
        m_pStateInfo->setTimerMain(0);
        action = StateHandler::getStateFromTimeout(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_CLOSE_CONNECTION);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::STATE_WAIT_CLOSE_CONNECTION);
    }
    m_connectionStateHandlerListener.clear();
}
/**
 * CMIStateEnd_HelloStart.
 */
TEST_F(ConnectionStateHandlerTest, testInitState_CMIStateEnd_HelloStart)
{
    { // client role
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pStateInfo->setState(SmeConnectionState::CMI_STATE_CLIENT_WAIT);
        m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutCmi());
        std::vector<char> data;
        data.push_back(0x00);
        data.push_back(0x00);
        m_pConnectionStateHandler->receiveCMIInitMessage(data);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
        ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
        CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[0];
        ASSERT_EQ(sentClass->getDataType(), ShipDataType::CONNECTION_HELLO_TYPE);
        ConnectionHello* hello = (ConnectionHello*)sentClass;
        ASSERT_TRUE(hello->getPhaseIsSet());
        ASSERT_EQ(hello->getPhase().getDataString(), "pending"); // no trust level
        ASSERT_TRUE(hello->getWaitingIsSet());
        ASSERT_EQ(hello->getWaiting(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
        ASSERT_FALSE(hello->getProlongationRequestIsSet());
        // wait timeout
        m_pStateInfo->setTimerMain(0);
        ActionState action = StateHandler::getStateFromTimeout(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_HELLO_STATE_PENDING_TIMEOUT);
    }
    { // server role
        initNodeInfo(false);
        m_connectionStateHandlerListener.clear();
        m_pStateInfo->setState(SmeConnectionState::CMI_STATE_SERVER_WAIT);
        m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutCmi());
        TrustLevel trustLevel = m_pNodeInfo->getTrustLevel();
        trustLevel.setUserTrust(TrustLevel::TRUST_VALUE_USER_AUTO_ACCEPT);
        m_pNodeInfo->setTrustLevel(trustLevel); // set trustLevel so the phase is ready
        std::vector<char> data;
        data.push_back(0x00);
        data.push_back(0x00);
        m_pConnectionStateHandler->receiveCMIInitMessage(data);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_HELLO_STATE_READY_LISTEN);
        ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
        CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[0];
        ASSERT_EQ(sentClass->getDataType(), ShipDataType::CONNECTION_HELLO_TYPE);
        ConnectionHello* hello = (ConnectionHello*)sentClass;
        ASSERT_TRUE(hello->getPhaseIsSet());
        ASSERT_EQ(hello->getPhase().getDataString(), "ready");
        ASSERT_TRUE(hello->getWaitingIsSet());
        ASSERT_EQ(hello->getWaiting(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
        ASSERT_FALSE(hello->getProlongationRequestIsSet());
        // wait timeout
        m_pStateInfo->setTimerMain(0);
        ActionState action = StateHandler::getStateFromTimeout(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_HELLO_STATE_READY_TIMEOUT);
    }
    m_connectionStateHandlerListener.clear();
}

/**
 * HelloState
 */
TEST_F(ConnectionStateHandlerTest, testInitState_HelloState)
{
    { // pending role
      { // send hello update message - pending
          initNodeInfo(true);
    m_connectionStateHandlerListener.clear();
    m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
    m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
    ConnectionHello* hello = new ConnectionHello();
    hello->setPhase(ConnectionHelloPhase::CONNECTIONHELLOPHASE_PENDING);
    hello->setWaiting(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
    m_pConnectionStateHandler->receiveCMIControlMessage(hello);
    ASSERT_EQ(m_pStateInfo->getTimerSendProlongationRequest(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady()
            - (m_pConnectionStateHandler->getProtocolConfig().getMinimumHelloWaitForReadyForProlongation() / 2));
    ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
    ASSERT_EQ(m_pStateInfo->getLastWaitingReceived(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
}
{ // send hello update message - pending & prolongationRequest
    initNodeInfo(true);
    m_connectionStateHandlerListener.clear();
    m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
    m_pStateInfo->setTimerMain(10000);
    ConnectionHello* hello = new ConnectionHello();
    hello->setPhase(ConnectionHelloPhase::CONNECTIONHELLOPHASE_PENDING);
    hello->setProlongationRequest(true);
    m_pConnectionStateHandler->receiveCMIControlMessage(hello);
    ASSERT_EQ(m_pStateInfo->getTimerMain(), 10000 + m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
    ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
    CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[0];
    ASSERT_EQ(sentClass->getDataType(), ShipDataType::CONNECTION_HELLO_TYPE);
    hello = (ConnectionHello*)sentClass;
    ASSERT_TRUE(hello->getPhaseIsSet());
    ASSERT_EQ(hello->getPhase().getDataString(), "pending");
    ASSERT_TRUE(hello->getWaitingIsSet());
    ASSERT_EQ(hello->getWaiting(), m_pStateInfo->getTimerMain());
    ASSERT_FALSE(hello->getProlongationRequestIsSet());
}
{ // send hello update message - ready
    initNodeInfo(true);
    m_connectionStateHandlerListener.clear();
    m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
    m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
    ConnectionHello* hello = new ConnectionHello();
    hello->setPhase(ConnectionHelloPhase::CONNECTIONHELLOPHASE_READY);
    hello->setWaiting(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
    m_pConnectionStateHandler->receiveCMIControlMessage(hello);
    ASSERT_EQ(m_pStateInfo->getTimerSendProlongationRequest(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady()
            - (m_pConnectionStateHandler->getProtocolConfig().getMinimumHelloWaitForReadyForProlongation() / 2));
    ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
    ASSERT_EQ(m_pStateInfo->getLastWaitingReceived(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
}
}
{ // ready role
  { // send hello update message - pending - client
      initNodeInfo(true);
m_connectionStateHandlerListener.clear();
m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_READY_LISTEN);
m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
ConnectionHello* hello = new ConnectionHello();
hello->setPhase(ConnectionHelloPhase::CONNECTIONHELLOPHASE_PENDING);
m_pConnectionStateHandler->receiveCMIControlMessage(hello);
ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_HELLO_STATE_READY_LISTEN);
ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 0);
}
{ // send hello update message - pending - client & prolongationRequest
    initNodeInfo(true);
    m_connectionStateHandlerListener.clear();
    m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_READY_LISTEN);
    m_pStateInfo->setTimerMain(10000);
    TrustLevel trustLevel = m_pNodeInfo->getTrustLevel();
    trustLevel.setUserTrust(8);
    m_pNodeInfo->setTrustLevel(trustLevel);
    // nodeProtocolInfo.m_pNodeInfo->trustLevel.m_2ndFactor = ship.TRUST_VALUE_2NDFACTOR__PIN;
    ConnectionHello* hello = new ConnectionHello();
    hello->setPhase(ConnectionHelloPhase::CONNECTIONHELLOPHASE_PENDING);
    hello->setProlongationRequest(true);
    m_pConnectionStateHandler->receiveCMIControlMessage(hello);
    ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_HELLO_STATE_READY_LISTEN);
    ASSERT_EQ(m_pStateInfo->getTimerMain(), 10000 + m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
    ASSERT_TRUE(m_pStateInfo->getNumberOfAcceptedProlongationRequests() == 1);
    ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
}
{ // send hello update message - ready - client
    initNodeInfo(true);
    m_connectionStateHandlerListener.clear();
    m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_READY_LISTEN);
    m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
    ConnectionHello* hello = new ConnectionHello();
    hello->setPhase(ConnectionHelloPhase::CONNECTIONHELLOPHASE_READY);
    m_pConnectionStateHandler->receiveCMIControlMessage(hello);
    ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_PROT_H_STATE_CLIENT_LISTEN_CHOICE);
    ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHandshakeWaitForReady());
    ASSERT_TRUE(m_pStateInfo->isPartnerIsHelloReady());
    ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
    CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[0];
    ASSERT_EQ(sentClass->getDataType(), ShipDataType::MESSAGE_PROTOCOL_HANDSHAKE_TYPE);
    MessageProtocolHandshake* message = (MessageProtocolHandshake*)sentClass;
    ASSERT_TRUE(message->getHandshakeTypeIsSet() && message->getVersionIsSet() && message->getFormatsIsSet());
    ASSERT_EQ(message->getHandshakeType().getData(), ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_ANNOUNCEMAX);
    ASSERT_EQ(message->getVersion().getMajor(), 1);
    ASSERT_EQ(message->getVersion().getMinor(), 0);
    ASSERT_TRUE(message->getFormats().getFormat().size() == 1);
    ASSERT_EQ(message->getFormats().getFormat()[0], "JSON-UTF8");
    delete hello;
}
{ // send hello update message - ready - server
    initNodeInfo(false);
    m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_READY_LISTEN);
    m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
    ConnectionHello* hello = new ConnectionHello();
    hello->setPhase(ConnectionHelloPhase::CONNECTIONHELLOPHASE_READY);
    m_pConnectionStateHandler->receiveCMIControlMessage(hello);
    ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_PROPOSAL);
    ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHandshakeWaitForReady());
    delete hello;
}
{ // send hello update message - aborted
    initNodeInfo(true);
    m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_READY_LISTEN);
    m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHelloWaitForReady());
    ConnectionHello* hello = new ConnectionHello();
    hello->setPhase(ConnectionHelloPhase::CONNECTIONHELLOPHASE_ABORTED);
    m_pConnectionStateHandler->receiveCMIControlMessage(hello);
    ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::STATE_WAIT_CLOSE_CONNECTION);
    ASSERT_EQ(m_pStateInfo->getTimerMain(), 0U);
    delete hello;
}
}
{ { // pending role - main timeout
    initNodeInfo(false);
m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
m_pStateInfo->setTimerMain(0);
ActionState action = StateHandler::getStateFromTimeout(m_pStateInfo);
ASSERT_EQ(action, ActionState::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION);
}
{ // pending role - SendProlongationRequest timeout
    initNodeInfo(false);
    m_connectionStateHandlerListener.clear();
    m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
    m_pStateInfo->setTimerSendProlongationRequest(0);
    m_pStateInfo->setLastWaitingReceived(25000);
    ActionState action = StateHandler::getStateFromSendProlongationRequestTimeout(m_pStateInfo);
    ASSERT_EQ(action, ActionState::ACTION_SEND_PROLONGATION_MESSAGE_AND_START_PROLONGATION_TIMER);
    m_pConnectionStateHandler->doAction(action);
    ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
    ASSERT_EQ(m_pStateInfo->getTimerProlongationRequestReply(), m_pStateInfo->getLastWaitingReceived());
    ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
    CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[0];
    ASSERT_EQ(sentClass->getDataType(), ShipDataType::CONNECTION_HELLO_TYPE);
    ConnectionHello* hello = (ConnectionHello*)sentClass;
    ASSERT_TRUE(hello->getPhaseIsSet());
    ASSERT_EQ(hello->getPhase().getDataString(), "pending");
    ASSERT_FALSE(hello->getWaitingIsSet());
    ASSERT_TRUE(hello->getProlongationRequestIsSet());
    ASSERT_TRUE(hello->getProlongationRequest());
}
{ // pending role - SendProlongationRequest timeout
    initNodeInfo(false);
    m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
    m_pStateInfo->setTimerProlongationRequestReply(0);
    ActionState action = StateHandler::getStateFromTimeout(m_pStateInfo);
    ASSERT_EQ(action, ActionState::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION);
}
}
{ { // ready role - main timeout
    initNodeInfo(false);
m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_READY_LISTEN);
m_pStateInfo->setTimerMain(0);
ActionState action = StateHandler::getStateFromTimeout(m_pStateInfo);
ASSERT_EQ(action, ActionState::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION);
}
}
{
    { // user input - switch state from pending to ready
        initNodeInfo(false);
        m_connectionStateHandlerListener.clear();
        m_pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
        m_pStateInfo->setTimerMain(0);
        ActionState action = StateHandler::getStateFromTimeout(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION);
    }
}
m_connectionStateHandlerListener.clear();
}
/**
 * HandshakeState
 */
TEST_F(ConnectionStateHandlerTest, testInitState_HandshakeState)
{
    { // client role
        initNodeInfo(true);
        m_pStateInfo->setState(SmeConnectionState::SME_PROT_H_STATE_CLIENT_LISTEN_CHOICE);
        m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHandshakeWaitForReady());
        MessageProtocolHandshake* message = new MessageProtocolHandshake();
        message->setHandshakeType(ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_SELECT);
        message->setVersion(ClassVersion(1, 0));
        std::vector<std::string> formats;
        formats.push_back("JSON-UTF8");
        MessageProtocolFormats messageProtocolFormats(formats);
        message->setFormats(messageProtocolFormats);
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_PIN_STATE_CHECK_OK);
        ASSERT_TRUE(m_pStateInfo->isPinOk());
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_INIT);
        ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutPinAskInit());
    }
    { // client role - pin required
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pNodeInfo->setPinOwnRequirement(PinRequirement::PIN_REQUIRED);
        m_pStateInfo->setState(SmeConnectionState::SME_PROT_H_STATE_CLIENT_LISTEN_CHOICE);
        m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHandshakeWaitForReady());
        MessageProtocolHandshake* message = new MessageProtocolHandshake();
        message->setHandshakeType(ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_SELECT);
        message->setVersion(ClassVersion(1, 0));
        std::vector<std::string> formats;
        formats.push_back("JSON-UTF8");
        MessageProtocolFormats messageProtocolFormats(formats);
        message->setFormats(messageProtocolFormats);
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_PIN_STATE_CHECK_LISTEN);
        ASSERT_FALSE(m_pStateInfo->isPinOk());
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_INIT);
        ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutPinAskInit());
    }
    { // server role - get protocol handshake message
        initNodeInfo(false);
        m_pStateInfo->setState(SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_PROPOSAL);
        m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHandshakeWaitForReady());
        MessageProtocolHandshake* message = new MessageProtocolHandshake();
        message->setHandshakeType(ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_ANNOUNCEMAX);
        message->setVersion(ClassVersion(1, 0));
        std::vector<std::string> formats;
        formats.push_back("JSON-UTF8");
        MessageProtocolFormats messageProtocolFormats(formats);
        message->setFormats(messageProtocolFormats);
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_CONFIRM);
        ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutHandshakeWaitForReady());
    }
    { // server role - get protocol handshake message
        initNodeInfo(false);
        m_pStateInfo->setState(SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_CONFIRM);
        m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHandshakeWaitForReady());
        m_pNodeInfo->setShipFormat("JSON-UTF8");
        MessageProtocolHandshake* message = new MessageProtocolHandshake();
        message->setHandshakeType(ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_SELECT);
        message->setVersion(ClassVersion(1, 0));
        std::vector<std::string> formats;
        formats.push_back("JSON-UTF8");
        MessageProtocolFormats messageProtocolFormats(formats);
        message->setFormats(messageProtocolFormats);
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_PIN_STATE_CHECK_OK);
        ASSERT_TRUE(m_pStateInfo->isPinOk());
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_INIT);
        ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutPinAskInit());
    }
    { // server role - pin required
        initNodeInfo(false);
        m_pNodeInfo->setPinOwnRequirement(PinRequirement::PIN_REQUIRED);
        m_pStateInfo->setState(SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_CONFIRM);
        m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHandshakeWaitForReady());
        m_pNodeInfo->setShipFormat("JSON-UTF8");
        MessageProtocolHandshake* message = new MessageProtocolHandshake();
        message->setHandshakeType(ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_SELECT);
        message->setVersion(ClassVersion(1, 0));
        std::vector<std::string> formats;
        formats.push_back("JSON-UTF8");
        MessageProtocolFormats messageProtocolFormats(formats);
        message->setFormats(messageProtocolFormats);
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_PIN_STATE_CHECK_LISTEN);
        ASSERT_FALSE(m_pStateInfo->isPinOk());
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_INIT);
        ASSERT_EQ(m_pStateInfo->getTimerMain(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutPinAskInit());
    }
    { // server role - timeout
        initNodeInfo(false);
        m_pStateInfo->setState(SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_CONFIRM);
        m_pStateInfo->setTimerMain(0);
        ActionState action = StateHandler::getStateFromTimeout(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_SEND_PROT_H_ERROR_MESSAGE_AND_CLOSE_CONNECTION);
        ASSERT_EQ(m_pStateInfo->getError(), 1);
    }
}

/**
 * PinState
 *
 * @throws UnsupportedEncodingException
 */
TEST_F(ConnectionStateHandlerTest, testInitState_PinState)
{
    { // check role - ok
        initNodeInfo(true);
        m_pStateInfo->setState(SmeConnectionState::SME_PIN_STATE_CHECK_OK);
        ConnectionPinInput* message = new ConnectionPinInput();
        message->setPin("12345678");
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_PIN_STATE_CHECK_OK);
        ASSERT_EQ(0U, m_connectionStateHandlerListener.getSentEvent().size());
    }
    { // check role - busy wait - pin message is not possible here because m_pinRequirement = NONE
        initNodeInfo(true);
        m_pStateInfo->setState(SmeConnectionState::SME_PIN_STATE_CHECK_BUSY_WAIT);
        ConnectionPinInput* message = new ConnectionPinInput();
        message->setPin("12345678");
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_PIN_STATE_CHECK_BUSY_WAIT);
        ASSERT_EQ(0U, m_connectionStateHandlerListener.getSentEvent().size());
    }
    { // check role - busy wait - pin message is answered with busy message
        initNodeInfo(true);
        m_pNodeInfo->setPinOwnRequirement(PinRequirement::PIN_OPTIONAL);
        m_pStateInfo->setState(SmeConnectionState::SME_PIN_STATE_CHECK_BUSY_WAIT);
        m_pStateInfo->setTimerPin(m_pConnectionStateHandler->getProtocolConfig().getTimeoutPinRecall());
        ConnectionPinInput* message = new ConnectionPinInput();
        message->setPin("12345678");
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::SME_PIN_STATE_CHECK_BUSY_WAIT);
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
        CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[0];
        ASSERT_EQ(sentClass->getDataType(), ShipDataType::CONNECTION_PIN_STATE_TYPE);
        ConnectionPinState* sendMessage = (ConnectionPinState*)sentClass;
        ASSERT_TRUE(sendMessage->getPinStateIsSet() && sendMessage->getInputPermissionIsSet());
        ASSERT_EQ(sendMessage->getPinState().getData(), PinState::PINSTATE_OPTIONAL);
        ASSERT_EQ(sendMessage->getInputPermission().getData(), PinInputPermission::PININPUTPERMISSION_BUSY);
        ASSERT_EQ(0U, m_connectionStateHandlerListener.getSentEvent().size());
    }
    { // check listen - got correct pin and send an event (with pin) to the parent
        initNodeInfo(true);
        m_pNodeInfo->setPinOwnRequirement(PinRequirement::PIN_OPTIONAL);
        m_pStateInfo->setState(SmeConnectionState::SME_PIN_STATE_CHECK_LISTEN);
        ConnectionPinInput* message = new ConnectionPinInput();
        message->setPin("12345678");
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        std::vector<NodeEvent> sentEvents = m_connectionStateHandlerListener.getSentEvent();

        ASSERT_EQ(1U, sentEvents.size());
        ASSERT_EQ(NodeEvent::NODE_EVENT_PIN_RECEIVED, sentEvents[0]);
        ASSERT_EQ(SmeConnectionState::SME_PIN_STATE_CHECK_LISTEN, m_pStateInfo->getState());

        m_pConnectionStateHandler->setSecondFactorTrust(TrustLevel::TRUST_VALUE_2NDFACTOR_PIN);
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 2);
        CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[1];
        ASSERT_EQ(sentClass->getDataType(), ShipDataType::CONNECTION_PIN_STATE_TYPE);
        ConnectionPinState* sendMessage = (ConnectionPinState*)sentClass;
        ASSERT_EQ(PinState::PINSTATE_PINOK, sendMessage->getPinState().getData());
        ASSERT_FALSE(sendMessage->getInputPermissionIsSet());
        ASSERT_EQ(SmeConnectionState::SME_PIN_STATE_CHECK_OK, m_pStateInfo->getState());
    }
    { // main timeout
        initNodeInfo(true);
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_INIT);
        m_pStateInfo->setTimerPin(0);
        ActionState action = StateHandler::getStateFromTimeout(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_CLOSE_CONNECTION);
        ASSERT_EQ(m_pStateInfo->getState(), SmeConnectionState::STATE_WAIT_CLOSE_CONNECTION);
    }
    { // got pin state - BUSY
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ConnectionPinState* sendMessage = new ConnectionPinState();
        sendMessage->setPinState(PinState::PINSTATE_OPTIONAL);
        sendMessage->setInputPermission(PinInputPermission::PININPUTPERMISSION_BUSY);
        m_pConnectionStateHandler->receiveCMIControlMessage(sendMessage);
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
    }
    { // got pin state - OK
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ConnectionPinState* sendMessage = new ConnectionPinState();
        sendMessage->setPinState(PinState::PINSTATE_OPTIONAL);
        sendMessage->setInputPermission(PinInputPermission::PININPUTPERMISSION_OK);
        m_pConnectionStateHandler->receiveCMIControlMessage(sendMessage);
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        std::vector<NodeEvent> sentEvents = m_connectionStateHandlerListener.getSentEvent();
        ASSERT_TRUE(sentEvents.size() == 1);
        ASSERT_EQ(sentEvents[0], NodeEvent::NODE_EVENT_PIN_INPUT_READY);
    }
    { // got pin error - penalty on
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pNodeInfo->setPinOwnRequirement(PinRequirement::PIN_OPTIONAL);
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ConnectionPinError* pinError = new ConnectionPinError();
        pinError->setError((short)1); // wrong pin
        m_pConnectionStateHandler->receiveCMIControlMessage(pinError);
        std::vector<NodeEvent> sentEvents = m_connectionStateHandlerListener.getSentEvent();
        ASSERT_TRUE(sentEvents.size() == 1);
        ASSERT_EQ(sentEvents[0], NodeEvent::NODE_EVENT_WRONG_PIN);
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ConnectionPinState* sendMessage = new ConnectionPinState();
        sendMessage->setPinState(PinState::PINSTATE_OPTIONAL);
        sendMessage->setInputPermission(PinInputPermission::PININPUTPERMISSION_BUSY);
        m_pConnectionStateHandler->receiveCMIControlMessage(sendMessage);
        sentEvents = m_connectionStateHandlerListener.getSentEvent();
        ASSERT_EQ(1U, sentEvents.size());
    }
    { // got pin error - penalty off
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pNodeInfo->setPinOwnRequirement(PinRequirement::PIN_OPTIONAL);
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ConnectionPinError* pinError = new ConnectionPinError();
        pinError->setError((short)1); // wrong pin
        m_pConnectionStateHandler->receiveCMIControlMessage(pinError);
        std::vector<NodeEvent> sentEvents = m_connectionStateHandlerListener.getSentEvent();
        ASSERT_TRUE(sentEvents.size() == 1);
        ASSERT_EQ(sentEvents[0], NodeEvent::NODE_EVENT_WRONG_PIN);
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ConnectionPinState* sendMessage = new ConnectionPinState();
        sendMessage->setPinState(PinState::PINSTATE_OPTIONAL);
        sendMessage->setInputPermission(PinInputPermission::PININPUTPERMISSION_OK);
        m_pConnectionStateHandler->receiveCMIControlMessage(sendMessage);
        sentEvents = m_connectionStateHandlerListener.getSentEvent();
        ASSERT_TRUE(sentEvents.size() == 2);
        ASSERT_EQ(sentEvents[1], NodeEvent::NODE_EVENT_PIN_INPUT_READY);
    }
    { // got pin state - required
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pNodeInfo->setPinOwnRequirement(PinRequirement::PIN_OPTIONAL);
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ConnectionPinState* sendMessage = new ConnectionPinState();
        sendMessage->setPinState(PinState::PINSTATE_REQUIRED);
        sendMessage->setInputPermission(PinInputPermission::PININPUTPERMISSION_OK);
        m_pConnectionStateHandler->receiveCMIControlMessage(sendMessage);
        std::vector<NodeEvent> sentEvents = m_connectionStateHandlerListener.getSentEvent();
        ASSERT_EQ(1U, sentEvents.size());
        ASSERT_EQ(NodeEvent::NODE_EVENT_PIN_INPUT_READY, sentEvents[0]);
    }
    { // got pin state - optional
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pNodeInfo->setPinOwnRequirement(PinRequirement::PIN_OPTIONAL);
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ConnectionPinState* sendMessage = new ConnectionPinState();
        sendMessage->setPinState(PinState::PINSTATE_OPTIONAL);
        sendMessage->setInputPermission(PinInputPermission::PININPUTPERMISSION_OK);
        m_pConnectionStateHandler->receiveCMIControlMessage(sendMessage);
        std::vector<NodeEvent> sentEvents = m_connectionStateHandlerListener.getSentEvent();
        ASSERT_EQ(1U, sentEvents.size());
        ASSERT_EQ(NodeEvent::NODE_EVENT_PIN_INPUT_READY, sentEvents[0]);
    }
    { // main timeout
        initNodeInfo(true);
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ActionState action = StateHandler::getStateFromPenaltyWaitTimeout(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_PIN_INPUT_READY);
    }
    { // got pinOk
        initNodeInfo(true);
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ConnectionPinState* sendMessage = new ConnectionPinState();
        sendMessage->setPinState(PinState::PINSTATE_PINOK);
        m_pConnectionStateHandler->receiveCMIControlMessage(sendMessage);
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_OK);
        // ASSERT_TRUE(m_pStateInfo->partnerIsPinOk);
    }
    { // pin recall timeout
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ActionState action = StateHandler::getStateFromPinRecallTimeout(m_pStateInfo);
        ASSERT_EQ(action, ActionState::ACTION_PIN_RECALL_TIMEOUT);
        m_pConnectionStateHandler->doAction(action);
        std::vector<NodeEvent> sentEvents = m_connectionStateHandlerListener.getSentEvent();
        ASSERT_TRUE(sentEvents.size() == 1);
        ASSERT_EQ(sentEvents[0], NodeEvent::NODE_EVENT_PIN_RECALL_TIMEOUT);
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
    }
    { // pin input - pin length == 8
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_RESTRICTED_OK);
        m_pNodeInfo->setPin("12345678");
        m_pConnectionStateHandler->doAction(ActionState::ACTION_SEND_PIN_INPUT_AND_START_WAIT_FOR_PIN_TIMER);
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
        ASSERT_EQ(m_pStateInfo->getTimerPinRecall(), m_pConnectionStateHandler->getProtocolConfig().getTimeoutPinRecall());
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
        CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[0];
        ASSERT_EQ(sentClass->getDataType(), ShipDataType::CONNECTION_PIN_INPUT_TYPE);
        ConnectionPinInput* sendMessage = (ConnectionPinInput*)sentClass;
        ASSERT_TRUE(sendMessage->getPinIsSet());
        ASSERT_EQ(sendMessage->getPin().length(), 8U);
    }
    { // pin input - but pin length < 8
        initNodeInfo(true);
        m_connectionStateHandlerListener.clear();
        m_pStateInfo->setPinState(SmeConnectionState::SME_PIN_STATE_ASK_RESTRICTED_OK);
        m_pNodeInfo->setPin("1234567");
        m_pConnectionStateHandler->doAction(ActionState::ACTION_SEND_PIN_INPUT_AND_START_WAIT_FOR_PIN_TIMER);
        ASSERT_EQ(m_pStateInfo->getPinState(), SmeConnectionState::SME_PIN_STATE_ASK_RESTRICTED_OK);
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 0);
    }
}

/**
 * Access Methods
 *
 * @throws UnsupportedEncodingException
 */
TEST_F(ConnectionStateHandlerTest, testInitState_AccessMethods)
{
    { // send access request
        initNodeInfo(true);
        m_pConnectionStateHandler->start();
        m_pStateInfo->setSendAccessMethods(true);
        m_pStateInfo->setPinOk(true);
        m_pStateInfo->setPartnerIsPinOk(true);
        m_pConnectionStateHandler->doAction(ActionState::ACTION_TRY_ENABLE_CONNECTION_DATA_EXCHANGE);
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
        CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[0];
        ASSERT_EQ(sentClass->getDataType(), ShipDataType::ACCESS_METHODS_REQUEST_TYPE);
        m_connectionStateHandlerListener.clear();
    }
    { // got access request
        initNodeInfo(true);
        m_pStateInfo->setState(SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_CONFIRM);
        m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHandshakeWaitForReady());
        AccessMethodsRequest* message = new AccessMethodsRequest();
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
        CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[0];
        ASSERT_EQ(sentClass->getDataType(), ShipDataType::ACCESS_METHODS_TYPE);
        AccessMethods* access = (AccessMethods*)sentClass;
        ASSERT_TRUE(access->getIdIsSet());
        ASSERT_EQ(access->getId(), "ID");
        m_connectionStateHandlerListener.clear();
    }
    { // got access answer
        initNodeInfo(true);
        m_pStateInfo->setState(SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_CONFIRM);
        m_pStateInfo->setTimerMain(m_pConnectionStateHandler->getProtocolConfig().getTimeoutHandshakeWaitForReady());
        AccessMethods* message = new AccessMethods();
        message->setId("OtherId");
        m_pConnectionStateHandler->receiveCMIControlMessage(message);
        // ASSERT_EQ(this.m_pNodeInfo->id, "OtherId");
    }
}

/**
 * Close Connection
 *
 * @throws UnsupportedEncodingException
 */
TEST_F(ConnectionStateHandlerTest, testInitState_CloseConnection)
{
    { // send close connection announce
        initNodeInfo(true);
        ConnectionClose* message = new ConnectionClose();
        message->setPhase(ConnectionClosePhase::CONNECTIONCLOSEPHASE_ANNOUNCE);
        message->setMaxTime(10);
        m_pConnectionStateHandler->receiveEndMessage(message);
        m_pConnectionStateHandler->closeAnnounceConfirm();
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 1);
        CShipDataClass* sentClass = m_connectionStateHandlerListener.getSentClasses()[0];
        ASSERT_EQ(sentClass->getDataType(), ShipDataType::CONNECTION_CLOSE_TYPE);
        ConnectionClose* closeMessage = (ConnectionClose*)sentClass;
        ASSERT_TRUE(closeMessage->getPhaseIsSet());
        ASSERT_EQ(closeMessage->getPhase().getData(), ConnectionClosePhase::CONNECTIONCLOSEPHASE_CONFIRM);
        m_connectionStateHandlerListener.clear();
    }
    { // send close connection confirm
        initNodeInfo(true);
        ConnectionClose* message = new ConnectionClose();
        message->setPhase(ConnectionClosePhase::CONNECTIONCLOSEPHASE_CONFIRM);
        m_pConnectionStateHandler->receiveEndMessage(message);
        ASSERT_TRUE(m_connectionStateHandlerListener.getSentClasses().size() == 0);
    }
}
