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

#include <keo_datagram/taskmanagement/TaskManagementJobData.h>

#include <keo_datagram/taskmanagement/TaskManagementJobDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobData::TaskManagementJobData()
    : m_jobIdIsSet(false), m_jobId(0), m_timestampIsSet(false),
      m_timestamp(AbsoluteOrRelativeTime()), m_jobStateIsSet(false),
      m_jobState(TaskManagementJobState()), m_elapsedTimeIsSet(false),
      m_elapsedTime(xs_duration()), m_remainingTimeIsSet(false),
      m_remainingTime(xs_duration())

{}

bool TaskManagementJobData::
operator==(const TaskManagementJobData &c_classObject) const {
  if (m_jobIdIsSet != c_classObject.m_jobIdIsSet ||
      (m_jobIdIsSet && (m_jobId != c_classObject.m_jobId))) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_jobStateIsSet != c_classObject.m_jobStateIsSet ||
      (m_jobStateIsSet && (m_jobState != c_classObject.m_jobState))) {
    return false;
  }
  if (m_elapsedTimeIsSet != c_classObject.m_elapsedTimeIsSet ||
      (m_elapsedTimeIsSet && (m_elapsedTime != c_classObject.m_elapsedTime))) {
    return false;
  }
  if (m_remainingTimeIsSet != c_classObject.m_remainingTimeIsSet ||
      (m_remainingTimeIsSet &&
       (m_remainingTime != c_classObject.m_remainingTime))) {
    return false;
  }

  return true;
}

bool TaskManagementJobData::
operator!=(const TaskManagementJobData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobData::isEmpty() const {
  return !m_jobIdIsSet && !m_timestampIsSet && !m_jobStateIsSet &&
         !m_elapsedTimeIsSet && !m_remainingTimeIsSet;
}

void TaskManagementJobData::setJobId(const xs_unsignedInt &jobId) {
  m_jobId = jobId;
  m_jobIdIsSet = true;
}

const xs_unsignedInt &TaskManagementJobData::getJobId() const {
  return m_jobId;
}

void TaskManagementJobData::cleanJobId() {
  m_jobId = 0;
  m_jobIdIsSet = false;
}

bool TaskManagementJobData::getJobIdIsSet() const { return m_jobIdIsSet; }

void TaskManagementJobData::setTimestamp(
    const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &TaskManagementJobData::getTimestamp() const {
  return m_timestamp;
}

void TaskManagementJobData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool TaskManagementJobData::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void TaskManagementJobData::setJobState(
    const TaskManagementJobState &jobState) {
  m_jobState = jobState;
  m_jobStateIsSet = true;
}

const TaskManagementJobState &TaskManagementJobData::getJobState() const {
  return m_jobState;
}

void TaskManagementJobData::cleanJobState() {
  m_jobState = TaskManagementJobState();
  m_jobStateIsSet = false;
}

bool TaskManagementJobData::getJobStateIsSet() const { return m_jobStateIsSet; }

void TaskManagementJobData::setElapsedTime(const xs_duration &elapsedTime) {
  m_elapsedTime = elapsedTime;
  m_elapsedTimeIsSet = true;
}

const xs_duration &TaskManagementJobData::getElapsedTime() const {
  return m_elapsedTime;
}

void TaskManagementJobData::cleanElapsedTime() {
  m_elapsedTime = xs_duration();
  m_elapsedTimeIsSet = false;
}

bool TaskManagementJobData::getElapsedTimeIsSet() const {
  return m_elapsedTimeIsSet;
}

void TaskManagementJobData::setRemainingTime(const xs_duration &remainingTime) {
  m_remainingTime = remainingTime;
  m_remainingTimeIsSet = true;
}

const xs_duration &TaskManagementJobData::getRemainingTime() const {
  return m_remainingTime;
}

void TaskManagementJobData::cleanRemainingTime() {
  m_remainingTime = xs_duration();
  m_remainingTimeIsSet = false;
}

bool TaskManagementJobData::getRemainingTimeIsSet() const {
  return m_remainingTimeIsSet;
}

TaskManagementJobData TaskManagementJobData::reduce(
    const TaskManagementJobDataElements &elements) const {
  TaskManagementJobData dataOut;
  if (getJobIdIsSet() && elements.getJobIdIsSet()) {
    dataOut.setJobId(getJobId());
  }
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getJobStateIsSet() && elements.getJobStateIsSet()) {
    dataOut.setJobState(getJobState());
  }
  if (getElapsedTimeIsSet() && elements.getElapsedTimeIsSet()) {
    dataOut.setElapsedTime(getElapsedTime());
  }
  if (getRemainingTimeIsSet() && elements.getRemainingTimeIsSet()) {
    dataOut.setRemainingTime(getRemainingTime());
  }
  return dataOut;
}

bool TaskManagementJobData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"jobId", "timestamp", "jobState", "elapsedTime",
                   "remainingTime"})) {
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
                                   "timestamp", &m_timestamp)) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "jobState", &m_jobState)) {
      m_jobStateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "elapsedTime", &m_elapsedTime)) {
      m_elapsedTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "remainingTime", &m_remainingTime)) {
      m_remainingTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobData::toJson() const {
  std::string result = "[";
  if (m_jobIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobId", m_jobId);
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_jobStateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobState", m_jobState);
  }
  if (m_elapsedTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("elapsedTime", m_elapsedTime);
  }
  if (m_remainingTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("remainingTime", m_remainingTime);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram