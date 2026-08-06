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

#include <keo_datagram/taskmanagement/TaskManagementOverviewData.h>

#include <keo_datagram/taskmanagement/TaskManagementOverviewDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementOverviewData::TaskManagementOverviewData()
    : CmdData(), m_remoteControllableIsSet(false), m_remoteControllable(false),
      m_jobsActiveIsSet(false), m_jobsActive(false)

{}

TaskManagementOverviewData::TaskManagementOverviewData(
    const xs_boolean &c_remoteControllable, const xs_boolean &c_jobsActive)
    : CmdData(), m_remoteControllableIsSet(true),
      m_remoteControllable(c_remoteControllable), m_jobsActiveIsSet(true),
      m_jobsActive(c_jobsActive)

{}

bool TaskManagementOverviewData::
operator==(const TaskManagementOverviewData &c_classObject) const {
  if (m_remoteControllableIsSet != c_classObject.m_remoteControllableIsSet ||
      (m_remoteControllableIsSet &&
       (m_remoteControllable != c_classObject.m_remoteControllable))) {
    return false;
  }
  if (m_jobsActiveIsSet != c_classObject.m_jobsActiveIsSet ||
      (m_jobsActiveIsSet && (m_jobsActive != c_classObject.m_jobsActive))) {
    return false;
  }

  return true;
}

bool TaskManagementOverviewData::
operator!=(const TaskManagementOverviewData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementOverviewData::isEmpty() const {
  return !m_remoteControllableIsSet && !m_jobsActiveIsSet;
}

CmdData::Type TaskManagementOverviewData::getDataType() const {
  return CmdData::Type::TASK_MANAGEMENT_OVERVIEW_DATA_TYPE;
}

CmdDataPtr TaskManagementOverviewData::clone() const {
  return std::make_shared<TaskManagementOverviewData>(*this);
}

void TaskManagementOverviewData::setRemoteControllable(
    const xs_boolean &remoteControllable) {
  m_remoteControllable = remoteControllable;
  m_remoteControllableIsSet = true;
}

const xs_boolean &TaskManagementOverviewData::getRemoteControllable() const {
  return m_remoteControllable;
}

void TaskManagementOverviewData::cleanRemoteControllable() {
  m_remoteControllable = false;
  m_remoteControllableIsSet = false;
}

bool TaskManagementOverviewData::getRemoteControllableIsSet() const {
  return m_remoteControllableIsSet;
}

void TaskManagementOverviewData::setJobsActive(const xs_boolean &jobsActive) {
  m_jobsActive = jobsActive;
  m_jobsActiveIsSet = true;
}

const xs_boolean &TaskManagementOverviewData::getJobsActive() const {
  return m_jobsActive;
}

void TaskManagementOverviewData::cleanJobsActive() {
  m_jobsActive = false;
  m_jobsActiveIsSet = false;
}

bool TaskManagementOverviewData::getJobsActiveIsSet() const {
  return m_jobsActiveIsSet;
}

CmdDataPtr
TaskManagementOverviewData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      TaskManagementOverviewDataElementsPtr elements =
          std::dynamic_pointer_cast<TaskManagementOverviewDataElements>(
              filter.getDataElements());
      if (elements) {
        TaskManagementOverviewDataPtr dataOut =
            std::make_shared<TaskManagementOverviewData>();
        // TODO make sure to always set identifier

        if (getRemoteControllableIsSet() &&
            elements->getRemoteControllableIsSet()) {
          dataOut->setRemoteControllable(getRemoteControllable());
        }

        if (getJobsActiveIsSet() && elements->getJobsActiveIsSet()) {
          dataOut->setJobsActive(getJobsActive());
        }

        return dataOut;
      } else {
        return std::make_shared<TaskManagementOverviewData>(*this);
      }
    } else {
      return std::make_shared<TaskManagementOverviewData>(*this);
    }
  } else {
    return std::make_shared<TaskManagementOverviewData>(*this);
  }
}

bool TaskManagementOverviewData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"remoteControllable", "jobsActive"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "remoteControllable",
                                   &m_remoteControllable)) {
      m_remoteControllableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "jobsActive", &m_jobsActive)) {
      m_jobsActiveIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementOverviewData::toJson() const {
  std::string result = "[";
  if (m_remoteControllableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("remoteControllable",
                                           m_remoteControllable);
  }
  if (m_jobsActiveIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobsActive", m_jobsActive);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram