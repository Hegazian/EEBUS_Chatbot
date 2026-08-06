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

#ifndef KEO_DATAGRAM_TIMESERIES_TIMESERIESSLOT_H_
#define KEO_DATAGRAM_TIMESERIES_TIMESERIESSLOT_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRecurringTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/TimePeriod.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeSeries
 * @{
 */

/**
 * Declaration TimeSeriesSlot
 */
class TimeSeriesSlot : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TimeSeriesSlot();

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
  bool operator==(const TimeSeriesSlot &c_classObject) const;

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
  bool operator!=(const TimeSeriesSlot &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member TimeSeriesSlotId.
   * @param c_timeSeriesSlotId Value to set
   */
  void setTimeSeriesSlotId(const xs_unsignedInt &c_timeSeriesSlotId);

  /**
   * Returns const reference to member TimeSeriesSlotId.
   * @return const reference to member timeSeriesSlotId
   */
  const xs_unsignedInt &getTimeSeriesSlotId() const;

  /**
   * Returns if member TimeSeriesSlotId is set.
   * @retval true member TimeSeriesSlotId is set
   * @retval false member TimeSeriesSlotId is not set
   */
  bool getTimeSeriesSlotIdIsSet() const;

  /**
   * Unsets member TimeSeriesSlotId
   */
  void cleanTimeSeriesSlotId();

  /**
   * Set member TimePeriod.
   * @param c_timePeriod Value to set
   */
  void setTimePeriod(const TimePeriod &c_timePeriod);

  /**
   * Returns const reference to member TimePeriod.
   * @return const reference to member timePeriod
   */
  const TimePeriod &getTimePeriod() const;

  /**
   * Returns if member TimePeriod is set.
   * @retval true member TimePeriod is set
   * @retval false member TimePeriod is not set
   */
  bool getTimePeriodIsSet() const;

  /**
   * Unsets member TimePeriod
   */
  void cleanTimePeriod();

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
   * Set member RecurrenceInformation.
   * @param c_recurrenceInformation Value to set
   */
  void setRecurrenceInformation(
      const AbsoluteOrRecurringTime &c_recurrenceInformation);

  /**
   * Returns const reference to member RecurrenceInformation.
   * @return const reference to member recurrenceInformation
   */
  const AbsoluteOrRecurringTime &getRecurrenceInformation() const;

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
   * Set member Value.
   * @param c_value Value to set
   */
  void setValue(const ScaledNumber &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const ScaledNumber &getValue() const;

  /**
   * Returns if member Value is set.
   * @retval true member Value is set
   * @retval false member Value is not set
   */
  bool getValueIsSet() const;

  /**
   * Unsets member Value
   */
  void cleanValue();

  /**
   * Set member MinValue.
   * @param c_minValue Value to set
   */
  void setMinValue(const ScaledNumber &c_minValue);

  /**
   * Returns const reference to member MinValue.
   * @return const reference to member minValue
   */
  const ScaledNumber &getMinValue() const;

  /**
   * Returns if member MinValue is set.
   * @retval true member MinValue is set
   * @retval false member MinValue is not set
   */
  bool getMinValueIsSet() const;

  /**
   * Unsets member MinValue
   */
  void cleanMinValue();

  /**
   * Set member MaxValue.
   * @param c_maxValue Value to set
   */
  void setMaxValue(const ScaledNumber &c_maxValue);

  /**
   * Returns const reference to member MaxValue.
   * @return const reference to member maxValue
   */
  const ScaledNumber &getMaxValue() const;

  /**
   * Returns if member MaxValue is set.
   * @retval true member MaxValue is set
   * @retval false member MaxValue is not set
   */
  bool getMaxValueIsSet() const;

  /**
   * Unsets member MaxValue
   */
  void cleanMaxValue();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timeSeriesSlotIdIsSet;
  xs_unsignedInt m_timeSeriesSlotId;

  bool m_timePeriodIsSet;
  TimePeriod m_timePeriod;

  bool m_durationIsSet;
  xs_duration m_duration;

  bool m_recurrenceInformationIsSet;
  AbsoluteOrRecurringTime m_recurrenceInformation;

  bool m_valueIsSet;
  ScaledNumber m_value;

  bool m_minValueIsSet;
  ScaledNumber m_minValue;

  bool m_maxValueIsSet;
  ScaledNumber m_maxValue;
};

//! typedef for non-const smart pointer type TimeSeriesSlot
using TimeSeriesSlotPtr = std::shared_ptr<TimeSeriesSlot>;

//! typedef for const type TimeSeriesSlot
using TimeSeriesSlotConst = const TimeSeriesSlot;

//! typedef for const type TimeSeriesSlot
using TimeSeriesSlotConstPtr = std::shared_ptr<TimeSeriesSlotConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMESERIES_TIMESERIESSLOT_H_