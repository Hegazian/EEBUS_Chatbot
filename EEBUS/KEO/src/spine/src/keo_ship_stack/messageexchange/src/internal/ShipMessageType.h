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
 *     @file       ShipMessageType.h
 *     @brief      Definition of ShipMessageType.
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_SHIP_MESSAGE_TYPE_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_SHIP_MESSAGE_TYPE_H_

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
    MESSAGE_TYPE_INIT = 0,
    MESSAGE_TYPE_CONTROL = 1,
    MESSAGE_TYPE_DATA = 2,
    MESSAGE_TYPE_END = 3,
    MESSGAE_TYPE_RFU = 4
} ShipMessageType;

} // namespace keo_ship
#endif
/** @}
 * end of file
 */
