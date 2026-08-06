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

#ifndef KEO_DATAGRAM_TIMETABLE_TIMETABLEDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_TIMETABLE_TIMETABLEDESCRIPTIONDATAELEMENTS_H_

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
 * Declaration TimeTableDescriptionDataElements
 */
class TimeTableDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TimeTableDescriptionDataElements();

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
  bool operator==(const TimeTableDescriptionDataElements &c_classObject) const;

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
  bool operator!=(const TimeTableDescriptionDataElements &c_classObject) const;

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
   * Set member TimeSlotCountChangeable.
   */
  void setTimeSlotCountChangeable();

  /**
   * Returns if member TimeSlotCountChangeable is set.
   * @retval true member TimeSlotCountChangeable is set
   * @retval false member TimeSlotCountChangeable is not set
   */
  bool getTimeSlotCountChangeableIsSet() const;

  /**
   * Unsets member TimeSlotCountChangeable
   */
  void cleanTimeSlotCountChangeable();

  /**
   * Set member TimeSlotTimesChangeable.
   */
  void setTimeSlotTimesChangeable();

  /**
   * Returns if member TimeSlotTimesChangeable is set.
   * @retval true member TimeSlotTimesChangeable is set
   * @retval false member TimeSlotTimesChangeable is not set
   */
  bool getTimeSlotTimesChangeableIsSet() const;

  /**
   * Unsets member TimeSlotTimesChangeable
   */
  void cleanTimeSlotTimesChangeable();

  /**
   * Set member TimeSlotTimeMode.
   */
  void setTimeSlotTimeMode();

  /**
   * Returns if member TimeSlotTimeMode is set.
   * @retval true member TimeSlotTimeMode is set
   * @retval false member TimeSlotTimeMode is not set
   */
  bool getTimeSlotTimeModeIsSet() const;

  /**
   * Unsets member TimeSlotTimeMode
   */
  void cleanTimeSlotTimeMode();

  /**
   * Set member Label.
   */
  void setLabel();

  /**
   * Returns if member Label is set.
   * @retval true member Label is set
   * @retval false member Label is not set
   */
  bool getLabelIsSet() const;

  /**
   * Unsets member Label
   */
  void cleanLabel();

  /**
   * Set member Description.
   */
  void setDescription();

  /**
   * Returns if member Description is set.
   * @retval true member Description is set
   * @retval false member Description is not set
   */
  bool getDescriptionIsSet() const;

  /**
   * Unsets member Description
   */
  void cleanDescription();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timeTableIdIsSet;

  // ElementTag
  bool m_timeSlotCountChangeableIsSet;

  // ElementTag
  bool m_timeSlotTimesChangeableIsSet;

  // ElementTag
  bool m_timeSlotTimeModeIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type TimeTableDescriptionDataElements
using TimeTableDescriptionDataElementsPtr =
    std::shared_ptr<TimeTableDescriptionDataElements>;

//! typedef for const type TimeTableDescriptionDataElements
using TimeTableDescriptionDataElementsConst =
    const TimeTableDescriptionDataElements;

//! typedef for const type TimeTableDescriptionDataElements
using TimeTableDescriptionDataElementsConstPtr =
    std::shared_ptr<TimeTableDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMETABLE_TIMETABLEDESCRIPTIONDATAELEMENTS_H_