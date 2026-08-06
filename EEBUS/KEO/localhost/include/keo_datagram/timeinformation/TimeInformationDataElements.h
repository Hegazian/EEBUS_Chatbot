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

#ifndef KEO_DATAGRAM_TIMEINFORMATION_TIMEINFORMATIONDATAELEMENTS_H_
#define KEO_DATAGRAM_TIMEINFORMATION_TIMEINFORMATIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeInformation
 * @{
 */

/**
 * Declaration TimeInformationDataElements
 */
class TimeInformationDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TimeInformationDataElements();

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
  bool operator==(const TimeInformationDataElements &c_classObject) const;

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
  bool operator!=(const TimeInformationDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member Utc.
   */
  void setUtc();

  /**
   * Returns if member Utc is set.
   * @retval true member Utc is set
   * @retval false member Utc is not set
   */
  bool getUtcIsSet() const;

  /**
   * Unsets member Utc
   */
  void cleanUtc();

  /**
   * Set member UtcOffset.
   */
  void setUtcOffset();

  /**
   * Returns if member UtcOffset is set.
   * @retval true member UtcOffset is set
   * @retval false member UtcOffset is not set
   */
  bool getUtcOffsetIsSet() const;

  /**
   * Unsets member UtcOffset
   */
  void cleanUtcOffset();

  /**
   * Set member DayOfWeek.
   */
  void setDayOfWeek();

  /**
   * Returns if member DayOfWeek is set.
   * @retval true member DayOfWeek is set
   * @retval false member DayOfWeek is not set
   */
  bool getDayOfWeekIsSet() const;

  /**
   * Unsets member DayOfWeek
   */
  void cleanDayOfWeek();

  /**
   * Set member CalendarWeek.
   */
  void setCalendarWeek();

  /**
   * Returns if member CalendarWeek is set.
   * @retval true member CalendarWeek is set
   * @retval false member CalendarWeek is not set
   */
  bool getCalendarWeekIsSet() const;

  /**
   * Unsets member CalendarWeek
   */
  void cleanCalendarWeek();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_utcIsSet;

  // ElementTag
  bool m_utcOffsetIsSet;

  // ElementTag
  bool m_dayOfWeekIsSet;

  // ElementTag
  bool m_calendarWeekIsSet;
};

//! typedef for non-const smart pointer type TimeInformationDataElements
using TimeInformationDataElementsPtr =
    std::shared_ptr<TimeInformationDataElements>;

//! typedef for const type TimeInformationDataElements
using TimeInformationDataElementsConst = const TimeInformationDataElements;

//! typedef for const type TimeInformationDataElements
using TimeInformationDataElementsConstPtr =
    std::shared_ptr<TimeInformationDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMEINFORMATION_TIMEINFORMATIONDATAELEMENTS_H_