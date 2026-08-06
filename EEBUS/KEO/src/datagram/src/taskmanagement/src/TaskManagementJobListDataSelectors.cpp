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

#include <keo_datagram/taskmanagement/TaskManagementJobListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobListDataSelectors::TaskManagementJobListDataSelectors()
    : DataSelectors(), m_jobIdIsSet(false), m_jobId(0), m_jobStateIsSet(false),
      m_jobState(TaskManagementJobState())

{}

TaskManagementJobListDataSelectors::TaskManagementJobListDataSelectors(
    const xs_unsignedInt &c_jobId, const TaskManagementJobState &c_jobState)
    : DataSelectors(), m_jobIdIsSet(true), m_jobId(c_jobId),
      m_jobStateIsSet(true), m_jobState(c_jobState)

{}

bool TaskManagementJobListDataSelectors::
operator==(const TaskManagementJobListDataSelectors &c_classObject) const {
  if (m_jobIdIsSet != c_classObject.m_jobIdIsSet ||
      (m_jobIdIsSet && (m_jobId != c_classObject.m_jobId))) {
    return false;
  }
  if (m_jobStateIsSet != c_classObject.m_jobStateIsSet ||
      (m_jobStateIsSet && (m_jobState != c_classObject.m_jobState))) {
    return false;
  }

  return true;
}

bool TaskManagementJobListDataSelectors::
operator!=(const TaskManagementJobListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobListDataSelectors::isEmpty() const {
  return !m_jobIdIsSet && !m_jobStateIsSet;
}

DataSelectors::Type TaskManagementJobListDataSelectors::getDataType() const {
  return DataSelectors::Type::TASK_MANAGEMENT_JOB_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TaskManagementJobListDataSelectors::clone() const {
  return std::make_shared<TaskManagementJobListDataSelectors>(*this);
}

void TaskManagementJobListDataSelectors::setJobId(const xs_unsignedInt &jobId) {
  m_jobId = jobId;
  m_jobIdIsSet = true;
}

const xs_unsignedInt &TaskManagementJobListDataSelectors::getJobId() const {
  return m_jobId;
}

void TaskManagementJobListDataSelectors::cleanJobId() {
  m_jobId = 0;
  m_jobIdIsSet = false;
}

bool TaskManagementJobListDataSelectors::getJobIdIsSet() const {
  return m_jobIdIsSet;
}

void TaskManagementJobListDataSelectors::setJobState(
    const TaskManagementJobState &jobState) {
  m_jobState = jobState;
  m_jobStateIsSet = true;
}

const TaskManagementJobState &
TaskManagementJobListDataSelectors::getJobState() const {
  return m_jobState;
}

void TaskManagementJobListDataSelectors::cleanJobState() {
  m_jobState = TaskManagementJobState();
  m_jobStateIsSet = false;
}

bool TaskManagementJobListDataSelectors::getJobStateIsSet() const {
  return m_jobStateIsSet;
}

bool TaskManagementJobListDataSelectors::selects(
    const TaskManagementJobData &data) const {
  if (getJobIdIsSet() &&
      (!data.getJobIdIsSet() || getJobId() != data.getJobId())) {
    return false;
  }
  if (getJobStateIsSet() &&
      (!data.getJobStateIsSet() || getJobState() != data.getJobState())) {
    return false;
  }
  return true;
}

bool TaskManagementJobListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"jobId", "jobState"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "jobId", &m_jobId)) {
      m_jobIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "jobState", &m_jobState)) {
      m_jobStateIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_jobIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobId", m_jobId);
  }
  if (m_jobStateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobState", m_jobState);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram