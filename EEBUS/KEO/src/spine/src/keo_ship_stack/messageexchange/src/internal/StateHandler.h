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

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_STATE_HANDLER_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_STATE_HANDLER_H_

/** @addtogroup keo_ship_stack
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ActionState.h"
#include "SmeConnectionState.h"
#include "StateInfo.h"

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_ship
{
/**
 * Handling of states during SME phase
 */
class StateHandler
{
public:
    /**
     * Initialize state
     * @param pStateInfo
     *        Referencing a connection depending object containing the current status concerning SME phase.
     * @return
     */
    static keo_ship::ActionState initState(keo_ship::StateInfo* pStateInfo);

    /**
     * Retrieve state in case main timeout occurred
     * @param pStateInfo
     *        Referencing a connection depending object containing the current status concerning SME phase.
     * @return
     */
    static keo_ship::ActionState getStateFromTimeout(keo_ship::StateInfo* pStateInfo);

    /**
     * Retrieve state in case main prolongation request timeout occurred
     * @param pStateInfo
     *        Referencing a connection depending object containing the current status concerning SME phase.
     * @return
     */
    static keo_ship::ActionState getStateFromSendProlongationRequestTimeout(keo_ship::StateInfo* pStateInfo);

    /**
     * Retrieve state in case PIN timeout occurred
     * @param pStateInfo
     *        Referencing a connection depending object containing the current status concerning SME phase.
     * @return
     */
    static keo_ship::ActionState getStateFromPinTimeout(keo_ship::StateInfo* pStateInfo);

    /**
     * Retrieve state in case penalty wait timeout occurred
     * @param pStateInfo
     *        Referencing a connection depending object containing the current status concerning SME phase.
     * @return
     */
    static keo_ship::ActionState getStateFromPenaltyWaitTimeout(keo_ship::StateInfo* pStateInfo);

    /**
     * Retrieve state in case Pin Recall timeout occurred
     * @param pStateInfo
     *        Referencing a connection depending object containing the current status concerning SME phase.
     * @return
     */
    static keo_ship::ActionState getStateFromPinRecallTimeout(keo_ship::StateInfo* pStateInfo);

    /**
     * Retrieve state in case Connection timeout occurred
     * @param pStateInfo
     *        Referencing a connection depending object containing the current status concerning SME phase.
     * @return
     */
    static keo_ship::ActionState getStateFromConnectionTimeout(keo_ship::StateInfo* pStateInfo);

    static keo_ship::ActionState getStateFromTimeoutConnectionStateHello(keo_ship::StateInfo* pStateInfo);

    static keo_ship::ActionState getStateFromMainTimeoutConnectionStateProtocolHandshake(keo_ship::StateInfo* pStateInfo);

    static keo_ship::ActionState getStateFromMainTimeoutConnectionPINVerification(keo_ship::StateInfo* pStateInfo);

private:
    static keo_ship::ActionState getState_ConnectionStateProtocolHandshake(keo_ship::StateInfo* pStateInfo);
    static keo_ship::ActionState getState_ConnectionPINVerification(keo_ship::StateInfo* pStateInfo);
    static keo_ship::ActionState getStateFromTimeout_ConnectionStateHello(keo_ship::StateInfo* pStateInfo);
    static keo_ship::ActionState getStateFromMainTimeout_ConnectionStateProtocolHandshake(keo_ship::StateInfo* pStateInfo);
    static keo_ship::ActionState getStateFromMainTimeout_ConnectionPINVerification(keo_ship::StateInfo* pStateInfo);

    StateHandler();
    virtual ~StateHandler(){};
};
}
/** @}
 * end of file
 */

#endif /* STATE_HANDLER_H_ */
