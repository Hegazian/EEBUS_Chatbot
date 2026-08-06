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

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_STATE_INFO_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_STATE_INFO_H_

/** @addtogroup keo_ship_stack
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include "SmeConnectionState.h"
#include "keo_ship/ConnectionCloseReason.h"
/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_ship
{
/**
 * Handling of states during SME phase
 */
class StateInfo
{
public:
    StateInfo();

    bool isInitialized();

    void setInitialized(bool isInitialized);

    bool isClient();

    void setClient(bool isClient);

    bool isSendAccessMethods();

    void setSendAccessMethods(bool sendAccessMethods);

    bool isPartnerIsHelloReady();

    void setPartnerIsHelloReady(bool partnerIsHelloReady);

    bool isAcceptProlongationRequest();

    void setAcceptProlongationRequest(bool acceptProlongationRequest);

    bool isPinOk();

    void setPinOk(bool isPinOk);

    bool isPartnerIsPinOk();

    void setPartnerIsPinOk(bool partnerIsPinOk);

    uint8_t getNumberOfAcceptedProlongationRequests();

    void setNumberOfAcceptedProlongationRequests(uint8_t numberOfAcceptedProlongationRequests);

    uint8_t getError();

    void setError(uint8_t error);

    SmeConnectionState getState();

    void setState(SmeConnectionState state);

    SmeConnectionState getPinState();

    void setPinState(SmeConnectionState pinState);

    SmeConnectionState getCloseState();

    void setCloseState(SmeConnectionState closeState);

    uint32_t getTimerMain();

    void setTimerMain(uint32_t timerMain);

    uint32_t getTimerSendProlongationRequest();

    void setTimerSendProlongationRequest(uint32_t timerSendProlongationRequest);

    uint32_t getLastWaitingReceived();

    void setLastWaitingReceived(uint32_t lastWaitingReceived);

    uint32_t getTimerProlongationRequestReply();

    void setTimerProlongationRequestReply(uint32_t timerProlongationRequestReply);

    uint32_t getTimerPin();

    void setTimerPin(uint32_t timerPin);

    uint32_t getTimerPinRecall();

    void setTimerPinRecall(uint32_t timerPinRecall);

    uint32_t getTimerConnectionTimeout();

    void setTimerConnectionTimeout(uint32_t timerConnectionTimeout);

    ConnectionCloseReason getCloseReason();

    void setCloseReason(ConnectionCloseReason reason);

private:
    bool m_isInitialized;
    bool m_isClient;
    bool m_sendAccessMethods;
    bool m_partnerIsHelloReady;
    bool m_acceptProlongationRequest;
    bool m_isPinOk;
    bool m_partnerIsPinOk;
    uint8_t m_numberOfAcceptedProlongationRequests;
    uint8_t m_error;
    SmeConnectionState m_state;
    SmeConnectionState m_pinState;
    SmeConnectionState m_closeState;
    uint32_t m_timerMain;
    uint32_t m_timerSendProlongationRequest;
    uint32_t m_lastWaitingReceived;
    uint32_t m_timerProlongationRequestReply;
    uint32_t m_timerPin;
    uint32_t m_timerPinRecall;
    uint32_t m_timerConnectionTimeout;
    ConnectionCloseReason m_closeReason;
};
}
/** @}
 * end of file
 */

#endif /* STATE_INFO_H_ */
