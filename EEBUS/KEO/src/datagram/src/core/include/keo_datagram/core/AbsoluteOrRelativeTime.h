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

#ifndef KEO_DATAGRAM_CORE_ABSOLUTEORRELATIVETIME_H_
#define KEO_DATAGRAM_CORE_ABSOLUTEORRELATIVETIME_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration AbsoluteOrRelativeTime
 */
class AbsoluteOrRelativeTime : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  AbsoluteOrRelativeTime();

  /**
   * Construct an instance of this class.
   * @param c_duration the duration to set
   */
  AbsoluteOrRelativeTime(const xs_duration &c_duration);

  /**
   * Construct an instance of this class.
   * @param c_dateTime the dateTime to set
   */
  AbsoluteOrRelativeTime(const xs_dateTime &c_dateTime);

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
  bool operator==(const AbsoluteOrRelativeTime &c_classObject) const;

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
  bool operator!=(const AbsoluteOrRelativeTime &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Duration.
   * @param c_duration Value to set
   */
  void setDuration(const xs_duration &c_duration);

  /**
   * Returns const reference to member Duration.
   * @return const reference to member duration
   */
  const xs_duration &getDuration() const;

  /**
   * Returns if member Duration is set.
   * @retval true member Duration is set
   * @retval false member Duration is not set
   */
  bool getDurationIsSet() const;

  /**
   * Unsets member Duration
   */
  void cleanDuration();

  /**
   * Set member DateTime.
   * @param c_dateTime Value to set
   */
  void setDateTime(const xs_dateTime &c_dateTime);

  /**
   * Returns const reference to member DateTime.
   * @return const reference to member dateTime
   */
  const xs_dateTime &getDateTime() const;

  /**
   * Returns if member DateTime is set.
   * @retval true member DateTime is set
   * @retval false member DateTime is not set
   */
  bool getDateTimeIsSet() const;

  /**
   * Unsets member DateTime
   */
  void cleanDateTime();

  /**
   * Check validity of this instance.
   * @return true if this instance is valid
   */
  bool isValid() const;

  /**
   * Returns a string representation of this instance.
   * @return the instance as a string
   */
  std::string toString() const;

  /**
   * Create an instance from string.
   * @param str string representation of the time
   * @return the instance (check isValid() to ensure it is valid)
   */
  static AbsoluteOrRelativeTime fromString(const std::string &str);

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_durationIsSet;
  xs_duration m_duration;

  bool m_dateTimeIsSet;
  xs_dateTime m_dateTime;
};

//! typedef for non-const smart pointer type AbsoluteOrRelativeTime
using AbsoluteOrRelativeTimePtr = std::shared_ptr<AbsoluteOrRelativeTime>;

//! typedef for const type AbsoluteOrRelativeTime
using AbsoluteOrRelativeTimeConst = const AbsoluteOrRelativeTime;

//! typedef for const type AbsoluteOrRelativeTime
using AbsoluteOrRelativeTimeConstPtr =
    std::shared_ptr<AbsoluteOrRelativeTimeConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_ABSOLUTEORRELATIVETIME_H_