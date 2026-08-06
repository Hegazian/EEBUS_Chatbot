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

#include <keo_datagram/taskmanagement/TaskManagementJobRelationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobRelationListDataSelectors::
    TaskManagementJobRelationListDataSelectors()
    : DataSelectors(), m_jobIdIsSet(false), m_jobId(0)

{}

TaskManagementJobRelationListDataSelectors::
    TaskManagementJobRelationListDataSelectors(const xs_unsignedInt &c_jobId) {
  setJobId(c_jobId);
}

bool TaskManagementJobRelationListDataSelectors::operator==(
    const TaskManagementJobRelationListDataSelectors &c_classObject) const {
  if (m_jobIdIsSet != c_classObject.m_jobIdIsSet ||
      (m_jobIdIsSet && (m_jobId != c_classObject.m_jobId))) {
    return false;
  }

  return true;
}

bool TaskManagementJobRelationListDataSelectors::operator!=(
    const TaskManagementJobRelationListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobRelationListDataSelectors::isEmpty() const {
  return !m_jobIdIsSet;
}

DataSelectors::Type
TaskManagementJobRelationListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TaskManagementJobRelationListDataSelectors::clone() const {
  return std::make_shared<TaskManagementJobRelationListDataSelectors>(*this);
}

void TaskManagementJobRelationListDataSelectors::setJobId(
    const xs_unsignedInt &jobId) {
  m_jobId = jobId;
  m_jobIdIsSet = true;
}

const xs_unsignedInt &
TaskManagementJobRelationListDataSelectors::getJobId() const {
  return m_jobId;
}

void TaskManagementJobRelationListDataSelectors::cleanJobId() {
  m_jobId = 0;
  m_jobIdIsSet = false;
}

bool TaskManagementJobRelationListDataSelectors::getJobIdIsSet() const {
  return m_jobIdIsSet;
}

bool TaskManagementJobRelationListDataSelectors::selects(
    const TaskManagementJobRelationData &data) const {
  if (getJobIdIsSet() &&
      (!data.getJobIdIsSet() || getJobId() != data.getJobId())) {
    return false;
  }
  return true;
}

bool TaskManagementJobRelationListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"jobId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "jobId", &m_jobId)) {
      m_jobIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobRelationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_jobIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobId", m_jobId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram