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

#include <keo_datagram/taskmanagement/TaskManagementJobRelationData.h>

#include <keo_datagram/taskmanagement/TaskManagementJobRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobRelationData::TaskManagementJobRelationData()
    : m_jobIdIsSet(false), m_jobId(0), m_directControlRelatedIsSet(false),
      m_directControlRelated(TaskManagementDirectControlRelated()),
      m_hvacRelatedIsSet(false), m_hvacRelated(TaskManagementHvacRelated()),
      m_loadControlReleatedIsSet(false),
      m_loadControlReleated(TaskManagementLoadControlReleated()),
      m_powerSequencesRelatedIsSet(false),
      m_powerSequencesRelated(TaskManagementPowerSequencesRelated()),
      m_smartEnergyManagementPsRelatedIsSet(false),
      m_smartEnergyManagementPsRelated(
          TaskManagementSmartEnergyManagementPsRelated())

{}

bool TaskManagementJobRelationData::
operator==(const TaskManagementJobRelationData &c_classObject) const {
  if (m_jobIdIsSet != c_classObject.m_jobIdIsSet ||
      (m_jobIdIsSet && (m_jobId != c_classObject.m_jobId))) {
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

bool TaskManagementJobRelationData::
operator!=(const TaskManagementJobRelationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobRelationData::isEmpty() const {
  return !m_jobIdIsSet && !m_directControlRelatedIsSet && !m_hvacRelatedIsSet &&
         !m_loadControlReleatedIsSet && !m_powerSequencesRelatedIsSet &&
         !m_smartEnergyManagementPsRelatedIsSet;
}

void TaskManagementJobRelationData::setJobId(const xs_unsignedInt &jobId) {
  m_jobId = jobId;
  m_jobIdIsSet = true;
}

const xs_unsignedInt &TaskManagementJobRelationData::getJobId() const {
  return m_jobId;
}

void TaskManagementJobRelationData::cleanJobId() {
  m_jobId = 0;
  m_jobIdIsSet = false;
}

bool TaskManagementJobRelationData::getJobIdIsSet() const {
  return m_jobIdIsSet;
}

void TaskManagementJobRelationData::setDirectControlRelated(
    const TaskManagementDirectControlRelated &directControlRelated) {
  m_directControlRelated = directControlRelated;
  m_directControlRelatedIsSet = true;
}

const TaskManagementDirectControlRelated &
TaskManagementJobRelationData::getDirectControlRelated() const {
  return m_directControlRelated;
}

void TaskManagementJobRelationData::cleanDirectControlRelated() {
  m_directControlRelated = TaskManagementDirectControlRelated();
  m_directControlRelatedIsSet = false;
}

bool TaskManagementJobRelationData::getDirectControlRelatedIsSet() const {
  return m_directControlRelatedIsSet;
}

void TaskManagementJobRelationData::setHvacRelated(
    const TaskManagementHvacRelated &hvacRelated) {
  m_hvacRelated = hvacRelated;
  m_hvacRelatedIsSet = true;
}

const TaskManagementHvacRelated &
TaskManagementJobRelationData::getHvacRelated() const {
  return m_hvacRelated;
}

void TaskManagementJobRelationData::cleanHvacRelated() {
  m_hvacRelated = TaskManagementHvacRelated();
  m_hvacRelatedIsSet = false;
}

bool TaskManagementJobRelationData::getHvacRelatedIsSet() const {
  return m_hvacRelatedIsSet;
}

void TaskManagementJobRelationData::setLoadControlReleated(
    const TaskManagementLoadControlReleated &loadControlReleated) {
  m_loadControlReleated = loadControlReleated;
  m_loadControlReleatedIsSet = true;
}

const TaskManagementLoadControlReleated &
TaskManagementJobRelationData::getLoadControlReleated() const {
  return m_loadControlReleated;
}

void TaskManagementJobRelationData::cleanLoadControlReleated() {
  m_loadControlReleated = TaskManagementLoadControlReleated();
  m_loadControlReleatedIsSet = false;
}

bool TaskManagementJobRelationData::getLoadControlReleatedIsSet() const {
  return m_loadControlReleatedIsSet;
}

void TaskManagementJobRelationData::setPowerSequencesRelated(
    const TaskManagementPowerSequencesRelated &powerSequencesRelated) {
  m_powerSequencesRelated = powerSequencesRelated;
  m_powerSequencesRelatedIsSet = true;
}

const TaskManagementPowerSequencesRelated &
TaskManagementJobRelationData::getPowerSequencesRelated() const {
  return m_powerSequencesRelated;
}

void TaskManagementJobRelationData::cleanPowerSequencesRelated() {
  m_powerSequencesRelated = TaskManagementPowerSequencesRelated();
  m_powerSequencesRelatedIsSet = false;
}

bool TaskManagementJobRelationData::getPowerSequencesRelatedIsSet() const {
  return m_powerSequencesRelatedIsSet;
}

void TaskManagementJobRelationData::setSmartEnergyManagementPsRelated(
    const TaskManagementSmartEnergyManagementPsRelated
        &smartEnergyManagementPsRelated) {
  m_smartEnergyManagementPsRelated = smartEnergyManagementPsRelated;
  m_smartEnergyManagementPsRelatedIsSet = true;
}

const TaskManagementSmartEnergyManagementPsRelated &
TaskManagementJobRelationData::getSmartEnergyManagementPsRelated() const {
  return m_smartEnergyManagementPsRelated;
}

void TaskManagementJobRelationData::cleanSmartEnergyManagementPsRelated() {
  m_smartEnergyManagementPsRelated =
      TaskManagementSmartEnergyManagementPsRelated();
  m_smartEnergyManagementPsRelatedIsSet = false;
}

bool TaskManagementJobRelationData::getSmartEnergyManagementPsRelatedIsSet()
    const {
  return m_smartEnergyManagementPsRelatedIsSet;
}

TaskManagementJobRelationData TaskManagementJobRelationData::reduce(
    const TaskManagementJobRelationDataElements &elements) const {
  TaskManagementJobRelationData dataOut;
  if (getJobIdIsSet() && elements.getJobIdIsSet()) {
    dataOut.setJobId(getJobId());
  }
  if (getDirectControlRelatedIsSet() &&
      elements.getDirectControlRelatedIsSet()) {
    dataOut.setDirectControlRelated(
        getDirectControlRelated().reduce(elements.getDirectControlRelated()));
  }
  if (getHvacRelatedIsSet() && elements.getHvacRelatedIsSet()) {
    dataOut.setHvacRelated(getHvacRelated().reduce(elements.getHvacRelated()));
  }
  if (getLoadControlReleatedIsSet() && elements.getLoadControlReleatedIsSet()) {
    dataOut.setLoadControlReleated(
        getLoadControlReleated().reduce(elements.getLoadControlReleated()));
  }
  if (getPowerSequencesRelatedIsSet() &&
      elements.getPowerSequencesRelatedIsSet()) {
    dataOut.setPowerSequencesRelated(
        getPowerSequencesRelated().reduce(elements.getPowerSequencesRelated()));
  }
  if (getSmartEnergyManagementPsRelatedIsSet() &&
      elements.getSmartEnergyManagementPsRelatedIsSet()) {
    dataOut.setSmartEnergyManagementPsRelated(
        getSmartEnergyManagementPsRelated().reduce(
            elements.getSmartEnergyManagementPsRelated()));
  }
  return dataOut;
}

bool TaskManagementJobRelationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"jobId", "directControlRelated", "hvacRelated",
                   "loadControlReleated", "powerSequencesRelated",
                   "smartEnergyManagementPsRelated"})) {
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

std::string TaskManagementJobRelationData::toJson() const {
  std::string result = "[";
  if (m_jobIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("jobId", m_jobId);
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