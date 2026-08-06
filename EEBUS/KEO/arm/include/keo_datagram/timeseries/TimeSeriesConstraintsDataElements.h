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

#ifndef KEO_DATAGRAM_TIMESERIES_TIMESERIESCONSTRAINTSDATAELEMENTS_H_
#define KEO_DATAGRAM_TIMESERIES_TIMESERIESCONSTRAINTSDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeSeries
 * @{
 */

/**
 * Declaration TimeSeriesConstraintsDataElements
 */
class TimeSeriesConstraintsDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TimeSeriesConstraintsDataElements();

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
  bool operator==(const TimeSeriesConstraintsDataElements &c_classObject) const;

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
  bool operator!=(const TimeSeriesConstraintsDataElements &c_classObject) const;

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
   * Set member SlotCountMin.
   */
  void setSlotCountMin();

  /**
   * Returns if member SlotCountMin is set.
   * @retval true member SlotCountMin is set
   * @retval false member SlotCountMin is not set
   */
  bool getSlotCountMinIsSet() const;

  /**
   * Unsets member SlotCountMin
   */
  void cleanSlotCountMin();

  /**
   * Set member SlotCountMax.
   */
  void setSlotCountMax();

  /**
   * Returns if member SlotCountMax is set.
   * @retval true member SlotCountMax is set
   * @retval false member SlotCountMax is not set
   */
  bool getSlotCountMaxIsSet() const;

  /**
   * Unsets member SlotCountMax
   */
  void cleanSlotCountMax();

  /**
   * Set member SlotDurationMin.
   */
  void setSlotDurationMin();

  /**
   * Returns if member SlotDurationMin is set.
   * @retval true member SlotDurationMin is set
   * @retval false member SlotDurationMin is not set
   */
  bool getSlotDurationMinIsSet() const;

  /**
   * Unsets member SlotDurationMin
   */
  void cleanSlotDurationMin();

  /**
   * Set member SlotDurationMax.
   */
  void setSlotDurationMax();

  /**
   * Returns if member SlotDurationMax is set.
   * @retval true member SlotDurationMax is set
   * @retval false member SlotDurationMax is not set
   */
  bool getSlotDurationMaxIsSet() const;

  /**
   * Unsets member SlotDurationMax
   */
  void cleanSlotDurationMax();

  /**
   * Set member SlotDurationStepSize.
   */
  void setSlotDurationStepSize();

  /**
   * Returns if member SlotDurationStepSize is set.
   * @retval true member SlotDurationStepSize is set
   * @retval false member SlotDurationStepSize is not set
   */
  bool getSlotDurationStepSizeIsSet() const;

  /**
   * Unsets member SlotDurationStepSize
   */
  void cleanSlotDurationStepSize();

  /**
   * Set member EarliestTimeSeriesStartTime.
   */
  void setEarliestTimeSeriesStartTime();

  /**
   * Returns if member EarliestTimeSeriesStartTime is set.
   * @retval true member EarliestTimeSeriesStartTime is set
   * @retval false member EarliestTimeSeriesStartTime is not set
   */
  bool getEarliestTimeSeriesStartTimeIsSet() const;

  /**
   * Unsets member EarliestTimeSeriesStartTime
   */
  void cleanEarliestTimeSeriesStartTime();

  /**
   * Set member LatestTimeSeriesEndTime.
   */
  void setLatestTimeSeriesEndTime();

  /**
   * Returns if member LatestTimeSeriesEndTime is set.
   * @retval true member LatestTimeSeriesEndTime is set
   * @retval false member LatestTimeSeriesEndTime is not set
   */
  bool getLatestTimeSeriesEndTimeIsSet() const;

  /**
   * Unsets member LatestTimeSeriesEndTime
   */
  void cleanLatestTimeSeriesEndTime();

  /**
   * Set member SlotValueMin.
   * @param c_slotValueMin Value to set
   */
  void setSlotValueMin(const ScaledNumberElements &c_slotValueMin);

  /**
   * Returns const reference to member SlotValueMin.
   * @return const reference to member slotValueMin
   */
  const ScaledNumberElements &getSlotValueMin() const;

  /**
   * Returns if member SlotValueMin is set.
   * @retval true member SlotValueMin is set
   * @retval false member SlotValueMin is not set
   */
  bool getSlotValueMinIsSet() const;

  /**
   * Unsets member SlotValueMin
   */
  void cleanSlotValueMin();

  /**
   * Set member SlotValueMax.
   * @param c_slotValueMax Value to set
   */
  void setSlotValueMax(const ScaledNumberElements &c_slotValueMax);

  /**
   * Returns const reference to member SlotValueMax.
   * @return const reference to member slotValueMax
   */
  const ScaledNumberElements &getSlotValueMax() const;

  /**
   * Returns if member SlotValueMax is set.
   * @retval true member SlotValueMax is set
   * @retval false member SlotValueMax is not set
   */
  bool getSlotValueMaxIsSet() const;

  /**
   * Unsets member SlotValueMax
   */
  void cleanSlotValueMax();

  /**
   * Set member SlotValueStepSize.
   * @param c_slotValueStepSize Value to set
   */
  void setSlotValueStepSize(const ScaledNumberElements &c_slotValueStepSize);

  /**
   * Returns const reference to member SlotValueStepSize.
   * @return const reference to member slotValueStepSize
   */
  const ScaledNumberElements &getSlotValueStepSize() const;

  /**
   * Returns if member SlotValueStepSize is set.
   * @retval true member SlotValueStepSize is set
   * @retval false member SlotValueStepSize is not set
   */
  bool getSlotValueStepSizeIsSet() const;

  /**
   * Unsets member SlotValueStepSize
   */
  void cleanSlotValueStepSize();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timeSeriesIdIsSet;

  // ElementTag
  bool m_slotCountMinIsSet;

  // ElementTag
  bool m_slotCountMaxIsSet;

  // ElementTag
  bool m_slotDurationMinIsSet;

  // ElementTag
  bool m_slotDurationMaxIsSet;

  // ElementTag
  bool m_slotDurationStepSizeIsSet;

  // ElementTag
  bool m_earliestTimeSeriesStartTimeIsSet;

  // ElementTag
  bool m_latestTimeSeriesEndTimeIsSet;

  bool m_slotValueMinIsSet;
  ScaledNumberElements m_slotValueMin;

  bool m_slotValueMaxIsSet;
  ScaledNumberElements m_slotValueMax;

  bool m_slotValueStepSizeIsSet;
  ScaledNumberElements m_slotValueStepSize;
};

//! typedef for non-const smart pointer type TimeSeriesConstraintsDataElements
using TimeSeriesConstraintsDataElementsPtr =
    std::shared_ptr<TimeSeriesConstraintsDataElements>;

//! typedef for const type TimeSeriesConstraintsDataElements
using TimeSeriesConstraintsDataElementsConst =
    const TimeSeriesConstraintsDataElements;

//! typedef for const type TimeSeriesConstraintsDataElements
using TimeSeriesConstraintsDataElementsConstPtr =
    std::shared_ptr<TimeSeriesConstraintsDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMESERIES_TIMESERIESCONSTRAINTSDATAELEMENTS_H_