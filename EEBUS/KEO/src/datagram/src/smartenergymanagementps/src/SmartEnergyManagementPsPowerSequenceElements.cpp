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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerSequenceElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsPowerSequenceElements::
    SmartEnergyManagementPsPowerSequenceElements()
    : m_descriptionIsSet(false),
      m_description(PowerSequenceDescriptionDataElements()),
      m_stateIsSet(false), m_state(PowerSequenceStateDataElements()),
      m_scheduleIsSet(false), m_schedule(PowerSequenceScheduleDataElements()),
      m_scheduleConstraintsIsSet(false),
      m_scheduleConstraints(PowerSequenceScheduleConstraintsDataElements()),
      m_schedulePreferenceIsSet(false),
      m_schedulePreference(PowerSequenceSchedulePreferenceDataElements()),
      m_operatingConstraintsInterruptIsSet(false),
      m_operatingConstraintsInterrupt(
          OperatingConstraintsInterruptDataElements()),
      m_operatingConstraintsDurationIsSet(false),
      m_operatingConstraintsDuration(
          OperatingConstraintsDurationDataElements()),
      m_operatingConstraintsResumeImplicationIsSet(false),
      m_operatingConstraintsResumeImplication(
          OperatingConstraintsResumeImplicationDataElements()),
      m_powerTimeSlotIsSet(false),
      m_powerTimeSlot(SmartEnergyManagementPsPowerTimeSlotElements())

{}

bool SmartEnergyManagementPsPowerSequenceElements::operator==(
    const SmartEnergyManagementPsPowerSequenceElements &c_classObject) const {
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }
  if (m_stateIsSet != c_classObject.m_stateIsSet ||
      (m_stateIsSet && (m_state != c_classObject.m_state))) {
    return false;
  }
  if (m_scheduleIsSet != c_classObject.m_scheduleIsSet ||
      (m_scheduleIsSet && (m_schedule != c_classObject.m_schedule))) {
    return false;
  }
  if (m_scheduleConstraintsIsSet != c_classObject.m_scheduleConstraintsIsSet ||
      (m_scheduleConstraintsIsSet &&
       (m_scheduleConstraints != c_classObject.m_scheduleConstraints))) {
    return false;
  }
  if (m_schedulePreferenceIsSet != c_classObject.m_schedulePreferenceIsSet ||
      (m_schedulePreferenceIsSet &&
       (m_schedulePreference != c_classObject.m_schedulePreference))) {
    return false;
  }
  if (m_operatingConstraintsInterruptIsSet !=
          c_classObject.m_operatingConstraintsInterruptIsSet ||
      (m_operatingConstraintsInterruptIsSet &&
       (m_operatingConstraintsInterrupt !=
        c_classObject.m_operatingConstraintsInterrupt))) {
    return false;
  }
  if (m_operatingConstraintsDurationIsSet !=
          c_classObject.m_operatingConstraintsDurationIsSet ||
      (m_operatingConstraintsDurationIsSet &&
       (m_operatingConstraintsDuration !=
        c_classObject.m_operatingConstraintsDuration))) {
    return false;
  }
  if (m_operatingConstraintsResumeImplicationIsSet !=
          c_classObject.m_operatingConstraintsResumeImplicationIsSet ||
      (m_operatingConstraintsResumeImplicationIsSet &&
       (m_operatingConstraintsResumeImplication !=
        c_classObject.m_operatingConstraintsResumeImplication))) {
    return false;
  }
  if (m_powerTimeSlotIsSet != c_classObject.m_powerTimeSlotIsSet ||
      (m_powerTimeSlotIsSet &&
       (m_powerTimeSlot != c_classObject.m_powerTimeSlot))) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsPowerSequenceElements::operator!=(
    const SmartEnergyManagementPsPowerSequenceElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsPowerSequenceElements::isEmpty() const {
  return !m_descriptionIsSet && !m_stateIsSet && !m_scheduleIsSet &&
         !m_scheduleConstraintsIsSet && !m_schedulePreferenceIsSet &&
         !m_operatingConstraintsInterruptIsSet &&
         !m_operatingConstraintsDurationIsSet &&
         !m_operatingConstraintsResumeImplicationIsSet && !m_powerTimeSlotIsSet;
}

void SmartEnergyManagementPsPowerSequenceElements::setDescription(
    const PowerSequenceDescriptionDataElements &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const PowerSequenceDescriptionDataElements &
SmartEnergyManagementPsPowerSequenceElements::getDescription() const {
  return m_description;
}

void SmartEnergyManagementPsPowerSequenceElements::cleanDescription() {
  m_description = PowerSequenceDescriptionDataElements();
  m_descriptionIsSet = false;
}

bool SmartEnergyManagementPsPowerSequenceElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void SmartEnergyManagementPsPowerSequenceElements::setState(
    const PowerSequenceStateDataElements &state) {
  m_state = state;
  m_stateIsSet = true;
}

const PowerSequenceStateDataElements &
SmartEnergyManagementPsPowerSequenceElements::getState() const {
  return m_state;
}

void SmartEnergyManagementPsPowerSequenceElements::cleanState() {
  m_state = PowerSequenceStateDataElements();
  m_stateIsSet = false;
}

bool SmartEnergyManagementPsPowerSequenceElements::getStateIsSet() const {
  return m_stateIsSet;
}

void SmartEnergyManagementPsPowerSequenceElements::setSchedule(
    const PowerSequenceScheduleDataElements &schedule) {
  m_schedule = schedule;
  m_scheduleIsSet = true;
}

const PowerSequenceScheduleDataElements &
SmartEnergyManagementPsPowerSequenceElements::getSchedule() const {
  return m_schedule;
}

void SmartEnergyManagementPsPowerSequenceElements::cleanSchedule() {
  m_schedule = PowerSequenceScheduleDataElements();
  m_scheduleIsSet = false;
}

bool SmartEnergyManagementPsPowerSequenceElements::getScheduleIsSet() const {
  return m_scheduleIsSet;
}

void SmartEnergyManagementPsPowerSequenceElements::setScheduleConstraints(
    const PowerSequenceScheduleConstraintsDataElements &scheduleConstraints) {
  m_scheduleConstraints = scheduleConstraints;
  m_scheduleConstraintsIsSet = true;
}

const PowerSequenceScheduleConstraintsDataElements &
SmartEnergyManagementPsPowerSequenceElements::getScheduleConstraints() const {
  return m_scheduleConstraints;
}

void SmartEnergyManagementPsPowerSequenceElements::cleanScheduleConstraints() {
  m_scheduleConstraints = PowerSequenceScheduleConstraintsDataElements();
  m_scheduleConstraintsIsSet = false;
}

bool SmartEnergyManagementPsPowerSequenceElements::getScheduleConstraintsIsSet()
    const {
  return m_scheduleConstraintsIsSet;
}

void SmartEnergyManagementPsPowerSequenceElements::setSchedulePreference(
    const PowerSequenceSchedulePreferenceDataElements &schedulePreference) {
  m_schedulePreference = schedulePreference;
  m_schedulePreferenceIsSet = true;
}

const PowerSequenceSchedulePreferenceDataElements &
SmartEnergyManagementPsPowerSequenceElements::getSchedulePreference() const {
  return m_schedulePreference;
}

void SmartEnergyManagementPsPowerSequenceElements::cleanSchedulePreference() {
  m_schedulePreference = PowerSequenceSchedulePreferenceDataElements();
  m_schedulePreferenceIsSet = false;
}

bool SmartEnergyManagementPsPowerSequenceElements::getSchedulePreferenceIsSet()
    const {
  return m_schedulePreferenceIsSet;
}

void SmartEnergyManagementPsPowerSequenceElements::
    setOperatingConstraintsInterrupt(
        const OperatingConstraintsInterruptDataElements
            &operatingConstraintsInterrupt) {
  m_operatingConstraintsInterrupt = operatingConstraintsInterrupt;
  m_operatingConstraintsInterruptIsSet = true;
}

const OperatingConstraintsInterruptDataElements &
SmartEnergyManagementPsPowerSequenceElements::getOperatingConstraintsInterrupt()
    const {
  return m_operatingConstraintsInterrupt;
}

void SmartEnergyManagementPsPowerSequenceElements::
    cleanOperatingConstraintsInterrupt() {
  m_operatingConstraintsInterrupt = OperatingConstraintsInterruptDataElements();
  m_operatingConstraintsInterruptIsSet = false;
}

bool SmartEnergyManagementPsPowerSequenceElements::
    getOperatingConstraintsInterruptIsSet() const {
  return m_operatingConstraintsInterruptIsSet;
}

void SmartEnergyManagementPsPowerSequenceElements::
    setOperatingConstraintsDuration(
        const OperatingConstraintsDurationDataElements
            &operatingConstraintsDuration) {
  m_operatingConstraintsDuration = operatingConstraintsDuration;
  m_operatingConstraintsDurationIsSet = true;
}

const OperatingConstraintsDurationDataElements &
SmartEnergyManagementPsPowerSequenceElements::getOperatingConstraintsDuration()
    const {
  return m_operatingConstraintsDuration;
}

void SmartEnergyManagementPsPowerSequenceElements::
    cleanOperatingConstraintsDuration() {
  m_operatingConstraintsDuration = OperatingConstraintsDurationDataElements();
  m_operatingConstraintsDurationIsSet = false;
}

bool SmartEnergyManagementPsPowerSequenceElements::
    getOperatingConstraintsDurationIsSet() const {
  return m_operatingConstraintsDurationIsSet;
}

void SmartEnergyManagementPsPowerSequenceElements::
    setOperatingConstraintsResumeImplication(
        const OperatingConstraintsResumeImplicationDataElements
            &operatingConstraintsResumeImplication) {
  m_operatingConstraintsResumeImplication =
      operatingConstraintsResumeImplication;
  m_operatingConstraintsResumeImplicationIsSet = true;
}

const OperatingConstraintsResumeImplicationDataElements &
SmartEnergyManagementPsPowerSequenceElements::
    getOperatingConstraintsResumeImplication() const {
  return m_operatingConstraintsResumeImplication;
}

void SmartEnergyManagementPsPowerSequenceElements::
    cleanOperatingConstraintsResumeImplication() {
  m_operatingConstraintsResumeImplication =
      OperatingConstraintsResumeImplicationDataElements();
  m_operatingConstraintsResumeImplicationIsSet = false;
}

bool SmartEnergyManagementPsPowerSequenceElements::
    getOperatingConstraintsResumeImplicationIsSet() const {
  return m_operatingConstraintsResumeImplicationIsSet;
}

void SmartEnergyManagementPsPowerSequenceElements::setPowerTimeSlot(
    const SmartEnergyManagementPsPowerTimeSlotElements &powerTimeSlot) {
  m_powerTimeSlot = powerTimeSlot;
  m_powerTimeSlotIsSet = true;
}

const SmartEnergyManagementPsPowerTimeSlotElements &
SmartEnergyManagementPsPowerSequenceElements::getPowerTimeSlot() const {
  return m_powerTimeSlot;
}

void SmartEnergyManagementPsPowerSequenceElements::cleanPowerTimeSlot() {
  m_powerTimeSlot = SmartEnergyManagementPsPowerTimeSlotElements();
  m_powerTimeSlotIsSet = false;
}

bool SmartEnergyManagementPsPowerSequenceElements::getPowerTimeSlotIsSet()
    const {
  return m_powerTimeSlotIsSet;
}

bool SmartEnergyManagementPsPowerSequenceElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"description", "state", "schedule", "scheduleConstraints",
                   "schedulePreference", "operatingConstraintsInterrupt",
                   "operatingConstraintsDuration",
                   "operatingConstraintsResumeImplication", "powerTimeSlot"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "state", &m_state)) {
      m_stateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "schedule", &m_schedule)) {
      m_scheduleIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scheduleConstraints",
                                   &m_scheduleConstraints)) {
      m_scheduleConstraintsIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "schedulePreference",
                                   &m_schedulePreference)) {
      m_schedulePreferenceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "operatingConstraintsInterrupt",
                                   &m_operatingConstraintsInterrupt)) {
      m_operatingConstraintsInterruptIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "operatingConstraintsDuration",
                                   &m_operatingConstraintsDuration)) {
      m_operatingConstraintsDurationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "operatingConstraintsResumeImplication",
                                   &m_operatingConstraintsResumeImplication)) {
      m_operatingConstraintsResumeImplicationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerTimeSlot", &m_powerTimeSlot)) {
      m_powerTimeSlotIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsPowerSequenceElements::toJson() const {
  std::string result = "[";
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  if (m_stateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("state", m_state);
  }
  if (m_scheduleIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("schedule", m_schedule);
  }
  if (m_scheduleConstraintsIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scheduleConstraints",
                                           m_scheduleConstraints);
  }
  if (m_schedulePreferenceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("schedulePreference",
                                           m_schedulePreference);
  }
  if (m_operatingConstraintsInterruptIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("operatingConstraintsInterrupt",
                                           m_operatingConstraintsInterrupt);
  }
  if (m_operatingConstraintsDurationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("operatingConstraintsDuration",
                                           m_operatingConstraintsDuration);
  }
  if (m_operatingConstraintsResumeImplicationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("operatingConstraintsResumeImplication",
                                     m_operatingConstraintsResumeImplication);
  }
  if (m_powerTimeSlotIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerTimeSlot", m_powerTimeSlot);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram