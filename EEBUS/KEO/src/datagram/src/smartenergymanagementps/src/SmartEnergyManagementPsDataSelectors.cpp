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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsDataSelectors::SmartEnergyManagementPsDataSelectors()
    : DataSelectors(), m_alternativesRelationIsSet(false),
      m_alternativesRelation(
          PowerSequenceAlternativesRelationListDataSelectors()),
      m_powerSequenceDescriptionIsSet(false),
      m_powerSequenceDescription(PowerSequenceDescriptionListDataSelectors()),
      m_powerTimeSlotScheduleIsSet(false),
      m_powerTimeSlotSchedule(PowerTimeSlotScheduleListDataSelectors()),
      m_powerTimeSlotValueIsSet(false),
      m_powerTimeSlotValue(PowerTimeSlotValueListDataSelectors())

{}

bool SmartEnergyManagementPsDataSelectors::
operator==(const SmartEnergyManagementPsDataSelectors &c_classObject) const {
  if (m_alternativesRelationIsSet !=
          c_classObject.m_alternativesRelationIsSet ||
      (m_alternativesRelationIsSet &&
       (m_alternativesRelation != c_classObject.m_alternativesRelation))) {
    return false;
  }
  if (m_powerSequenceDescriptionIsSet !=
          c_classObject.m_powerSequenceDescriptionIsSet ||
      (m_powerSequenceDescriptionIsSet &&
       (m_powerSequenceDescription !=
        c_classObject.m_powerSequenceDescription))) {
    return false;
  }
  if (m_powerTimeSlotScheduleIsSet !=
          c_classObject.m_powerTimeSlotScheduleIsSet ||
      (m_powerTimeSlotScheduleIsSet &&
       (m_powerTimeSlotSchedule != c_classObject.m_powerTimeSlotSchedule))) {
    return false;
  }
  if (m_powerTimeSlotValueIsSet != c_classObject.m_powerTimeSlotValueIsSet ||
      (m_powerTimeSlotValueIsSet &&
       (m_powerTimeSlotValue != c_classObject.m_powerTimeSlotValue))) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsDataSelectors::
operator!=(const SmartEnergyManagementPsDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsDataSelectors::isEmpty() const {
  return !m_alternativesRelationIsSet && !m_powerSequenceDescriptionIsSet &&
         !m_powerTimeSlotScheduleIsSet && !m_powerTimeSlotValueIsSet;
}

DataSelectors::Type SmartEnergyManagementPsDataSelectors::getDataType() const {
  return DataSelectors::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr SmartEnergyManagementPsDataSelectors::clone() const {
  return std::make_shared<SmartEnergyManagementPsDataSelectors>(*this);
}

void SmartEnergyManagementPsDataSelectors::setAlternativesRelation(
    const PowerSequenceAlternativesRelationListDataSelectors
        &alternativesRelation) {
  m_alternativesRelation = alternativesRelation;
  m_alternativesRelationIsSet = true;
}

const PowerSequenceAlternativesRelationListDataSelectors &
SmartEnergyManagementPsDataSelectors::getAlternativesRelation() const {
  return m_alternativesRelation;
}

void SmartEnergyManagementPsDataSelectors::cleanAlternativesRelation() {
  m_alternativesRelation = PowerSequenceAlternativesRelationListDataSelectors();
  m_alternativesRelationIsSet = false;
}

bool SmartEnergyManagementPsDataSelectors::getAlternativesRelationIsSet()
    const {
  return m_alternativesRelationIsSet;
}

void SmartEnergyManagementPsDataSelectors::setPowerSequenceDescription(
    const PowerSequenceDescriptionListDataSelectors &powerSequenceDescription) {
  m_powerSequenceDescription = powerSequenceDescription;
  m_powerSequenceDescriptionIsSet = true;
}

const PowerSequenceDescriptionListDataSelectors &
SmartEnergyManagementPsDataSelectors::getPowerSequenceDescription() const {
  return m_powerSequenceDescription;
}

void SmartEnergyManagementPsDataSelectors::cleanPowerSequenceDescription() {
  m_powerSequenceDescription = PowerSequenceDescriptionListDataSelectors();
  m_powerSequenceDescriptionIsSet = false;
}

bool SmartEnergyManagementPsDataSelectors::getPowerSequenceDescriptionIsSet()
    const {
  return m_powerSequenceDescriptionIsSet;
}

void SmartEnergyManagementPsDataSelectors::setPowerTimeSlotSchedule(
    const PowerTimeSlotScheduleListDataSelectors &powerTimeSlotSchedule) {
  m_powerTimeSlotSchedule = powerTimeSlotSchedule;
  m_powerTimeSlotScheduleIsSet = true;
}

const PowerTimeSlotScheduleListDataSelectors &
SmartEnergyManagementPsDataSelectors::getPowerTimeSlotSchedule() const {
  return m_powerTimeSlotSchedule;
}

void SmartEnergyManagementPsDataSelectors::cleanPowerTimeSlotSchedule() {
  m_powerTimeSlotSchedule = PowerTimeSlotScheduleListDataSelectors();
  m_powerTimeSlotScheduleIsSet = false;
}

bool SmartEnergyManagementPsDataSelectors::getPowerTimeSlotScheduleIsSet()
    const {
  return m_powerTimeSlotScheduleIsSet;
}

void SmartEnergyManagementPsDataSelectors::setPowerTimeSlotValue(
    const PowerTimeSlotValueListDataSelectors &powerTimeSlotValue) {
  m_powerTimeSlotValue = powerTimeSlotValue;
  m_powerTimeSlotValueIsSet = true;
}

const PowerTimeSlotValueListDataSelectors &
SmartEnergyManagementPsDataSelectors::getPowerTimeSlotValue() const {
  return m_powerTimeSlotValue;
}

void SmartEnergyManagementPsDataSelectors::cleanPowerTimeSlotValue() {
  m_powerTimeSlotValue = PowerTimeSlotValueListDataSelectors();
  m_powerTimeSlotValueIsSet = false;
}

bool SmartEnergyManagementPsDataSelectors::getPowerTimeSlotValueIsSet() const {
  return m_powerTimeSlotValueIsSet;
}

bool SmartEnergyManagementPsDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"alternativesRelation", "powerSequenceDescription",
                   "powerTimeSlotSchedule", "powerTimeSlotValue"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "alternativesRelation",
                                   &m_alternativesRelation)) {
      m_alternativesRelationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerSequenceDescription",
                                   &m_powerSequenceDescription)) {
      m_powerSequenceDescriptionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerTimeSlotSchedule",
                                   &m_powerTimeSlotSchedule)) {
      m_powerTimeSlotScheduleIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerTimeSlotValue",
                                   &m_powerTimeSlotValue)) {
      m_powerTimeSlotValueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsDataSelectors::toJson() const {
  std::string result = "[";
  if (m_alternativesRelationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("alternativesRelation",
                                           m_alternativesRelation);
  }
  if (m_powerSequenceDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerSequenceDescription",
                                           m_powerSequenceDescription);
  }
  if (m_powerTimeSlotScheduleIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerTimeSlotSchedule",
                                           m_powerTimeSlotSchedule);
  }
  if (m_powerTimeSlotValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerTimeSlotValue",
                                           m_powerTimeSlotValue);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram