/*
 *     Copyright KEO GmbH 2014 - All rights reserved!
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
#include <assert.h>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <vector>

#include "ConnectionStateHandler.h"
#include "ShipControlTransformer.h"
#include "StateHandler.h"
#include "keo_ship/ShipHeader.h"
#include <keo_util/KELogging.h>

using namespace keo_ship;

static char const* const mapSubstate[] = {
#define MACRO_CMI_STATE(x, y) #x,
#define MACRO_SME_STATE_HELLO(x, y) #x,
#define MACRO_SME_PROT_H_STATE(x, y) #x,
#define MACRO_SME_PIN_STATE(x, y) #x,
#define MACRO_ACCESS_METHODS(x, y) #x,
#define MACRO_STATE_CONNECTION_TERMINATION(x, y) #x,

#include "SmeConnectionState.h"

#undef MACRO_CMI_STATE
#undef MACRO_SME_STATE_HELLO
#undef MACRO_SME_PROT_H_STATE
#undef MACRO_SME_PIN_STATE
#undef MACRO_ACCESS_METHODS
#undef MACRO_STATE_CONNECTION_TERMINATION
};

char const* getSmeSubstateStr(keo_ship::SmeConnectionState state)
{
    keo_ship::SmeConnectionState stateSme = (keo_ship::SmeConnectionState)(state & 0xFF);
    if (stateSme < keo_ship::SME_SUBSTATE_LAST)
    {
        return (mapSubstate[stateSme]);
    }
    return ("undefined");
}

static char const* const mapAction[] = {
#define MACRO_ACTION(x) #x,
#include "ActionState.h"
#undef MACRO_ACTION
};

char const* getActionStr(ActionState action)
{
    if (action < ACTION_LAST)
    {
        return (mapAction[action]);
    }
    return ("undefined");
}

static char const* const mapSmeState[] = {
#define MACRO_STATE_OVERVIEW(x) #x,
#include "SmeConnectionStateOverview.h"
#undef MACRO_STATE_OVERVIEW
};

char const* getSmeStateStr(keo_ship::SmeConnectionState sme_state)
{
    SmeConnectionStateOverview overwiev = (SmeConnectionStateOverview)(sme_state >> SME_STATUS_TYPE_SHIFT);
    // assert((sizeof(mapSmeState) / sizeof(mapSmeState[0])) == keo_ship::SME_STATE_LAST);
    if (overwiev < keo_ship::SME_STATE_OVERVIEW_LAST)
    {
        return (mapSmeState[overwiev]);
    }
    return ("undefined");
}

const char ConnectionStateHandler::CMI_MESSAGE_DATA_VALUE = 0x00;
const uint16_t ConnectionStateHandler::CLOSE_STATUS_CODE = 4400;
const uint8_t ConnectionStateHandler::PIN_NO_PENALTY = 2;
const uint8_t ConnectionStateHandler::PIN_SHORT_PENALTY = 5;
const size_t ConnectionStateHandler::PIN_NEEDED_LENGTH = 8;
const size_t ConnectionStateHandler::COMMISSIONING_TIMER_INTERVAL = 2500;
struct timeval tp;

// Only used for testing
ConnectionStateHandler::ConnectionStateHandler(const std::string& id, const NodeInfo& nodeInfo, bool isClient,
    ConnectionStateHandlerListener* actionModuleListener, const std::string& serverUri)
    : m_nodeInfo(nodeInfo)
    , m_stateInfo()
    , m_actionModuleListener(actionModuleListener)
    , m_id(id)
    , m_timeoutTimer(std::bind(&ConnectionStateHandler::handleTimer, this))
    , m_lastTime(0)
    , m_mtx()
    , m_displayName("")
    , m_serverUri(serverUri)
    , m_protocolConfig()

{
    m_stateInfo.setClient(isClient);
    m_stateInfo.setSendAccessMethods(true);
}

ConnectionStateHandler::ConnectionStateHandler(ConnectionStateHandlerListener* actionModuleListener)
    : m_stateInfo()
    , m_actionModuleListener(actionModuleListener)
    , m_timeoutTimer(std::bind(&ConnectionStateHandler::handleTimer, this))
    , m_lastTime(0)
    , m_mtx()
    , m_displayName()
    , m_serverUri()
    , m_protocolConfig()
{
}

ConnectionStateHandler::~ConnectionStateHandler()
{
    m_stateInfo.setInitialized(true); // ToDo warum true ?
    m_timeoutTimer.stop();
}

void ConnectionStateHandler::setDisplayName(const std::string& displayName)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    m_displayName = displayName;
}

void ConnectionStateHandler::start(
    const std::string& id, const NodeInfo& nodeInfo, bool isClient, const std::string& serverUri)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);

    DEBUG_FUNC() << " " << m_displayName;

    m_nodeInfo = nodeInfo;
    m_id = id;

    m_stateInfo.setClient(isClient);
    m_stateInfo.setSendAccessMethods(true);
    m_serverUri = serverUri;

    startTimer();

    ActionState initState = StateHandler::initState(&m_stateInfo);
    doAction(initState);
    m_stateInfo.setInitialized(true);
}

void ConnectionStateHandler::start()
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    DEBUG_FUNC() << " " << m_displayName;

    startTimer();

    ActionState initState = StateHandler::initState(&m_stateInfo);
    doAction(initState);
    m_stateInfo.setInitialized(true);
}

void ConnectionStateHandler::startTimer()
{
    DEBUG_FUNC() << " " << m_displayName;
    gettimeofday(&tp, NULL);
    m_lastTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    m_timeoutTimer.start(0, COMMISSIONING_TIMER_INTERVAL);
}

void ConnectionStateHandler::stopTimerIfPossible()
{
    DEBUG_FUNC() << " " << m_displayName;
    if (m_stateInfo.getTimerMain() == 0 && m_stateInfo.getTimerSendProlongationRequest() == 0
        && m_stateInfo.getLastWaitingReceived() == 0 && m_stateInfo.getTimerProlongationRequestReply() == 0
        && m_stateInfo.getTimerPin() == 0 && m_stateInfo.getTimerPinRecall() == 0
        && m_stateInfo.getTimerConnectionTimeout() == 0)
    {
        m_timeoutTimer.stop();
    }
    else
    {
        LOG_TRACE() << m_stateInfo.getTimerMain() << " " << m_stateInfo.getTimerSendProlongationRequest() << " "
                    << m_stateInfo.getLastWaitingReceived() << " " << m_stateInfo.getTimerProlongationRequestReply()
                    << " " << m_stateInfo.getTimerPin() << " " << m_stateInfo.getTimerPinRecall() << " "
                    << m_stateInfo.getTimerConnectionTimeout();
    }
}

const NodeInfo& ConnectionStateHandler::getNodeProtocolInfoReference() const
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    return m_nodeInfo;
}

void ConnectionStateHandler::setUserTrust(unsigned short userTrust)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);

    TrustLevel trustLevel = m_nodeInfo.getTrustLevel();
    trustLevel.setUserTrust(userTrust);
    m_nodeInfo.setTrustLevel(trustLevel);
    LOG_INFO() << m_displayName << " Set user trust " << userTrust;

    if (m_stateInfo.getState() == keo_ship::SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN)
    {
        DEBUG_INFO() << m_displayName << " Set state SME_HELLO_STATE_READY_INIT";
        m_stateInfo.setState(keo_ship::SmeConnectionState::SME_HELLO_STATE_READY_INIT);
        m_stateInfo.setTimerMain(m_protocolConfig.getTimeoutHelloWaitForReady());
        doAction(ActionState::ACTION_SEND_HELLO_MESSAGE_AND_START_HELLO_TIMER_IFNEEDED);
    }
    else
    {
        LOG_TRACE() << m_displayName << " no need to send 'Ready'. SME is "
                    << "' in state '" << getSmeStateStr(m_stateInfo.getState()) << "' substate '"
                    << getSmeSubstateStr(m_stateInfo.getState()) << "'";
    }
}

void ConnectionStateHandler::setSecondFactorTrust(unsigned short pinTrustLevel)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    if (pinTrustLevel > 0)
    {
        m_nodeInfo.setPinOwnRequirement(PinRequirement::PIN_OK);
        TrustLevel trustLevel = m_nodeInfo.getTrustLevel();
        trustLevel.setSecondFactorTrust(pinTrustLevel);
        m_nodeInfo.setTrustLevel(trustLevel);
        LOG_INFO() << m_displayName << " Verify pin ok";
        doAction(ActionState::ACTION_VERIFY_PIN_OK);
    }
    else
    {
        LOG_INFO() << m_displayName << " Verify pin failed";
        doAction(ActionState::ACTION_VERIFY_PIN_FAILED);
    }
}

void ConnectionStateHandler::setPin(const std::string& pin)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);

    m_nodeInfo.setPin(pin);
    if (m_stateInfo.getPinState() == keo_ship::SmeConnectionState::SME_PIN_STATE_ASK_PROCESS
        || m_stateInfo.getPinState() == keo_ship::SmeConnectionState::SME_PIN_STATE_ASK_RESTRICTED_OK)
    {
        LOG_INFO() << m_displayName << " Send PIN";
        doAction(ActionState::ACTION_SEND_PIN_INPUT_AND_START_WAIT_FOR_PIN_TIMER);
    }
}

void ConnectionStateHandler::setPinPenaltyTime(long penaltyTime)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    LOG_INFO() << m_displayName << " Send pin penalty timer " << penaltyTime;
    m_stateInfo.setTimerPin(penaltyTime);
}

void ConnectionStateHandler::closeAnnounce(int maxTimeMilliSeconds, keo_ship::ConnectionCloseReason reason)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);

    DEBUG_FUNC() << " " << m_displayName;
    m_stateInfo.setTimerConnectionTimeout(maxTimeMilliSeconds);
    m_stateInfo.setCloseReason(reason);
    doAction(ActionState::ACTION_CLOSE_CONNECTION_ANNOUNCE);
}

void ConnectionStateHandler::closeAnnounceConfirm()
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);

    DEBUG_FUNC() << " " << m_displayName;
    keo_ship::ConnectionClose message;
    message.setPhase(keo_ship::ConnectionClosePhase::CONNECTIONCLOSEPHASE_CONFIRM);
    toShipTransport(ShipMessageType::MESSAGE_TYPE_END, &message);
}

void ConnectionStateHandler::doAction(ActionState action)
{
    if (m_actionModuleListener == NULL)
    {
        return;
    }

    DEBUG_INFO() << m_displayName << " doAction: " << getActionStr(action) << "' in state '"
                 << getSmeStateStr(m_stateInfo.getState()) << "' substate '"
                 << getSmeSubstateStr(m_stateInfo.getState()) << "'";

    switch (action)
    {
        // -----------------------------------------------------------------------------
        // Connection Mode Initialisation (CMI) state
        // -----------------------------------------------------------------------------
        case keo_ship::ACTION_SERVER_START_CMI_TIMER:
        {
            if (m_stateInfo.getState() == keo_ship::SmeConnectionState::CMI_INIT_STATE)
            {
                m_stateInfo.setTimerMain(m_protocolConfig.getTimeoutCmi());
                m_stateInfo.setState(keo_ship::SmeConnectionState::CMI_STATE_SERVER_WAIT);
                return; // ok
            }
            // go to close connection at function end
            break;
        }
        case keo_ship::ACTION_SERVER_SEND_CMI_MESSAGE_AND_GO_HELLO:
        {
            if (m_stateInfo.getState() == keo_ship::SmeConnectionState::CMI_STATE_SERVER_EVALUATE)
            {
                std::vector<char> cmiMessage(2, CMI_MESSAGE_DATA_VALUE);
                if (cmiToShipTransport(cmiMessage))
                {
                    if (m_nodeInfo.getTrustLevel().getUserTrust() /*
                                                                   * todo: is this category OK?
                                                                   */
                        > 0)
                    {
                        m_stateInfo.setState(keo_ship::SmeConnectionState::SME_HELLO_STATE_READY_INIT);
                    }
                    else
                    {
                        m_stateInfo.setState(keo_ship::SmeConnectionState::SME_HELLO_STATE_PENDING_INIT);
                    }
                    m_stateInfo.setTimerMain(m_protocolConfig.getTimeoutHelloWaitForReady());
                    doAction(ActionState::ACTION_SEND_HELLO_MESSAGE_AND_START_HELLO_TIMER_IFNEEDED);
                    return; // ok
                }
            }
            // go to close connection at function end
            break;
        }
        case keo_ship::ACTION_SERVER_SEND_CMI_ERROR_AND_CLOSE_CONNECTION:
        {
            if (m_stateInfo.getState() == keo_ship::SmeConnectionState::CMI_STATE_SERVER_EVALUATE)
            {
                std::vector<char> cmiMessage(2, CMI_MESSAGE_DATA_VALUE);
                cmiToShipTransport(cmiMessage);
            }
            // go to close connection at function end
            break;
        }
        case keo_ship::ACTION_CLIENT_SEND_CMI_MESSAGE_AND_START_CMI_TIMER:
        {
            if (m_stateInfo.getState() == keo_ship::SmeConnectionState::CMI_STATE_CLIENT_SEND)
            {
                std::vector<char> cmiMessage(2, CMI_MESSAGE_DATA_VALUE);
                if (cmiToShipTransport(cmiMessage))
                {
                    m_stateInfo.setTimerMain(m_protocolConfig.getTimeoutCmi());
                    m_stateInfo.setState(keo_ship::SmeConnectionState::CMI_STATE_CLIENT_WAIT);
                    return; // ok
                }
            }
            // go to close connection at function end
            break;
        }
        case keo_ship::ACTION_CLIENT_GO_HELLO:
        {
            if (m_stateInfo.getState() == keo_ship::SmeConnectionState::CMI_STATE_CLIENT_EVALUATE)
            {
                if (m_nodeInfo.getTrustLevel().getUserTrust() /*
                                                               * todo: is this category OK?
                                                               */
                    > 0)
                {
                    m_stateInfo.setState(keo_ship::SmeConnectionState::SME_HELLO_STATE_READY_INIT);
                }
                else
                {
                    m_stateInfo.setState(keo_ship::SmeConnectionState::SME_HELLO_STATE_PENDING_INIT);
                }
                m_stateInfo.setTimerMain(m_protocolConfig.getTimeoutHelloWaitForReady());
                doAction(ActionState::ACTION_SEND_HELLO_MESSAGE_AND_START_HELLO_TIMER_IFNEEDED);
                return; // ok
            }
            // go to close connection at function end
            break;
        }
        // -----------------------------------------------------------------------------
        // Connection state "Hello"
        // -----------------------------------------------------------------------------
        case keo_ship::ACTION_SEND_HELLO_MESSAGE_AND_START_HELLO_TIMER_IFNEEDED:
        {
            // synchronized (this) {
            keo_ship::ConnectionHello hello;
            if (m_nodeInfo.getTrustLevel().getUserTrust() /*
                                                           * todo: is this category OK?
                                                           */
                > 0)
            {
                hello.setPhase(keo_ship::ConnectionHelloPhase::CONNECTIONHELLOPHASE_READY);
            }
            else
            {
                hello.setPhase(keo_ship::ConnectionHelloPhase::CONNECTIONHELLOPHASE_PENDING);
            }
            if (m_stateInfo.getTimerMain() > 0)
            {
                hello.setWaiting(m_stateInfo.getTimerMain());
            }
            if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &hello))
            {
                if (m_stateInfo.isPartnerIsHelloReady())
                { // switch from pending to ready
                    m_stateInfo.setState(keo_ship::SmeConnectionState::SME_HELLO_OK);
                    if (m_stateInfo.isClient())
                    {
                        doAction(ActionState::ACTION_CLIENT_SEND_PROT_H_SELECT_MESSAGE_AND_START_PROT_H_TIMER);
                        return;
                    }
                    doAction(ActionState::ACTION_SERVER_START_PROT_H_TIMER);
                    return;
                }

                if (m_stateInfo.getTimerMain() == 0)
                { // start timer
                    m_stateInfo.setTimerMain(m_protocolConfig.getTimeoutHelloWaitForReady());
                }
                if (m_nodeInfo.getTrustLevel().getUserTrust() /*
                                                               * todo: is this category OK?
                                                               */
                    > 0)
                {
                    m_stateInfo.setState(keo_ship::SmeConnectionState::SME_HELLO_STATE_READY_LISTEN);
                }
                else
                {
                    m_stateInfo.setState(keo_ship::SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
                }
                return; // OK
            }

            doAction(ActionState::ACTION_CLOSE_CONNECTION);
            return;
        }
        case keo_ship::ACTION_SEND_PROLONGATION_MESSAGE_AND_START_PROLONGATION_TIMER:
        {
            keo_ship::ConnectionHello hello;
            hello.setPhase(keo_ship::ConnectionHelloPhase::CONNECTIONHELLOPHASE_PENDING);
            hello.setProlongationRequest(true);
            if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &hello))
            {
                m_stateInfo.setTimerProlongationRequestReply(m_stateInfo.getLastWaitingReceived());
                m_stateInfo.setState(keo_ship::SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN);
                return; // OK
            }

            doAction(ActionState::ACTION_CLOSE_CONNECTION);
            return;
        }
        case keo_ship::ACTION_START_PROLONGATION_TIMER:
        {
            return; // OK
        }
        case keo_ship::ACTION_CHECK_PROLONGATION_REQUEST:
        {
            if (m_stateInfo.isAcceptProlongationRequest()
                && m_stateInfo.getNumberOfAcceptedProlongationRequests()
                    < m_protocolConfig.getMaximumHelloAllowProlongationRequests())
            {
                // accept ProlongationRequest
                m_stateInfo.setTimerMain(m_stateInfo.getTimerMain() + m_protocolConfig.getTimeoutHelloWaitForReady());
                m_stateInfo.setNumberOfAcceptedProlongationRequests(
                    m_stateInfo.getNumberOfAcceptedProlongationRequests() + 1);
            }
            doAction(ActionState::ACTION_SEND_HELLO_MESSAGE_AND_START_HELLO_TIMER_IFNEEDED);
            return;
        }
        case keo_ship::ACTION_SWITCH_TO_READY_STATE:
        {
            if (m_stateInfo.getState() == keo_ship::SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN)
            {
                m_stateInfo.setTimerProlongationRequestReply(0);
                m_stateInfo.setTimerSendProlongationRequest(0);
                doAction(ActionState::ACTION_SEND_HELLO_MESSAGE_AND_START_HELLO_TIMER_IFNEEDED);
                return;
            }
            return; // OK
        }
        case keo_ship::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION:
        {
            keo_ship::ConnectionHello hello;
            m_stateInfo.setTimerMain(0);
            m_stateInfo.setTimerProlongationRequestReply(0);
            m_stateInfo.setTimerSendProlongationRequest(0);
            hello.setPhase(keo_ship::ConnectionHelloPhase::CONNECTIONHELLOPHASE_ABORTED);
            toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &hello);

            doAction(ActionState::ACTION_CLOSE_CONNECTION);
            return;
        }
        // -----------------------------------------------------------------------------
        // Connection state "Protocol handshake"
        // -----------------------------------------------------------------------------
        case keo_ship::ACTION_SERVER_START_PROT_H_TIMER:
        {
            m_stateInfo.setTimerMain(m_protocolConfig.getTimeoutHandshakeWaitForReady());
            m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_PROPOSAL);
            return; // OK
        }
        case keo_ship::ACTION_CLIENT_SEND_PROT_H_SELECT_MESSAGE_AND_START_PROT_H_TIMER:
        {
            keo_ship::MessageProtocolHandshake message;
            message.setHandshakeType(keo_ship::ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_ANNOUNCEMAX);
            message.setVersion(
                keo_ship::ClassVersion(m_protocolConfig.SHIP_VERSION_MAJOR, m_protocolConfig.SHIP_VERSION_MINOR));

            message.setFormats(keo_ship::MessageProtocolFormats(m_protocolConfig.PROTOCOL_FORMATS));
            if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &message))
            {
                m_stateInfo.setTimerMain(m_protocolConfig.getTimeoutHandshakeWaitForReady());
                m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PROT_H_STATE_CLIENT_LISTEN_CHOICE);
                return; // OK
            }

            doAction(ActionState::ACTION_CLOSE_CONNECTION);
            return;
        }
        case keo_ship::ACTION_SEND_PROT_H_ERROR_MESSAGE_AND_CLOSE_CONNECTION:
        {
            keo_ship::MessageProtocolHandshakeError message;
            message.setError(m_stateInfo.getError());
            toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &message);

            doAction(ActionState::ACTION_CLOSE_CONNECTION);
            return;
        }
        // -----------------------------------------------------------------------------
        // Connection state "PIN verification"
        // -----------------------------------------------------------------------------
        case keo_ship::ACTION_SEND_PIN_REQUIREMENTS_INITIAL:
        {
            keo_ship::ConnectionPinState pinState;
            switch (m_nodeInfo.getPinOwnRequirement())
            {
                case PIN_NONE:
                {
                    pinState.setPinState(keo_ship::PinState::PINSTATE_NONE);
                    m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_OK);
                    m_stateInfo.setPinOk(true);
                    break;
                }
                case PIN_OK:
                {
                    pinState.setPinState(keo_ship::PinState::PINSTATE_PINOK);
                    m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_OK);
                    m_stateInfo.setPinOk(true);
                    break;
                }
                case PIN_OPTIONAL:
                {
                    pinState.setPinState(keo_ship::PinState::PINSTATE_OPTIONAL);
                    if (m_stateInfo.getTimerPin() > 0)
                    {
                        pinState.setInputPermission(keo_ship::PinInputPermission::PININPUTPERMISSION_BUSY);
                        m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_BUSY_WAIT);
                    }
                    else
                    {
                        pinState.setInputPermission(keo_ship::PinInputPermission::PININPUTPERMISSION_OK);
                        m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_LISTEN);
                    }
                    m_stateInfo.setPinOk(true);
                    break;
                }
                default:
                { // PIN_REQUIRED
                    pinState.setPinState(keo_ship::PinState::PINSTATE_REQUIRED);
                    if (m_stateInfo.getTimerPin() > 0)
                    {
                        pinState.setInputPermission(keo_ship::PinInputPermission::PININPUTPERMISSION_BUSY);
                        m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_BUSY_WAIT);
                    }
                    else
                    {
                        pinState.setInputPermission(keo_ship::PinInputPermission::PININPUTPERMISSION_OK);
                        m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_LISTEN);
                    }
                }
            }
            m_stateInfo.setPinState(keo_ship::SmeConnectionState::SME_PIN_STATE_ASK_INIT);
            m_stateInfo.setTimerMain(m_protocolConfig.getTimeoutPinAskInit());
            if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &pinState))
            {
                if (m_nodeInfo.getPinOwnRequirement() != keo_ship::PinRequirement::PIN_REQUIRED)
                {
                    doAction(ActionState::ACTION_TRY_ENABLE_CONNECTION_DATA_EXCHANGE);
                    return;
                }
                return; // OK
            }

            doAction(ActionState::ACTION_CLOSE_CONNECTION);
            return;
        }
        case keo_ship::ACTION_SEND_PIN_REQUIREMENTS:
        {
            keo_ship::ConnectionPinState pinState;
            switch (m_nodeInfo.getPinOwnRequirement())
            {
                case PIN_OPTIONAL:
                {
                    pinState.setPinState(keo_ship::PinState::PINSTATE_OPTIONAL);
                    break;
                }
                case PIN_REQUIRED:
                {
                    pinState.setPinState(keo_ship::PinState::PINSTATE_REQUIRED);
                    break;
                }
                default:
                {
                    return; // OK
                }
            }
            if (m_stateInfo.getTimerPin() > 0)
            {
                pinState.setInputPermission(keo_ship::PinInputPermission::PININPUTPERMISSION_BUSY);
            }
            else
            {
                pinState.setInputPermission(keo_ship::PinInputPermission::PININPUTPERMISSION_OK);
            }
            if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &pinState))
            {
                return; // OK
            }

            doAction(ActionState::ACTION_CLOSE_CONNECTION);
            return;
        }
        case keo_ship::ACTION_VERIFY_PIN_OK:
        {
            if (m_stateInfo.getState() == keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_LISTEN)
            {

                m_nodeInfo.setPinOwnRequirement(keo_ship::PinRequirement::PIN_OK);
                m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_OK);
                m_stateInfo.setPinOk(true);
                m_stateInfo.setTimerPin(0);
                keo_ship::ConnectionPinState pinState;
                pinState.setPinState(keo_ship::PinState::PINSTATE_PINOK);
                if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &pinState))
                {
                    doAction(ActionState::ACTION_TRY_ENABLE_CONNECTION_DATA_EXCHANGE);
                    return;
                }

                doAction(ActionState::ACTION_CLOSE_CONNECTION);
                return;
            }
            return; // OK
        }
        case keo_ship::ACTION_VERIFY_PIN_FAILED:
        {
            if (m_stateInfo.getState() == keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_LISTEN)
            {
                m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_ERROR);

                keo_ship::ConnectionPinError pinError;
                pinError.setError(1); // wrong pin
                if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &pinError))
                {
                    if (m_stateInfo.getTimerPin() == 0)
                    {
                        m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_LISTEN);
                        return; // OK
                    }
                    m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PIN_STATE_CHECK_BUSY_WAIT);
                    doAction(ActionState::ACTION_SEND_PIN_REQUIREMENTS);
                    return;
                }

                doAction(ActionState::ACTION_CLOSE_CONNECTION);
                return;
            }
            return; // OK
        }
        case keo_ship::ACTION_PIN_INPUT_READY:
        {
            // send ready for next PIN
            m_actionModuleListener->announceEvent(NodeEvent::NODE_EVENT_PIN_INPUT_READY, "");
            return; // OK
        }
        case keo_ship::ACTION_PIN_RECALL_TIMEOUT:
        {
            // send a timeout that the other device didn't send a pinState message
            m_actionModuleListener->announceEvent(NodeEvent::NODE_EVENT_PIN_RECALL_TIMEOUT, "");
            return; // OK
        }
        case keo_ship::ACTION_SEND_PIN_INPUT_AND_START_WAIT_FOR_PIN_TIMER:
        {
            if (!m_nodeInfo.getPin().empty() && isPinFormatValid(m_nodeInfo.getPin()))
            {
                if (m_stateInfo.getPinState() == keo_ship::SmeConnectionState::SME_PIN_STATE_ASK_RESTRICTED_OK)
                {
                    m_stateInfo.setPinState(keo_ship::SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
                }
                if (m_stateInfo.getPinState() == keo_ship::SmeConnectionState::SME_PIN_STATE_ASK_PROCESS)
                {
                    keo_ship::ConnectionPinInput message;
                    message.setPin(m_nodeInfo.getPin());
                    if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &message))
                    {
                        m_stateInfo.setTimerPinRecall(m_protocolConfig.getTimeoutPinRecall());
                        m_nodeInfo.setPin("");
                        return; // OK
                    }

                    doAction(ActionState::ACTION_CLOSE_CONNECTION);
                    return;
                }
            }
            else
            {
                LOG_WARN() << m_displayName << " Not sending invalid PIN";
            }
            return; // OK
        }
        // -----------------------------------------------------------------------------
        // Some actions which comes up in between
        // -----------------------------------------------------------------------------
        case keo_ship::ACTION_TRY_ENABLE_CONNECTION_DATA_EXCHANGE:
        {
            LOG_TRACE() << m_displayName << " PinOk: " << m_stateInfo.isPinOk()
                        << " PartnerPinOk: " << m_stateInfo.isPartnerIsPinOk();
            if (m_stateInfo.isPinOk() && m_stateInfo.isPartnerIsPinOk())
            {

                DEBUG_INFO() << m_displayName << "':  ----> Enable Data Exchange (announcing event)";
                m_nodeInfo.setEnabledDataExchange(true);
                // The commissioning phase is successful ended here!!
                m_actionModuleListener->announceEvent(NodeEvent::NODE_EVENT_ENABLE_DATA_EXCHANGE, "");
                stopTimerIfPossible();
                if (m_nodeInfo.getId().empty())
                {
                    doAction(ActionState::ACTION_SEND_ACCESS_METHODS_REQUEST);
                }
            }
            return; // OK
        }
        // Close connection
        case keo_ship::ACTION_SEND_ACCESS_METHODS_REQUEST:
        {
            keo_ship::AccessMethodsRequest accessMethodsRequest;
            if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &accessMethodsRequest))
            {
                return; // OK
            }

            doAction(ActionState::ACTION_CLOSE_CONNECTION);
        }
        // fall through
        // no break here!!
        case keo_ship::ACTION_CLOSE_CONNECTION_ANNOUNCE:
        {
            keo_ship::ConnectionClose message;
            message.setPhase(keo_ship::ConnectionClosePhase::CONNECTIONCLOSEPHASE_ANNOUNCE);
            message.setMaxTime(m_stateInfo.getTimerConnectionTimeout());
            message.setReason(m_stateInfo.getCloseReason());
            if (toShipTransport(ShipMessageType::MESSAGE_TYPE_END, &message))
            {
                m_stateInfo.setCloseState(keo_ship::SmeConnectionState::STATE_WAIT_CONFIRM_CLOSE_CONNECTION);
                return; // OK
            }

            doAction(ActionState::ACTION_CLOSE_CONNECTION);
        }
        case keo_ship::ACTION_NONE:
            return; // OK
        // Close connection
        case keo_ship::ACTION_CLOSE_CONNECTION:
        default:
        {
            m_stateInfo.setInitialized(true);
            m_stateInfo.setState(keo_ship::SmeConnectionState::STATE_WAIT_CLOSE_CONNECTION);
            m_actionModuleListener->closeConnection(CLOSE_STATUS_CODE, getSmeSubstateStr(m_stateInfo.getState()));
            return; // Close Connection
        }
    }
    doAction(ActionState::ACTION_CLOSE_CONNECTION);
}

void ConnectionStateHandler::receiveCMIInitMessage(const std::vector<char>& data)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);

    assert(m_stateInfo.isInitialized());

    DEBUG_INFO() << m_displayName << " receiveCMIInitMessage: "
                 << "' in state '" << getSmeStateStr(m_stateInfo.getState()) << "' substate '"
                 << getSmeSubstateStr(m_stateInfo.getState()) << "'";

    if (data.size() == 2 && data[0] == 0 && data[1] == 0)
    {
        // here MessageType == 0 and CmiHead == 0
        if (!m_stateInfo.isClient() && m_stateInfo.getState() == keo_ship::SmeConnectionState::CMI_STATE_SERVER_WAIT)
        {
            m_stateInfo.setState(keo_ship::SmeConnectionState::CMI_STATE_SERVER_EVALUATE);
            m_stateInfo.setTimerMain(0);
            doAction(ActionState::ACTION_SERVER_SEND_CMI_MESSAGE_AND_GO_HELLO);
            return;
        }
        if (m_stateInfo.isClient() && m_stateInfo.getState() == keo_ship::SmeConnectionState::CMI_STATE_CLIENT_WAIT)
        {
            m_stateInfo.setState(keo_ship::SmeConnectionState::CMI_STATE_CLIENT_EVALUATE);
            m_stateInfo.setTimerMain(0);
            doAction(ActionState::ACTION_CLIENT_GO_HELLO);
            return;
        }
    }
    else
    {
        if (!m_stateInfo.isClient() && m_stateInfo.getState() == keo_ship::SmeConnectionState::CMI_STATE_SERVER_WAIT)
        {
            // server send cmi error
            m_stateInfo.setState(keo_ship::SmeConnectionState::CMI_STATE_SERVER_EVALUATE);
            m_stateInfo.setTimerMain(0);
            doAction(ActionState::ACTION_SERVER_SEND_CMI_ERROR_AND_CLOSE_CONNECTION);
            return;
        }
    }
    LOG_WARNING() << m_displayName << " Invalid state - close connection";
    // in all other cases close connection immediately
    doAction(ActionState::ACTION_CLOSE_CONNECTION);
}

void ConnectionStateHandler::receiveCMIControlMessage(keo_ship::CShipDataClass* pDataClass)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);

    if (!pDataClass)
    {
        return;
    }

    DEBUG_INFO() << m_displayName << " receiveCMIControlMessage: "
                 << "' in state '" << getSmeStateStr(m_stateInfo.getState()) << "' substate '"
                 << getSmeSubstateStr(m_stateInfo.getState()) << "'";

    {
        std::vector<char> jsonArray;
        ShipControlTransformer::getJsonFromDataClass(pDataClass, jsonArray, ShipMessageType::MESSAGE_TYPE_CONTROL);
        if (jsonArray.size())
        {
            std::string jsonString(jsonArray.begin() + 1, jsonArray.end());
            LOG_VERBOSE(9) << m_displayName << " CMI message " << jsonString;
        }
    }
    if (pDataClass->getDataType() == keo_ship::ShipDataType::ACCESS_METHODS_REQUEST_TYPE)
    {
        LOG_TRACE() << m_displayName << " ACCESS_METHODS_REQUEST_TYPE";
        keo_ship::AccessMethods accessMethods;
        accessMethods.setId(m_id);
        // TODO define API to set mdns support and Uri
        // accessMethods.setDnsSd_mDns() and accessMethods.setDns(m_serverUri)
        toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &accessMethods);

        return; // OK
    }
    if (pDataClass->getDataType() == keo_ship::ShipDataType::ACCESS_METHODS_TYPE)
    {
        LOG_TRACE() << m_displayName << " ACCESS_METHODS_TYPE";
        keo_ship::AccessMethods* access = static_cast<keo_ship::AccessMethods*>(pDataClass);
        if (access->getIdIsSet())
        {

            m_nodeInfo.setId(access->getId());
            m_actionModuleListener->announceEvent(keo_ship::NodeEvent::NODE_EVENT_RECEIVED_ID, "");
            return;
        }
        return; // OK
    }

    switch (m_stateInfo.getPinState())
    {
        // -----------------------------------------------------------------------------
        // Connection state "Pin"
        // -----------------------------------------------------------------------------
        case SME_PIN_STATE_ASK_INIT:
            LOG_TRACE() << m_displayName << " SME_PIN_STATE_ASK_INIT";
            if (pDataClass->getDataType() == keo_ship::ShipDataType::CONNECTION_PIN_STATE_TYPE)
            {
                m_stateInfo.setTimerMain(0);
            }
            m_stateInfo.setPinState(keo_ship::SmeConnectionState::SME_PIN_STATE_ASK_PROCESS);
            // go further to SME_PIN_STATE_ASK_PROCESS
            // fallthrough

        case SME_PIN_STATE_ASK_PROCESS:
            LOG_TRACE() << m_displayName << " SME_PIN_STATE_ASK_PROCESS";
            if (pDataClass)
            {
                if (pDataClass->getDataType() == keo_ship::ShipDataType::CONNECTION_PIN_STATE_TYPE)
                {
                    keo_ship::ConnectionPinState* message = static_cast<keo_ship::ConnectionPinState*>(pDataClass);
                    if (message->getPinStateIsSet())
                    {
                        PinState pinState = message->getPinState();
                        m_nodeInfo.setPinRequirement(static_cast<PinRequirement>(pinState.getData()));
                        if (pinState.getData() != keo_ship::PinState::PINSTATE_OPTIONAL)
                        { // TODO checkThis
                            if (!m_nodeInfo.isNeedUnrestrictedAccess())
                            {
                                m_stateInfo.setPinState(keo_ship::SmeConnectionState::SME_PIN_STATE_ASK_RESTRICTED_OK);
                                doAction(ActionState::ACTION_TRY_ENABLE_CONNECTION_DATA_EXCHANGE);
                                return;
                            }
                        }
                        if (pinState.getData() != keo_ship::PinState::PINSTATE_REQUIRED)
                        {
                            if (pinState.getData() == keo_ship::PinState::PINSTATE_NONE
                                || pinState.getData() == keo_ship::PinState::PINSTATE_PINOK)
                            {
                                m_stateInfo.setPinState(keo_ship::SmeConnectionState::SME_PIN_STATE_ASK_OK);
                                m_stateInfo.setPartnerIsPinOk(true);
                                // no trust level is set here, only by CHECK
                            }
                            doAction(ActionState::ACTION_TRY_ENABLE_CONNECTION_DATA_EXCHANGE);
                        }
                        if (message->getInputPermissionIsSet())
                        {
                            if (message->getInputPermission().getData()
                                == keo_ship::PinInputPermission::PININPUTPERMISSION_BUSY)
                            {
                                return; // OK
                            }
                            if (message->getInputPermission().getData()
                                == keo_ship::PinInputPermission::PININPUTPERMISSION_OK)
                            {
                                if (!m_nodeInfo.getPin().empty())
                                {
                                    doAction(ActionState::ACTION_SEND_PIN_INPUT_AND_START_WAIT_FOR_PIN_TIMER);
                                    return;
                                }
                                doAction(ActionState::ACTION_PIN_INPUT_READY);
                                return;
                            }
                        }
                        return; // OK;
                    }
                }
                if (pDataClass->getDataType() == keo_ship::ShipDataType::CONNECTION_PIN_ERROR_TYPE)
                {
                    keo_ship::ConnectionPinError* message = static_cast<keo_ship::ConnectionPinError*>(pDataClass);
                    if (message->getErrorIsSet() && message->getError() == 1)
                    {
                        // send pin error, wait for ok
                        m_actionModuleListener->announceEvent(NodeEvent::NODE_EVENT_WRONG_PIN, "");
                        return; // OK;
                    }
                }
            }
            // maybe close connection, but for the beginning its a hard move
            break; // OK;

        case SME_PIN_STATE_ASK_OK:
        case SME_PIN_STATE_ASK_RESTRICTED_OK:
            LOG_TRACE() << m_displayName << " SME_PIN_STATE_ASK_(RESTRICTED)_OK";
            if (pDataClass->getDataType() == keo_ship::ShipDataType::CONNECTION_PIN_ERROR_TYPE)
            {
                return; // OK
            }
            break;

        default:
            break;
    }

    switch (m_stateInfo.getState())
    {
        // -----------------------------------------------------------------------------
        // Connection state "Hello"
        // -----------------------------------------------------------------------------
        case SME_HELLO_STATE_READY_LISTEN:
        {
            if (pDataClass && pDataClass->getDataType() == keo_ship::ShipDataType::CONNECTION_HELLO_TYPE)
            {
                keo_ship::ConnectionHello* hello = static_cast<keo_ship::ConnectionHello*>(pDataClass);
                if (hello->getPhaseIsSet())
                {
                    if (hello->getPhase().getData() == keo_ship::ConnectionHelloPhase::CONNECTIONHELLOPHASE_READY)
                    {
                        m_stateInfo.setTimerMain(0);
                        m_stateInfo.setState(keo_ship::SmeConnectionState::SME_HELLO_OK);
                        m_stateInfo.setPartnerIsHelloReady(true);
                        if (m_stateInfo.isClient())
                        {
                            doAction(ActionState::ACTION_CLIENT_SEND_PROT_H_SELECT_MESSAGE_AND_START_PROT_H_TIMER);
                            return;
                        }
                        doAction(ActionState::ACTION_SERVER_START_PROT_H_TIMER);
                        return;
                    }
                    else if (hello->getPhase().getData()
                        == keo_ship::ConnectionHelloPhase::CONNECTIONHELLOPHASE_PENDING)
                    {
                        if (!hello->getProlongationRequestIsSet())
                        { // FIXME dubious null vs. boolean value distinction
                            return; // OK
                        }
                        else if (hello->getProlongationRequest())
                        {
                            doAction(ActionState::ACTION_CHECK_PROLONGATION_REQUEST);
                            return;
                        }
                        else
                        { // == false is not specified in spec
                            return; // OK
                        }
                    }
                }
            }
            doAction(ActionState::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION);
            return;
        }
        case SME_HELLO_STATE_PENDING_LISTEN:
        {
            if (pDataClass && pDataClass->getDataType() == keo_ship::ShipDataType::CONNECTION_HELLO_TYPE)
            {
                keo_ship::ConnectionHello* hello = static_cast<keo_ship::ConnectionHello*>(pDataClass);
                if (hello->getPhaseIsSet())
                {
                    if (hello->getPhase().getData() == keo_ship::ConnectionHelloPhase::CONNECTIONHELLOPHASE_READY)
                    {
                        if (hello->getWaitingIsSet())
                        {
                            m_stateInfo.setTimerMain(0);
                            m_stateInfo.setTimerProlongationRequestReply(0);
                            m_stateInfo.setLastWaitingReceived(hello->getWaiting());
                            if (hello->getWaiting() >= m_protocolConfig.getMinimumHelloWaitForReadyForProlongation())
                            {
                                m_stateInfo.setTimerSendProlongationRequest(hello->getWaiting()
                                    - (m_protocolConfig.getMinimumHelloWaitForReadyForProlongation() >> 1));
                            }
                            else
                            {
                                m_stateInfo.setTimerSendProlongationRequest(0);
                            }
                            m_stateInfo.setPartnerIsHelloReady(true);
                            return; // OK
                        }
                    }
                    else if (hello->getPhase().getData()
                        == keo_ship::ConnectionHelloPhase::CONNECTIONHELLOPHASE_PENDING)
                    {
                        if (hello->getWaitingIsSet())
                        {
                            if (!hello->getProlongationRequestIsSet())
                            {
                                m_stateInfo.setTimerProlongationRequestReply(0);
                                m_stateInfo.setLastWaitingReceived(hello->getWaiting());
                                if (hello->getWaiting()
                                    >= m_protocolConfig.getMinimumHelloWaitForReadyForProlongation())
                                {
                                    m_stateInfo.setTimerSendProlongationRequest(hello->getWaiting()
                                        - (m_protocolConfig.getMinimumHelloWaitForReadyForProlongation() >> 1));
                                }
                                else
                                {
                                    m_stateInfo.setTimerSendProlongationRequest(0);
                                }
                                return; // OK
                            }
                        }
                        else if (hello->getProlongationRequestIsSet() && hello->getProlongationRequest())
                        { // == false is not specified in spec
                            doAction(ActionState::ACTION_CHECK_PROLONGATION_REQUEST);
                            return;
                        }
                    }
                }
            }
            doAction(ActionState::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION);
            return;
        }
        case SME_PROT_H_STATE_CLIENT_LISTEN_CHOICE:
        {
            m_stateInfo.setTimerMain(0);
            if (pDataClass && pDataClass->getDataType() == keo_ship::ShipDataType::MESSAGE_PROTOCOL_HANDSHAKE_TYPE)
            {
                keo_ship::MessageProtocolHandshake* message
                    = static_cast<keo_ship::MessageProtocolHandshake*>(pDataClass);
                if (message->getHandshakeType().getData()
                    == keo_ship::ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_SELECT)
                {
                    keo_ship::ClassVersion version = message->getVersion();
                    if (message->getVersionIsSet() && version.getMajorIsSet() && version.getMinorIsSet())
                    {
                        if (m_protocolConfig.isVersionValid(version.getMajor(), version.getMinor()))
                        {
                            if (message->getFormatsIsSet())
                            {
                                uint16_t shipVersionMajor = version.getMajor();
                                uint16_t shipVersionMinor = version.getMinor();
                                std::vector<std::string> formatStringList = message->getFormats().getFormat();
                                if (!formatStringList.empty())
                                {
                                    if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, message))
                                    {
                                        m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PROT_H_STATE_CLIENT_OK);

                                        m_nodeInfo.setShipVersionMajor(shipVersionMajor);
                                        m_nodeInfo.setShipVersionMinor(shipVersionMinor);
                                        m_nodeInfo.setShipFormat(formatStringList[0]);
                                        doAction(ActionState::ACTION_SEND_PIN_REQUIREMENTS_INITIAL);
                                        return;
                                    }

                                    doAction(ActionState::ACTION_CLOSE_CONNECTION);
                                    return;
                                }
                            }
                        }
                    }
                }
                m_stateInfo.setError(3);
                doAction(ActionState::ACTION_SEND_PROT_H_ERROR_MESSAGE_AND_CLOSE_CONNECTION);
                return;
            }
            m_stateInfo.setError(2);
            doAction(ActionState::ACTION_SEND_PROT_H_ERROR_MESSAGE_AND_CLOSE_CONNECTION);
            return;
        }
        case SME_PROT_H_STATE_SERVER_LISTEN_PROPOSAL:
        {
            m_stateInfo.setTimerMain(0);
            if (pDataClass && pDataClass->getDataType() == keo_ship::ShipDataType::MESSAGE_PROTOCOL_HANDSHAKE_TYPE)
            {
                keo_ship::MessageProtocolHandshake* messageIn
                    = static_cast<keo_ship::MessageProtocolHandshake*>(pDataClass);
                if (messageIn->getHandshakeType().getData()
                    == keo_ship::ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_ANNOUNCEMAX)
                {
                    keo_ship::ClassVersion version = messageIn->getVersion();
                    if (messageIn->getVersionIsSet() && version.getMajorIsSet() && version.getMinorIsSet())
                    {
                        keo_ship::MessageProtocolHandshake messageOut;
                        uint16_t major = version.getMajor();
                        uint16_t minor = version.getMinor();
                        if (m_protocolConfig.agreedVersion(major, minor))
                        {
                            if (messageIn->getFormatsIsSet())
                            {
                                std::vector<std::string>::iterator itSelect = m_protocolConfig.PROTOCOL_FORMATS.begin();
                                std::vector<std::string> formatStringList = messageIn->getFormats().getFormat();
                                std::vector<std::string>::iterator itSearch = formatStringList.begin();
                                std::vector<std::string> selectedElementList;
                                std::string elementSelect;
                                while (
                                    selectedElementList.empty() && itSelect != m_protocolConfig.PROTOCOL_FORMATS.end())
                                {
                                    while (itSearch != formatStringList.end())
                                    {
                                        if (itSelect->compare(*itSearch) == 0)
                                        {
                                            selectedElementList.push_back(*itSelect);
                                            break;
                                        }
                                    }
                                }
                                if (!selectedElementList.empty())
                                {
                                    messageOut.setHandshakeType(
                                        keo_ship::ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_SELECT);
                                    keo_ship::MessageProtocolFormats messageProtocolFormats(selectedElementList);
                                    messageOut.setFormats(messageProtocolFormats);
                                    messageOut.setVersion(keo_ship::ClassVersion(major, minor));
                                    if (toShipTransport(ShipMessageType::MESSAGE_TYPE_CONTROL, &messageOut))
                                    {

                                        m_nodeInfo.setShipVersionMajor(major);
                                        m_nodeInfo.setShipVersionMinor(minor);
                                        m_nodeInfo.setShipFormat(selectedElementList[0]);
                                        m_stateInfo.setState(
                                            keo_ship::SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_CONFIRM);
                                        m_stateInfo.setTimerMain(m_protocolConfig.getTimeoutHandshakeWaitForReady());
                                        return; // OK
                                    }
                                    doAction(ActionState::ACTION_CLOSE_CONNECTION);
                                    return;
                                }
                            }
                        }
                    }
                }
            }

            m_stateInfo.setError(2);
            doAction(ActionState::ACTION_SEND_PROT_H_ERROR_MESSAGE_AND_CLOSE_CONNECTION);
            return;
        }
        case SME_PROT_H_STATE_SERVER_LISTEN_CONFIRM:
        {
            m_stateInfo.setTimerMain(0);
            if (pDataClass && pDataClass->getDataType() == keo_ship::ShipDataType::MESSAGE_PROTOCOL_HANDSHAKE_TYPE)
            {
                keo_ship::MessageProtocolHandshake* message
                    = static_cast<keo_ship::MessageProtocolHandshake*>(pDataClass);
                if (message->getHandshakeType().getData()
                    == keo_ship::ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_SELECT)
                {
                    keo_ship::ClassVersion version = message->getVersion();
                    if (message->getVersionIsSet() && version.getMajorIsSet() && version.getMinorIsSet())
                    {
                        if (version.getMajor() == m_nodeInfo.getShipVersionMajor()
                            && version.getMinor() == m_nodeInfo.getShipVersionMinor())
                        {
                            if (message->getFormatsIsSet())
                            {
                                std::vector<std::string> formatList = message->getFormats().getFormat();
                                if (!formatList.empty() && m_nodeInfo.getShipFormat().compare(formatList[0]) == 0)
                                {
                                    m_stateInfo.setState(keo_ship::SmeConnectionState::SME_PROT_H_STATE_SERVER_OK);
                                    doAction(ActionState::ACTION_SEND_PIN_REQUIREMENTS_INITIAL);
                                    return;
                                }
                            }
                        }
                    }
                }

                m_stateInfo.setError(3);
                doAction(ActionState::ACTION_SEND_PROT_H_ERROR_MESSAGE_AND_CLOSE_CONNECTION);
                return;
            }

            m_stateInfo.setError(2);
            doAction(ActionState::ACTION_SEND_PROT_H_ERROR_MESSAGE_AND_CLOSE_CONNECTION);
            return;
        }
        case SME_PIN_STATE_CHECK_LISTEN:
        {
            if (pDataClass && pDataClass->getDataType() == keo_ship::ShipDataType::CONNECTION_PIN_INPUT_TYPE)
            {
                keo_ship::ConnectionPinInput* message = static_cast<keo_ship::ConnectionPinInput*>(pDataClass);
                if (message->getPinIsSet())
                {
                    m_actionModuleListener->announceEvent(NodeEvent::NODE_EVENT_PIN_RECEIVED, message->getPin());
                }
            }
            return; // OK
        }
        case SME_PIN_STATE_CHECK_BUSY_WAIT:
            if (pDataClass && pDataClass->getDataType() == keo_ship::ShipDataType::CONNECTION_PIN_INPUT_TYPE)
            {
                doAction(ActionState::ACTION_SEND_PIN_REQUIREMENTS);
                return;
            }
            return; // OK

        case SME_PIN_STATE_CHECK_OK:
            return; // OK

        default:
            break;
    }
    LOG_WARN() << m_displayName << " receiveCMIControlMessage: no case found ";
    doAction(ActionState::ACTION_CLOSE_CONNECTION);
    return;
}

void ConnectionStateHandler::receiveEndMessage(keo_ship::CShipDataClass* pDataClass)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);

    DEBUG_INFO() << m_displayName << " receive end message ";

    {
        std::vector<char> jsonArray;
        ShipControlTransformer::getJsonFromDataClass(pDataClass, jsonArray, ShipMessageType::MESSAGE_TYPE_END);
        if (jsonArray.size())
        {
            std::string jsonString(jsonArray.begin() + 1, jsonArray.end());
            LOG_VERBOSE(9) << m_displayName << " end message " << jsonString;
        }
    }
    switch (m_stateInfo.getCloseState())
    {
        // -----------------------------------------------------------------------------
        // Close connection
        // -----------------------------------------------------------------------------
        case STATE_WAIT_CONFIRM_CLOSE_CONNECTION:
            if (pDataClass && pDataClass->getDataType() == keo_ship::ShipDataType::CONNECTION_CLOSE_TYPE)
            {
                keo_ship::ConnectionClose* closeMsg = static_cast<keo_ship::ConnectionClose*>(pDataClass);
                if (closeMsg->getPhaseIsSet()
                    && closeMsg->getPhase().getData() == keo_ship::ConnectionClosePhase::CONNECTIONCLOSEPHASE_CONFIRM)
                {
                    m_stateInfo.setTimerConnectionTimeout(0);
                }
                m_actionModuleListener->announceEvent(NodeEvent::NODE_EVENT_CLOSE_ANNOUNCE_CONFIRM, "");
                doAction(ActionState::ACTION_CLOSE_CONNECTION);
                return;
            }
        default:
            break;
    }
    if (pDataClass && pDataClass->getDataType() == keo_ship::ShipDataType::CONNECTION_CLOSE_TYPE)
    {
        keo_ship::ConnectionClose* closeMessage = static_cast<keo_ship::ConnectionClose*>(pDataClass);
        if (closeMessage->getPhaseIsSet())
        {
            if (closeMessage->getPhase().getData() == keo_ship::ConnectionClosePhase::CONNECTIONCLOSEPHASE_ANNOUNCE)
            {
                std::string data;
                if (closeMessage->getMaxTimeIsSet())
                {
                    data = std::to_string(closeMessage->getMaxTime());
                }
                else
                {
                    data = "0";
                }
                if (closeMessage->getReasonIsSet())
                {
                    data += " " + closeMessage->getReason().getDataString();
                }
                m_actionModuleListener->announceEvent(NodeEvent::NODE_EVENT_CLOSE_ANNOUNCE, data);
                return;
            }
            else if (closeMessage->getPhase().getData() == keo_ship::ConnectionClosePhase::CONNECTIONCLOSEPHASE_CONFIRM)
            {
                m_actionModuleListener->announceEvent(NodeEvent::NODE_EVENT_CLOSE_ANNOUNCE_CONFIRM, "");
                doAction(ActionState::ACTION_CLOSE_CONNECTION);
                return;
            }
        }
        doAction(ActionState::ACTION_CLOSE_CONNECTION);
        return;
    }
}

bool ConnectionStateHandler::cmiToShipTransport(const std::vector<char>& cmiMessage)
{
    if (!m_actionModuleListener)
    {
        return false;
    }
    LOG_TRACE() << m_displayName << " to Ship Tansport CMI " << cmiMessage.size();

    return m_actionModuleListener->sendToShipTransport(cmiMessage);
}

bool ConnectionStateHandler::toShipTransport(ShipMessageType cmiState, keo_ship::CShipDataClass* pDataClass)
{
    if (!m_actionModuleListener)
    {
        return false;
    }

    std::vector<char> jsonArray;
    ShipControlTransformer::getJsonFromDataClass(pDataClass, jsonArray, cmiState);

    {
        if (jsonArray.size())
        {
            std::string jsonString(jsonArray.begin() + 1, jsonArray.end());
            LOG_VERBOSE(9) << m_displayName << " to Ship Transport " << cmiState << jsonString;
        }
        else
        {
            LOG_VERBOSE(9) << m_displayName << " to Ship Transport " << cmiState << "[empty]";
        }
    }

    return m_actionModuleListener->sendToShipTransport(jsonArray);
}

uint32_t ConnectionStateHandler::timerElapsedAfterUpdate(uint32_t timer, uint32_t elapsedTicks)
{
    if (timer <= elapsedTicks)
    {
        // timeout
        return 0;
    }

    return timer - elapsedTicks;
}

void ConnectionStateHandler::handleTimer()
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);

    gettimeofday(&tp, NULL);
    long int currentTime = tp.tv_sec * 1000 + tp.tv_usec / 1000; // current time
    long int elapsedTicks = currentTime - m_lastTime;
    m_lastTime = currentTime;
    if (elapsedTicks < 0)
    {
        LOG_WARNING() << m_displayName << " Timeout error!";
        return;
    }
    if (!m_nodeInfo.isEnabledDataExchange() && m_stateInfo.getTimerMain() > 0)
    {
        // do commissioning
        m_stateInfo.setTimerMain(timerElapsedAfterUpdate(m_stateInfo.getTimerMain(), elapsedTicks));
        if (m_stateInfo.getTimerMain() == 0)
        {
            LOG_WARNING() << m_displayName << "Main timer timeout " << getSmeSubstateStr(m_stateInfo.getState());
            doAction(StateHandler::getStateFromTimeout(&m_stateInfo));
        }
        if (m_stateInfo.getTimerSendProlongationRequest() > 0)
        {
            m_stateInfo.setTimerSendProlongationRequest(
                timerElapsedAfterUpdate(m_stateInfo.getTimerSendProlongationRequest(), elapsedTicks));
            if (m_stateInfo.getTimerSendProlongationRequest() == 0)
            {
                LOG_WARNING() << m_displayName << "SendProlongationRequest timer timeout "
                              << getSmeSubstateStr(m_stateInfo.getState());
                doAction(StateHandler::getStateFromSendProlongationRequestTimeout(&m_stateInfo));
            }
        }
        if (m_stateInfo.getTimerProlongationRequestReply() > 0)
        {
            m_stateInfo.setTimerProlongationRequestReply(
                timerElapsedAfterUpdate(m_stateInfo.getTimerProlongationRequestReply(), elapsedTicks));
            if (m_stateInfo.getTimerProlongationRequestReply() == 0)
            {
                LOG_WARNING() << m_displayName << "ProlongationRequestReply timer timeout "
                              << getSmeSubstateStr(m_stateInfo.getState());
                doAction(StateHandler::getStateFromTimeout(&m_stateInfo));
            }
        }
    }
    if (m_stateInfo.getTimerPin() > 0)
    {
        m_stateInfo.setTimerPin(timerElapsedAfterUpdate(m_stateInfo.getTimerPin(), elapsedTicks));
        if (m_stateInfo.getTimerPin() == 0)
        {
            LOG_WARNING() << m_displayName << "Pin Timer timeout "
                          << getSmeSubstateStr(m_stateInfo.getPinState()); // warn
            doAction(StateHandler::getStateFromPinTimeout(&m_stateInfo));
        }
    }
    if (m_stateInfo.getTimerPinRecall() > 0)
    {
        m_stateInfo.setTimerPinRecall(timerElapsedAfterUpdate(m_stateInfo.getTimerPinRecall(), elapsedTicks));
        if (m_stateInfo.getTimerPinRecall() == 0)
        {
            LOG_WARNING() << m_displayName << "PinRecall timer timeout "
                          << getSmeSubstateStr(m_stateInfo.getPinState()); // warn
            doAction(StateHandler::getStateFromPinRecallTimeout(&m_stateInfo));
        }
    }
}

bool ConnectionStateHandler::isPinFormatValid(const std::string& pin)
{
    if (pin.length() >= 8 && pin.length() <= 16)
    {
        for (size_t i = 0; i < pin.length(); i++)
        {
            if (!isxdigit(pin[i]))
                return false;
        }
        return true;
    }
    return false;
}

void ConnectionStateHandler::setProtocolConfig(const ProtocolConfig& protocolConfig)
{
    this->m_protocolConfig = protocolConfig;
}

const ProtocolConfig ConnectionStateHandler::getProtocolConfig()
{
    return m_protocolConfig;
}
