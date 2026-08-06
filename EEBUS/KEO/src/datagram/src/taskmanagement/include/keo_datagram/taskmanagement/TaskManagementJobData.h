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

#ifndef KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBDATA_H_
#define KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/taskmanagement/TaskManagementJobDataElements.h>
#include <keo_datagram/taskmanagement/TaskManagementJobState.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTaskManagement
 * @{
 */

/**
 * Declaration TaskManagementJobData
 */
class TaskManagementJobData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TaskManagementJobData();

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
  bool operator==(const TaskManagementJobData &c_classObject) const;

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
  bool operator!=(const TaskManagementJobData &c_classObject) const;

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
   * Set member Timestamp.
   * @param c_timestamp Value to set
   */
  void setTimestamp(const AbsoluteOrRelativeTime &c_timestamp);

  /**
   * Returns const reference to member Timestamp.
   * @return const reference to member timestamp
   */
  const AbsoluteOrRelativeTime &getTimestamp() const;

  /**
   * Returns if member Timestamp is set.
   * @retval true member Timestamp is set
   * @retval false member Timestamp is not set
   */
  bool getTimestampIsSet() const;

  /**
   * Unsets member Timestamp
   */
  void cleanTimestamp();

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
   * Set member ElapsedTime.
   * @param c_elapsedTime Value to set
   */
  void setElapsedTime(const xs_duration &c_elapsedTime);

  /**
   * Returns const reference to member ElapsedTime.
   * @return const reference to member elapsedTime
   */
  const xs_duration &getElapsedTime() const;

  /**
   * Returns if member ElapsedTime is set.
   * @retval true member ElapsedTime is set
   * @retval false member ElapsedTime is not set
   */
  bool getElapsedTimeIsSet() const;

  /**
   * Unsets member ElapsedTime
   */
  void cleanElapsedTime();

  /**
   * Set member RemainingTime.
   * @param c_remainingTime Value to set
   */
  void setRemainingTime(const xs_duration &c_remainingTime);

  /**
   * Returns const reference to member RemainingTime.
   * @return const reference to member remainingTime
   */
  const xs_duration &getRemainingTime() const;

  /**
   * Returns if member RemainingTime is set.
   * @retval true member RemainingTime is set
   * @retval false member RemainingTime is not set
   */
  bool getRemainingTimeIsSet() const;

  /**
   * Unsets member RemainingTime
   */
  void cleanRemainingTime();

  /**
   * @copydoc CmdData::reduce()
   */
  TaskManagementJobData
  reduce(const TaskManagementJobDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_jobIdIsSet;
  xs_unsignedInt m_jobId;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_jobStateIsSet;
  TaskManagementJobState m_jobState;

  bool m_elapsedTimeIsSet;
  xs_duration m_elapsedTime;

  bool m_remainingTimeIsSet;
  xs_duration m_remainingTime;
};

//! typedef for non-const smart pointer type TaskManagementJobData
using TaskManagementJobDataPtr = std::shared_ptr<TaskManagementJobData>;

//! typedef for const type TaskManagementJobData
using TaskManagementJobDataConst = const TaskManagementJobData;

//! typedef for const type TaskManagementJobData
using TaskManagementJobDataConstPtr =
    std::shared_ptr<TaskManagementJobDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBDATA_H_