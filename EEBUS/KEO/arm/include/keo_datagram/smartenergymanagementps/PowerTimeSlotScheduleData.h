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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULEDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/TimePeriod.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerTimeSlotScheduleData
 */
class PowerTimeSlotScheduleData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  PowerTimeSlotScheduleData();

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
  bool operator==(const PowerTimeSlotScheduleData &c_classObject) const;

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
  bool operator!=(const PowerTimeSlotScheduleData &c_classObject) const;

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
   * Set member TimePeriod.
   * @param c_timePeriod Value to set
   */
  void setTimePeriod(const TimePeriod &c_timePeriod);

  /**
   * Returns const reference to member TimePeriod.
   * @return const reference to member timePeriod
   */
  const TimePeriod &getTimePeriod() const;

  /**
   * Returns if member TimePeriod is set.
   * @retval true member TimePeriod is set
   * @retval false member TimePeriod is not set
   */
  bool getTimePeriodIsSet() const;

  /**
   * Unsets member TimePeriod
   */
  void cleanTimePeriod();

  /**
   * Set member DefaultDuration.
   * @param c_defaultDuration Value to set
   */
  void setDefaultDuration(const xs_duration &c_defaultDuration);

  /**
   * Returns const reference to member DefaultDuration.
   * @return const reference to member defaultDuration
   */
  const xs_duration &getDefaultDuration() const;

  /**
   * Returns if member DefaultDuration is set.
   * @retval true member DefaultDuration is set
   * @retval false member DefaultDuration is not set
   */
  bool getDefaultDurationIsSet() const;

  /**
   * Unsets member DefaultDuration
   */
  void cleanDefaultDuration();

  /**
   * Set member DurationUncertainty.
   * @param c_durationUncertainty Value to set
   */
  void setDurationUncertainty(const xs_duration &c_durationUncertainty);

  /**
   * Returns const reference to member DurationUncertainty.
   * @return const reference to member durationUncertainty
   */
  const xs_duration &getDurationUncertainty() const;

  /**
   * Returns if member DurationUncertainty is set.
   * @retval true member DurationUncertainty is set
   * @retval false member DurationUncertainty is not set
   */
  bool getDurationUncertaintyIsSet() const;

  /**
   * Unsets member DurationUncertainty
   */
  void cleanDurationUncertainty();

  /**
   * Set member SlotActivated.
   * @param c_slotActivated Value to set
   */
  void setSlotActivated(const xs_boolean &c_slotActivated);

  /**
   * Returns const reference to member SlotActivated.
   * @return const reference to member slotActivated
   */
  const xs_boolean &getSlotActivated() const;

  /**
   * Returns if member SlotActivated is set.
   * @retval true member SlotActivated is set
   * @retval false member SlotActivated is not set
   */
  bool getSlotActivatedIsSet() const;

  /**
   * Unsets member SlotActivated
   */
  void cleanSlotActivated();

  /**
   * Set member Description.
   * @param c_description Value to set
   */
  void setDescription(const xs_string &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const xs_string &getDescription() const;

  /**
   * Returns if member Description is set.
   * @retval true member Description is set
   * @retval false member Description is not set
   */
  bool getDescriptionIsSet() const;

  /**
   * Unsets member Description
   */
  void cleanDescription();

  /**
   * @copydoc CmdData::reduce()
   */
  PowerTimeSlotScheduleData
  reduce(const PowerTimeSlotScheduleDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_slotNumberIsSet;
  xs_unsignedInt m_slotNumber;

  bool m_timePeriodIsSet;
  TimePeriod m_timePeriod;

  bool m_defaultDurationIsSet;
  xs_duration m_defaultDuration;

  bool m_durationUncertaintyIsSet;
  xs_duration m_durationUncertainty;

  bool m_slotActivatedIsSet;
  xs_boolean m_slotActivated;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type PowerTimeSlotScheduleData
using PowerTimeSlotScheduleDataPtr = std::shared_ptr<PowerTimeSlotScheduleData>;

//! typedef for const type PowerTimeSlotScheduleData
using PowerTimeSlotScheduleDataConst = const PowerTimeSlotScheduleData;

//! typedef for const type PowerTimeSlotScheduleData
using PowerTimeSlotScheduleDataConstPtr =
    std::shared_ptr<PowerTimeSlotScheduleDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULEDATA_H_