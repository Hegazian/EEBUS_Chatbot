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

#ifndef KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBRELATIONDATA_H_
#define KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBRELATIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/taskmanagement/TaskManagementDirectControlRelated.h>
#include <keo_datagram/taskmanagement/TaskManagementHvacRelated.h>
#include <keo_datagram/taskmanagement/TaskManagementJobRelationDataElements.h>
#include <keo_datagram/taskmanagement/TaskManagementLoadControlReleated.h>
#include <keo_datagram/taskmanagement/TaskManagementPowerSequencesRelated.h>
#include <keo_datagram/taskmanagement/TaskManagementSmartEnergyManagementPsRelated.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTaskManagement
 * @{
 */

/**
 * Declaration TaskManagementJobRelationData
 */
class TaskManagementJobRelationData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TaskManagementJobRelationData();

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
  bool operator==(const TaskManagementJobRelationData &c_classObject) const;

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
  bool operator!=(const TaskManagementJobRelationData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member JobId.
   * @param c_jobId Value to set
   */
  void setJobId(const xs_unsignedInt &c_jobId);

  /**
   * Returns const reference to member JobId.
   * @return const reference to member jobId
   */
  const xs_unsignedInt &getJobId() const;

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
      const TaskManagementDirectControlRelated &c_directControlRelated);

  /**
   * Returns const reference to member DirectControlRelated.
   * @return const reference to member directControlRelated
   */
  const TaskManagementDirectControlRelated &getDirectControlRelated() const;

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
  void setHvacRelated(const TaskManagementHvacRelated &c_hvacRelated);

  /**
   * Returns const reference to member HvacRelated.
   * @return const reference to member hvacRelated
   */
  const TaskManagementHvacRelated &getHvacRelated() const;

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
      const TaskManagementLoadControlReleated &c_loadControlReleated);

  /**
   * Returns const reference to member LoadControlReleated.
   * @return const reference to member loadControlReleated
   */
  const TaskManagementLoadControlReleated &getLoadControlReleated() const;

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
  void setPowerSequencesRelated(
      const TaskManagementPowerSequencesRelated &c_powerSequencesRelated);

  /**
   * Returns const reference to member PowerSequencesRelated.
   * @return const reference to member powerSequencesRelated
   */
  const TaskManagementPowerSequencesRelated &getPowerSequencesRelated() const;

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
      const TaskManagementSmartEnergyManagementPsRelated
          &c_smartEnergyManagementPsRelated);

  /**
   * Returns const reference to member SmartEnergyManagementPsRelated.
   * @return const reference to member smartEnergyManagementPsRelated
   */
  const TaskManagementSmartEnergyManagementPsRelated &
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

  /**
   * @copydoc CmdData::reduce()
   */
  TaskManagementJobRelationData
  reduce(const TaskManagementJobRelationDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_jobIdIsSet;
  xs_unsignedInt m_jobId;

  bool m_directControlRelatedIsSet;
  TaskManagementDirectControlRelated m_directControlRelated;

  bool m_hvacRelatedIsSet;
  TaskManagementHvacRelated m_hvacRelated;

  bool m_loadControlReleatedIsSet;
  TaskManagementLoadControlReleated m_loadControlReleated;

  bool m_powerSequencesRelatedIsSet;
  TaskManagementPowerSequencesRelated m_powerSequencesRelated;

  bool m_smartEnergyManagementPsRelatedIsSet;
  TaskManagementSmartEnergyManagementPsRelated m_smartEnergyManagementPsRelated;
};

//! typedef for non-const smart pointer type TaskManagementJobRelationData
using TaskManagementJobRelationDataPtr =
    std::shared_ptr<TaskManagementJobRelationData>;

//! typedef for const type TaskManagementJobRelationData
using TaskManagementJobRelationDataConst = const TaskManagementJobRelationData;

//! typedef for const type TaskManagementJobRelationData
using TaskManagementJobRelationDataConstPtr =
    std::shared_ptr<TaskManagementJobRelationDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBRELATIONDATA_H_