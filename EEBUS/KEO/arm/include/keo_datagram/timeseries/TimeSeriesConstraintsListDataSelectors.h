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

#ifndef KEO_DATAGRAM_TIMESERIES_TIMESERIESCONSTRAINTSLISTDATASELECTORS_H_
#define KEO_DATAGRAM_TIMESERIES_TIMESERIESCONSTRAINTSLISTDATASELECTORS_H_

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
 * Declaration TimeSeriesConstraintsListDataSelectors
 */
class TimeSeriesConstraintsListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  TimeSeriesConstraintsListDataSelectors();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_timeSeriesId the member to set
   */
  explicit TimeSeriesConstraintsListDataSelectors(
      const xs_unsignedInt &c_timeSeriesId);

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
  bool
  operator==(const TimeSeriesConstraintsListDataSelectors &c_classObject) const;

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
  bool
  operator!=(const TimeSeriesConstraintsListDataSelectors &c_classObject) const;

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timeSeriesIdIsSet;
  xs_unsignedInt m_timeSeriesId;
};

//! typedef for non-const smart pointer type
//! TimeSeriesConstraintsListDataSelectors
using TimeSeriesConstraintsListDataSelectorsPtr =
    std::shared_ptr<TimeSeriesConstraintsListDataSelectors>;

//! typedef for const type TimeSeriesConstraintsListDataSelectors
using TimeSeriesConstraintsListDataSelectorsConst =
    const TimeSeriesConstraintsListDataSelectors;

//! typedef for const type TimeSeriesConstraintsListDataSelectors
using TimeSeriesConstraintsListDataSelectorsConstPtr =
    std::shared_ptr<TimeSeriesConstraintsListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMESERIES_TIMESERIESCONSTRAINTSLISTDATASELECTORS_H_