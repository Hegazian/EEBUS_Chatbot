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

#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsPowerDescriptionDataElements::
    OperatingConstraintsPowerDescriptionDataElements()
    : DataElements(), m_sequenceIdIsSet(false),
      m_positiveEnergyDirectionIsSet(false), m_powerUnitIsSet(false),
      m_energyUnitIsSet(false), m_descriptionIsSet(false)

{}

bool OperatingConstraintsPowerDescriptionDataElements::operator==(
    const OperatingConstraintsPowerDescriptionDataElements &c_classObject)
    const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
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
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool OperatingConstraintsPowerDescriptionDataElements::operator!=(
    const OperatingConstraintsPowerDescriptionDataElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsPowerDescriptionDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_positiveEnergyDirectionIsSet &&
         !m_powerUnitIsSet && !m_energyUnitIsSet && !m_descriptionIsSet;
}

DataElements::Type
OperatingConstraintsPowerDescriptionDataElements::getDataType() const {
  return DataElements::Type::
      OPERATING_CONSTRAINTS_POWER_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr
OperatingConstraintsPowerDescriptionDataElements::clone() const {
  return std::make_shared<OperatingConstraintsPowerDescriptionDataElements>(
      *this);
}

void OperatingConstraintsPowerDescriptionDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void OperatingConstraintsPowerDescriptionDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsPowerDescriptionDataElements::getSequenceIdIsSet()
    const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsPowerDescriptionDataElements::
    setPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = true;
}

void OperatingConstraintsPowerDescriptionDataElements::
    cleanPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = false;
}

bool OperatingConstraintsPowerDescriptionDataElements::
    getPositiveEnergyDirectionIsSet() const {
  return m_positiveEnergyDirectionIsSet;
}

void OperatingConstraintsPowerDescriptionDataElements::setPowerUnit() {
  m_powerUnitIsSet = true;
}

void OperatingConstraintsPowerDescriptionDataElements::cleanPowerUnit() {
  m_powerUnitIsSet = false;
}

bool OperatingConstraintsPowerDescriptionDataElements::getPowerUnitIsSet()
    const {
  return m_powerUnitIsSet;
}

void OperatingConstraintsPowerDescriptionDataElements::setEnergyUnit() {
  m_energyUnitIsSet = true;
}

void OperatingConstraintsPowerDescriptionDataElements::cleanEnergyUnit() {
  m_energyUnitIsSet = false;
}

bool OperatingConstraintsPowerDescriptionDataElements::getEnergyUnitIsSet()
    const {
  return m_energyUnitIsSet;
}

void OperatingConstraintsPowerDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void OperatingConstraintsPowerDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool OperatingConstraintsPowerDescriptionDataElements::getDescriptionIsSet()
    const {
  return m_descriptionIsSet;
}

bool OperatingConstraintsPowerDescriptionDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "positiveEnergyDirection", "powerUnit",
                   "energyUnit", "description"})) {
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
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsPowerDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
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
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram