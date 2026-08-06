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

#include <keo_datagram/taskmanagement/TaskManagementJobDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobDataElements::TaskManagementJobDataElements()
    : DataElements(), m_jobIdIsSet(false), m_timestampIsSet(false),
      m_jobStateIsSet(false), m_elapsedTimeIsSet(false),
      m_remainingTimeIsSet(false)

{}

bool TaskManagementJobDataElements::
operator==(const TaskManagementJobDataElements &c_classObject) const {
  if (m_jobIdIsSet != c_classObject.m_jobIdIsSet) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_jobStateIsSet != c_classObject.m_jobStateIsSet) {
    return false;
  }
  if (m_elapsedTimeIsSet != c_classObject.m_elapsedTimeIsSet) {
    return false;
  }
  if (m_remainingTimeIsSet != c_classObject.m_remainingTimeIsSet) {
    return false;
  }

  return true;
}

bool TaskManagementJobDataElements::
operator!=(const TaskManagementJobDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobDataElements::isEmpty() const {
  return !m_jobIdIsSet && !m_timestampIsSet && !m_jobStateIsSet &&
         !m_elapsedTimeIsSet && !m_remainingTimeIsSet;
}

DataElements::Type TaskManagementJobDataElements::getDataType() const {
  return DataElements::Type::TASK_MANAGEMENT_JOB_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TaskManagementJobDataElements::clone() const {
  return std::make_shared<TaskManagementJobDataElements>(*this);
}

void TaskManagementJobDataElements::setJobId() { m_jobIdIsSet = true; }

void TaskManagementJobDataElements::cleanJobId() { m_jobIdIsSet = false; }

bool TaskManagementJobDataElements::getJobIdIsSet() const {
  return m_jobIdIsSet;
}

void TaskManagementJobDataElements::setTimestamp() { m_timestampIsSet = true; }

void TaskManagementJobDataElements::cleanTimestamp() {
  m_timestampIsSet = false;
}

bool TaskManagementJobDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void TaskManagementJobDataElements::setJobState() { m_jobStateIsSet = true; }

void TaskManagementJobDataElements::cleanJobState() { m_jobStateIsSet = false; }

bool TaskManagementJobDataElements::getJobStateIsSet() const {
  return m_jobStateIsSet;
}

void TaskManagementJobDataElements::setElapsedTime() {
  m_elapsedTimeIsSet = true;
}

void TaskManagementJobDataElements::cleanElapsedTime() {
  m_elapsedTimeIsSet = false;
}

bool TaskManagementJobDataElements::getElapsedTimeIsSet() const {
  return m_elapsedTimeIsSet;
}

void TaskManagementJobDataElements::setRemainingTime() {
  m_remainingTimeIsSet = true;
}

void TaskManagementJobDataElements::cleanRemainingTime() {
  m_remainingTimeIsSet = false;
}

bool TaskManagementJobDataElements::getRemainingTimeIsSet() const {
  return m_remainingTimeIsSet;
}

bool TaskManagementJobDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"jobId", "timestamp", "jobState", "elapsedTime",
                   "remainingTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "jobId")) {
      m_jobIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timestamp")) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "jobState")) {
      m_jobStateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "elapsedTime")) {
      m_elapsedTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "remainingTime")) {
      m_remainingTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobDataElements::toJson() const {
  std::string result = "[";
  if (m_jobIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("jobId");
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_jobStateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("jobState");
  }
  if (m_elapsedTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("elapsedTime");
  }
  if (m_remainingTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("remainingTime");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram