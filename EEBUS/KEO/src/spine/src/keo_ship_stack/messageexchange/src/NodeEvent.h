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
 *     @file       NodeEvent.h
 *     @brief      Definition of events.
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_NODE_EVENT_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_NODE_EVENT_H_

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
typedef enum {
    NODE_EVENT_UNKNOWN = 0, // Undefined event
    NODE_EVENT_CONNECTION_MUST_BE_TRUSTED,
    NODE_EVENT_PIN_RECEIVED,
    NODE_EVENT_PIN_INPUT_READY,
    NODE_EVENT_WRONG_PIN,
    NODE_EVENT_PIN_RECALL_TIMEOUT,
    NODE_EVENT_ENABLE_DATA_EXCHANGE,
    NODE_EVENT_RECEIVED_ID,
    NODE_EVENT_CLOSE_ANNOUNCE,
    NODE_EVENT_CLOSE_ANNOUNCE_CONFIRM
} NodeEvent;

} // namespace keo_ship
#endif
/** @}
 * end of file
 */
