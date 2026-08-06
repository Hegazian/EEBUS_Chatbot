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
/**
 *     @file       StateInfo.h
 *     @brief      State information.
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "StateInfo.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */
#define DBG_MODULE_NAME "StateInfo"
/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */
using namespace keo_ship;

StateInfo::StateInfo()
    : m_isInitialized(true)
    , m_isClient(true)
    , m_sendAccessMethods(false)
    , m_partnerIsHelloReady(false)
    , m_acceptProlongationRequest(true)
    , m_isPinOk(false)
    , m_partnerIsPinOk(false)
    , m_numberOfAcceptedProlongationRequests(0)
    , m_error(0)
    , m_state(SmeConnectionState::STATE_UNDEFINED)
    , m_pinState(SmeConnectionState::STATE_UNDEFINED)
    , m_closeState(SmeConnectionState::STATE_UNDEFINED)
    , m_timerMain(0)
    , m_timerSendProlongationRequest(0)
    , m_lastWaitingReceived(0)
    , m_timerProlongationRequestReply(0)
    , m_timerPin(0)
    , m_timerPinRecall(0)
    , m_timerConnectionTimeout(0)
{
}

bool StateInfo::isInitialized()
{
    return m_isInitialized;
}

void StateInfo::setInitialized(bool isInitialized)
{
    m_isInitialized = isInitialized;
}

bool StateInfo::isClient()
{
    return m_isClient;
}

void StateInfo::setClient(bool isClient)
{
    m_isClient = isClient;
}

bool StateInfo::isSendAccessMethods()
{
    return m_sendAccessMethods;
}

void StateInfo::setSendAccessMethods(bool sendAccessMethods)
{
    m_sendAccessMethods = sendAccessMethods;
}

bool StateInfo::isPartnerIsHelloReady()
{
    return m_partnerIsHelloReady;
}

void StateInfo::setPartnerIsHelloReady(bool partnerIsHelloReady)
{
    m_partnerIsHelloReady = partnerIsHelloReady;
}

bool StateInfo::isAcceptProlongationRequest()
{
    return m_acceptProlongationRequest;
}

void StateInfo::setAcceptProlongationRequest(bool acceptProlongationRequest)
{
    m_acceptProlongationRequest = acceptProlongationRequest;
}

bool StateInfo::isPinOk()
{
    return m_isPinOk;
}

void StateInfo::setPinOk(bool isPinOk)
{
    m_isPinOk = isPinOk;
}

bool StateInfo::isPartnerIsPinOk()
{
    return m_partnerIsPinOk;
}

void StateInfo::setPartnerIsPinOk(bool partnerIsPinOk)
{
    m_partnerIsPinOk = partnerIsPinOk;
}

uint8_t StateInfo::getNumberOfAcceptedProlongationRequests()
{
    return m_numberOfAcceptedProlongationRequests;
}

void StateInfo::setNumberOfAcceptedProlongationRequests(uint8_t numberOfAcceptedProlongationRequests)
{
    m_numberOfAcceptedProlongationRequests = numberOfAcceptedProlongationRequests;
}

uint8_t StateInfo::getError()
{
    return m_error;
}

void StateInfo::setError(uint8_t error)
{
    m_error = error;
}

SmeConnectionState StateInfo::getState()
{
    return m_state;
}

void StateInfo::setState(SmeConnectionState state)
{
    m_state = state;
}

SmeConnectionState StateInfo::getPinState()
{
    return m_pinState;
}

void StateInfo::setPinState(SmeConnectionState pinState)
{
    m_pinState = pinState;
}

SmeConnectionState StateInfo::getCloseState()
{
    return m_closeState;
}

void StateInfo::setCloseState(SmeConnectionState closeState)
{
    m_closeState = closeState;
}

uint32_t StateInfo::getTimerMain()
{
    return m_timerMain;
}

void StateInfo::setTimerMain(uint32_t timerMain)
{
    m_timerMain = timerMain;
}

uint32_t StateInfo::getTimerSendProlongationRequest()
{
    return m_timerSendProlongationRequest;
}

void StateInfo::setTimerSendProlongationRequest(uint32_t timerSendProlongationRequest)
{
    m_timerSendProlongationRequest = timerSendProlongationRequest;
}

uint32_t StateInfo::getLastWaitingReceived()
{
    return m_lastWaitingReceived;
}

void StateInfo::setLastWaitingReceived(uint32_t lastWaitingReceived)
{
    m_lastWaitingReceived = lastWaitingReceived;
}

uint32_t StateInfo::getTimerProlongationRequestReply()
{
    return m_timerProlongationRequestReply;
}

void StateInfo::setTimerProlongationRequestReply(uint32_t timerProlongationRequestReply)
{
    m_timerProlongationRequestReply = timerProlongationRequestReply;
}

uint32_t StateInfo::getTimerPin()
{
    return m_timerPin;
}

void StateInfo::setTimerPin(uint32_t timerPin)
{
    m_timerPin = timerPin;
}

uint32_t StateInfo::getTimerPinRecall()
{
    return m_timerPinRecall;
}

void StateInfo::setTimerPinRecall(uint32_t timerPinRecall)
{
    m_timerPinRecall = timerPinRecall;
}

uint32_t StateInfo::getTimerConnectionTimeout()
{
    return m_timerConnectionTimeout;
}

void StateInfo::setTimerConnectionTimeout(uint32_t timerConnectionTimeout)
{
    m_timerConnectionTimeout = timerConnectionTimeout;
}

keo_ship::ConnectionCloseReason StateInfo::getCloseReason()
{
    return m_closeReason;
}

void StateInfo::setCloseReason(keo_ship::ConnectionCloseReason reason)
{
    m_closeReason = reason;
}
