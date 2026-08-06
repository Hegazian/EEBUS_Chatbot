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

#ifndef KEO_DATAGRAM_TIMESERIES_TIMESERIESSLOTELEMENTS_H_
#define KEO_DATAGRAM_TIMESERIES_TIMESERIESSLOTELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRecurringTimeElements.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/TimePeriodElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeSeries
 * @{
 */

/**
 * Declaration TimeSeriesSlotElements
 */
class TimeSeriesSlotElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TimeSeriesSlotElements();

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
  bool operator==(const TimeSeriesSlotElements &c_classObject) const;

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
  bool operator!=(const TimeSeriesSlotElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member TimeSeriesSlotId.
   */
  void setTimeSeriesSlotId();

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
  void setTimePeriod(const TimePeriodElements &c_timePeriod);

  /**
   * Returns const reference to member TimePeriod.
   * @return const reference to member timePeriod
   */
  const TimePeriodElements &getTimePeriod() const;

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
   */
  void setDuration();

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
      const AbsoluteOrRecurringTimeElements &c_recurrenceInformation);

  /**
   * Returns const reference to member RecurrenceInformation.
   * @return const reference to member recurrenceInformation
   */
  const AbsoluteOrRecurringTimeElements &getRecurrenceInformation() const;

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
   */
  void setValue();

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
   */
  void setMinValue();

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
   */
  void setMaxValue();

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

  // ElementTag
  bool m_timeSeriesSlotIdIsSet;

  bool m_timePeriodIsSet;
  TimePeriodElements m_timePeriod;

  // ElementTag
  bool m_durationIsSet;

  bool m_recurrenceInformationIsSet;
  AbsoluteOrRecurringTimeElements m_recurrenceInformation;

  // ElementTag
  bool m_valueIsSet;

  // ElementTag
  bool m_minValueIsSet;

  // ElementTag
  bool m_maxValueIsSet;
};

//! typedef for non-const smart pointer type TimeSeriesSlotElements
using TimeSeriesSlotElementsPtr = std::shared_ptr<TimeSeriesSlotElements>;

//! typedef for const type TimeSeriesSlotElements
using TimeSeriesSlotElementsConst = const TimeSeriesSlotElements;

//! typedef for const type TimeSeriesSlotElements
using TimeSeriesSlotElementsConstPtr =
    std::shared_ptr<TimeSeriesSlotElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMESERIES_TIMESERIESSLOTELEMENTS_H_