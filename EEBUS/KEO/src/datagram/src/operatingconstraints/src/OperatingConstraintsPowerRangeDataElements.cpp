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

#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsPowerRangeDataElements::
    OperatingConstraintsPowerRangeDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_powerMinIsSet(false),
      m_powerMin(ScaledNumberElements()), m_powerMaxIsSet(false),
      m_powerMax(ScaledNumberElements()), m_energyMinIsSet(false),
      m_energyMin(ScaledNumberElements()), m_energyMaxIsSet(false),
      m_energyMax(ScaledNumberElements())

{}

bool OperatingConstraintsPowerRangeDataElements::operator==(
    const OperatingConstraintsPowerRangeDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_powerMinIsSet != c_classObject.m_powerMinIsSet ||
      (m_powerMinIsSet && (m_powerMin != c_classObject.m_powerMin))) {
    return false;
  }
  if (m_powerMaxIsSet != c_classObject.m_powerMaxIsSet ||
      (m_powerMaxIsSet && (m_powerMax != c_classObject.m_powerMax))) {
    return false;
  }
  if (m_energyMinIsSet != c_classObject.m_energyMinIsSet ||
      (m_energyMinIsSet && (m_energyMin != c_classObject.m_energyMin))) {
    return false;
  }
  if (m_energyMaxIsSet != c_classObject.m_energyMaxIsSet ||
      (m_energyMaxIsSet && (m_energyMax != c_classObject.m_energyMax))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsPowerRangeDataElements::operator!=(
    const OperatingConstraintsPowerRangeDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsPowerRangeDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_powerMinIsSet && !m_powerMaxIsSet &&
         !m_energyMinIsSet && !m_energyMaxIsSet;
}

DataElements::Type
OperatingConstraintsPowerRangeDataElements::getDataType() const {
  return DataElements::Type::
      OPERATING_CONSTRAINTS_POWER_RANGE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr OperatingConstraintsPowerRangeDataElements::clone() const {
  return std::make_shared<OperatingConstraintsPowerRangeDataElements>(*this);
}

void OperatingConstraintsPowerRangeDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void OperatingConstraintsPowerRangeDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsPowerRangeDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsPowerRangeDataElements::setPowerMin(
    const ScaledNumberElements &powerMin) {
  m_powerMin = powerMin;
  m_powerMinIsSet = true;
}

const ScaledNumberElements &
OperatingConstraintsPowerRangeDataElements::getPowerMin() const {
  return m_powerMin;
}

void OperatingConstraintsPowerRangeDataElements::cleanPowerMin() {
  m_powerMin = ScaledNumberElements();
  m_powerMinIsSet = false;
}

bool OperatingConstraintsPowerRangeDataElements::getPowerMinIsSet() const {
  return m_powerMinIsSet;
}

void OperatingConstraintsPowerRangeDataElements::setPowerMax(
    const ScaledNumberElements &powerMax) {
  m_powerMax = powerMax;
  m_powerMaxIsSet = true;
}

const ScaledNumberElements &
OperatingConstraintsPowerRangeDataElements::getPowerMax() const {
  return m_powerMax;
}

void OperatingConstraintsPowerRangeDataElements::cleanPowerMax() {
  m_powerMax = ScaledNumberElements();
  m_powerMaxIsSet = false;
}

bool OperatingConstraintsPowerRangeDataElements::getPowerMaxIsSet() const {
  return m_powerMaxIsSet;
}

void OperatingConstraintsPowerRangeDataElements::setEnergyMin(
    const ScaledNumberElements &energyMin) {
  m_energyMin = energyMin;
  m_energyMinIsSet = true;
}

const ScaledNumberElements &
OperatingConstraintsPowerRangeDataElements::getEnergyMin() const {
  return m_energyMin;
}

void OperatingConstraintsPowerRangeDataElements::cleanEnergyMin() {
  m_energyMin = ScaledNumberElements();
  m_energyMinIsSet = false;
}

bool OperatingConstraintsPowerRangeDataElements::getEnergyMinIsSet() const {
  return m_energyMinIsSet;
}

void OperatingConstraintsPowerRangeDataElements::setEnergyMax(
    const ScaledNumberElements &energyMax) {
  m_energyMax = energyMax;
  m_energyMaxIsSet = true;
}

const ScaledNumberElements &
OperatingConstraintsPowerRangeDataElements::getEnergyMax() const {
  return m_energyMax;
}

void OperatingConstraintsPowerRangeDataElements::cleanEnergyMax() {
  m_energyMax = ScaledNumberElements();
  m_energyMaxIsSet = false;
}

bool OperatingConstraintsPowerRangeDataElements::getEnergyMaxIsSet() const {
  return m_energyMaxIsSet;
}

bool OperatingConstraintsPowerRangeDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"sequenceId", "powerMin", "powerMax", "energyMin", "energyMax"})) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerMin", &m_powerMin)) {
      m_powerMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerMax", &m_powerMax)) {
      m_powerMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "energyMin", &m_energyMin)) {
      m_energyMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "energyMax", &m_energyMax)) {
      m_energyMaxIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsPowerRangeDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_powerMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerMin", m_powerMin);
  }
  if (m_powerMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerMax", m_powerMax);
  }
  if (m_energyMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("energyMin", m_energyMin);
  }
  if (m_energyMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("energyMax", m_energyMax);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram