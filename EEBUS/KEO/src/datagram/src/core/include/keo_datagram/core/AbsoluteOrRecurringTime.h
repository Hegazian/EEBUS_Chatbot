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

#ifndef KEO_DATAGRAM_CORE_ABSOLUTEORRECURRINGTIME_H_
#define KEO_DATAGRAM_CORE_ABSOLUTEORRECURRINGTIME_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRecurringTimeElements.h>
#include <keo_datagram/core/DaysOfWeek.h>
#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/KeoTime.h>
#include <keo_datagram/core/Month.h>
#include <keo_datagram/core/Occurrence.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration AbsoluteOrRecurringTime
 */
class AbsoluteOrRecurringTime : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  AbsoluteOrRecurringTime();

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
  bool operator==(const AbsoluteOrRecurringTime &c_classObject) const;

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
  bool operator!=(const AbsoluteOrRecurringTime &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member Month.
   * @param c_month Value to set
   */
  void setMonth(const Month &c_month);

  /**
   * Returns const reference to member Month.
   * @return const reference to member month
   */
  const Month &getMonth() const;

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
   * @param c_dayOfMonth Value to set
   */
  void setDayOfMonth(const xs_unsignedByte &c_dayOfMonth);

  /**
   * Returns const reference to member DayOfMonth.
   * @return const reference to member dayOfMonth
   */
  const xs_unsignedByte &getDayOfMonth() const;

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
   * @param c_calendarWeek Value to set
   */
  void setCalendarWeek(const xs_unsignedByte &c_calendarWeek);

  /**
   * Returns const reference to member CalendarWeek.
   * @return const reference to member calendarWeek
   */
  const xs_unsignedByte &getCalendarWeek() const;

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
   * @param c_dayOfWeekOccurrence Value to set
   */
  void setDayOfWeekOccurrence(const Occurrence &c_dayOfWeekOccurrence);

  /**
   * Returns const reference to member DayOfWeekOccurrence.
   * @return const reference to member dayOfWeekOccurrence
   */
  const Occurrence &getDayOfWeekOccurrence() const;

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
   * @param c_daysOfWeek Value to set
   */
  void setDaysOfWeek(const DaysOfWeek &c_daysOfWeek);

  /**
   * Returns const reference to member DaysOfWeek.
   * @return const reference to member daysOfWeek
   */
  const DaysOfWeek &getDaysOfWeek() const;

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
   * @param c_time Value to set
   */
  void setTime(const xs_time &c_time);

  /**
   * Returns const reference to member Time.
   * @return const reference to member time
   */
  const xs_time &getTime() const;

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
   * @param c_relative Value to set
   */
  void setRelative(const xs_duration &c_relative);

  /**
   * Returns const reference to member Relative.
   * @return const reference to member relative
   */
  const xs_duration &getRelative() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  AbsoluteOrRecurringTime
  reduce(const AbsoluteOrRecurringTimeElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_dateTimeIsSet;
  xs_dateTime m_dateTime;

  bool m_monthIsSet;
  Month m_month;

  bool m_dayOfMonthIsSet;
  xs_unsignedByte m_dayOfMonth;

  bool m_calendarWeekIsSet;
  xs_unsignedByte m_calendarWeek;

  bool m_dayOfWeekOccurrenceIsSet;
  Occurrence m_dayOfWeekOccurrence;

  bool m_daysOfWeekIsSet;
  DaysOfWeek m_daysOfWeek;

  bool m_timeIsSet;
  xs_time m_time;

  bool m_relativeIsSet;
  xs_duration m_relative;
};

//! typedef for non-const smart pointer type AbsoluteOrRecurringTime
using AbsoluteOrRecurringTimePtr = std::shared_ptr<AbsoluteOrRecurringTime>;

//! typedef for const type AbsoluteOrRecurringTime
using AbsoluteOrRecurringTimeConst = const AbsoluteOrRecurringTime;

//! typedef for const type AbsoluteOrRecurringTime
using AbsoluteOrRecurringTimeConstPtr =
    std::shared_ptr<AbsoluteOrRecurringTimeConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_ABSOLUTEORRECURRINGTIME_H_