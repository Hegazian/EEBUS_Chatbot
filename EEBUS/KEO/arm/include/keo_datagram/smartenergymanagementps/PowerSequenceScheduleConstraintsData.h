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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONSTRAINTSDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONSTRAINTSDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequenceScheduleConstraintsData
 */
class PowerSequenceScheduleConstraintsData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceScheduleConstraintsData();

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
  operator==(const PowerSequenceScheduleConstraintsData &c_classObject) const;

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
  operator!=(const PowerSequenceScheduleConstraintsData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member SequenceId.
   * @param c_sequenceId Value to set
   */
  void setSequenceId(const xs_unsignedInt &c_sequenceId);

  /**
   * Returns const reference to member SequenceId.
   * @return const reference to member sequenceId
   */
  const xs_unsignedInt &getSequenceId() const;

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
   * @param c_earliestStartTime Value to set
   */
  void setEarliestStartTime(const AbsoluteOrRelativeTime &c_earliestStartTime);

  /**
   * Returns const reference to member EarliestStartTime.
   * @return const reference to member earliestStartTime
   */
  const AbsoluteOrRelativeTime &getEarliestStartTime() const;

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
   * @param c_latestStartTime Value to set
   */
  void setLatestStartTime(const AbsoluteOrRelativeTime &c_latestStartTime);

  /**
   * Returns const reference to member LatestStartTime.
   * @return const reference to member latestStartTime
   */
  const AbsoluteOrRelativeTime &getLatestStartTime() const;

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
   * @param c_earliestEndTime Value to set
   */
  void setEarliestEndTime(const AbsoluteOrRelativeTime &c_earliestEndTime);

  /**
   * Returns const reference to member EarliestEndTime.
   * @return const reference to member earliestEndTime
   */
  const AbsoluteOrRelativeTime &getEarliestEndTime() const;

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
   * @param c_latestEndTime Value to set
   */
  void setLatestEndTime(const AbsoluteOrRelativeTime &c_latestEndTime);

  /**
   * Returns const reference to member LatestEndTime.
   * @return const reference to member latestEndTime
   */
  const AbsoluteOrRelativeTime &getLatestEndTime() const;

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
   * @param c_optionalSequence Value to set
   */
  void setOptionalSequence(const xs_boolean &c_optionalSequence);

  /**
   * Returns const reference to member OptionalSequence.
   * @return const reference to member optionalSequence
   */
  const xs_boolean &getOptionalSequence() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  PowerSequenceScheduleConstraintsData
  reduce(const PowerSequenceScheduleConstraintsDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_earliestStartTimeIsSet;
  AbsoluteOrRelativeTime m_earliestStartTime;

  bool m_latestStartTimeIsSet;
  AbsoluteOrRelativeTime m_latestStartTime;

  bool m_earliestEndTimeIsSet;
  AbsoluteOrRelativeTime m_earliestEndTime;

  bool m_latestEndTimeIsSet;
  AbsoluteOrRelativeTime m_latestEndTime;

  bool m_optionalSequenceIsSet;
  xs_boolean m_optionalSequence;
};

//! typedef for non-const smart pointer type
//! PowerSequenceScheduleConstraintsData
using PowerSequenceScheduleConstraintsDataPtr =
    std::shared_ptr<PowerSequenceScheduleConstraintsData>;

//! typedef for const type PowerSequenceScheduleConstraintsData
using PowerSequenceScheduleConstraintsDataConst =
    const PowerSequenceScheduleConstraintsData;

//! typedef for const type PowerSequenceScheduleConstraintsData
using PowerSequenceScheduleConstraintsDataConstPtr =
    std::shared_ptr<PowerSequenceScheduleConstraintsDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONSTRAINTSDATA_H_