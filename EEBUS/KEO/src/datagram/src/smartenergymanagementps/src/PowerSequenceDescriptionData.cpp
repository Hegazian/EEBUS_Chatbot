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

#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionData.h>

#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceDescriptionData::PowerSequenceDescriptionData()
    : m_sequenceIdIsSet(false), m_sequenceId(0), m_descriptionIsSet(false),
      m_description(""), m_positiveEnergyDirectionIsSet(false),
      m_positiveEnergyDirection(EnergyDirection()), m_powerUnitIsSet(false),
      m_powerUnit(UnitOfMeasurement()), m_energyUnitIsSet(false),
      m_energyUnit(UnitOfMeasurement()), m_valueSourceIsSet(false),
      m_valueSource(MeasurementValueSource()), m_scopeIsSet(false),
      m_scope(PowerSequenceScope()), m_taskIdentifierIsSet(false),
      m_taskIdentifier(0), m_repetitionsTotalIsSet(false), m_repetitionsTotal(0)

{}

bool PowerSequenceDescriptionData::
operator==(const PowerSequenceDescriptionData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
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
  if (m_valueSourceIsSet != c_classObject.m_valueSourceIsSet ||
      (m_valueSourceIsSet && (m_valueSource != c_classObject.m_valueSource))) {
    return false;
  }
  if (m_scopeIsSet != c_classObject.m_scopeIsSet ||
      (m_scopeIsSet && (m_scope != c_classObject.m_scope))) {
    return false;
  }
  if (m_taskIdentifierIsSet != c_classObject.m_taskIdentifierIsSet ||
      (m_taskIdentifierIsSet &&
       (m_taskIdentifier != c_classObject.m_taskIdentifier))) {
    return false;
  }
  if (m_repetitionsTotalIsSet != c_classObject.m_repetitionsTotalIsSet ||
      (m_repetitionsTotalIsSet &&
       (m_repetitionsTotal != c_classObject.m_repetitionsTotal))) {
    return false;
  }

  return true;
}

bool PowerSequenceDescriptionData::
operator!=(const PowerSequenceDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceDescriptionData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_descriptionIsSet &&
         !m_positiveEnergyDirectionIsSet && !m_powerUnitIsSet &&
         !m_energyUnitIsSet && !m_valueSourceIsSet && !m_scopeIsSet &&
         !m_taskIdentifierIsSet && !m_repetitionsTotalIsSet;
}

void PowerSequenceDescriptionData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &PowerSequenceDescriptionData::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequenceDescriptionData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequenceDescriptionData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequenceDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &PowerSequenceDescriptionData::getDescription() const {
  return m_description;
}

void PowerSequenceDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool PowerSequenceDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void PowerSequenceDescriptionData::setPositiveEnergyDirection(
    const EnergyDirection &positiveEnergyDirection) {
  m_positiveEnergyDirection = positiveEnergyDirection;
  m_positiveEnergyDirectionIsSet = true;
}

const EnergyDirection &
PowerSequenceDescriptionData::getPositiveEnergyDirection() const {
  return m_positiveEnergyDirection;
}

void PowerSequenceDescriptionData::cleanPositiveEnergyDirection() {
  m_positiveEnergyDirection = EnergyDirection();
  m_positiveEnergyDirectionIsSet = false;
}

bool PowerSequenceDescriptionData::getPositiveEnergyDirectionIsSet() const {
  return m_positiveEnergyDirectionIsSet;
}

void PowerSequenceDescriptionData::setPowerUnit(
    const UnitOfMeasurement &powerUnit) {
  m_powerUnit = powerUnit;
  m_powerUnitIsSet = true;
}

const UnitOfMeasurement &PowerSequenceDescriptionData::getPowerUnit() const {
  return m_powerUnit;
}

void PowerSequenceDescriptionData::cleanPowerUnit() {
  m_powerUnit = UnitOfMeasurement();
  m_powerUnitIsSet = false;
}

bool PowerSequenceDescriptionData::getPowerUnitIsSet() const {
  return m_powerUnitIsSet;
}

void PowerSequenceDescriptionData::setEnergyUnit(
    const UnitOfMeasurement &energyUnit) {
  m_energyUnit = energyUnit;
  m_energyUnitIsSet = true;
}

const UnitOfMeasurement &PowerSequenceDescriptionData::getEnergyUnit() const {
  return m_energyUnit;
}

void PowerSequenceDescriptionData::cleanEnergyUnit() {
  m_energyUnit = UnitOfMeasurement();
  m_energyUnitIsSet = false;
}

bool PowerSequenceDescriptionData::getEnergyUnitIsSet() const {
  return m_energyUnitIsSet;
}

void PowerSequenceDescriptionData::setValueSource(
    const MeasurementValueSource &valueSource) {
  m_valueSource = valueSource;
  m_valueSourceIsSet = true;
}

const MeasurementValueSource &
PowerSequenceDescriptionData::getValueSource() const {
  return m_valueSource;
}

void PowerSequenceDescriptionData::cleanValueSource() {
  m_valueSource = MeasurementValueSource();
  m_valueSourceIsSet = false;
}

bool PowerSequenceDescriptionData::getValueSourceIsSet() const {
  return m_valueSourceIsSet;
}

void PowerSequenceDescriptionData::setScope(const PowerSequenceScope &scope) {
  m_scope = scope;
  m_scopeIsSet = true;
}

const PowerSequenceScope &PowerSequenceDescriptionData::getScope() const {
  return m_scope;
}

void PowerSequenceDescriptionData::cleanScope() {
  m_scope = PowerSequenceScope();
  m_scopeIsSet = false;
}

bool PowerSequenceDescriptionData::getScopeIsSet() const {
  return m_scopeIsSet;
}

void PowerSequenceDescriptionData::setTaskIdentifier(
    const xs_unsignedInt &taskIdentifier) {
  m_taskIdentifier = taskIdentifier;
  m_taskIdentifierIsSet = true;
}

const xs_unsignedInt &PowerSequenceDescriptionData::getTaskIdentifier() const {
  return m_taskIdentifier;
}

void PowerSequenceDescriptionData::cleanTaskIdentifier() {
  m_taskIdentifier = 0;
  m_taskIdentifierIsSet = false;
}

bool PowerSequenceDescriptionData::getTaskIdentifierIsSet() const {
  return m_taskIdentifierIsSet;
}

void PowerSequenceDescriptionData::setRepetitionsTotal(
    const xs_unsignedInt &repetitionsTotal) {
  m_repetitionsTotal = repetitionsTotal;
  m_repetitionsTotalIsSet = true;
}

const xs_unsignedInt &
PowerSequenceDescriptionData::getRepetitionsTotal() const {
  return m_repetitionsTotal;
}

void PowerSequenceDescriptionData::cleanRepetitionsTotal() {
  m_repetitionsTotal = 0;
  m_repetitionsTotalIsSet = false;
}

bool PowerSequenceDescriptionData::getRepetitionsTotalIsSet() const {
  return m_repetitionsTotalIsSet;
}

PowerSequenceDescriptionData PowerSequenceDescriptionData::reduce(
    const PowerSequenceDescriptionDataElements &elements) const {
  PowerSequenceDescriptionData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
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
  if (getValueSourceIsSet() && elements.getValueSourceIsSet()) {
    dataOut.setValueSource(getValueSource());
  }
  if (getScopeIsSet() && elements.getScopeIsSet()) {
    dataOut.setScope(getScope());
  }
  if (getTaskIdentifierIsSet() && elements.getTaskIdentifierIsSet()) {
    dataOut.setTaskIdentifier(getTaskIdentifier());
  }
  if (getRepetitionsTotalIsSet() && elements.getRepetitionsTotalIsSet()) {
    dataOut.setRepetitionsTotal(getRepetitionsTotal());
  }
  return dataOut;
}

bool PowerSequenceDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "description", "positiveEnergyDirection",
                   "powerUnit", "energyUnit", "valueSource", "scope",
                   "taskIdentifier", "repetitionsTotal"})) {
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
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
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
                                   "valueSource", &m_valueSource)) {
      m_valueSourceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scope", &m_scope)) {
      m_scopeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "taskIdentifier", &m_taskIdentifier)) {
      m_taskIdentifierIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "repetitionsTotal", &m_repetitionsTotal)) {
      m_repetitionsTotalIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceDescriptionData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
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
  if (m_valueSourceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueSource", m_valueSource);
  }
  if (m_scopeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scope", m_scope);
  }
  if (m_taskIdentifierIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("taskIdentifier", m_taskIdentifier);
  }
  if (m_repetitionsTotalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("repetitionsTotal", m_repetitionsTotal);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram