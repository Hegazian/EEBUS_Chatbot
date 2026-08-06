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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerTimeSlotElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsPowerTimeSlotElements::
    SmartEnergyManagementPsPowerTimeSlotElements()
    : m_scheduleIsSet(false), m_schedule(PowerTimeSlotScheduleDataElements()),
      m_valueListIsSet(false),
      m_valueList(SmartEnergyManagementPsPowerTimeSlotValueListElements()),
      m_scheduleConstraintsIsSet(false),
      m_scheduleConstraints(PowerTimeSlotScheduleConstraintsDataElements())

{}

SmartEnergyManagementPsPowerTimeSlotElements::
    SmartEnergyManagementPsPowerTimeSlotElements(
        const PowerTimeSlotScheduleDataElements &c_schedule,
        const SmartEnergyManagementPsPowerTimeSlotValueListElements
            &c_valueList,
        const PowerTimeSlotScheduleConstraintsDataElements
            &c_scheduleConstraints)
    : m_scheduleIsSet(true), m_schedule(c_schedule), m_valueListIsSet(true),
      m_valueList(c_valueList), m_scheduleConstraintsIsSet(true),
      m_scheduleConstraints(c_scheduleConstraints)

{}

bool SmartEnergyManagementPsPowerTimeSlotElements::operator==(
    const SmartEnergyManagementPsPowerTimeSlotElements &c_classObject) const {
  if (m_scheduleIsSet != c_classObject.m_scheduleIsSet ||
      (m_scheduleIsSet && (m_schedule != c_classObject.m_schedule))) {
    return false;
  }
  if (m_valueListIsSet != c_classObject.m_valueListIsSet ||
      (m_valueListIsSet && (m_valueList != c_classObject.m_valueList))) {
    return false;
  }
  if (m_scheduleConstraintsIsSet != c_classObject.m_scheduleConstraintsIsSet ||
      (m_scheduleConstraintsIsSet &&
       (m_scheduleConstraints != c_classObject.m_scheduleConstraints))) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsPowerTimeSlotElements::operator!=(
    const SmartEnergyManagementPsPowerTimeSlotElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsPowerTimeSlotElements::isEmpty() const {
  return !m_scheduleIsSet && !m_valueListIsSet && !m_scheduleConstraintsIsSet;
}

void SmartEnergyManagementPsPowerTimeSlotElements::setSchedule(
    const PowerTimeSlotScheduleDataElements &schedule) {
  m_schedule = schedule;
  m_scheduleIsSet = true;
}

const PowerTimeSlotScheduleDataElements &
SmartEnergyManagementPsPowerTimeSlotElements::getSchedule() const {
  return m_schedule;
}

void SmartEnergyManagementPsPowerTimeSlotElements::cleanSchedule() {
  m_schedule = PowerTimeSlotScheduleDataElements();
  m_scheduleIsSet = false;
}

bool SmartEnergyManagementPsPowerTimeSlotElements::getScheduleIsSet() const {
  return m_scheduleIsSet;
}

void SmartEnergyManagementPsPowerTimeSlotElements::setValueList(
    const SmartEnergyManagementPsPowerTimeSlotValueListElements &valueList) {
  m_valueList = valueList;
  m_valueListIsSet = true;
}

const SmartEnergyManagementPsPowerTimeSlotValueListElements &
SmartEnergyManagementPsPowerTimeSlotElements::getValueList() const {
  return m_valueList;
}

void SmartEnergyManagementPsPowerTimeSlotElements::cleanValueList() {
  m_valueList = SmartEnergyManagementPsPowerTimeSlotValueListElements();
  m_valueListIsSet = false;
}

bool SmartEnergyManagementPsPowerTimeSlotElements::getValueListIsSet() const {
  return m_valueListIsSet;
}

void SmartEnergyManagementPsPowerTimeSlotElements::setScheduleConstraints(
    const PowerTimeSlotScheduleConstraintsDataElements &scheduleConstraints) {
  m_scheduleConstraints = scheduleConstraints;
  m_scheduleConstraintsIsSet = true;
}

const PowerTimeSlotScheduleConstraintsDataElements &
SmartEnergyManagementPsPowerTimeSlotElements::getScheduleConstraints() const {
  return m_scheduleConstraints;
}

void SmartEnergyManagementPsPowerTimeSlotElements::cleanScheduleConstraints() {
  m_scheduleConstraints = PowerTimeSlotScheduleConstraintsDataElements();
  m_scheduleConstraintsIsSet = false;
}

bool SmartEnergyManagementPsPowerTimeSlotElements::getScheduleConstraintsIsSet()
    const {
  return m_scheduleConstraintsIsSet;
}

bool SmartEnergyManagementPsPowerTimeSlotElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"schedule", "valueList", "scheduleConstraints"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "schedule", &m_schedule)) {
      m_scheduleIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueList", &m_valueList)) {
      m_valueListIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scheduleConstraints",
                                   &m_scheduleConstraints)) {
      m_scheduleConstraintsIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsPowerTimeSlotElements::toJson() const {
  std::string result = "[";
  if (m_scheduleIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("schedule", m_schedule);
  }
  if (m_valueListIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueList", m_valueList);
  }
  if (m_scheduleConstraintsIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scheduleConstraints",
                                           m_scheduleConstraints);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram