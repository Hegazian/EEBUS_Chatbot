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

#ifndef __KEO_DATAGRAM_CORE_SPINEENUMCLASS_H__
#define __KEO_DATAGRAM_CORE_SPINEENUMCLASS_H__

#include <string>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/** Base class for SPINE enumerations **/
class SpineEnum {
public:
  virtual ~SpineEnum(){};

  /**
   * Function to generate an enum object from string
   * @param c_text for the enumeration object
   */
  virtual bool setFromString(const std::string &c_text) = 0;

  /**
   * Return enumeration object as string
   * @return enumeration object as string
   */
  virtual std::string toString() const = 0;
};

/** Base class for extendable enumerations **/
class ExtendableSpineEnum : public SpineEnum {
public:
  virtual ~ExtendableSpineEnum(){};

  //! The enum extendable string
  std::string enumExtend;
};

/**
 * \deprecated Use SpineEnum instead.
 */
using SpineEnumClass = SpineEnum;

/**
 * \deprecated Use ExtendableSpineEnum instead.
 */
using SpineEnumClassStruct = ExtendableSpineEnum;

/** @}
 */

} // end namespace keo_datagram
#endif