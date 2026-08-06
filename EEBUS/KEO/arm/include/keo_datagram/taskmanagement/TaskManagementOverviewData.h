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

#ifndef KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTOVERVIEWDATA_H_
#define KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTOVERVIEWDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTaskManagement
 * @{
 */

/**
 * Declaration TaskManagementOverviewData
 */
class TaskManagementOverviewData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  TaskManagementOverviewData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_remoteControllable the member to set
   * @param c_jobsActive the member to set
   */
  TaskManagementOverviewData(const xs_boolean &c_remoteControllable,
                             const xs_boolean &c_jobsActive);

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
  bool operator==(const TaskManagementOverviewData &c_classObject) const;

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
  bool operator!=(const TaskManagementOverviewData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member RemoteControllable.
   * @param c_remoteControllable Value to set
   */
  void setRemoteControllable(const xs_boolean &c_remoteControllable);

  /**
   * Returns const reference to member RemoteControllable.
   * @return const reference to member remoteControllable
   */
  const xs_boolean &getRemoteControllable() const;

  /**
   * Returns if member RemoteControllable is set.
   * @retval true member RemoteControllable is set
   * @retval false member RemoteControllable is not set
   */
  bool getRemoteControllableIsSet() const;

  /**
   * Unsets member RemoteControllable
   */
  void cleanRemoteControllable();

  /**
   * Set member JobsActive.
   * @param c_jobsActive Value to set
   */
  void setJobsActive(const xs_boolean &c_jobsActive);

  /**
   * Returns const reference to member JobsActive.
   * @return const reference to member jobsActive
   */
  const xs_boolean &getJobsActive() const;

  /**
   * Returns if member JobsActive is set.
   * @retval true member JobsActive is set
   * @retval false member JobsActive is not set
   */
  bool getJobsActiveIsSet() const;

  /**
   * Unsets member JobsActive
   */
  void cleanJobsActive();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_remoteControllableIsSet;
  xs_boolean m_remoteControllable;

  bool m_jobsActiveIsSet;
  xs_boolean m_jobsActive;
};

//! typedef for non-const smart pointer type TaskManagementOverviewData
using TaskManagementOverviewDataPtr =
    std::shared_ptr<TaskManagementOverviewData>;

//! typedef for const type TaskManagementOverviewData
using TaskManagementOverviewDataConst = const TaskManagementOverviewData;

//! typedef for const type TaskManagementOverviewData
using TaskManagementOverviewDataConstPtr =
    std::shared_ptr<TaskManagementOverviewDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTOVERVIEWDATA_H_