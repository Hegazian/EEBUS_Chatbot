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

#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceDescriptionDataElements::PowerSequenceDescriptionDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_descriptionIsSet(false),
      m_positiveEnergyDirectionIsSet(false), m_powerUnitIsSet(false),
      m_energyUnitIsSet(false), m_valueSourceIsSet(false), m_scopeIsSet(false),
      m_taskIdentifierIsSet(false), m_repetitionsTotalIsSet(false)

{}

bool PowerSequenceDescriptionDataElements::
operator==(const PowerSequenceDescriptionDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }
  if (m_positiveEnergyDirectionIsSet !=
      c_classObject.m_positiveEnergyDirectionIsSet) {
    return false;
  }
  if (m_powerUnitIsSet != c_classObject.m_powerUnitIsSet) {
    return false;
  }
  if (m_energyUnitIsSet != c_classObject.m_energyUnitIsSet) {
    return false;
  }
  if (m_valueSourceIsSet != c_classObject.m_valueSourceIsSet) {
    return false;
  }
  if (m_scopeIsSet != c_classObject.m_scopeIsSet) {
    return false;
  }
  if (m_taskIdentifierIsSet != c_classObject.m_taskIdentifierIsSet) {
    return false;
  }
  if (m_repetitionsTotalIsSet != c_classObject.m_repetitionsTotalIsSet) {
    return false;
  }

  return true;
}

bool PowerSequenceDescriptionDataElements::
operator!=(const PowerSequenceDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceDescriptionDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_descriptionIsSet &&
         !m_positiveEnergyDirectionIsSet && !m_powerUnitIsSet &&
         !m_energyUnitIsSet && !m_valueSourceIsSet && !m_scopeIsSet &&
         !m_taskIdentifierIsSet && !m_repetitionsTotalIsSet;
}

DataElements::Type PowerSequenceDescriptionDataElements::getDataType() const {
  return DataElements::Type::POWER_SEQUENCE_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr PowerSequenceDescriptionDataElements::clone() const {
  return std::make_shared<PowerSequenceDescriptionDataElements>(*this);
}

void PowerSequenceDescriptionDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerSequenceDescriptionDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerSequenceDescriptionDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequenceDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void PowerSequenceDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool PowerSequenceDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void PowerSequenceDescriptionDataElements::setPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = true;
}

void PowerSequenceDescriptionDataElements::cleanPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = false;
}

bool PowerSequenceDescriptionDataElements::getPositiveEnergyDirectionIsSet()
    const {
  return m_positiveEnergyDirectionIsSet;
}

void PowerSequenceDescriptionDataElements::setPowerUnit() {
  m_powerUnitIsSet = true;
}

void PowerSequenceDescriptionDataElements::cleanPowerUnit() {
  m_powerUnitIsSet = false;
}

bool PowerSequenceDescriptionDataElements::getPowerUnitIsSet() const {
  return m_powerUnitIsSet;
}

void PowerSequenceDescriptionDataElements::setEnergyUnit() {
  m_energyUnitIsSet = true;
}

void PowerSequenceDescriptionDataElements::cleanEnergyUnit() {
  m_energyUnitIsSet = false;
}

bool PowerSequenceDescriptionDataElements::getEnergyUnitIsSet() const {
  return m_energyUnitIsSet;
}

void PowerSequenceDescriptionDataElements::setValueSource() {
  m_valueSourceIsSet = true;
}

void PowerSequenceDescriptionDataElements::cleanValueSource() {
  m_valueSourceIsSet = false;
}

bool PowerSequenceDescriptionDataElements::getValueSourceIsSet() const {
  return m_valueSourceIsSet;
}

void PowerSequenceDescriptionDataElements::setScope() { m_scopeIsSet = true; }

void PowerSequenceDescriptionDataElements::cleanScope() {
  m_scopeIsSet = false;
}

bool PowerSequenceDescriptionDataElements::getScopeIsSet() const {
  return m_scopeIsSet;
}

void PowerSequenceDescriptionDataElements::setTaskIdentifier() {
  m_taskIdentifierIsSet = true;
}

void PowerSequenceDescriptionDataElements::cleanTaskIdentifier() {
  m_taskIdentifierIsSet = false;
}

bool PowerSequenceDescriptionDataElements::getTaskIdentifierIsSet() const {
  return m_taskIdentifierIsSet;
}

void PowerSequenceDescriptionDataElements::setRepetitionsTotal() {
  m_repetitionsTotalIsSet = true;
}

void PowerSequenceDescriptionDataElements::cleanRepetitionsTotal() {
  m_repetitionsTotalIsSet = false;
}

bool PowerSequenceDescriptionDataElements::getRepetitionsTotalIsSet() const {
  return m_repetitionsTotalIsSet;
}

bool PowerSequenceDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "description", "positiveEnergyDirection",
                   "powerUnit", "energyUnit", "valueSource", "scope",
                   "taskIdentifier", "repetitionsTotal"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "positiveEnergyDirection")) {
      m_positiveEnergyDirectionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "powerUnit")) {
      m_powerUnitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "energyUnit")) {
      m_energyUnitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "valueSource")) {
      m_valueSourceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "scope")) {
      m_scopeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "taskIdentifier")) {
      m_taskIdentifierIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "repetitionsTotal")) {
      m_repetitionsTotalIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  if (m_positiveEnergyDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("positiveEnergyDirection");
  }
  if (m_powerUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("powerUnit");
  }
  if (m_energyUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("energyUnit");
  }
  if (m_valueSourceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("valueSource");
  }
  if (m_scopeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scope");
  }
  if (m_taskIdentifierIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("taskIdentifier");
  }
  if (m_repetitionsTotalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("repetitionsTotal");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram