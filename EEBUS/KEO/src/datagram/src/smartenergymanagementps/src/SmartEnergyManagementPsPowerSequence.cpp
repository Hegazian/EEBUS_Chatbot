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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerSequence.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsPowerSequence::SmartEnergyManagementPsPowerSequence()
    : m_descriptionIsSet(false), m_description(PowerSequenceDescriptionData()),
      m_stateIsSet(false), m_state(PowerSequenceStateData()),
      m_scheduleIsSet(false), m_schedule(PowerSequenceScheduleData()),
      m_scheduleConstraintsIsSet(false),
      m_scheduleConstraints(PowerSequenceScheduleConstraintsData()),
      m_schedulePreferenceIsSet(false),
      m_schedulePreference(PowerSequenceSchedulePreferenceData()),
      m_operatingConstraintsInterruptIsSet(false),
      m_operatingConstraintsInterrupt(OperatingConstraintsInterruptData()),
      m_operatingConstraintsDurationIsSet(false),
      m_operatingConstraintsDuration(OperatingConstraintsDurationData()),
      m_operatingConstraintsResumeImplicationIsSet(false),
      m_operatingConstraintsResumeImplication(
          OperatingConstraintsResumeImplicationData()),
      m_powerTimeSlotIsSet(false),
      m_powerTimeSlot(std::vector<SmartEnergyManagementPsPowerTimeSlot>())

{}

bool SmartEnergyManagementPsPowerSequence::
operator==(const SmartEnergyManagementPsPowerSequence &c_classObject) const {
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

bool SmartEnergyManagementPsPowerSequence::
operator!=(const SmartEnergyManagementPsPowerSequence &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsPowerSequence::isEmpty() const {
  return !m_descriptionIsSet && !m_stateIsSet && !m_scheduleIsSet &&
         !m_scheduleConstraintsIsSet && !m_schedulePreferenceIsSet &&
         !m_operatingConstraintsInterruptIsSet &&
         !m_operatingConstraintsDurationIsSet &&
         !m_operatingConstraintsResumeImplicationIsSet && !m_powerTimeSlotIsSet;
}

void SmartEnergyManagementPsPowerSequence::setDescription(
    const PowerSequenceDescriptionData &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const PowerSequenceDescriptionData &
SmartEnergyManagementPsPowerSequence::getDescription() const {
  return m_description;
}

void SmartEnergyManagementPsPowerSequence::cleanDescription() {
  m_description = PowerSequenceDescriptionData();
  m_descriptionIsSet = false;
}

bool SmartEnergyManagementPsPowerSequence::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void SmartEnergyManagementPsPowerSequence::setState(
    const PowerSequenceStateData &state) {
  m_state = state;
  m_stateIsSet = true;
}

const PowerSequenceStateData &
SmartEnergyManagementPsPowerSequence::getState() const {
  return m_state;
}

void SmartEnergyManagementPsPowerSequence::cleanState() {
  m_state = PowerSequenceStateData();
  m_stateIsSet = false;
}

bool SmartEnergyManagementPsPowerSequence::getStateIsSet() const {
  return m_stateIsSet;
}

void SmartEnergyManagementPsPowerSequence::setSchedule(
    const PowerSequenceScheduleData &schedule) {
  m_schedule = schedule;
  m_scheduleIsSet = true;
}

const PowerSequenceScheduleData &
SmartEnergyManagementPsPowerSequence::getSchedule() const {
  return m_schedule;
}

void SmartEnergyManagementPsPowerSequence::cleanSchedule() {
  m_schedule = PowerSequenceScheduleData();
  m_scheduleIsSet = false;
}

bool SmartEnergyManagementPsPowerSequence::getScheduleIsSet() const {
  return m_scheduleIsSet;
}

void SmartEnergyManagementPsPowerSequence::setScheduleConstraints(
    const PowerSequenceScheduleConstraintsData &scheduleConstraints) {
  m_scheduleConstraints = scheduleConstraints;
  m_scheduleConstraintsIsSet = true;
}

const PowerSequenceScheduleConstraintsData &
SmartEnergyManagementPsPowerSequence::getScheduleConstraints() const {
  return m_scheduleConstraints;
}

void SmartEnergyManagementPsPowerSequence::cleanScheduleConstraints() {
  m_scheduleConstraints = PowerSequenceScheduleConstraintsData();
  m_scheduleConstraintsIsSet = false;
}

bool SmartEnergyManagementPsPowerSequence::getScheduleConstraintsIsSet() const {
  return m_scheduleConstraintsIsSet;
}

void SmartEnergyManagementPsPowerSequence::setSchedulePreference(
    const PowerSequenceSchedulePreferenceData &schedulePreference) {
  m_schedulePreference = schedulePreference;
  m_schedulePreferenceIsSet = true;
}

const PowerSequenceSchedulePreferenceData &
SmartEnergyManagementPsPowerSequence::getSchedulePreference() const {
  return m_schedulePreference;
}

void SmartEnergyManagementPsPowerSequence::cleanSchedulePreference() {
  m_schedulePreference = PowerSequenceSchedulePreferenceData();
  m_schedulePreferenceIsSet = false;
}

bool SmartEnergyManagementPsPowerSequence::getSchedulePreferenceIsSet() const {
  return m_schedulePreferenceIsSet;
}

void SmartEnergyManagementPsPowerSequence::setOperatingConstraintsInterrupt(
    const OperatingConstraintsInterruptData &operatingConstraintsInterrupt) {
  m_operatingConstraintsInterrupt = operatingConstraintsInterrupt;
  m_operatingConstraintsInterruptIsSet = true;
}

const OperatingConstraintsInterruptData &
SmartEnergyManagementPsPowerSequence::getOperatingConstraintsInterrupt() const {
  return m_operatingConstraintsInterrupt;
}

void SmartEnergyManagementPsPowerSequence::
    cleanOperatingConstraintsInterrupt() {
  m_operatingConstraintsInterrupt = OperatingConstraintsInterruptData();
  m_operatingConstraintsInterruptIsSet = false;
}

bool SmartEnergyManagementPsPowerSequence::
    getOperatingConstraintsInterruptIsSet() const {
  return m_operatingConstraintsInterruptIsSet;
}

void SmartEnergyManagementPsPowerSequence::setOperatingConstraintsDuration(
    const OperatingConstraintsDurationData &operatingConstraintsDuration) {
  m_operatingConstraintsDuration = operatingConstraintsDuration;
  m_operatingConstraintsDurationIsSet = true;
}

const OperatingConstraintsDurationData &
SmartEnergyManagementPsPowerSequence::getOperatingConstraintsDuration() const {
  return m_operatingConstraintsDuration;
}

void SmartEnergyManagementPsPowerSequence::cleanOperatingConstraintsDuration() {
  m_operatingConstraintsDuration = OperatingConstraintsDurationData();
  m_operatingConstraintsDurationIsSet = false;
}

bool SmartEnergyManagementPsPowerSequence::
    getOperatingConstraintsDurationIsSet() const {
  return m_operatingConstraintsDurationIsSet;
}

void SmartEnergyManagementPsPowerSequence::
    setOperatingConstraintsResumeImplication(
        const OperatingConstraintsResumeImplicationData
            &operatingConstraintsResumeImplication) {
  m_operatingConstraintsResumeImplication =
      operatingConstraintsResumeImplication;
  m_operatingConstraintsResumeImplicationIsSet = true;
}

const OperatingConstraintsResumeImplicationData &
SmartEnergyManagementPsPowerSequence::getOperatingConstraintsResumeImplication()
    const {
  return m_operatingConstraintsResumeImplication;
}

void SmartEnergyManagementPsPowerSequence::
    cleanOperatingConstraintsResumeImplication() {
  m_operatingConstraintsResumeImplication =
      OperatingConstraintsResumeImplicationData();
  m_operatingConstraintsResumeImplicationIsSet = false;
}

bool SmartEnergyManagementPsPowerSequence::
    getOperatingConstraintsResumeImplicationIsSet() const {
  return m_operatingConstraintsResumeImplicationIsSet;
}

void SmartEnergyManagementPsPowerSequence::setPowerTimeSlot(
    const std::vector<SmartEnergyManagementPsPowerTimeSlot> &powerTimeSlot) {
  m_powerTimeSlot = powerTimeSlot;
  m_powerTimeSlotIsSet = true;
}

const std::vector<SmartEnergyManagementPsPowerTimeSlot> &
SmartEnergyManagementPsPowerSequence::getPowerTimeSlot() const {
  return m_powerTimeSlot;
}

void SmartEnergyManagementPsPowerSequence::cleanPowerTimeSlot() {
  m_powerTimeSlot.clear();
  m_powerTimeSlotIsSet = false;
}

bool SmartEnergyManagementPsPowerSequence::getPowerTimeSlotIsSet() const {
  return m_powerTimeSlotIsSet;
}

bool SmartEnergyManagementPsPowerSequence::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::getList<SmartEnergyManagementPsPowerTimeSlot>(
            static_cast<KeoJsonValue *>(&(*iter)), "powerTimeSlot",
            &m_powerTimeSlot)) {
      m_powerTimeSlotIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsPowerSequence::toJson() const {
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
    result +=
        KeoJsonTransformation::writeList<SmartEnergyManagementPsPowerTimeSlot>(
            "powerTimeSlot", m_powerTimeSlot);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram