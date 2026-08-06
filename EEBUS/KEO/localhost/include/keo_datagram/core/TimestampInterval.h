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

#ifndef KEO_DATAGRAM_CORE_TIMESTAMPINTERVAL_H_
#define KEO_DATAGRAM_CORE_TIMESTAMPINTERVAL_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration TimestampInterval
 */
class TimestampInterval : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TimestampInterval();

  /**
   * Construct an instance of this class and set its member.
   * @param c_startTime the member to set
   * @param c_endTime the member to set
   */
  TimestampInterval(const AbsoluteOrRelativeTime &c_startTime,
                    const AbsoluteOrRelativeTime &c_endTime);

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
  bool operator==(const TimestampInterval &c_classObject) const;

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
  bool operator!=(const TimestampInterval &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member StartTime.
   * @param c_startTime Value to set
   */
  void setStartTime(const AbsoluteOrRelativeTime &c_startTime);

  /**
   * Returns const reference to member StartTime.
   * @return const reference to member startTime
   */
  const AbsoluteOrRelativeTime &getStartTime() const;

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
   * @param c_endTime Value to set
   */
  void setEndTime(const AbsoluteOrRelativeTime &c_endTime);

  /**
   * Returns const reference to member EndTime.
   * @return const reference to member endTime
   */
  const AbsoluteOrRelativeTime &getEndTime() const;

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

  bool m_startTimeIsSet;
  AbsoluteOrRelativeTime m_startTime;

  bool m_endTimeIsSet;
  AbsoluteOrRelativeTime m_endTime;
};

//! typedef for non-const smart pointer type TimestampInterval
using TimestampIntervalPtr = std::shared_ptr<TimestampInterval>;

//! typedef for const type TimestampInterval
using TimestampIntervalConst = const TimestampInterval;

//! typedef for const type TimestampInterval
using TimestampIntervalConstPtr = std::shared_ptr<TimestampIntervalConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_TIMESTAMPINTERVAL_H_