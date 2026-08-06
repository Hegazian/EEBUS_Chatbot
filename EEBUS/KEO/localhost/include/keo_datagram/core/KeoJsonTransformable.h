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

#ifndef KEO_DATAGRAM_CORE_KEOJSONTRANSFORMABLE_H_
#define KEO_DATAGRAM_CORE_KEOJSONTRANSFORMABLE_H_

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */
#include <string>

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */

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

class KeoJsonValue;

class KeoJsonTransformable {
public:
  virtual bool fromJson(KeoJsonValue *json) = 0;
  virtual std::string toJson() const = 0;

  virtual ~KeoJsonTransformable() = default;
};

/** @}
 */

} // end namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_KEOJSONTRANSFORMABLE_H_