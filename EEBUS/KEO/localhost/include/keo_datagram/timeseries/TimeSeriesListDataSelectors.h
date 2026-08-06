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

#ifndef KEO_DATAGRAM_TIMESERIES_TIMESERIESLISTDATASELECTORS_H_
#define KEO_DATAGRAM_TIMESERIES_TIMESERIESLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeSeries
 * @{
 */

/**
 * Declaration TimeSeriesListDataSelectors
 */
class TimeSeriesListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  TimeSeriesListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_timeSeriesId the member to set
   * @param c_timeSeriesSlotId the member to set
   */
  TimeSeriesListDataSelectors(const xs_unsignedInt &c_timeSeriesId,
                              const xs_unsignedInt &c_timeSeriesSlotId);

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
  bool operator==(const TimeSeriesListDataSelectors &c_classObject) const;

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
  bool operator!=(const TimeSeriesListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timeSeriesIdIsSet;
  xs_unsignedInt m_timeSeriesId;

  bool m_timeSeriesSlotIdIsSet;
  xs_unsignedInt m_timeSeriesSlotId;
};

//! typedef for non-const smart pointer type TimeSeriesListDataSelectors
using TimeSeriesListDataSelectorsPtr =
    std::shared_ptr<TimeSeriesListDataSelectors>;

//! typedef for const type TimeSeriesListDataSelectors
using TimeSeriesListDataSelectorsConst = const TimeSeriesListDataSelectors;

//! typedef for const type TimeSeriesListDataSelectors
using TimeSeriesListDataSelectorsConstPtr =
    std::shared_ptr<TimeSeriesListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMESERIES_TIMESERIESLISTDATASELECTORS_H_