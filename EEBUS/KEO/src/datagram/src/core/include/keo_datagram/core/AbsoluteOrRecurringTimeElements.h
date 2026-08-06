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

#ifndef KEO_DATAGRAM_CORE_ABSOLUTEORRECURRINGTIMEELEMENTS_H_
#define KEO_DATAGRAM_CORE_ABSOLUTEORRECURRINGTIMEELEMENTS_H_

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
 * Declaration AbsoluteOrRecurringTimeElements
 */
class AbsoluteOrRecurringTimeElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  AbsoluteOrRecurringTimeElements();

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
  bool operator==(const AbsoluteOrRecurringTimeElements &c_classObject) const;

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
  bool operator!=(const AbsoluteOrRecurringTimeElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member DateTime.
   */
  void setDateTime();

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
   * Set member Month.
   */
  void setMonth();

  /**
   * Returns if member Month is set.
   * @retval true member Month is set
   * @retval false member Month is not set
   */
  bool getMonthIsSet() const;

  /**
   * Unsets member Month
   */
  void cleanMonth();

  /**
   * Set member DayOfMonth.
   */
  void setDayOfMonth();

  /**
   * Returns if member DayOfMonth is set.
   * @retval true member DayOfMonth is set
   * @retval false member DayOfMonth is not set
   */
  bool getDayOfMonthIsSet() const;

  /**
   * Unsets member DayOfMonth
   */
  void cleanDayOfMonth();

  /**
   * Set member CalendarWeek.
   */
  void setCalendarWeek();

  /**
   * Returns if member CalendarWeek is set.
   * @retval true member CalendarWeek is set
   * @retval false member CalendarWeek is not set
   */
  bool getCalendarWeekIsSet() const;

  /**
   * Unsets member CalendarWeek
   */
  void cleanCalendarWeek();

  /**
   * Set member DayOfWeekOccurrence.
   */
  void setDayOfWeekOccurrence();

  /**
   * Returns if member DayOfWeekOccurrence is set.
   * @retval true member DayOfWeekOccurrence is set
   * @retval false member DayOfWeekOccurrence is not set
   */
  bool getDayOfWeekOccurrenceIsSet() const;

  /**
   * Unsets member DayOfWeekOccurrence
   */
  void cleanDayOfWeekOccurrence();

  /**
   * Set member DaysOfWeek.
   */
  void setDaysOfWeek();

  /**
   * Returns if member DaysOfWeek is set.
   * @retval true member DaysOfWeek is set
   * @retval false member DaysOfWeek is not set
   */
  bool getDaysOfWeekIsSet() const;

  /**
   * Unsets member DaysOfWeek
   */
  void cleanDaysOfWeek();

  /**
   * Set member Time.
   */
  void setTime();

  /**
   * Returns if member Time is set.
   * @retval true member Time is set
   * @retval false member Time is not set
   */
  bool getTimeIsSet() const;

  /**
   * Unsets member Time
   */
  void cleanTime();

  /**
   * Set member Relative.
   */
  void setRelative();

  /**
   * Returns if member Relative is set.
   * @retval true member Relative is set
   * @retval false member Relative is not set
   */
  bool getRelativeIsSet() const;

  /**
   * Unsets member Relative
   */
  void cleanRelative();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_dateTimeIsSet;

  // ElementTag
  bool m_monthIsSet;

  // ElementTag
  bool m_dayOfMonthIsSet;

  // ElementTag
  bool m_calendarWeekIsSet;

  // ElementTag
  bool m_dayOfWeekOccurrenceIsSet;

  // ElementTag
  bool m_daysOfWeekIsSet;

  // ElementTag
  bool m_timeIsSet;

  // ElementTag
  bool m_relativeIsSet;
};

//! typedef for non-const smart pointer type AbsoluteOrRecurringTimeElements
using AbsoluteOrRecurringTimeElementsPtr =
    std::shared_ptr<AbsoluteOrRecurringTimeElements>;

//! typedef for const type AbsoluteOrRecurringTimeElements
using AbsoluteOrRecurringTimeElementsConst =
    const AbsoluteOrRecurringTimeElements;

//! typedef for const type AbsoluteOrRecurringTimeElements
using AbsoluteOrRecurringTimeElementsConstPtr =
    std::shared_ptr<AbsoluteOrRecurringTimeElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_ABSOLUTEORRECURRINGTIMEELEMENTS_H_