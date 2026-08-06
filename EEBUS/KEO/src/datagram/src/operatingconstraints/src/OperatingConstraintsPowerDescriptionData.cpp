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

#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionData.h>

#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsPowerDescriptionData::
    OperatingConstraintsPowerDescriptionData()
    : m_sequenceIdIsSet(false), m_sequenceId(0),
      m_positiveEnergyDirectionIsSet(false),
      m_positiveEnergyDirection(EnergyDirection()), m_powerUnitIsSet(false),
      m_powerUnit(UnitOfMeasurement()), m_energyUnitIsSet(false),
      m_energyUnit(UnitOfMeasurement()), m_descriptionIsSet(false),
      m_description("")

{}

bool OperatingConstraintsPowerDescriptionData::operator==(
    const OperatingConstraintsPowerDescriptionData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_positiveEnergyDirectionIsSet !=
          c_classObject.m_positiveEnergyDirectionIsSet ||
      (m_positiveEnergyDirectionIsSet &&
       (m_positiveEnergyDirection !=
        c_classObject.m_positiveEnergyDirection))) {
    return false;
  }
  if (m_powerUnitIsSet != c_classObject.m_powerUnitIsSet ||
      (m_powerUnitIsSet && (m_powerUnit != c_classObject.m_powerUnit))) {
    return false;
  }
  if (m_energyUnitIsSet != c_classObject.m_energyUnitIsSet ||
      (m_energyUnitIsSet && (m_energyUnit != c_classObject.m_energyUnit))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsPowerDescriptionData::operator!=(
    const OperatingConstraintsPowerDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsPowerDescriptionData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_positiveEnergyDirectionIsSet &&
         !m_powerUnitIsSet && !m_energyUnitIsSet && !m_descriptionIsSet;
}

void OperatingConstraintsPowerDescriptionData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
OperatingConstraintsPowerDescriptionData::getSequenceId() const {
  return m_sequenceId;
}

void OperatingConstraintsPowerDescriptionData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsPowerDescriptionData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsPowerDescriptionData::setPositiveEnergyDirection(
    const EnergyDirection &positiveEnergyDirection) {
  m_positiveEnergyDirection = positiveEnergyDirection;
  m_positiveEnergyDirectionIsSet = true;
}

const EnergyDirection &
OperatingConstraintsPowerDescriptionData::getPositiveEnergyDirection() const {
  return m_positiveEnergyDirection;
}

void OperatingConstraintsPowerDescriptionData::cleanPositiveEnergyDirection() {
  m_positiveEnergyDirection = EnergyDirection();
  m_positiveEnergyDirectionIsSet = false;
}

bool OperatingConstraintsPowerDescriptionData::getPositiveEnergyDirectionIsSet()
    const {
  return m_positiveEnergyDirectionIsSet;
}

void OperatingConstraintsPowerDescriptionData::setPowerUnit(
    const UnitOfMeasurement &powerUnit) {
  m_powerUnit = powerUnit;
  m_powerUnitIsSet = true;
}

const UnitOfMeasurement &
OperatingConstraintsPowerDescriptionData::getPowerUnit() const {
  return m_powerUnit;
}

void OperatingConstraintsPowerDescriptionData::cleanPowerUnit() {
  m_powerUnit = UnitOfMeasurement();
  m_powerUnitIsSet = false;
}

bool OperatingConstraintsPowerDescriptionData::getPowerUnitIsSet() const {
  return m_powerUnitIsSet;
}

void OperatingConstraintsPowerDescriptionData::setEnergyUnit(
    const UnitOfMeasurement &energyUnit) {
  m_energyUnit = energyUnit;
  m_energyUnitIsSet = true;
}

const UnitOfMeasurement &
OperatingConstraintsPowerDescriptionData::getEnergyUnit() const {
  return m_energyUnit;
}

void OperatingConstraintsPowerDescriptionData::cleanEnergyUnit() {
  m_energyUnit = UnitOfMeasurement();
  m_energyUnitIsSet = false;
}

bool OperatingConstraintsPowerDescriptionData::getEnergyUnitIsSet() const {
  return m_energyUnitIsSet;
}

void OperatingConstraintsPowerDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &
OperatingConstraintsPowerDescriptionData::getDescription() const {
  return m_description;
}

void OperatingConstraintsPowerDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool OperatingConstraintsPowerDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

OperatingConstraintsPowerDescriptionData
OperatingConstraintsPowerDescriptionData::reduce(
    const OperatingConstraintsPowerDescriptionDataElements &elements) const {
  OperatingConstraintsPowerDescriptionData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getPositiveEnergyDirectionIsSet() &&
      elements.getPositiveEnergyDirectionIsSet()) {
    dataOut.setPositiveEnergyDirection(getPositiveEnergyDirection());
  }
  if (getPowerUnitIsSet() && elements.getPowerUnitIsSet()) {
    dataOut.setPowerUnit(getPowerUnit());
  }
  if (getEnergyUnitIsSet() && elements.getEnergyUnitIsSet()) {
    dataOut.setEnergyUnit(getEnergyUnit());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool OperatingConstraintsPowerDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "positiveEnergyDirection", "powerUnit",
                   "energyUnit", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "positiveEnergyDirection",
                                   &m_positiveEnergyDirection)) {
      m_positiveEnergyDirectionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerUnit", &m_powerUnit)) {
      m_powerUnitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "energyUnit", &m_energyUnit)) {
      m_energyUnitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsPowerDescriptionData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_positiveEnergyDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("positiveEnergyDirection",
                                           m_positiveEnergyDirection);
  }
  if (m_powerUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerUnit", m_powerUnit);
  }
  if (m_energyUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("energyUnit", m_energyUnit);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram