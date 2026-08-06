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

#ifndef KEO_DATAGRAM_TIMETABLE_TIMETABLECONSTRAINTSDATA_H_
#define KEO_DATAGRAM_TIMETABLE_TIMETABLECONSTRAINTSDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/KeoTime.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/timetable/TimeTableConstraintsDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeTable
 * @{
 */

/**
 * Declaration TimeTableConstraintsData
 */
class TimeTableConstraintsData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TimeTableConstraintsData();

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
  bool operator==(const TimeTableConstraintsData &c_classObject) const;

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
  bool operator!=(const TimeTableConstraintsData &c_classObject) const;

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
   * Set member SlotShiftStepSize.
   * @param c_slotShiftStepSize Value to set
   */
  void setSlotShiftStepSize(const xs_duration &c_slotShiftStepSize);

  /**
   * Returns const reference to member SlotShiftStepSize.
   * @return const reference to member slotShiftStepSize
   */
  const xs_duration &getSlotShiftStepSize() const;

  /**
   * Returns if member SlotShiftStepSize is set.
   * @retval true member SlotShiftStepSize is set
   * @retval false member SlotShiftStepSize is not set
   */
  bool getSlotShiftStepSizeIsSet() const;

  /**
   * Unsets member SlotShiftStepSize
   */
  void cleanSlotShiftStepSize();

  /**
   * Set member FirstSlotBeginsAt.
   * @param c_firstSlotBeginsAt Value to set
   */
  void setFirstSlotBeginsAt(const xs_time &c_firstSlotBeginsAt);

  /**
   * Returns const reference to member FirstSlotBeginsAt.
   * @return const reference to member firstSlotBeginsAt
   */
  const xs_time &getFirstSlotBeginsAt() const;

  /**
   * Returns if member FirstSlotBeginsAt is set.
   * @retval true member FirstSlotBeginsAt is set
   * @retval false member FirstSlotBeginsAt is not set
   */
  bool getFirstSlotBeginsAtIsSet() const;

  /**
   * Unsets member FirstSlotBeginsAt
   */
  void cleanFirstSlotBeginsAt();

  /**
   * @copydoc CmdData::reduce()
   */
  TimeTableConstraintsData
  reduce(const TimeTableConstraintsDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timeTableIdIsSet;
  xs_unsignedInt m_timeTableId;

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

  bool m_slotShiftStepSizeIsSet;
  xs_duration m_slotShiftStepSize;

  bool m_firstSlotBeginsAtIsSet;
  xs_time m_firstSlotBeginsAt;
};

//! typedef for non-const smart pointer type TimeTableConstraintsData
using TimeTableConstraintsDataPtr = std::shared_ptr<TimeTableConstraintsData>;

//! typedef for const type TimeTableConstraintsData
using TimeTableConstraintsDataConst = const TimeTableConstraintsData;

//! typedef for const type TimeTableConstraintsData
using TimeTableConstraintsDataConstPtr =
    std::shared_ptr<TimeTableConstraintsDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMETABLE_TIMETABLECONSTRAINTSDATA_H_