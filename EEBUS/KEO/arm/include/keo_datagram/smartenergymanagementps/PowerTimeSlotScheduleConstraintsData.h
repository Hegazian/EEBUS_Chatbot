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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULECONSTRAINTSDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULECONSTRAINTSDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerTimeSlotScheduleConstraintsData
 */
class PowerTimeSlotScheduleConstraintsData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  PowerTimeSlotScheduleConstraintsData();

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
  operator==(const PowerTimeSlotScheduleConstraintsData &c_classObject) const;

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
  operator!=(const PowerTimeSlotScheduleConstraintsData &c_classObject) const;

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
   * Set member SlotNumber.
   * @param c_slotNumber Value to set
   */
  void setSlotNumber(const xs_unsignedInt &c_slotNumber);

  /**
   * Returns const reference to member SlotNumber.
   * @return const reference to member slotNumber
   */
  const xs_unsignedInt &getSlotNumber() const;

  /**
   * Returns if member SlotNumber is set.
   * @retval true member SlotNumber is set
   * @retval false member SlotNumber is not set
   */
  bool getSlotNumberIsSet() const;

  /**
   * Unsets member SlotNumber
   */
  void cleanSlotNumber();

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
   * Set member MinDuration.
   * @param c_minDuration Value to set
   */
  void setMinDuration(const xs_duration &c_minDuration);

  /**
   * Returns const reference to member MinDuration.
   * @return const reference to member minDuration
   */
  const xs_duration &getMinDuration() const;

  /**
   * Returns if member MinDuration is set.
   * @retval true member MinDuration is set
   * @retval false member MinDuration is not set
   */
  bool getMinDurationIsSet() const;

  /**
   * Unsets member MinDuration
   */
  void cleanMinDuration();

  /**
   * Set member MaxDuration.
   * @param c_maxDuration Value to set
   */
  void setMaxDuration(const xs_duration &c_maxDuration);

  /**
   * Returns const reference to member MaxDuration.
   * @return const reference to member maxDuration
   */
  const xs_duration &getMaxDuration() const;

  /**
   * Returns if member MaxDuration is set.
   * @retval true member MaxDuration is set
   * @retval false member MaxDuration is not set
   */
  bool getMaxDurationIsSet() const;

  /**
   * Unsets member MaxDuration
   */
  void cleanMaxDuration();

  /**
   * Set member OptionalSlot.
   * @param c_optionalSlot Value to set
   */
  void setOptionalSlot(const xs_boolean &c_optionalSlot);

  /**
   * Returns const reference to member OptionalSlot.
   * @return const reference to member optionalSlot
   */
  const xs_boolean &getOptionalSlot() const;

  /**
   * Returns if member OptionalSlot is set.
   * @retval true member OptionalSlot is set
   * @retval false member OptionalSlot is not set
   */
  bool getOptionalSlotIsSet() const;

  /**
   * Unsets member OptionalSlot
   */
  void cleanOptionalSlot();

  /**
   * @copydoc CmdData::reduce()
   */
  PowerTimeSlotScheduleConstraintsData
  reduce(const PowerTimeSlotScheduleConstraintsDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_slotNumberIsSet;
  xs_unsignedInt m_slotNumber;

  bool m_earliestStartTimeIsSet;
  AbsoluteOrRelativeTime m_earliestStartTime;

  bool m_latestEndTimeIsSet;
  AbsoluteOrRelativeTime m_latestEndTime;

  bool m_minDurationIsSet;
  xs_duration m_minDuration;

  bool m_maxDurationIsSet;
  xs_duration m_maxDuration;

  bool m_optionalSlotIsSet;
  xs_boolean m_optionalSlot;
};

//! typedef for non-const smart pointer type
//! PowerTimeSlotScheduleConstraintsData
using PowerTimeSlotScheduleConstraintsDataPtr =
    std::shared_ptr<PowerTimeSlotScheduleConstraintsData>;

//! typedef for const type PowerTimeSlotScheduleConstraintsData
using PowerTimeSlotScheduleConstraintsDataConst =
    const PowerTimeSlotScheduleConstraintsData;

//! typedef for const type PowerTimeSlotScheduleConstraintsData
using PowerTimeSlotScheduleConstraintsDataConstPtr =
    std::shared_ptr<PowerTimeSlotScheduleConstraintsDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULECONSTRAINTSDATA_H_