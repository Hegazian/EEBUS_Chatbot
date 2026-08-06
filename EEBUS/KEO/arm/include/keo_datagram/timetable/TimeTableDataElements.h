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

#ifndef KEO_DATAGRAM_TIMETABLE_TIMETABLEDATAELEMENTS_H_
#define KEO_DATAGRAM_TIMETABLE_TIMETABLEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRecurringTimeElements.h>
#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/RecurrenceInformationElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeTable
 * @{
 */

/**
 * Declaration TimeTableDataElements
 */
class TimeTableDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TimeTableDataElements();

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
  bool operator==(const TimeTableDataElements &c_classObject) const;

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
  bool operator!=(const TimeTableDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member TimeTableId.
   */
  void setTimeTableId();

  /**
   * Returns if member TimeTableId is set.
   * @retval true member TimeTableId is set
   * @retval false member TimeTableId is not set
   */
  bool getTimeTableIdIsSet() const;

  /**
   * Unsets member TimeTableId
   */
  void cleanTimeTableId();

  /**
   * Set member TimeSlotId.
   */
  void setTimeSlotId();

  /**
   * Returns if member TimeSlotId is set.
   * @retval true member TimeSlotId is set
   * @retval false member TimeSlotId is not set
   */
  bool getTimeSlotIdIsSet() const;

  /**
   * Unsets member TimeSlotId
   */
  void cleanTimeSlotId();

  /**
   * Set member RecurrenceInformation.
   * @param c_recurrenceInformation Value to set
   */
  void setRecurrenceInformation(
      const RecurrenceInformationElements &c_recurrenceInformation);

  /**
   * Returns const reference to member RecurrenceInformation.
   * @return const reference to member recurrenceInformation
   */
  const RecurrenceInformationElements &getRecurrenceInformation() const;

  /**
   * Returns if member RecurrenceInformation is set.
   * @retval true member RecurrenceInformation is set
   * @retval false member RecurrenceInformation is not set
   */
  bool getRecurrenceInformationIsSet() const;

  /**
   * Unsets member RecurrenceInformation
   */
  void cleanRecurrenceInformation();

  /**
   * Set member StartTime.
   * @param c_startTime Value to set
   */
  void setStartTime(const AbsoluteOrRecurringTimeElements &c_startTime);

  /**
   * Returns const reference to member StartTime.
   * @return const reference to member startTime
   */
  const AbsoluteOrRecurringTimeElements &getStartTime() const;

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
  void setEndTime(const AbsoluteOrRecurringTimeElements &c_endTime);

  /**
   * Returns const reference to member EndTime.
   * @return const reference to member endTime
   */
  const AbsoluteOrRecurringTimeElements &getEndTime() const;

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
  bool m_timeTableIdIsSet;

  // ElementTag
  bool m_timeSlotIdIsSet;

  bool m_recurrenceInformationIsSet;
  RecurrenceInformationElements m_recurrenceInformation;

  bool m_startTimeIsSet;
  AbsoluteOrRecurringTimeElements m_startTime;

  bool m_endTimeIsSet;
  AbsoluteOrRecurringTimeElements m_endTime;
};

//! typedef for non-const smart pointer type TimeTableDataElements
using TimeTableDataElementsPtr = std::shared_ptr<TimeTableDataElements>;

//! typedef for const type TimeTableDataElements
using TimeTableDataElementsConst = const TimeTableDataElements;

//! typedef for const type TimeTableDataElements
using TimeTableDataElementsConstPtr =
    std::shared_ptr<TimeTableDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMETABLE_TIMETABLEDATAELEMENTS_H_