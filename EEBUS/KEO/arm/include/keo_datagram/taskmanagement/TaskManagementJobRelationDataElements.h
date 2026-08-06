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

#ifndef KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBRELATIONDATAELEMENTS_H_
#define KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBRELATIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/taskmanagement/TaskManagementDirectControlRelatedElements.h>
#include <keo_datagram/taskmanagement/TaskManagementHvacRelatedElements.h>
#include <keo_datagram/taskmanagement/TaskManagementLoadControlReleatedElements.h>
#include <keo_datagram/taskmanagement/TaskManagementPowerSequencesRelatedElements.h>
#include <keo_datagram/taskmanagement/TaskManagementSmartEnergyManagementPsRelatedElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTaskManagement
 * @{
 */

/**
 * Declaration TaskManagementJobRelationDataElements
 */
class TaskManagementJobRelationDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TaskManagementJobRelationDataElements();

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
  operator==(const TaskManagementJobRelationDataElements &c_classObject) const;

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
  operator!=(const TaskManagementJobRelationDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member JobId.
   */
  void setJobId();

  /**
   * Returns if member JobId is set.
   * @retval true member JobId is set
   * @retval false member JobId is not set
   */
  bool getJobIdIsSet() const;

  /**
   * Unsets member JobId
   */
  void cleanJobId();

  /**
   * Set member DirectControlRelated.
   * @param c_directControlRelated Value to set
   */
  void setDirectControlRelated(
      const TaskManagementDirectControlRelatedElements &c_directControlRelated);

  /**
   * Returns const reference to member DirectControlRelated.
   * @return const reference to member directControlRelated
   */
  const TaskManagementDirectControlRelatedElements &
  getDirectControlRelated() const;

  /**
   * Returns if member DirectControlRelated is set.
   * @retval true member DirectControlRelated is set
   * @retval false member DirectControlRelated is not set
   */
  bool getDirectControlRelatedIsSet() const;

  /**
   * Unsets member DirectControlRelated
   */
  void cleanDirectControlRelated();

  /**
   * Set member HvacRelated.
   * @param c_hvacRelated Value to set
   */
  void setHvacRelated(const TaskManagementHvacRelatedElements &c_hvacRelated);

  /**
   * Returns const reference to member HvacRelated.
   * @return const reference to member hvacRelated
   */
  const TaskManagementHvacRelatedElements &getHvacRelated() const;

  /**
   * Returns if member HvacRelated is set.
   * @retval true member HvacRelated is set
   * @retval false member HvacRelated is not set
   */
  bool getHvacRelatedIsSet() const;

  /**
   * Unsets member HvacRelated
   */
  void cleanHvacRelated();

  /**
   * Set member LoadControlReleated.
   * @param c_loadControlReleated Value to set
   */
  void setLoadControlReleated(
      const TaskManagementLoadControlReleatedElements &c_loadControlReleated);

  /**
   * Returns const reference to member LoadControlReleated.
   * @return const reference to member loadControlReleated
   */
  const TaskManagementLoadControlReleatedElements &
  getLoadControlReleated() const;

  /**
   * Returns if member LoadControlReleated is set.
   * @retval true member LoadControlReleated is set
   * @retval false member LoadControlReleated is not set
   */
  bool getLoadControlReleatedIsSet() const;

  /**
   * Unsets member LoadControlReleated
   */
  void cleanLoadControlReleated();

  /**
   * Set member PowerSequencesRelated.
   * @param c_powerSequencesRelated Value to set
   */
  void
  setPowerSequencesRelated(const TaskManagementPowerSequencesRelatedElements
                               &c_powerSequencesRelated);

  /**
   * Returns const reference to member PowerSequencesRelated.
   * @return const reference to member powerSequencesRelated
   */
  const TaskManagementPowerSequencesRelatedElements &
  getPowerSequencesRelated() const;

  /**
   * Returns if member PowerSequencesRelated is set.
   * @retval true member PowerSequencesRelated is set
   * @retval false member PowerSequencesRelated is not set
   */
  bool getPowerSequencesRelatedIsSet() const;

  /**
   * Unsets member PowerSequencesRelated
   */
  void cleanPowerSequencesRelated();

  /**
   * Set member SmartEnergyManagementPsRelated.
   * @param c_smartEnergyManagementPsRelated Value to set
   */
  void setSmartEnergyManagementPsRelated(
      const TaskManagementSmartEnergyManagementPsRelatedElements
          &c_smartEnergyManagementPsRelated);

  /**
   * Returns const reference to member SmartEnergyManagementPsRelated.
   * @return const reference to member smartEnergyManagementPsRelated
   */
  const TaskManagementSmartEnergyManagementPsRelatedElements &
  getSmartEnergyManagementPsRelated() const;

  /**
   * Returns if member SmartEnergyManagementPsRelated is set.
   * @retval true member SmartEnergyManagementPsRelated is set
   * @retval false member SmartEnergyManagementPsRelated is not set
   */
  bool getSmartEnergyManagementPsRelatedIsSet() const;

  /**
   * Unsets member SmartEnergyManagementPsRelated
   */
  void cleanSmartEnergyManagementPsRelated();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_jobIdIsSet;

  bool m_directControlRelatedIsSet;
  TaskManagementDirectControlRelatedElements m_directControlRelated;

  bool m_hvacRelatedIsSet;
  TaskManagementHvacRelatedElements m_hvacRelated;

  bool m_loadControlReleatedIsSet;
  TaskManagementLoadControlReleatedElements m_loadControlReleated;

  bool m_powerSequencesRelatedIsSet;
  TaskManagementPowerSequencesRelatedElements m_powerSequencesRelated;

  bool m_smartEnergyManagementPsRelatedIsSet;
  TaskManagementSmartEnergyManagementPsRelatedElements
      m_smartEnergyManagementPsRelated;
};

//! typedef for non-const smart pointer type
//! TaskManagementJobRelationDataElements
using TaskManagementJobRelationDataElementsPtr =
    std::shared_ptr<TaskManagementJobRelationDataElements>;

//! typedef for const type TaskManagementJobRelationDataElements
using TaskManagementJobRelationDataElementsConst =
    const TaskManagementJobRelationDataElements;

//! typedef for const type TaskManagementJobRelationDataElements
using TaskManagementJobRelationDataElementsConstPtr =
    std::shared_ptr<TaskManagementJobRelationDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBRELATIONDATAELEMENTS_H_