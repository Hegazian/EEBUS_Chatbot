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

#include <keo_datagram/taskmanagement/TaskManagementJobDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobDescriptionListDataSelectors::
    TaskManagementJobDescriptionListDataSelectors()
    : DataSelectors(), m_jobIdIsSet(false), m_jobId(0), m_jobSourceIsSet(false),
      m_jobSource(TaskManagementJobSource())

{}

TaskManagementJobDescriptionListDataSelectors::
    TaskManagementJobDescriptionListDataSelectors(
        const xs_unsignedInt &c_jobId,
        const TaskManagementJobSource &c_jobSource)
    : DataSelectors(), m_jobIdIsSet(true), m_jobId(c_jobId),
      m_jobSourceIsSet(true), m_jobSource(c_jobSource)

{}

bool TaskManagementJobDescriptionListDataSelectors::operator==(
    const TaskManagementJobDescriptionListDataSelectors &c_classObject) const {
  if (m_jobIdIsSet != c_classObject.m_jobIdIsSet ||
      (m_jobIdIsSet && (m_jobId != c_classObject.m_jobId))) {
    return false;
  }
  if (m_jobSourceIsSet != c_classObject.m_jobSourceIsSet ||
      (m_jobSourceIsSet && (m_jobSource != c_classObject.m_jobSource))) {
    return false;
  }

  return true;
}

bool TaskManagementJobDescriptionListDataSelectors::operator!=(
    const TaskManagementJobDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobDescriptionListDataSelectors::isEmpty() const {
  return !m_jobIdIsSet && !m_jobSourceIsSet;
}

DataSelectors::Type
TaskManagementJobDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TaskManagementJobDescriptionListDataSelectors::clone() const {
  return std::make_shared<TaskManagementJobDescriptionListDataSelectors>(*this);
}

void TaskManagementJobDescriptionListDataSelectors::setJobId(
    const xs_unsignedInt &jobId) {
  m_jobId = jobId;
  m_jobIdIsSet = true;
}

const xs_unsignedInt &
TaskManagementJobDescriptionListDataSelectors::getJobId() const {
  return m_jobId;
}

void TaskManagementJobDescriptionListDataSelectors::cleanJobId() {
  m_jobId = 0;
  m_jobIdIsSet = false;
}

bool TaskManagementJobDescriptionListDataSelectors::getJobIdIsSet() const {
  return m_jobIdIsSet;
}

void TaskManagementJobDescriptionListDataSelectors::setJobSource(
    const TaskManagementJobSource &jobSource) {
  m_jobSource = jobSource;
  m_jobSourceIsSet = true;
}

const TaskManagementJobSource &
TaskManagementJobDescriptionListDataSelectors::getJobSource() const {
  return m_jobSource;
}

void TaskManagementJobDescriptionListDataSelectors::cleanJobSource() {
  m_jobSource = TaskManagementJobSource();
  m_jobSourceIsSet = false;
}

bool TaskManagementJobDescriptionListDataSelectors::getJobSourceIsSet() const {
  return m_jobSourceIsSet;
}

bool TaskManagementJobDescriptionListDataSelectors::selects(
    const TaskManagementJobDescriptionData &data) const {
  if (getJobIdIsSet() &&
      (!data.getJobIdIsSet() || getJobId() != data.getJobId())) {
    return false;
  }
  if (getJobSourceIsSet() &&
      (!data.getJobSourceIsSet() || getJobSource() != data.getJobSource())) {
    return false;
  }
  return true;
}

bool TaskManagementJobDescriptionListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"jobId", "jobSource"})) {
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
                                   "jobSource", &m_jobSource)) {
      m_jobSourceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_jobIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobId", m_jobId);
  }
  if (m_jobSourceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobSource", m_jobSource);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram