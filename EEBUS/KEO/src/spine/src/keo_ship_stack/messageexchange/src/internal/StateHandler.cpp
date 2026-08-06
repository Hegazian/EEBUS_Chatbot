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
 *     @file       StateHandler.h
 *     @brief      Get actions for some basic states.
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#include "StateHandler.h"
#include "StateInfo.h"
#include <keo_util/KELogging.h>

using namespace keo_ship;

StateHandler::StateHandler()
{
}

ActionState StateHandler::initState(StateInfo* pStateInfo)
{
    DEBUG_FUNC();
    if (pStateInfo->isClient())
    {
        pStateInfo->setState(SmeConnectionState::CMI_STATE_CLIENT_SEND);
        return ActionState::ACTION_CLIENT_SEND_CMI_MESSAGE_AND_START_CMI_TIMER;
    }
    else
    {
        pStateInfo->setState(SmeConnectionState::CMI_INIT_STATE);
        return ActionState::ACTION_SERVER_START_CMI_TIMER;
    }
}
SmeConnectionStateOverview getStateOverview(SmeConnectionState state)
{
    return (SmeConnectionStateOverview)(state >> SME_STATUS_TYPE_SHIFT);
}
ActionState StateHandler::getStateFromTimeout(StateInfo* pStateInfo)
{
    DEBUG_FUNC();
    SmeConnectionStateOverview stateStep = getStateOverview(pStateInfo->getState());
    switch (stateStep)
    {
        case STATE_OVERVIEW_CONNECTION_STATE_HELLO:
            return getStateFromTimeoutConnectionStateHello(pStateInfo);
        case STATE_OVERVIEW_CONNECTION_STATE_PROTOCOL_HANDSHAKE:
            return getStateFromMainTimeoutConnectionStateProtocolHandshake(pStateInfo);
        case STATE_OVERVIEW_CONNECTION_PIN_VERIFICATION:
            return getStateFromMainTimeoutConnectionPINVerification(pStateInfo);
        default:
            pStateInfo->setState(SmeConnectionState::STATE_WAIT_CLOSE_CONNECTION);
            return ActionState::ACTION_CLOSE_CONNECTION;
    }
}
ActionState StateHandler::getStateFromSendProlongationRequestTimeout(StateInfo* pStateInfo)
{
    DEBUG_FUNC();
    if (pStateInfo->getState() == SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN)
    {
        pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_PENDING_TIMEOUT);
        return ActionState::ACTION_SEND_PROLONGATION_MESSAGE_AND_START_PROLONGATION_TIMER;
    }
    // other states are not valid, so close connection
    pStateInfo->setState(SmeConnectionState::STATE_WAIT_CLOSE_CONNECTION);
    return ActionState::ACTION_CLOSE_CONNECTION;
}
ActionState StateHandler::getStateFromPinTimeout(StateInfo* pStateInfo)
{
    DEBUG_FUNC();
    if (pStateInfo->getState() == SmeConnectionState::SME_PIN_STATE_CHECK_BUSY_WAIT)
    {
        pStateInfo->setState(SmeConnectionState::SME_PIN_STATE_CHECK_LISTEN);
        return ActionState::ACTION_SEND_PIN_REQUIREMENTS;
    }
    return ActionState::ACTION_NONE;
}
ActionState StateHandler::getStateFromPenaltyWaitTimeout(StateInfo* pStateInfo)
{
    DEBUG_FUNC();
    if (pStateInfo->getPinState() == SmeConnectionState::SME_PIN_STATE_ASK_PROCESS)
    {
        return ActionState::ACTION_PIN_INPUT_READY;
    }
    return ActionState::ACTION_NONE;
}
ActionState StateHandler::getStateFromPinRecallTimeout(StateInfo* pStateInfo)
{
    DEBUG_FUNC();
    if (pStateInfo->getPinState() == SmeConnectionState::SME_PIN_STATE_ASK_PROCESS)
    {
        return ActionState::ACTION_PIN_RECALL_TIMEOUT;
    }
    return ActionState::ACTION_NONE;
}

ActionState StateHandler::getStateFromConnectionTimeout(StateInfo* pStateInfo)
{
    if (pStateInfo->getCloseState() == SmeConnectionState::STATE_WAIT_CONFIRM_CLOSE_CONNECTION)
    {
        return ActionState::ACTION_CLOSE_CONNECTION;
    }
    return ActionState::ACTION_NONE;
    /*    (void) pStateInfo;
    //    if(pStateInfo->closeState == STATE_WAIT_CONFIRM_CLOSE_CONNECTION) {
    //        return ACTION_CloseConnection;
    //    }
        return ACTION_None; */
}

ActionState StateHandler::getStateFromTimeoutConnectionStateHello(StateInfo* pStateInfo)
{
    DEBUG_FUNC();
    if (pStateInfo->getState() == SmeConnectionState::SME_HELLO_STATE_READY_LISTEN)
    {
        pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_READY_TIMEOUT);
        return ActionState::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION;
    }
    if (pStateInfo->getState() == SmeConnectionState::SME_HELLO_STATE_PENDING_LISTEN)
    {
        pStateInfo->setState(SmeConnectionState::SME_HELLO_STATE_PENDING_TIMEOUT);
        return ActionState::ACTION_SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION;
    }
    // other states are not valid, so close connection
    pStateInfo->setState(SmeConnectionState::STATE_WAIT_CLOSE_CONNECTION);
    return ActionState::ACTION_CLOSE_CONNECTION;
}

ActionState StateHandler::getStateFromMainTimeoutConnectionStateProtocolHandshake(StateInfo* pStateInfo)
{
    DEBUG_FUNC();
    if (pStateInfo->getState() == SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_PROPOSAL
        || pStateInfo->getState() == SmeConnectionState::SME_PROT_H_STATE_SERVER_LISTEN_CONFIRM
        || pStateInfo->getState() == SmeConnectionState::SME_PROT_H_STATE_CLIENT_LISTEN_CHOICE)
    {
        pStateInfo->setState(SmeConnectionState::SME_PROT_H_STATE_TIMEOUT);
        pStateInfo->setError(1);
        return ActionState::ACTION_SEND_PROT_H_ERROR_MESSAGE_AND_CLOSE_CONNECTION;
    }
    // other states are not valid, so close connection
    pStateInfo->setState(SmeConnectionState::STATE_WAIT_CLOSE_CONNECTION);
    return ActionState::ACTION_CLOSE_CONNECTION;
}

ActionState StateHandler::getStateFromMainTimeoutConnectionPINVerification(StateInfo* pStateInfo)
{
    DEBUG_FUNC();
    pStateInfo->setState(SmeConnectionState::STATE_WAIT_CLOSE_CONNECTION);
    return ActionState::ACTION_CLOSE_CONNECTION;
}
