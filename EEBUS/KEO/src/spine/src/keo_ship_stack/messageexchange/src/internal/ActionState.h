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
 *     @file       ActionState.h
 *     @brief      Definition of SHIP message exchange states and corresponding enums.
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_ACTION_STATE_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_ACTION_STATE_H_

/** @addtogroup keo_ship_stack
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
*  defines                                                                       *
* ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/// SHIP namespace
namespace keo_ship
{

/**
 * The statemachine result actions
 */
typedef enum {
#define MACRO_ACTION(x) ACTION_##x,
#include "ActionState.h"
#undef MACRO_ACTION
    ACTION_LAST
} ActionState;

} // namespace keo_ship
/** @}
 * end of file
 */

#endif /* ACTION_STATE_H_ */

#ifdef MACRO_ACTION
MACRO_ACTION(NONE)

// Connection Mode Initialisation (CMI) state
MACRO_ACTION(SERVER_START_CMI_TIMER)
MACRO_ACTION(SERVER_SEND_CMI_MESSAGE_AND_GO_HELLO)
MACRO_ACTION(SERVER_SEND_CMI_ERROR_AND_CLOSE_CONNECTION)
MACRO_ACTION(CLIENT_SEND_CMI_MESSAGE_AND_START_CMI_TIMER)
MACRO_ACTION(CLIENT_GO_HELLO)

// Connection state "Hello"
MACRO_ACTION(SEND_HELLO_MESSAGE_AND_START_HELLO_TIMER_IFNEEDED)
MACRO_ACTION(SEND_PROLONGATION_MESSAGE_AND_START_PROLONGATION_TIMER)
MACRO_ACTION(START_PROLONGATION_TIMER)
MACRO_ACTION(CHECK_PROLONGATION_REQUEST)
MACRO_ACTION(SEND_HELLO_ABORTED_MESSAGE_AND_CLOSE_CONNECTION)
MACRO_ACTION(SWITCH_TO_READY_STATE)

// Connection state "Protocol handshake"
MACRO_ACTION(SERVER_START_PROT_H_TIMER)
MACRO_ACTION(CLIENT_SEND_PROT_H_ANNOUNCE_MESSAGE_AND_START_PROT_H_TIMER)
MACRO_ACTION(CLIENT_SEND_PROT_H_SELECT_MESSAGE_AND_START_PROT_H_TIMER)
MACRO_ACTION(SEND_PROT_H_ERROR_MESSAGE_AND_CLOSE_CONNECTION)

// Connection state "PIN verification"
MACRO_ACTION(SEND_PIN_REQUIREMENTS_INITIAL)
MACRO_ACTION(SEND_PIN_REQUIREMENTS)
MACRO_ACTION(VERIFY_PIN_OK)
MACRO_ACTION(VERIFY_PIN_FAILED)
MACRO_ACTION(PIN_INPUT_READY)
MACRO_ACTION(SEND_PIN_INPUT_AND_START_WAIT_FOR_PIN_TIMER)
MACRO_ACTION(PIN_RECALL_TIMEOUT)
MACRO_ACTION(TRY_ENABLE_CONNECTION_DATA_EXCHANGE)

// Connection state "Access methods"
MACRO_ACTION(SEND_ACCESS_METHODS_REQUEST)

// Close connection
MACRO_ACTION(CLOSE_CONNECTION_ANNOUNCE)
MACRO_ACTION(CLOSE_CONNECTION)
#endif
