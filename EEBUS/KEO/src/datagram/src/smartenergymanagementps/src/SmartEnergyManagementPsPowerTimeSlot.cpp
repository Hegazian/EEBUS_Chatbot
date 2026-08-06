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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerTimeSlot.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsPowerTimeSlot::SmartEnergyManagementPsPowerTimeSlot()
    : m_scheduleIsSet(false), m_schedule(PowerTimeSlotScheduleData()),
      m_valueListIsSet(false),
      m_valueList(SmartEnergyManagementPsPowerTimeSlotValueList()),
      m_scheduleConstraintsIsSet(false),
      m_scheduleConstraints(PowerTimeSlotScheduleConstraintsData())

{}

SmartEnergyManagementPsPowerTimeSlot::SmartEnergyManagementPsPowerTimeSlot(
    const PowerTimeSlotScheduleData &c_schedule,
    const SmartEnergyManagementPsPowerTimeSlotValueList &c_valueList,
    const PowerTimeSlotScheduleConstraintsData &c_scheduleConstraints)
    : m_scheduleIsSet(true), m_schedule(c_schedule), m_valueListIsSet(true),
      m_valueList(c_valueList), m_scheduleConstraintsIsSet(true),
      m_scheduleConstraints(c_scheduleConstraints)

{}

bool SmartEnergyManagementPsPowerTimeSlot::
operator==(const SmartEnergyManagementPsPowerTimeSlot &c_classObject) const {
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

bool SmartEnergyManagementPsPowerTimeSlot::
operator!=(const SmartEnergyManagementPsPowerTimeSlot &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsPowerTimeSlot::isEmpty() const {
  return !m_scheduleIsSet && !m_valueListIsSet && !m_scheduleConstraintsIsSet;
}

void SmartEnergyManagementPsPowerTimeSlot::setSchedule(
    const PowerTimeSlotScheduleData &schedule) {
  m_schedule = schedule;
  m_scheduleIsSet = true;
}

const PowerTimeSlotScheduleData &
SmartEnergyManagementPsPowerTimeSlot::getSchedule() const {
  return m_schedule;
}

void SmartEnergyManagementPsPowerTimeSlot::cleanSchedule() {
  m_schedule = PowerTimeSlotScheduleData();
  m_scheduleIsSet = false;
}

bool SmartEnergyManagementPsPowerTimeSlot::getScheduleIsSet() const {
  return m_scheduleIsSet;
}

void SmartEnergyManagementPsPowerTimeSlot::setValueList(
    const SmartEnergyManagementPsPowerTimeSlotValueList &valueList) {
  m_valueList = valueList;
  m_valueListIsSet = true;
}

const SmartEnergyManagementPsPowerTimeSlotValueList &
SmartEnergyManagementPsPowerTimeSlot::getValueList() const {
  return m_valueList;
}

void SmartEnergyManagementPsPowerTimeSlot::cleanValueList() {
  m_valueList = SmartEnergyManagementPsPowerTimeSlotValueList();
  m_valueListIsSet = false;
}

bool SmartEnergyManagementPsPowerTimeSlot::getValueListIsSet() const {
  return m_valueListIsSet;
}

void SmartEnergyManagementPsPowerTimeSlot::setScheduleConstraints(
    const PowerTimeSlotScheduleConstraintsData &scheduleConstraints) {
  m_scheduleConstraints = scheduleConstraints;
  m_scheduleConstraintsIsSet = true;
}

const PowerTimeSlotScheduleConstraintsData &
SmartEnergyManagementPsPowerTimeSlot::getScheduleConstraints() const {
  return m_scheduleConstraints;
}

void SmartEnergyManagementPsPowerTimeSlot::cleanScheduleConstraints() {
  m_scheduleConstraints = PowerTimeSlotScheduleConstraintsData();
  m_scheduleConstraintsIsSet = false;
}

bool SmartEnergyManagementPsPowerTimeSlot::getScheduleConstraintsIsSet() const {
  return m_scheduleConstraintsIsSet;
}

bool SmartEnergyManagementPsPowerTimeSlot::fromJson(KeoJsonValue *json) {
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

std::string SmartEnergyManagementPsPowerTimeSlot::toJson() const {
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