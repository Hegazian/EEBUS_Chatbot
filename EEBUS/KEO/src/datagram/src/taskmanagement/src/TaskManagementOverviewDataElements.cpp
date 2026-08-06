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

#include <keo_datagram/taskmanagement/TaskManagementOverviewDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementOverviewDataElements::TaskManagementOverviewDataElements()
    : DataElements(), m_remoteControllableIsSet(false), m_jobsActiveIsSet(false)

{}

TaskManagementOverviewDataElements::TaskManagementOverviewDataElements(
    xs_boolean c_remoteControllableIsSet, xs_boolean c_jobsActiveIsSet)
    : DataElements(), m_remoteControllableIsSet(c_remoteControllableIsSet),
      m_jobsActiveIsSet(c_jobsActiveIsSet)

{}

bool TaskManagementOverviewDataElements::
operator==(const TaskManagementOverviewDataElements &c_classObject) const {
  if (m_remoteControllableIsSet != c_classObject.m_remoteControllableIsSet) {
    return false;
  }
  if (m_jobsActiveIsSet != c_classObject.m_jobsActiveIsSet) {
    return false;
  }

  return true;
}

bool TaskManagementOverviewDataElements::
operator!=(const TaskManagementOverviewDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementOverviewDataElements::isEmpty() const {
  return !m_remoteControllableIsSet && !m_jobsActiveIsSet;
}

DataElements::Type TaskManagementOverviewDataElements::getDataType() const {
  return DataElements::Type::TASK_MANAGEMENT_OVERVIEW_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TaskManagementOverviewDataElements::clone() const {
  return std::make_shared<TaskManagementOverviewDataElements>(*this);
}

void TaskManagementOverviewDataElements::setRemoteControllable() {
  m_remoteControllableIsSet = true;
}

void TaskManagementOverviewDataElements::cleanRemoteControllable() {
  m_remoteControllableIsSet = false;
}

bool TaskManagementOverviewDataElements::getRemoteControllableIsSet() const {
  return m_remoteControllableIsSet;
}

void TaskManagementOverviewDataElements::setJobsActive() {
  m_jobsActiveIsSet = true;
}

void TaskManagementOverviewDataElements::cleanJobsActive() {
  m_jobsActiveIsSet = false;
}

bool TaskManagementOverviewDataElements::getJobsActiveIsSet() const {
  return m_jobsActiveIsSet;
}

bool TaskManagementOverviewDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"remoteControllable", "jobsActive"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "remoteControllable")) {
      m_remoteControllableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "jobsActive")) {
      m_jobsActiveIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementOverviewDataElements::toJson() const {
  std::string result = "[";
  if (m_remoteControllableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("remoteControllable");
  }
  if (m_jobsActiveIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("jobsActive");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram