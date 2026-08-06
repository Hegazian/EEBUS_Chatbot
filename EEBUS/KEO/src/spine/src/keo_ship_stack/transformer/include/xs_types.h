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

/**
 *  @brief  Primitive xsd types for SHIP-STACK
 *
 *  @par    Module description
 *          xsd typedefs
 *
 *  @author KEO GmbH 2016 @n
 *          All rights reserved !
 */

#ifndef KEO_SHIP_STACK_INCLUDE_XS_TYPES_H_
#define KEO_SHIP_STACK_INCLUDE_XS_TYPES_H_

/** @addtogroup keo_ship_stack
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <stdint.h>
#include <string>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ShipByteArray.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_ship
{

/// Enumeration of the value type of a simple member
enum ValueType
{
    VALUE_FALSE = 0,
    VALUE_TRUE = 1,
    VALUE_NULL,
    VALUE_NUMBER,
    VALUE_STRING,
    VALUE_LIST,
    VALUE_EMPTY_LIST,
    VALUE_SIMPLE_LIST,
    VALUE_NOT_DEFINED
};

/// xsd boolean
typedef bool xs_boolean;
/// xsd double
typedef double xs_double;
/// xsd hexBinary
typedef ShipByteArray xs_hexBinary;
/// xsd language
typedef std::string xs_language;
/// xsd string
typedef std::string xs_string;
/// xsd byte
typedef int8_t xs_byte;
/// xsd unsignedByte
typedef uint8_t xs_unsignedByte;
/// xsd short
typedef int16_t xs_short;
/// xsd unsignedShort
typedef uint16_t xs_unsignedShort;
/// xsd integer
typedef int32_t xs_integer;
/// xsd unsignedInt
typedef uint32_t xs_unsignedInt;
/// xsd nonNegativeInteger
typedef uint32_t xs_nonNegativeInteger;
/// xsd unsignedLong
typedef uint64_t xs_unsignedLong;
/// xsd long
typedef int64_t xs_long;
}

/** @}
 * end of file
 */

#endif /* KEO_SHIP_STACK_INCLUDE_XS_TYPES_H_ */
