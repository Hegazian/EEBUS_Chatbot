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

#ifndef KEO_DATAGRAM_CORE_SPINEDATAGRAM_H_
#define KEO_DATAGRAM_CORE_SPINEDATAGRAM_H_

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */
#include <keo_datagram/core/CmdControlType.h>
#include <keo_datagram/core/CmdFilterType.h>
#include <keo_datagram/core/Datagram.h>

/* ************************************************************************** *
 *  defines                                                                   *
 * ************************************************************************** */

/* ************************************************************************** *
 *  types                                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  class definition                                                          *
 * ************************************************************************** */

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * \deprecated Use Datagram (Datagram.h) instead.
 */
using SpineDatagram = Datagram;

//! typedef for smart pointer to non-const SpineDatagram
using SpineDatagramPtr = std::shared_ptr<SpineDatagram>;

//! typedef for const SpineDatagram
using SpineDatagramConst = const SpineDatagram;

//! typedef for smart pointer to const SpineDatagram
using SpineDatagramConstPtr = std::shared_ptr<SpineDatagramConst>;

/** @}
 */

} // end namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_SPINEDATAGRAM_H_