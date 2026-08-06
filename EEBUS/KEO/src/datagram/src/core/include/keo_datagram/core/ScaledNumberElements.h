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

#ifndef KEO_DATAGRAM_CORE_SCALEDNUMBERELEMENTS_H_
#define KEO_DATAGRAM_CORE_SCALEDNUMBERELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration ScaledNumberElements
 */
class ScaledNumberElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  ScaledNumberElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_numberIsSet the member to set
   * @param c_scaleIsSet the member to set
   */
  ScaledNumberElements(xs_boolean c_numberIsSet, xs_boolean c_scaleIsSet);

  /**
   * Equality operator
   *
   * Two objects a and b are considered equal if and only if
   *     - all members that are set in a are also set in b
   *     - all members that are set in b are also set in a
   *     - all members that are set in a and b are equal
   *
   * @param c_classObject the object to compare to
   * @return true if the objects are equal
   */
  bool operator==(const ScaledNumberElements &c_classObject) const;

  /**
   * Inequality operator
   *
   * Two objects a and b are considered not equal if and only if
   *     - at least one member that is set in a is not set in b
   *     - at least one member that is set in b is not set in a
   *     - at least one member that is set in a and b differs
   *
   * @param c_classObject the object to compare to
   * @return true, if the objects are not equal
   */
  bool operator!=(const ScaledNumberElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Number.
   */
  void setNumber();

  /**
   * Returns if member Number is set.
   * @retval true member Number is set
   * @retval false member Number is not set
   */
  bool getNumberIsSet() const;

  /**
   * Unsets member Number
   */
  void cleanNumber();

  /**
   * Set member Scale.
   */
  void setScale();

  /**
   * Returns if member Scale is set.
   * @retval true member Scale is set
   * @retval false member Scale is not set
   */
  bool getScaleIsSet() const;

  /**
   * Unsets member Scale
   */
  void cleanScale();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_numberIsSet;

  // ElementTag
  bool m_scaleIsSet;
};

//! typedef for non-const smart pointer type ScaledNumberElements
using ScaledNumberElementsPtr = std::shared_ptr<ScaledNumberElements>;

//! typedef for const type ScaledNumberElements
using ScaledNumberElementsConst = const ScaledNumberElements;

//! typedef for const type ScaledNumberElements
using ScaledNumberElementsConstPtr = std::shared_ptr<ScaledNumberElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_SCALEDNUMBERELEMENTS_H_