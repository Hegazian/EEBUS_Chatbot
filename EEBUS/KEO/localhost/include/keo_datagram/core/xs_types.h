/*
 *     Copyright KEO GmbH 2019 - All rights reserved!
 *
 *     This software is protected by the inclusion of the above copyright
 * notice.
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

#ifndef KEO_DATAGRAM_CORE_XSTYPES_H_
#define KEO_DATAGRAM_CORE_XSTYPES_H_

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */

#include <keo_datagram/core/KeoByteArray.h>
#include <keo_datagram/core/KeoDate.h>
#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoTime.h>

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */

#include <cstdint>
#include <string>

/* ******************************************************************************
 * *
 *  definition *
 * ******************************************************************************
 */

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */
//! xs base type boolean
using xs_boolean = bool;
//! xs base type date
using xs_date = KeoDate;
//! xs base type dateTime
using xs_dateTime = KeoDateTime;
//! xs base type duration
using xs_duration = KeoDuration;
//! xs base hexBinary
using xs_hexBinary = KeoByteArray;
//! xs base type string
using xs_string = std::string;
//! xs base type time
using xs_time = KeoTime;
//! xs base type unsignedByte
using xs_unsignedByte = std::uint8_t;
//! xs base type short
using xs_short = std::int16_t;
//! xs base type integer
using xs_integer = std::int32_t;
//! xs base type unsignedInt
using xs_unsignedInt = std::uint32_t;
//! xs base type unsignedLong
using xs_unsignedLong = std::uint64_t;
//! xs base type long
using xs_long = std::int64_t;

/** @}
 */

} // end namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_XSTYPES_H_