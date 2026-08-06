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

#include <keo_datagram/taskmanagement/TaskManagementJobDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobDescriptionDataElements::
    TaskManagementJobDescriptionDataElements()
    : DataElements(), m_jobIdIsSet(false), m_jobSourceIsSet(false),
      m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool TaskManagementJobDescriptionDataElements::operator==(
    const TaskManagementJobDescriptionDataElements &c_classObject) const {
  if (m_jobIdIsSet != c_classObject.m_jobIdIsSet) {
    return false;
  }
  if (m_jobSourceIsSet != c_classObject.m_jobSourceIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool TaskManagementJobDescriptionDataElements::operator!=(
    const TaskManagementJobDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobDescriptionDataElements::isEmpty() const {
  return !m_jobIdIsSet && !m_jobSourceIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

DataElements::Type
TaskManagementJobDescriptionDataElements::getDataType() const {
  return DataElements::Type::TASK_MANAGEMENT_JOB_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TaskManagementJobDescriptionDataElements::clone() const {
  return std::make_shared<TaskManagementJobDescriptionDataElements>(*this);
}

void TaskManagementJobDescriptionDataElements::setJobId() {
  m_jobIdIsSet = true;
}

void TaskManagementJobDescriptionDataElements::cleanJobId() {
  m_jobIdIsSet = false;
}

bool TaskManagementJobDescriptionDataElements::getJobIdIsSet() const {
  return m_jobIdIsSet;
}

void TaskManagementJobDescriptionDataElements::setJobSource() {
  m_jobSourceIsSet = true;
}

void TaskManagementJobDescriptionDataElements::cleanJobSource() {
  m_jobSourceIsSet = false;
}

bool TaskManagementJobDescriptionDataElements::getJobSourceIsSet() const {
  return m_jobSourceIsSet;
}

void TaskManagementJobDescriptionDataElements::setLabel() {
  m_labelIsSet = true;
}

void TaskManagementJobDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool TaskManagementJobDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void TaskManagementJobDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void TaskManagementJobDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool TaskManagementJobDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool TaskManagementJobDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"jobId", "jobSource", "label", "description"})) {
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
                                     "jobSource")) {
      m_jobSourceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "label")) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_jobIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("jobId");
  }
  if (m_jobSourceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("jobSource");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram