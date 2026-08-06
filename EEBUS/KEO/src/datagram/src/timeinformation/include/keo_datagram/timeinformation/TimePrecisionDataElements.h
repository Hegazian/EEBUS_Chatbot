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

#ifndef KEO_DATAGRAM_TIMEINFORMATION_TIMEPRECISIONDATAELEMENTS_H_
#define KEO_DATAGRAM_TIMEINFORMATION_TIMEPRECISIONDATAELEMENTS_H_

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
 * Declaration TimePrecisionDataElements
 */
class TimePrecisionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TimePrecisionDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_isSynchronisedIsSet the member to set
   * @param c_lastSyncAtIsSet the member to set
   * @param c_clockDriftIsSet the member to set
   */
  TimePrecisionDataElements(xs_boolean c_isSynchronisedIsSet,
                            xs_boolean c_lastSyncAtIsSet,
                            xs_boolean c_clockDriftIsSet);

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
  bool operator==(const TimePrecisionDataElements &c_classObject) const;

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
  bool operator!=(const TimePrecisionDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member IsSynchronised.
   */
  void setIsSynchronised();

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
   */
  void setLastSyncAt();

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
   */
  void setClockDrift();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_isSynchronisedIsSet;

  // ElementTag
  bool m_lastSyncAtIsSet;

  // ElementTag
  bool m_clockDriftIsSet;
};

//! typedef for non-const smart pointer type TimePrecisionDataElements
using TimePrecisionDataElementsPtr = std::shared_ptr<TimePrecisionDataElements>;

//! typedef for const type TimePrecisionDataElements
using TimePrecisionDataElementsConst = const TimePrecisionDataElements;

//! typedef for const type TimePrecisionDataElements
using TimePrecisionDataElementsConstPtr =
    std::shared_ptr<TimePrecisionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMEINFORMATION_TIMEPRECISIONDATAELEMENTS_H_