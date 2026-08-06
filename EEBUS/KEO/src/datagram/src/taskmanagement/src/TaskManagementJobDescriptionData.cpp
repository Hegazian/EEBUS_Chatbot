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

#include <keo_datagram/taskmanagement/TaskManagementJobDescriptionData.h>

#include <keo_datagram/taskmanagement/TaskManagementJobDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobDescriptionData::TaskManagementJobDescriptionData()
    : m_jobIdIsSet(false), m_jobId(0), m_jobSourceIsSet(false),
      m_jobSource(TaskManagementJobSource()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool TaskManagementJobDescriptionData::
operator==(const TaskManagementJobDescriptionData &c_classObject) const {
  if (m_jobIdIsSet != c_classObject.m_jobIdIsSet ||
      (m_jobIdIsSet && (m_jobId != c_classObject.m_jobId))) {
    return false;
  }
  if (m_jobSourceIsSet != c_classObject.m_jobSourceIsSet ||
      (m_jobSourceIsSet && (m_jobSource != c_classObject.m_jobSource))) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet ||
      (m_labelIsSet && (m_label != c_classObject.m_label))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool TaskManagementJobDescriptionData::
operator!=(const TaskManagementJobDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobDescriptionData::isEmpty() const {
  return !m_jobIdIsSet && !m_jobSourceIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

void TaskManagementJobDescriptionData::setJobId(const xs_unsignedInt &jobId) {
  m_jobId = jobId;
  m_jobIdIsSet = true;
}

const xs_unsignedInt &TaskManagementJobDescriptionData::getJobId() const {
  return m_jobId;
}

void TaskManagementJobDescriptionData::cleanJobId() {
  m_jobId = 0;
  m_jobIdIsSet = false;
}

bool TaskManagementJobDescriptionData::getJobIdIsSet() const {
  return m_jobIdIsSet;
}

void TaskManagementJobDescriptionData::setJobSource(
    const TaskManagementJobSource &jobSource) {
  m_jobSource = jobSource;
  m_jobSourceIsSet = true;
}

const TaskManagementJobSource &
TaskManagementJobDescriptionData::getJobSource() const {
  return m_jobSource;
}

void TaskManagementJobDescriptionData::cleanJobSource() {
  m_jobSource = TaskManagementJobSource();
  m_jobSourceIsSet = false;
}

bool TaskManagementJobDescriptionData::getJobSourceIsSet() const {
  return m_jobSourceIsSet;
}

void TaskManagementJobDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &TaskManagementJobDescriptionData::getLabel() const {
  return m_label;
}

void TaskManagementJobDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool TaskManagementJobDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void TaskManagementJobDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &TaskManagementJobDescriptionData::getDescription() const {
  return m_description;
}

void TaskManagementJobDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool TaskManagementJobDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

TaskManagementJobDescriptionData TaskManagementJobDescriptionData::reduce(
    const TaskManagementJobDescriptionDataElements &elements) const {
  TaskManagementJobDescriptionData dataOut;
  if (getJobIdIsSet() && elements.getJobIdIsSet()) {
    dataOut.setJobId(getJobId());
  }
  if (getJobSourceIsSet() && elements.getJobSourceIsSet()) {
    dataOut.setJobSource(getJobSource());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool TaskManagementJobDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"jobId", "jobSource", "label", "description"})) {
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
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "label", &m_label)) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobDescriptionData::toJson() const {
  std::string result = "[";
  if (m_jobIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobId", m_jobId);
  }
  if (m_jobSourceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobSource", m_jobSource);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram