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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULEDATAELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequenceScheduleDataElements
 */
class PowerSequenceScheduleDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceScheduleDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_sequenceIdIsSet the member to set
   * @param c_startTimeIsSet the member to set
   * @param c_endTimeIsSet the member to set
   */
  PowerSequenceScheduleDataElements(xs_boolean c_sequenceIdIsSet,
                                    xs_boolean c_startTimeIsSet,
                                    xs_boolean c_endTimeIsSet);

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
  bool operator==(const PowerSequenceScheduleDataElements &c_classObject) const;

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
  bool operator!=(const PowerSequenceScheduleDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member SequenceId.
   */
  void setSequenceId();

  /**
   * Returns if member SequenceId is set.
   * @retval true member SequenceId is set
   * @retval false member SequenceId is not set
   */
  bool getSequenceIdIsSet() const;

  /**
   * Unsets member SequenceId
   */
  void cleanSequenceId();

  /**
   * Set member StartTime.
   */
  void setStartTime();

  /**
   * Returns if member StartTime is set.
   * @retval true member StartTime is set
   * @retval false member StartTime is not set
   */
  bool getStartTimeIsSet() const;

  /**
   * Unsets member StartTime
   */
  void cleanStartTime();

  /**
   * Set member EndTime.
   */
  void setEndTime();

  /**
   * Returns if member EndTime is set.
   * @retval true member EndTime is set
   * @retval false member EndTime is not set
   */
  bool getEndTimeIsSet() const;

  /**
   * Unsets member EndTime
   */
  void cleanEndTime();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  // ElementTag
  bool m_startTimeIsSet;

  // ElementTag
  bool m_endTimeIsSet;
};

//! typedef for non-const smart pointer type PowerSequenceScheduleDataElements
using PowerSequenceScheduleDataElementsPtr =
    std::shared_ptr<PowerSequenceScheduleDataElements>;

//! typedef for const type PowerSequenceScheduleDataElements
using PowerSequenceScheduleDataElementsConst =
    const PowerSequenceScheduleDataElements;

//! typedef for const type PowerSequenceScheduleDataElements
using PowerSequenceScheduleDataElementsConstPtr =
    std::shared_ptr<PowerSequenceScheduleDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULEDATAELEMENTS_H_