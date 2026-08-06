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
 *     @file       SmeConnectionStateOverview.h
 *     @brief      Definition of SmeConnectionStateOverview.
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_SME_CONNECTION_STATE_OVERVIEW_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_SME_CONNECTION_STATE_OVERVIEW_H_

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
 * List of all possible input events
 */
typedef enum SmeConnectionStateOverview {
#define MACRO_STATE_OVERVIEW(x) x,
#include "SmeConnectionStateOverview.h"
#undef MACRO_STATE_OVERVIEW
    SME_STATE_OVERVIEW_LAST,
} AllSmeConnectionStateOverviewEnum;

} // namespace keo_ship
#endif

#ifdef MACRO_STATE_OVERVIEW
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_UNDEFINED)
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_CONNECTION_MODE_INITIALISATION) // Connection Mode Initialisation (CMI) state
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_UNDEFINED_1)
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_CONNECTION_STATE_HELLO) // Connection state "Hello"
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_UNDEFINED_2)
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_CONNECTION_STATE_PROTOCOL_HANDSHAKE) // Connection state "Protocol handshake"
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_UNDEFINED_3)
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_CONNECTION_PIN_VERIFICATION) // Connection state "PIN verification"
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_UNDEFINED_4)
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_ACCESS_METHODS) // Access methods and data exchange
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_UNDEFINED_5)
MACRO_STATE_OVERVIEW(STATE_OVERVIEW_CLOSE_CONNECTION) // Close connection
#endif

/** @}
 * end of file
 */
