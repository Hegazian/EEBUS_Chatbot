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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSPOWERSEQUENCE_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSPOWERSEQUENCE_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsDurationData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsInterruptData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceStateData.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerTimeSlot.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration SmartEnergyManagementPsPowerSequence
 */
class SmartEnergyManagementPsPowerSequence : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  SmartEnergyManagementPsPowerSequence();

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
  operator==(const SmartEnergyManagementPsPowerSequence &c_classObject) const;

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
  operator!=(const SmartEnergyManagementPsPowerSequence &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Description.
   * @param c_description Value to set
   */
  void setDescription(const PowerSequenceDescriptionData &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const PowerSequenceDescriptionData &getDescription() const;

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
   * Set member State.
   * @param c_state Value to set
   */
  void setState(const PowerSequenceStateData &c_state);

  /**
   * Returns const reference to member State.
   * @return const reference to member state
   */
  const PowerSequenceStateData &getState() const;

  /**
   * Returns if member State is set.
   * @retval true member State is set
   * @retval false member State is not set
   */
  bool getStateIsSet() const;

  /**
   * Unsets member State
   */
  void cleanState();

  /**
   * Set member Schedule.
   * @param c_schedule Value to set
   */
  void setSchedule(const PowerSequenceScheduleData &c_schedule);

  /**
   * Returns const reference to member Schedule.
   * @return const reference to member schedule
   */
  const PowerSequenceScheduleData &getSchedule() const;

  /**
   * Returns if member Schedule is set.
   * @retval true member Schedule is set
   * @retval false member Schedule is not set
   */
  bool getScheduleIsSet() const;

  /**
   * Unsets member Schedule
   */
  void cleanSchedule();

  /**
   * Set member ScheduleConstraints.
   * @param c_scheduleConstraints Value to set
   */
  void setScheduleConstraints(
      const PowerSequenceScheduleConstraintsData &c_scheduleConstraints);

  /**
   * Returns const reference to member ScheduleConstraints.
   * @return const reference to member scheduleConstraints
   */
  const PowerSequenceScheduleConstraintsData &getScheduleConstraints() const;

  /**
   * Returns if member ScheduleConstraints is set.
   * @retval true member ScheduleConstraints is set
   * @retval false member ScheduleConstraints is not set
   */
  bool getScheduleConstraintsIsSet() const;

  /**
   * Unsets member ScheduleConstraints
   */
  void cleanScheduleConstraints();

  /**
   * Set member SchedulePreference.
   * @param c_schedulePreference Value to set
   */
  void setSchedulePreference(
      const PowerSequenceSchedulePreferenceData &c_schedulePreference);

  /**
   * Returns const reference to member SchedulePreference.
   * @return const reference to member schedulePreference
   */
  const PowerSequenceSchedulePreferenceData &getSchedulePreference() const;

  /**
   * Returns if member SchedulePreference is set.
   * @retval true member SchedulePreference is set
   * @retval false member SchedulePreference is not set
   */
  bool getSchedulePreferenceIsSet() const;

  /**
   * Unsets member SchedulePreference
   */
  void cleanSchedulePreference();

  /**
   * Set member OperatingConstraintsInterrupt.
   * @param c_operatingConstraintsInterrupt Value to set
   */
  void setOperatingConstraintsInterrupt(
      const OperatingConstraintsInterruptData &c_operatingConstraintsInterrupt);

  /**
   * Returns const reference to member OperatingConstraintsInterrupt.
   * @return const reference to member operatingConstraintsInterrupt
   */
  const OperatingConstraintsInterruptData &
  getOperatingConstraintsInterrupt() const;

  /**
   * Returns if member OperatingConstraintsInterrupt is set.
   * @retval true member OperatingConstraintsInterrupt is set
   * @retval false member OperatingConstraintsInterrupt is not set
   */
  bool getOperatingConstraintsInterruptIsSet() const;

  /**
   * Unsets member OperatingConstraintsInterrupt
   */
  void cleanOperatingConstraintsInterrupt();

  /**
   * Set member OperatingConstraintsDuration.
   * @param c_operatingConstraintsDuration Value to set
   */
  void setOperatingConstraintsDuration(
      const OperatingConstraintsDurationData &c_operatingConstraintsDuration);

  /**
   * Returns const reference to member OperatingConstraintsDuration.
   * @return const reference to member operatingConstraintsDuration
   */
  const OperatingConstraintsDurationData &
  getOperatingConstraintsDuration() const;

  /**
   * Returns if member OperatingConstraintsDuration is set.
   * @retval true member OperatingConstraintsDuration is set
   * @retval false member OperatingConstraintsDuration is not set
   */
  bool getOperatingConstraintsDurationIsSet() const;

  /**
   * Unsets member OperatingConstraintsDuration
   */
  void cleanOperatingConstraintsDuration();

  /**
   * Set member OperatingConstraintsResumeImplication.
   * @param c_operatingConstraintsResumeImplication Value to set
   */
  void setOperatingConstraintsResumeImplication(
      const OperatingConstraintsResumeImplicationData
          &c_operatingConstraintsResumeImplication);

  /**
   * Returns const reference to member OperatingConstraintsResumeImplication.
   * @return const reference to member operatingConstraintsResumeImplication
   */
  const OperatingConstraintsResumeImplicationData &
  getOperatingConstraintsResumeImplication() const;

  /**
   * Returns if member OperatingConstraintsResumeImplication is set.
   * @retval true member OperatingConstraintsResumeImplication is set
   * @retval false member OperatingConstraintsResumeImplication is not set
   */
  bool getOperatingConstraintsResumeImplicationIsSet() const;

  /**
   * Unsets member OperatingConstraintsResumeImplication
   */
  void cleanOperatingConstraintsResumeImplication();

  /**
   * Set member PowerTimeSlot.
   * @param c_powerTimeSlot Value to set
   */
  void setPowerTimeSlot(
      const std::vector<SmartEnergyManagementPsPowerTimeSlot> &c_powerTimeSlot);

  /**
   * Returns const reference to member PowerTimeSlot.
   * @return const reference to member powerTimeSlot
   */
  const std::vector<SmartEnergyManagementPsPowerTimeSlot> &
  getPowerTimeSlot() const;

  /**
   * Returns if member PowerTimeSlot is set.
   * @retval true member PowerTimeSlot is set
   * @retval false member PowerTimeSlot is not set
   */
  bool getPowerTimeSlotIsSet() const;

  /**
   * Unsets member PowerTimeSlot
   */
  void cleanPowerTimeSlot();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_descriptionIsSet;
  PowerSequenceDescriptionData m_description;

  bool m_stateIsSet;
  PowerSequenceStateData m_state;

  bool m_scheduleIsSet;
  PowerSequenceScheduleData m_schedule;

  bool m_scheduleConstraintsIsSet;
  PowerSequenceScheduleConstraintsData m_scheduleConstraints;

  bool m_schedulePreferenceIsSet;
  PowerSequenceSchedulePreferenceData m_schedulePreference;

  bool m_operatingConstraintsInterruptIsSet;
  OperatingConstraintsInterruptData m_operatingConstraintsInterrupt;

  bool m_operatingConstraintsDurationIsSet;
  OperatingConstraintsDurationData m_operatingConstraintsDuration;

  bool m_operatingConstraintsResumeImplicationIsSet;
  OperatingConstraintsResumeImplicationData
      m_operatingConstraintsResumeImplication;

  bool m_powerTimeSlotIsSet;
  std::vector<SmartEnergyManagementPsPowerTimeSlot> m_powerTimeSlot;
};

//! typedef for non-const smart pointer type
//! SmartEnergyManagementPsPowerSequence
using SmartEnergyManagementPsPowerSequencePtr =
    std::shared_ptr<SmartEnergyManagementPsPowerSequence>;

//! typedef for const type SmartEnergyManagementPsPowerSequence
using SmartEnergyManagementPsPowerSequenceConst =
    const SmartEnergyManagementPsPowerSequence;

//! typedef for const type SmartEnergyManagementPsPowerSequence
using SmartEnergyManagementPsPowerSequenceConstPtr =
    std::shared_ptr<SmartEnergyManagementPsPowerSequenceConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSPOWERSEQUENCE_H_