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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONSTRAINTSDATAELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONSTRAINTSDATAELEMENTS_H_

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
 * Declaration PowerSequenceScheduleConstraintsDataElements
 */
class PowerSequenceScheduleConstraintsDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceScheduleConstraintsDataElements();

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
  bool operator==(
      const PowerSequenceScheduleConstraintsDataElements &c_classObject) const;

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
  bool operator!=(
      const PowerSequenceScheduleConstraintsDataElements &c_classObject) const;

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
   * Set member EarliestStartTime.
   */
  void setEarliestStartTime();

  /**
   * Returns if member EarliestStartTime is set.
   * @retval true member EarliestStartTime is set
   * @retval false member EarliestStartTime is not set
   */
  bool getEarliestStartTimeIsSet() const;

  /**
   * Unsets member EarliestStartTime
   */
  void cleanEarliestStartTime();

  /**
   * Set member LatestStartTime.
   */
  void setLatestStartTime();

  /**
   * Returns if member LatestStartTime is set.
   * @retval true member LatestStartTime is set
   * @retval false member LatestStartTime is not set
   */
  bool getLatestStartTimeIsSet() const;

  /**
   * Unsets member LatestStartTime
   */
  void cleanLatestStartTime();

  /**
   * Set member EarliestEndTime.
   */
  void setEarliestEndTime();

  /**
   * Returns if member EarliestEndTime is set.
   * @retval true member EarliestEndTime is set
   * @retval false member EarliestEndTime is not set
   */
  bool getEarliestEndTimeIsSet() const;

  /**
   * Unsets member EarliestEndTime
   */
  void cleanEarliestEndTime();

  /**
   * Set member LatestEndTime.
   */
  void setLatestEndTime();

  /**
   * Returns if member LatestEndTime is set.
   * @retval true member LatestEndTime is set
   * @retval false member LatestEndTime is not set
   */
  bool getLatestEndTimeIsSet() const;

  /**
   * Unsets member LatestEndTime
   */
  void cleanLatestEndTime();

  /**
   * Set member OptionalSequence.
   */
  void setOptionalSequence();

  /**
   * Returns if member OptionalSequence is set.
   * @retval true member OptionalSequence is set
   * @retval false member OptionalSequence is not set
   */
  bool getOptionalSequenceIsSet() const;

  /**
   * Unsets member OptionalSequence
   */
  void cleanOptionalSequence();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  // ElementTag
  bool m_earliestStartTimeIsSet;

  // ElementTag
  bool m_latestStartTimeIsSet;

  // ElementTag
  bool m_earliestEndTimeIsSet;

  // ElementTag
  bool m_latestEndTimeIsSet;

  // ElementTag
  bool m_optionalSequenceIsSet;
};

//! typedef for non-const smart pointer type
//! PowerSequenceScheduleConstraintsDataElements
using PowerSequenceScheduleConstraintsDataElementsPtr =
    std::shared_ptr<PowerSequenceScheduleConstraintsDataElements>;

//! typedef for const type PowerSequenceScheduleConstraintsDataElements
using PowerSequenceScheduleConstraintsDataElementsConst =
    const PowerSequenceScheduleConstraintsDataElements;

//! typedef for const type PowerSequenceScheduleConstraintsDataElements
using PowerSequenceScheduleConstraintsDataElementsConstPtr =
    std::shared_ptr<PowerSequenceScheduleConstraintsDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONSTRAINTSDATAELEMENTS_H_