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

#ifndef KEO_DATAGRAM_TIMETABLE_TIMETABLEDATA_H_
#define KEO_DATAGRAM_TIMETABLE_TIMETABLEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRecurringTime.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/RecurrenceInformation.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/timetable/TimeTableDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeTable
 * @{
 */

/**
 * Declaration TimeTableData
 */
class TimeTableData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TimeTableData();

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
  bool operator==(const TimeTableData &c_classObject) const;

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
  bool operator!=(const TimeTableData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member TimeTableId.
   * @param c_timeTableId Value to set
   */
  void setTimeTableId(const xs_unsignedInt &c_timeTableId);

  /**
   * Returns const reference to member TimeTableId.
   * @return const reference to member timeTableId
   */
  const xs_unsignedInt &getTimeTableId() const;

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
   * @param c_timeSlotId Value to set
   */
  void setTimeSlotId(const xs_unsignedInt &c_timeSlotId);

  /**
   * Returns const reference to member TimeSlotId.
   * @return const reference to member timeSlotId
   */
  const xs_unsignedInt &getTimeSlotId() const;

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
      const RecurrenceInformation &c_recurrenceInformation);

  /**
   * Returns const reference to member RecurrenceInformation.
   * @return const reference to member recurrenceInformation
   */
  const RecurrenceInformation &getRecurrenceInformation() const;

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
  void setStartTime(const AbsoluteOrRecurringTime &c_startTime);

  /**
   * Returns const reference to member StartTime.
   * @return const reference to member startTime
   */
  const AbsoluteOrRecurringTime &getStartTime() const;

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
  void setEndTime(const AbsoluteOrRecurringTime &c_endTime);

  /**
   * Returns const reference to member EndTime.
   * @return const reference to member endTime
   */
  const AbsoluteOrRecurringTime &getEndTime() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  TimeTableData reduce(const TimeTableDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timeTableIdIsSet;
  xs_unsignedInt m_timeTableId;

  bool m_timeSlotIdIsSet;
  xs_unsignedInt m_timeSlotId;

  bool m_recurrenceInformationIsSet;
  RecurrenceInformation m_recurrenceInformation;

  bool m_startTimeIsSet;
  AbsoluteOrRecurringTime m_startTime;

  bool m_endTimeIsSet;
  AbsoluteOrRecurringTime m_endTime;
};

//! typedef for non-const smart pointer type TimeTableData
using TimeTableDataPtr = std::shared_ptr<TimeTableData>;

//! typedef for const type TimeTableData
using TimeTableDataConst = const TimeTableData;

//! typedef for const type TimeTableData
using TimeTableDataConstPtr = std::shared_ptr<TimeTableDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMETABLE_TIMETABLEDATA_H_