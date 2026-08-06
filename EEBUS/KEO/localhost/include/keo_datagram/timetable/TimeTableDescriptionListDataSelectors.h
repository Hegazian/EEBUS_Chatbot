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

#ifndef KEO_DATAGRAM_TIMETABLE_TIMETABLEDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_TIMETABLE_TIMETABLEDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/timetable/TimeTableDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeTable
 * @{
 */

/**
 * Declaration TimeTableDescriptionListDataSelectors
 */
class TimeTableDescriptionListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  TimeTableDescriptionListDataSelectors();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_timeTableId the member to set
   */
  explicit TimeTableDescriptionListDataSelectors(
      const xs_unsignedInt &c_timeTableId);

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
  operator==(const TimeTableDescriptionListDataSelectors &c_classObject) const;

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
  operator!=(const TimeTableDescriptionListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

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
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const TimeTableDescriptionData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timeTableIdIsSet;
  xs_unsignedInt m_timeTableId;
};

//! typedef for non-const smart pointer type
//! TimeTableDescriptionListDataSelectors
using TimeTableDescriptionListDataSelectorsPtr =
    std::shared_ptr<TimeTableDescriptionListDataSelectors>;

//! typedef for const type TimeTableDescriptionListDataSelectors
using TimeTableDescriptionListDataSelectorsConst =
    const TimeTableDescriptionListDataSelectors;

//! typedef for const type TimeTableDescriptionListDataSelectors
using TimeTableDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<TimeTableDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMETABLE_TIMETABLEDESCRIPTIONLISTDATASELECTORS_H_