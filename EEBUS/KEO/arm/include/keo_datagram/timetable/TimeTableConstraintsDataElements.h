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

#ifndef KEO_DATAGRAM_TIMETABLE_TIMETABLECONSTRAINTSDATAELEMENTS_H_
#define KEO_DATAGRAM_TIMETABLE_TIMETABLECONSTRAINTSDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeTable
 * @{
 */

/**
 * Declaration TimeTableConstraintsDataElements
 */
class TimeTableConstraintsDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TimeTableConstraintsDataElements();

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
  bool operator==(const TimeTableConstraintsDataElements &c_classObject) const;

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
  bool operator!=(const TimeTableConstraintsDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member TimeTableId.
   */
  void setTimeTableId();

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
   * Set member SlotShiftStepSize.
   */
  void setSlotShiftStepSize();

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
   */
  void setFirstSlotBeginsAt();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timeTableIdIsSet;

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
  bool m_slotShiftStepSizeIsSet;

  // ElementTag
  bool m_firstSlotBeginsAtIsSet;
};

//! typedef for non-const smart pointer type TimeTableConstraintsDataElements
using TimeTableConstraintsDataElementsPtr =
    std::shared_ptr<TimeTableConstraintsDataElements>;

//! typedef for const type TimeTableConstraintsDataElements
using TimeTableConstraintsDataElementsConst =
    const TimeTableConstraintsDataElements;

//! typedef for const type TimeTableConstraintsDataElements
using TimeTableConstraintsDataElementsConstPtr =
    std::shared_ptr<TimeTableConstraintsDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMETABLE_TIMETABLECONSTRAINTSDATAELEMENTS_H_