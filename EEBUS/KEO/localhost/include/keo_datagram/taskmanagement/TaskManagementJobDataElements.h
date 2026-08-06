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

#ifndef KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBDATAELEMENTS_H_
#define KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTaskManagement
 * @{
 */

/**
 * Declaration TaskManagementJobDataElements
 */
class TaskManagementJobDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TaskManagementJobDataElements();

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
  bool operator==(const TaskManagementJobDataElements &c_classObject) const;

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
  bool operator!=(const TaskManagementJobDataElements &c_classObject) const;

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
   * Set member Timestamp.
   */
  void setTimestamp();

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
   */
  void setJobState();

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
   */
  void setElapsedTime();

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
   */
  void setRemainingTime();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_jobIdIsSet;

  // ElementTag
  bool m_timestampIsSet;

  // ElementTag
  bool m_jobStateIsSet;

  // ElementTag
  bool m_elapsedTimeIsSet;

  // ElementTag
  bool m_remainingTimeIsSet;
};

//! typedef for non-const smart pointer type TaskManagementJobDataElements
using TaskManagementJobDataElementsPtr =
    std::shared_ptr<TaskManagementJobDataElements>;

//! typedef for const type TaskManagementJobDataElements
using TaskManagementJobDataElementsConst = const TaskManagementJobDataElements;

//! typedef for const type TaskManagementJobDataElements
using TaskManagementJobDataElementsConstPtr =
    std::shared_ptr<TaskManagementJobDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TASKMANAGEMENT_TASKMANAGEMENTJOBDATAELEMENTS_H_