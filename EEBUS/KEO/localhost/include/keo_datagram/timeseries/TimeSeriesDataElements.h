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

#ifndef KEO_DATAGRAM_TIMESERIES_TIMESERIESDATAELEMENTS_H_
#define KEO_DATAGRAM_TIMESERIES_TIMESERIESDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/TimePeriodElements.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/timeseries/TimeSeriesSlotElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeSeries
 * @{
 */

/**
 * Declaration TimeSeriesDataElements
 */
class TimeSeriesDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TimeSeriesDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_timeSeriesIdIsSet the member to set
   * @param c_timePeriod the member to set
   * @param c_timeSeriesSlot the member to set
   */
  TimeSeriesDataElements(xs_boolean c_timeSeriesIdIsSet,
                         const TimePeriodElements &c_timePeriod,
                         const TimeSeriesSlotElements &c_timeSeriesSlot);

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
  bool operator==(const TimeSeriesDataElements &c_classObject) const;

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
  bool operator!=(const TimeSeriesDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member TimeSeriesId.
   */
  void setTimeSeriesId();

  /**
   * Returns if member TimeSeriesId is set.
   * @retval true member TimeSeriesId is set
   * @retval false member TimeSeriesId is not set
   */
  bool getTimeSeriesIdIsSet() const;

  /**
   * Unsets member TimeSeriesId
   */
  void cleanTimeSeriesId();

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
   * Set member TimeSeriesSlot.
   * @param c_timeSeriesSlot Value to set
   */
  void setTimeSeriesSlot(const TimeSeriesSlotElements &c_timeSeriesSlot);

  /**
   * Returns const reference to member TimeSeriesSlot.
   * @return const reference to member timeSeriesSlot
   */
  const TimeSeriesSlotElements &getTimeSeriesSlot() const;

  /**
   * Returns if member TimeSeriesSlot is set.
   * @retval true member TimeSeriesSlot is set
   * @retval false member TimeSeriesSlot is not set
   */
  bool getTimeSeriesSlotIsSet() const;

  /**
   * Unsets member TimeSeriesSlot
   */
  void cleanTimeSeriesSlot();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timeSeriesIdIsSet;

  bool m_timePeriodIsSet;
  TimePeriodElements m_timePeriod;

  bool m_timeSeriesSlotIsSet;
  TimeSeriesSlotElements m_timeSeriesSlot;
};

//! typedef for non-const smart pointer type TimeSeriesDataElements
using TimeSeriesDataElementsPtr = std::shared_ptr<TimeSeriesDataElements>;

//! typedef for const type TimeSeriesDataElements
using TimeSeriesDataElementsConst = const TimeSeriesDataElements;

//! typedef for const type TimeSeriesDataElements
using TimeSeriesDataElementsConstPtr =
    std::shared_ptr<TimeSeriesDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMESERIES_TIMESERIESDATAELEMENTS_H_