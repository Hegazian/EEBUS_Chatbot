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

#ifndef KEO_DATAGRAM_CORE_TIMEPERIODELEMENTS_H_
#define KEO_DATAGRAM_CORE_TIMEPERIODELEMENTS_H_

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
 * Declaration TimePeriodElements
 */
class TimePeriodElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TimePeriodElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_startTimeIsSet the member to set
   * @param c_endTimeIsSet the member to set
   */
  TimePeriodElements(xs_boolean c_startTimeIsSet, xs_boolean c_endTimeIsSet);

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
  bool operator==(const TimePeriodElements &c_classObject) const;

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
  bool operator!=(const TimePeriodElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member StartTime.
   */
  void setStartTime();

  /**
   * Returns if member StartTime is set.
   * @retval true member StartTime is set
   * @retval false member StartTime is not set
   */
  bool getStartTimeIsSet() const;

  /**
   * Unsets member StartTime
   */
  void cleanStartTime();

  /**
   * Set member EndTime.
   */
  void setEndTime();

  /**
   * Returns if member EndTime is set.
   * @retval true member EndTime is set
   * @retval false member EndTime is not set
   */
  bool getEndTimeIsSet() const;

  /**
   * Unsets member EndTime
   */
  void cleanEndTime();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_startTimeIsSet;

  // ElementTag
  bool m_endTimeIsSet;
};

//! typedef for non-const smart pointer type TimePeriodElements
using TimePeriodElementsPtr = std::shared_ptr<TimePeriodElements>;

//! typedef for const type TimePeriodElements
using TimePeriodElementsConst = const TimePeriodElements;

//! typedef for const type TimePeriodElements
using TimePeriodElementsConstPtr = std::shared_ptr<TimePeriodElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_TIMEPERIODELEMENTS_H_