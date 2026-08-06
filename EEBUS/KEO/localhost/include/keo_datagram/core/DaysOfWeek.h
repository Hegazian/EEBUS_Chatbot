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

#ifndef KEO_DATAGRAM_CORE_DAYSOFWEEK_H_
#define KEO_DATAGRAM_CORE_DAYSOFWEEK_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration DaysOfWeek
 */
class DaysOfWeek : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  DaysOfWeek();

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
  bool operator==(const DaysOfWeek &c_classObject) const;

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
  bool operator!=(const DaysOfWeek &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Monday.
   */
  void setMonday();

  /**
   * Returns if member Monday is set.
   * @retval true member Monday is set
   * @retval false member Monday is not set
   */
  bool getMondayIsSet() const;

  /**
   * Unsets member Monday
   */
  void cleanMonday();

  /**
   * Set member Tuesday.
   */
  void setTuesday();

  /**
   * Returns if member Tuesday is set.
   * @retval true member Tuesday is set
   * @retval false member Tuesday is not set
   */
  bool getTuesdayIsSet() const;

  /**
   * Unsets member Tuesday
   */
  void cleanTuesday();

  /**
   * Set member Wednesday.
   */
  void setWednesday();

  /**
   * Returns if member Wednesday is set.
   * @retval true member Wednesday is set
   * @retval false member Wednesday is not set
   */
  bool getWednesdayIsSet() const;

  /**
   * Unsets member Wednesday
   */
  void cleanWednesday();

  /**
   * Set member Thursday.
   */
  void setThursday();

  /**
   * Returns if member Thursday is set.
   * @retval true member Thursday is set
   * @retval false member Thursday is not set
   */
  bool getThursdayIsSet() const;

  /**
   * Unsets member Thursday
   */
  void cleanThursday();

  /**
   * Set member Friday.
   */
  void setFriday();

  /**
   * Returns if member Friday is set.
   * @retval true member Friday is set
   * @retval false member Friday is not set
   */
  bool getFridayIsSet() const;

  /**
   * Unsets member Friday
   */
  void cleanFriday();

  /**
   * Set member Saturday.
   */
  void setSaturday();

  /**
   * Returns if member Saturday is set.
   * @retval true member Saturday is set
   * @retval false member Saturday is not set
   */
  bool getSaturdayIsSet() const;

  /**
   * Unsets member Saturday
   */
  void cleanSaturday();

  /**
   * Set member Sunday.
   */
  void setSunday();

  /**
   * Returns if member Sunday is set.
   * @retval true member Sunday is set
   * @retval false member Sunday is not set
   */
  bool getSundayIsSet() const;

  /**
   * Unsets member Sunday
   */
  void cleanSunday();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_mondayIsSet;

  // ElementTag
  bool m_tuesdayIsSet;

  // ElementTag
  bool m_wednesdayIsSet;

  // ElementTag
  bool m_thursdayIsSet;

  // ElementTag
  bool m_fridayIsSet;

  // ElementTag
  bool m_saturdayIsSet;

  // ElementTag
  bool m_sundayIsSet;
};

//! typedef for non-const smart pointer type DaysOfWeek
using DaysOfWeekPtr = std::shared_ptr<DaysOfWeek>;

//! typedef for const type DaysOfWeek
using DaysOfWeekConst = const DaysOfWeek;

//! typedef for const type DaysOfWeek
using DaysOfWeekConstPtr = std::shared_ptr<DaysOfWeekConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_DAYSOFWEEK_H_