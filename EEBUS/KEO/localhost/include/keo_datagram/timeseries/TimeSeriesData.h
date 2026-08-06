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

#ifndef KEO_DATAGRAM_TIMESERIES_TIMESERIESDATA_H_
#define KEO_DATAGRAM_TIMESERIES_TIMESERIESDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/TimePeriod.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/timeseries/TimeSeriesSlot.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeSeries
 * @{
 */

/**
 * Declaration TimeSeriesData
 */
class TimeSeriesData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TimeSeriesData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_timeSeriesId the member to set
   * @param c_timePeriod the member to set
   * @param c_timeSeriesSlot the member to set
   */
  TimeSeriesData(const xs_unsignedInt &c_timeSeriesId,
                 const TimePeriod &c_timePeriod,
                 const std::vector<TimeSeriesSlot> &c_timeSeriesSlot);

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
  bool operator==(const TimeSeriesData &c_classObject) const;

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
  bool operator!=(const TimeSeriesData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member TimeSeriesId.
   * @param c_timeSeriesId Value to set
   */
  void setTimeSeriesId(const xs_unsignedInt &c_timeSeriesId);

  /**
   * Returns const reference to member TimeSeriesId.
   * @return const reference to member timeSeriesId
   */
  const xs_unsignedInt &getTimeSeriesId() const;

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
   * Set member TimeSeriesSlot.
   * @param c_timeSeriesSlot Value to set
   */
  void setTimeSeriesSlot(const std::vector<TimeSeriesSlot> &c_timeSeriesSlot);

  /**
   * Returns const reference to member TimeSeriesSlot.
   * @return const reference to member timeSeriesSlot
   */
  const std::vector<TimeSeriesSlot> &getTimeSeriesSlot() const;

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

  bool m_timeSeriesIdIsSet;
  xs_unsignedInt m_timeSeriesId;

  bool m_timePeriodIsSet;
  TimePeriod m_timePeriod;

  bool m_timeSeriesSlotIsSet;
  std::vector<TimeSeriesSlot> m_timeSeriesSlot;
};

//! typedef for non-const smart pointer type TimeSeriesData
using TimeSeriesDataPtr = std::shared_ptr<TimeSeriesData>;

//! typedef for const type TimeSeriesData
using TimeSeriesDataConst = const TimeSeriesData;

//! typedef for const type TimeSeriesData
using TimeSeriesDataConstPtr = std::shared_ptr<TimeSeriesDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMESERIES_TIMESERIESDATA_H_