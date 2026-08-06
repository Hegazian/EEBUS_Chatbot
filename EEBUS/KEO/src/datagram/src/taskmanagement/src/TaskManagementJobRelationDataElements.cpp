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

#include <keo_datagram/taskmanagement/TaskManagementJobRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobRelationDataElements::TaskManagementJobRelationDataElements()
    : DataElements(), m_jobIdIsSet(false), m_directControlRelatedIsSet(false),
      m_directControlRelated(TaskManagementDirectControlRelatedElements()),
      m_hvacRelatedIsSet(false),
      m_hvacRelated(TaskManagementHvacRelatedElements()),
      m_loadControlReleatedIsSet(false),
      m_loadControlReleated(TaskManagementLoadControlReleatedElements()),
      m_powerSequencesRelatedIsSet(false),
      m_powerSequencesRelated(TaskManagementPowerSequencesRelatedElements()),
      m_smartEnergyManagementPsRelatedIsSet(false),
      m_smartEnergyManagementPsRelated(
          TaskManagementSmartEnergyManagementPsRelatedElements())

{}

bool TaskManagementJobRelationDataElements::
operator==(const TaskManagementJobRelationDataElements &c_classObject) const {
  if (m_jobIdIsSet != c_classObject.m_jobIdIsSet) {
    return false;
  }
  if (m_directControlRelatedIsSet !=
          c_classObject.m_directControlRelatedIsSet ||
      (m_directControlRelatedIsSet &&
       (m_directControlRelated != c_classObject.m_directControlRelated))) {
    return false;
  }
  if (m_hvacRelatedIsSet != c_classObject.m_hvacRelatedIsSet ||
      (m_hvacRelatedIsSet && (m_hvacRelated != c_classObject.m_hvacRelated))) {
    return false;
  }
  if (m_loadControlReleatedIsSet != c_classObject.m_loadControlReleatedIsSet ||
      (m_loadControlReleatedIsSet &&
       (m_loadControlReleated != c_classObject.m_loadControlReleated))) {
    return false;
  }
  if (m_powerSequencesRelatedIsSet !=
          c_classObject.m_powerSequencesRelatedIsSet ||
      (m_powerSequencesRelatedIsSet &&
       (m_powerSequencesRelated != c_classObject.m_powerSequencesRelated))) {
    return false;
  }
  if (m_smartEnergyManagementPsRelatedIsSet !=
          c_classObject.m_smartEnergyManagementPsRelatedIsSet ||
      (m_smartEnergyManagementPsRelatedIsSet &&
       (m_smartEnergyManagementPsRelated !=
        c_classObject.m_smartEnergyManagementPsRelated))) {
    return false;
  }

  return true;
}

bool TaskManagementJobRelationDataElements::
operator!=(const TaskManagementJobRelationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobRelationDataElements::isEmpty() const {
  return !m_jobIdIsSet && !m_directControlRelatedIsSet && !m_hvacRelatedIsSet &&
         !m_loadControlReleatedIsSet && !m_powerSequencesRelatedIsSet &&
         !m_smartEnergyManagementPsRelatedIsSet;
}

DataElements::Type TaskManagementJobRelationDataElements::getDataType() const {
  return DataElements::Type::TASK_MANAGEMENT_JOB_RELATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TaskManagementJobRelationDataElements::clone() const {
  return std::make_shared<TaskManagementJobRelationDataElements>(*this);
}

void TaskManagementJobRelationDataElements::setJobId() { m_jobIdIsSet = true; }

void TaskManagementJobRelationDataElements::cleanJobId() {
  m_jobIdIsSet = false;
}

bool TaskManagementJobRelationDataElements::getJobIdIsSet() const {
  return m_jobIdIsSet;
}

void TaskManagementJobRelationDataElements::setDirectControlRelated(
    const TaskManagementDirectControlRelatedElements &directControlRelated) {
  m_directControlRelated = directControlRelated;
  m_directControlRelatedIsSet = true;
}

const TaskManagementDirectControlRelatedElements &
TaskManagementJobRelationDataElements::getDirectControlRelated() const {
  return m_directControlRelated;
}

void TaskManagementJobRelationDataElements::cleanDirectControlRelated() {
  m_directControlRelated = TaskManagementDirectControlRelatedElements();
  m_directControlRelatedIsSet = false;
}

bool TaskManagementJobRelationDataElements::getDirectControlRelatedIsSet()
    const {
  return m_directControlRelatedIsSet;
}

void TaskManagementJobRelationDataElements::setHvacRelated(
    const TaskManagementHvacRelatedElements &hvacRelated) {
  m_hvacRelated = hvacRelated;
  m_hvacRelatedIsSet = true;
}

const TaskManagementHvacRelatedElements &
TaskManagementJobRelationDataElements::getHvacRelated() const {
  return m_hvacRelated;
}

void TaskManagementJobRelationDataElements::cleanHvacRelated() {
  m_hvacRelated = TaskManagementHvacRelatedElements();
  m_hvacRelatedIsSet = false;
}

bool TaskManagementJobRelationDataElements::getHvacRelatedIsSet() const {
  return m_hvacRelatedIsSet;
}

void TaskManagementJobRelationDataElements::setLoadControlReleated(
    const TaskManagementLoadControlReleatedElements &loadControlReleated) {
  m_loadControlReleated = loadControlReleated;
  m_loadControlReleatedIsSet = true;
}

const TaskManagementLoadControlReleatedElements &
TaskManagementJobRelationDataElements::getLoadControlReleated() const {
  return m_loadControlReleated;
}

void TaskManagementJobRelationDataElements::cleanLoadControlReleated() {
  m_loadControlReleated = TaskManagementLoadControlReleatedElements();
  m_loadControlReleatedIsSet = false;
}

bool TaskManagementJobRelationDataElements::getLoadControlReleatedIsSet()
    const {
  return m_loadControlReleatedIsSet;
}

void TaskManagementJobRelationDataElements::setPowerSequencesRelated(
    const TaskManagementPowerSequencesRelatedElements &powerSequencesRelated) {
  m_powerSequencesRelated = powerSequencesRelated;
  m_powerSequencesRelatedIsSet = true;
}

const TaskManagementPowerSequencesRelatedElements &
TaskManagementJobRelationDataElements::getPowerSequencesRelated() const {
  return m_powerSequencesRelated;
}

void TaskManagementJobRelationDataElements::cleanPowerSequencesRelated() {
  m_powerSequencesRelated = TaskManagementPowerSequencesRelatedElements();
  m_powerSequencesRelatedIsSet = false;
}

bool TaskManagementJobRelationDataElements::getPowerSequencesRelatedIsSet()
    const {
  return m_powerSequencesRelatedIsSet;
}

void TaskManagementJobRelationDataElements::setSmartEnergyManagementPsRelated(
    const TaskManagementSmartEnergyManagementPsRelatedElements
        &smartEnergyManagementPsRelated) {
  m_smartEnergyManagementPsRelated = smartEnergyManagementPsRelated;
  m_smartEnergyManagementPsRelatedIsSet = true;
}

const TaskManagementSmartEnergyManagementPsRelatedElements &
TaskManagementJobRelationDataElements::getSmartEnergyManagementPsRelated()
    const {
  return m_smartEnergyManagementPsRelated;
}

void TaskManagementJobRelationDataElements::
    cleanSmartEnergyManagementPsRelated() {
  m_smartEnergyManagementPsRelated =
      TaskManagementSmartEnergyManagementPsRelatedElements();
  m_smartEnergyManagementPsRelatedIsSet = false;
}

bool TaskManagementJobRelationDataElements::
    getSmartEnergyManagementPsRelatedIsSet() const {
  return m_smartEnergyManagementPsRelatedIsSet;
}

bool TaskManagementJobRelationDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"jobId", "directControlRelated", "hvacRelated",
                   "loadControlReleated", "powerSequencesRelated",
                   "smartEnergyManagementPsRelated"})) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "directControlRelated",
                                   &m_directControlRelated)) {
      m_directControlRelatedIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "hvacRelated", &m_hvacRelated)) {
      m_hvacRelatedIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "loadControlReleated",
                                   &m_loadControlReleated)) {
      m_loadControlReleatedIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerSequencesRelated",
                                   &m_powerSequencesRelated)) {
      m_powerSequencesRelatedIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "smartEnergyManagementPsRelated",
                                   &m_smartEnergyManagementPsRelated)) {
      m_smartEnergyManagementPsRelatedIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobRelationDataElements::toJson() const {
  std::string result = "[";
  if (m_jobIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("jobId");
  }
  if (m_directControlRelatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("directControlRelated",
                                           m_directControlRelated);
  }
  if (m_hvacRelatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("hvacRelated", m_hvacRelated);
  }
  if (m_loadControlReleatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("loadControlReleated",
                                           m_loadControlReleated);
  }
  if (m_powerSequencesRelatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerSequencesRelated",
                                           m_powerSequencesRelated);
  }
  if (m_smartEnergyManagementPsRelatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("smartEnergyManagementPsRelated",
                                           m_smartEnergyManagementPsRelated);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram