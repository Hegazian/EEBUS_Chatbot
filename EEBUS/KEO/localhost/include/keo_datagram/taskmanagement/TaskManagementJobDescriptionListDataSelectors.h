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

#ifndef KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/taskmanagement/TaskManagementJobSource.h>

#include <keo_datagram/taskmanagement/TaskManagementJobDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTaskManagement
 * @{
 */

/**
 * Declaration TaskManagementJobDescriptionListDataSelectors
 */
class TaskManagementJobDescriptionListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  TaskManagementJobDescriptionListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_jobId the member to set
   * @param c_jobSource the member to set
   */
  TaskManagementJobDescriptionListDataSelectors(
      const xs_unsignedInt &c_jobId,
      const TaskManagementJobSource &c_jobSource);

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
  bool operator==(
      const TaskManagementJobDescriptionListDataSelectors &c_classObject) const;

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
  bool operator!=(
      const TaskManagementJobDescriptionListDataSelectors &c_classObject) const;

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
   * Set member JobSource.
   * @param c_jobSource Value to set
   */
  void setJobSource(const TaskManagementJobSource &c_jobSource);

  /**
   * Returns const reference to member JobSource.
   * @return const reference to member jobSource
   */
  const TaskManagementJobSource &getJobSource() const;

  /**
   * Returns if member JobSource is set.
   * @retval true member JobSource is set
   * @retval false member JobSource is not set
   */
  bool getJobSourceIsSet() const;

  /**
   * Unsets member JobSource
   */
  void cleanJobSource();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const TaskManagementJobDescriptionData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_jobIdIsSet;
  xs_unsignedInt m_jobId;

  bool m_jobSourceIsSet;
  TaskManagementJobSource m_jobSource;
};

//! typedef for non-const smart pointer type
//! TaskManagementJobDescriptionListDataSelectors
using TaskManagementJobDescriptionListDataSelectorsPtr =
    std::shared_ptr<TaskManagementJobDescriptionListDataSelectors>;

//! typedef for const type TaskManagementJobDescriptionListDataSelectors
using TaskManagementJobDescriptionListDataSelectorsConst =
    const TaskManagementJobDescriptionListDataSelectors;

//! typedef for const type TaskManagementJobDescriptionListDataSelectors
using TaskManagementJobDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<TaskManagementJobDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBDESCRIPTIONLISTDATASELECTORS_H_