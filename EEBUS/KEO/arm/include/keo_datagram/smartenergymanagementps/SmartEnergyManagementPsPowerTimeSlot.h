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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSPOWERTIMESLOT_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSPOWERTIMESLOT_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsData.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleData.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerTimeSlotValueList.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration SmartEnergyManagementPsPowerTimeSlot
 */
class SmartEnergyManagementPsPowerTimeSlot : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  SmartEnergyManagementPsPowerTimeSlot();

  /**
   * Construct an instance of this class and set its member.
   * @param c_schedule the member to set
   * @param c_valueList the member to set
   * @param c_scheduleConstraints the member to set
   */
  SmartEnergyManagementPsPowerTimeSlot(
      const PowerTimeSlotScheduleData &c_schedule,
      const SmartEnergyManagementPsPowerTimeSlotValueList &c_valueList,
      const PowerTimeSlotScheduleConstraintsData &c_scheduleConstraints);

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
  operator==(const SmartEnergyManagementPsPowerTimeSlot &c_classObject) const;

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
  operator!=(const SmartEnergyManagementPsPowerTimeSlot &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Schedule.
   * @param c_schedule Value to set
   */
  void setSchedule(const PowerTimeSlotScheduleData &c_schedule);

  /**
   * Returns const reference to member Schedule.
   * @return const reference to member schedule
   */
  const PowerTimeSlotScheduleData &getSchedule() const;

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
   * Set member ValueList.
   * @param c_valueList Value to set
   */
  void setValueList(
      const SmartEnergyManagementPsPowerTimeSlotValueList &c_valueList);

  /**
   * Returns const reference to member ValueList.
   * @return const reference to member valueList
   */
  const SmartEnergyManagementPsPowerTimeSlotValueList &getValueList() const;

  /**
   * Returns if member ValueList is set.
   * @retval true member ValueList is set
   * @retval false member ValueList is not set
   */
  bool getValueListIsSet() const;

  /**
   * Unsets member ValueList
   */
  void cleanValueList();

  /**
   * Set member ScheduleConstraints.
   * @param c_scheduleConstraints Value to set
   */
  void setScheduleConstraints(
      const PowerTimeSlotScheduleConstraintsData &c_scheduleConstraints);

  /**
   * Returns const reference to member ScheduleConstraints.
   * @return const reference to member scheduleConstraints
   */
  const PowerTimeSlotScheduleConstraintsData &getScheduleConstraints() const;

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_scheduleIsSet;
  PowerTimeSlotScheduleData m_schedule;

  bool m_valueListIsSet;
  SmartEnergyManagementPsPowerTimeSlotValueList m_valueList;

  bool m_scheduleConstraintsIsSet;
  PowerTimeSlotScheduleConstraintsData m_scheduleConstraints;
};

//! typedef for non-const smart pointer type
//! SmartEnergyManagementPsPowerTimeSlot
using SmartEnergyManagementPsPowerTimeSlotPtr =
    std::shared_ptr<SmartEnergyManagementPsPowerTimeSlot>;

//! typedef for const type SmartEnergyManagementPsPowerTimeSlot
using SmartEnergyManagementPsPowerTimeSlotConst =
    const SmartEnergyManagementPsPowerTimeSlot;

//! typedef for const type SmartEnergyManagementPsPowerTimeSlot
using SmartEnergyManagementPsPowerTimeSlotConstPtr =
    std::shared_ptr<SmartEnergyManagementPsPowerTimeSlotConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSPOWERTIMESLOT_H_