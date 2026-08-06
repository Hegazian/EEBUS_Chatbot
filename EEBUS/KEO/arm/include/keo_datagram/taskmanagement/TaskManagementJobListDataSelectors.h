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

#ifndef KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBLISTDATASELECTORS_H_
#define KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/taskmanagement/TaskManagementJobState.h>

#include <keo_datagram/taskmanagement/TaskManagementJobData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTaskManagement
 * @{
 */

/**
 * Declaration TaskManagementJobListDataSelectors
 */
class TaskManagementJobListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  TaskManagementJobListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_jobId the member to set
   * @param c_jobState the member to set
   */
  TaskManagementJobListDataSelectors(const xs_unsignedInt &c_jobId,
                                     const TaskManagementJobState &c_jobState);

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
  operator==(const TaskManagementJobListDataSelectors &c_classObject) const;

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
  operator!=(const TaskManagementJobListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

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
   * Set member JobState.
   * @param c_jobState Value to set
   */
  void setJobState(const TaskManagementJobState &c_jobState);

  /**
   * Returns const reference to member JobState.
   * @return const reference to member jobState
   */
  const TaskManagementJobState &getJobState() const;

  /**
   * Returns if member JobState is set.
   * @retval true member JobState is set
   * @retval false member JobState is not set
   */
  bool getJobStateIsSet() const;

  /**
   * Unsets member JobState
   */
  void cleanJobState();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const TaskManagementJobData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_jobIdIsSet;
  xs_unsignedInt m_jobId;

  bool m_jobStateIsSet;
  TaskManagementJobState m_jobState;
};

//! typedef for non-const smart pointer type TaskManagementJobListDataSelectors
using TaskManagementJobListDataSelectorsPtr =
    std::shared_ptr<TaskManagementJobListDataSelectors>;

//! typedef for const type TaskManagementJobListDataSelectors
using TaskManagementJobListDataSelectorsConst =
    const TaskManagementJobListDataSelectors;

//! typedef for const type TaskManagementJobListDataSelectors
using TaskManagementJobListDataSelectorsConstPtr =
    std::shared_ptr<TaskManagementJobListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBLISTDATASELECTORS_H_