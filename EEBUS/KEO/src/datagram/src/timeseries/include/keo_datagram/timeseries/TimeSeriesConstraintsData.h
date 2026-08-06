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

#ifndef KEO_DATAGRAM_TIMESERIES_TIMESERIESCONSTRAINTSDATA_H_
#define KEO_DATAGRAM_TIMESERIES_TIMESERIESCONSTRAINTSDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeSeries
 * @{
 */

/**
 * Declaration TimeSeriesConstraintsData
 */
class TimeSeriesConstraintsData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TimeSeriesConstraintsData();

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
  bool operator==(const TimeSeriesConstraintsData &c_classObject) const;

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
  bool operator!=(const TimeSeriesConstraintsData &c_classObject) const;

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
   * Set member SlotCountMin.
   * @param c_slotCountMin Value to set
   */
  void setSlotCountMin(const xs_unsignedInt &c_slotCountMin);

  /**
   * Returns const reference to member SlotCountMin.
   * @return const reference to member slotCountMin
   */
  const xs_unsignedInt &getSlotCountMin() const;

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
   * @param c_slotCountMax Value to set
   */
  void setSlotCountMax(const xs_unsignedInt &c_slotCountMax);

  /**
   * Returns const reference to member SlotCountMax.
   * @return const reference to member slotCountMax
   */
  const xs_unsignedInt &getSlotCountMax() const;

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
   * @param c_slotDurationMin Value to set
   */
  void setSlotDurationMin(const xs_duration &c_slotDurationMin);

  /**
   * Returns const reference to member SlotDurationMin.
   * @return const reference to member slotDurationMin
   */
  const xs_duration &getSlotDurationMin() const;

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
   * @param c_slotDurationMax Value to set
   */
  void setSlotDurationMax(const xs_duration &c_slotDurationMax);

  /**
   * Returns const reference to member SlotDurationMax.
   * @return const reference to member slotDurationMax
   */
  const xs_duration &getSlotDurationMax() const;

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
   * @param c_slotDurationStepSize Value to set
   */
  void setSlotDurationStepSize(const xs_duration &c_slotDurationStepSize);

  /**
   * Returns const reference to member SlotDurationStepSize.
   * @return const reference to member slotDurationStepSize
   */
  const xs_duration &getSlotDurationStepSize() const;

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
   * @param c_earliestTimeSeriesStartTime Value to set
   */
  void setEarliestTimeSeriesStartTime(
      const AbsoluteOrRelativeTime &c_earliestTimeSeriesStartTime);

  /**
   * Returns const reference to member EarliestTimeSeriesStartTime.
   * @return const reference to member earliestTimeSeriesStartTime
   */
  const AbsoluteOrRelativeTime &getEarliestTimeSeriesStartTime() const;

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
   * @param c_latestTimeSeriesEndTime Value to set
   */
  void setLatestTimeSeriesEndTime(
      const AbsoluteOrRelativeTime &c_latestTimeSeriesEndTime);

  /**
   * Returns const reference to member LatestTimeSeriesEndTime.
   * @return const reference to member latestTimeSeriesEndTime
   */
  const AbsoluteOrRelativeTime &getLatestTimeSeriesEndTime() const;

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
  void setSlotValueMin(const ScaledNumber &c_slotValueMin);

  /**
   * Returns const reference to member SlotValueMin.
   * @return const reference to member slotValueMin
   */
  const ScaledNumber &getSlotValueMin() const;

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
  void setSlotValueMax(const ScaledNumber &c_slotValueMax);

  /**
   * Returns const reference to member SlotValueMax.
   * @return const reference to member slotValueMax
   */
  const ScaledNumber &getSlotValueMax() const;

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
  void setSlotValueStepSize(const ScaledNumber &c_slotValueStepSize);

  /**
   * Returns const reference to member SlotValueStepSize.
   * @return const reference to member slotValueStepSize
   */
  const ScaledNumber &getSlotValueStepSize() const;

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

  bool m_timeSeriesIdIsSet;
  xs_unsignedInt m_timeSeriesId;

  bool m_slotCountMinIsSet;
  xs_unsignedInt m_slotCountMin;

  bool m_slotCountMaxIsSet;
  xs_unsignedInt m_slotCountMax;

  bool m_slotDurationMinIsSet;
  xs_duration m_slotDurationMin;

  bool m_slotDurationMaxIsSet;
  xs_duration m_slotDurationMax;

  bool m_slotDurationStepSizeIsSet;
  xs_duration m_slotDurationStepSize;

  bool m_earliestTimeSeriesStartTimeIsSet;
  AbsoluteOrRelativeTime m_earliestTimeSeriesStartTime;

  bool m_latestTimeSeriesEndTimeIsSet;
  AbsoluteOrRelativeTime m_latestTimeSeriesEndTime;

  bool m_slotValueMinIsSet;
  ScaledNumber m_slotValueMin;

  bool m_slotValueMaxIsSet;
  ScaledNumber m_slotValueMax;

  bool m_slotValueStepSizeIsSet;
  ScaledNumber m_slotValueStepSize;
};

//! typedef for non-const smart pointer type TimeSeriesConstraintsData
using TimeSeriesConstraintsDataPtr = std::shared_ptr<TimeSeriesConstraintsData>;

//! typedef for const type TimeSeriesConstraintsData
using TimeSeriesConstraintsDataConst = const TimeSeriesConstraintsData;

//! typedef for const type TimeSeriesConstraintsData
using TimeSeriesConstraintsDataConstPtr =
    std::shared_ptr<TimeSeriesConstraintsDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMESERIES_TIMESERIESCONSTRAINTSDATA_H_