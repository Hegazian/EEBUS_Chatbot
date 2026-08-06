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

#ifndef KEO_DATAGRAM_TIMEINFORMATION_TIMEPRECISIONDATA_H_
#define KEO_DATAGRAM_TIMEINFORMATION_TIMEPRECISIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeInformation
 * @{
 */

/**
 * Declaration TimePrecisionData
 */
class TimePrecisionData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  TimePrecisionData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_isSynchronised the member to set
   * @param c_lastSyncAt the member to set
   * @param c_clockDrift the member to set
   */
  TimePrecisionData(const xs_boolean &c_isSynchronised,
                    const xs_dateTime &c_lastSyncAt,
                    const xs_integer &c_clockDrift);

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
  bool operator==(const TimePrecisionData &c_classObject) const;

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
  bool operator!=(const TimePrecisionData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member IsSynchronised.
   * @param c_isSynchronised Value to set
   */
  void setIsSynchronised(const xs_boolean &c_isSynchronised);

  /**
   * Returns const reference to member IsSynchronised.
   * @return const reference to member isSynchronised
   */
  const xs_boolean &getIsSynchronised() const;

  /**
   * Returns if member IsSynchronised is set.
   * @retval true member IsSynchronised is set
   * @retval false member IsSynchronised is not set
   */
  bool getIsSynchronisedIsSet() const;

  /**
   * Unsets member IsSynchronised
   */
  void cleanIsSynchronised();

  /**
   * Set member LastSyncAt.
   * @param c_lastSyncAt Value to set
   */
  void setLastSyncAt(const xs_dateTime &c_lastSyncAt);

  /**
   * Returns const reference to member LastSyncAt.
   * @return const reference to member lastSyncAt
   */
  const xs_dateTime &getLastSyncAt() const;

  /**
   * Returns if member LastSyncAt is set.
   * @retval true member LastSyncAt is set
   * @retval false member LastSyncAt is not set
   */
  bool getLastSyncAtIsSet() const;

  /**
   * Unsets member LastSyncAt
   */
  void cleanLastSyncAt();

  /**
   * Set member ClockDrift.
   * @param c_clockDrift Value to set
   */
  void setClockDrift(const xs_integer &c_clockDrift);

  /**
   * Returns const reference to member ClockDrift.
   * @return const reference to member clockDrift
   */
  const xs_integer &getClockDrift() const;

  /**
   * Returns if member ClockDrift is set.
   * @retval true member ClockDrift is set
   * @retval false member ClockDrift is not set
   */
  bool getClockDriftIsSet() const;

  /**
   * Unsets member ClockDrift
   */
  void cleanClockDrift();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_isSynchronisedIsSet;
  xs_boolean m_isSynchronised;

  bool m_lastSyncAtIsSet;
  xs_dateTime m_lastSyncAt;

  bool m_clockDriftIsSet;
  xs_integer m_clockDrift;
};

//! typedef for non-const smart pointer type TimePrecisionData
using TimePrecisionDataPtr = std::shared_ptr<TimePrecisionData>;

//! typedef for const type TimePrecisionData
using TimePrecisionDataConst = const TimePrecisionData;

//! typedef for const type TimePrecisionData
using TimePrecisionDataConstPtr = std::shared_ptr<TimePrecisionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMEINFORMATION_TIMEPRECISIONDATA_H_