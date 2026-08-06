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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULEDATAELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/TimePeriodElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerTimeSlotScheduleDataElements
 */
class PowerTimeSlotScheduleDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  PowerTimeSlotScheduleDataElements();

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
  bool operator==(const PowerTimeSlotScheduleDataElements &c_classObject) const;

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
  bool operator!=(const PowerTimeSlotScheduleDataElements &c_classObject) const;

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
   * Set member SlotNumber.
   */
  void setSlotNumber();

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
  void setTimePeriod(const TimePeriodElements &c_timePeriod);

  /**
   * Returns const reference to member TimePeriod.
   * @return const reference to member timePeriod
   */
  const TimePeriodElements &getTimePeriod() const;

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
   */
  void setDefaultDuration();

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
   */
  void setDurationUncertainty();

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
   */
  void setSlotActivated();

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
   */
  void setDescription();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  // ElementTag
  bool m_slotNumberIsSet;

  bool m_timePeriodIsSet;
  TimePeriodElements m_timePeriod;

  // ElementTag
  bool m_defaultDurationIsSet;

  // ElementTag
  bool m_durationUncertaintyIsSet;

  // ElementTag
  bool m_slotActivatedIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type PowerTimeSlotScheduleDataElements
using PowerTimeSlotScheduleDataElementsPtr =
    std::shared_ptr<PowerTimeSlotScheduleDataElements>;

//! typedef for const type PowerTimeSlotScheduleDataElements
using PowerTimeSlotScheduleDataElementsConst =
    const PowerTimeSlotScheduleDataElements;

//! typedef for const type PowerTimeSlotScheduleDataElements
using PowerTimeSlotScheduleDataElementsConstPtr =
    std::shared_ptr<PowerTimeSlotScheduleDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULEDATAELEMENTS_H_