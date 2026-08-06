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

#ifndef KEO_DATAGRAM_TIMETABLE_TIMETABLEDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_TIMETABLE_TIMETABLEDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/timetable/TimeSlotTimeMode.h>
#include <keo_datagram/timetable/TimeTableDescriptionDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeTable
 * @{
 */

/**
 * Declaration TimeTableDescriptionData
 */
class TimeTableDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TimeTableDescriptionData();

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
  bool operator==(const TimeTableDescriptionData &c_classObject) const;

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
  bool operator!=(const TimeTableDescriptionData &c_classObject) const;

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
   * Set member TimeSlotCountChangeable.
   * @param c_timeSlotCountChangeable Value to set
   */
  void setTimeSlotCountChangeable(const xs_boolean &c_timeSlotCountChangeable);

  /**
   * Returns const reference to member TimeSlotCountChangeable.
   * @return const reference to member timeSlotCountChangeable
   */
  const xs_boolean &getTimeSlotCountChangeable() const;

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
   * @param c_timeSlotTimesChangeable Value to set
   */
  void setTimeSlotTimesChangeable(const xs_boolean &c_timeSlotTimesChangeable);

  /**
   * Returns const reference to member TimeSlotTimesChangeable.
   * @return const reference to member timeSlotTimesChangeable
   */
  const xs_boolean &getTimeSlotTimesChangeable() const;

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
   * @param c_timeSlotTimeMode Value to set
   */
  void setTimeSlotTimeMode(const TimeSlotTimeMode &c_timeSlotTimeMode);

  /**
   * Returns const reference to member TimeSlotTimeMode.
   * @return const reference to member timeSlotTimeMode
   */
  const TimeSlotTimeMode &getTimeSlotTimeMode() const;

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
   * @param c_label Value to set
   */
  void setLabel(const xs_string &c_label);

  /**
   * Returns const reference to member Label.
   * @return const reference to member label
   */
  const xs_string &getLabel() const;

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
   * @param c_description Value to set
   */
  void setDescription(const xs_string &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const xs_string &getDescription() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  TimeTableDescriptionData
  reduce(const TimeTableDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timeTableIdIsSet;
  xs_unsignedInt m_timeTableId;

  bool m_timeSlotCountChangeableIsSet;
  xs_boolean m_timeSlotCountChangeable;

  bool m_timeSlotTimesChangeableIsSet;
  xs_boolean m_timeSlotTimesChangeable;

  bool m_timeSlotTimeModeIsSet;
  TimeSlotTimeMode m_timeSlotTimeMode;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type TimeTableDescriptionData
using TimeTableDescriptionDataPtr = std::shared_ptr<TimeTableDescriptionData>;

//! typedef for const type TimeTableDescriptionData
using TimeTableDescriptionDataConst = const TimeTableDescriptionData;

//! typedef for const type TimeTableDescriptionData
using TimeTableDescriptionDataConstPtr =
    std::shared_ptr<TimeTableDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMETABLE_TIMETABLEDESCRIPTIONDATA_H_