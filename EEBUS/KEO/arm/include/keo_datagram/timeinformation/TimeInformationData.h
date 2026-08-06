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

#ifndef KEO_DATAGRAM_TIMEINFORMATION_TIMEINFORMATIONDATA_H_
#define KEO_DATAGRAM_TIMEINFORMATION_TIMEINFORMATIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/DayOfWeek.h>
#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeInformation
 * @{
 */

/**
 * Declaration TimeInformationData
 */
class TimeInformationData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  TimeInformationData();

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
  bool operator==(const TimeInformationData &c_classObject) const;

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
  bool operator!=(const TimeInformationData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member Utc.
   * @param c_utc Value to set
   */
  void setUtc(const xs_dateTime &c_utc);

  /**
   * Returns const reference to member Utc.
   * @return const reference to member utc
   */
  const xs_dateTime &getUtc() const;

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
   * @param c_utcOffset Value to set
   */
  void setUtcOffset(const xs_duration &c_utcOffset);

  /**
   * Returns const reference to member UtcOffset.
   * @return const reference to member utcOffset
   */
  const xs_duration &getUtcOffset() const;

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
   * @param c_dayOfWeek Value to set
   */
  void setDayOfWeek(const DayOfWeek &c_dayOfWeek);

  /**
   * Returns const reference to member DayOfWeek.
   * @return const reference to member dayOfWeek
   */
  const DayOfWeek &getDayOfWeek() const;

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
   * @param c_calendarWeek Value to set
   */
  void setCalendarWeek(const xs_unsignedByte &c_calendarWeek);

  /**
   * Returns const reference to member CalendarWeek.
   * @return const reference to member calendarWeek
   */
  const xs_unsignedByte &getCalendarWeek() const;

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

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_utcIsSet;
  xs_dateTime m_utc;

  bool m_utcOffsetIsSet;
  xs_duration m_utcOffset;

  bool m_dayOfWeekIsSet;
  DayOfWeek m_dayOfWeek;

  bool m_calendarWeekIsSet;
  xs_unsignedByte m_calendarWeek;
};

//! typedef for non-const smart pointer type TimeInformationData
using TimeInformationDataPtr = std::shared_ptr<TimeInformationData>;

//! typedef for const type TimeInformationData
using TimeInformationDataConst = const TimeInformationData;

//! typedef for const type TimeInformationData
using TimeInformationDataConstPtr = std::shared_ptr<TimeInformationDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMEINFORMATION_TIMEINFORMATIONDATA_H_