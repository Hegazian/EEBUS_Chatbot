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

#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeData.h>

#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsPowerRangeData::OperatingConstraintsPowerRangeData()
    : m_sequenceIdIsSet(false), m_sequenceId(0), m_powerMinIsSet(false),
      m_powerMin(ScaledNumber()), m_powerMaxIsSet(false),
      m_powerMax(ScaledNumber()), m_energyMinIsSet(false),
      m_energyMin(ScaledNumber()), m_energyMaxIsSet(false),
      m_energyMax(ScaledNumber())

{}

bool OperatingConstraintsPowerRangeData::
operator==(const OperatingConstraintsPowerRangeData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
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

bool OperatingConstraintsPowerRangeData::
operator!=(const OperatingConstraintsPowerRangeData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsPowerRangeData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_powerMinIsSet && !m_powerMaxIsSet &&
         !m_energyMinIsSet && !m_energyMaxIsSet;
}

void OperatingConstraintsPowerRangeData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
OperatingConstraintsPowerRangeData::getSequenceId() const {
  return m_sequenceId;
}

void OperatingConstraintsPowerRangeData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsPowerRangeData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsPowerRangeData::setPowerMin(
    const ScaledNumber &powerMin) {
  m_powerMin = powerMin;
  m_powerMinIsSet = true;
}

const ScaledNumber &OperatingConstraintsPowerRangeData::getPowerMin() const {
  return m_powerMin;
}

void OperatingConstraintsPowerRangeData::cleanPowerMin() {
  m_powerMin = ScaledNumber();
  m_powerMinIsSet = false;
}

bool OperatingConstraintsPowerRangeData::getPowerMinIsSet() const {
  return m_powerMinIsSet;
}

void OperatingConstraintsPowerRangeData::setPowerMax(
    const ScaledNumber &powerMax) {
  m_powerMax = powerMax;
  m_powerMaxIsSet = true;
}

const ScaledNumber &OperatingConstraintsPowerRangeData::getPowerMax() const {
  return m_powerMax;
}

void OperatingConstraintsPowerRangeData::cleanPowerMax() {
  m_powerMax = ScaledNumber();
  m_powerMaxIsSet = false;
}

bool OperatingConstraintsPowerRangeData::getPowerMaxIsSet() const {
  return m_powerMaxIsSet;
}

void OperatingConstraintsPowerRangeData::setEnergyMin(
    const ScaledNumber &energyMin) {
  m_energyMin = energyMin;
  m_energyMinIsSet = true;
}

const ScaledNumber &OperatingConstraintsPowerRangeData::getEnergyMin() const {
  return m_energyMin;
}

void OperatingConstraintsPowerRangeData::cleanEnergyMin() {
  m_energyMin = ScaledNumber();
  m_energyMinIsSet = false;
}

bool OperatingConstraintsPowerRangeData::getEnergyMinIsSet() const {
  return m_energyMinIsSet;
}

void OperatingConstraintsPowerRangeData::setEnergyMax(
    const ScaledNumber &energyMax) {
  m_energyMax = energyMax;
  m_energyMaxIsSet = true;
}

const ScaledNumber &OperatingConstraintsPowerRangeData::getEnergyMax() const {
  return m_energyMax;
}

void OperatingConstraintsPowerRangeData::cleanEnergyMax() {
  m_energyMax = ScaledNumber();
  m_energyMaxIsSet = false;
}

bool OperatingConstraintsPowerRangeData::getEnergyMaxIsSet() const {
  return m_energyMaxIsSet;
}

OperatingConstraintsPowerRangeData OperatingConstraintsPowerRangeData::reduce(
    const OperatingConstraintsPowerRangeDataElements &elements) const {
  OperatingConstraintsPowerRangeData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getPowerMinIsSet() && elements.getPowerMinIsSet()) {
    dataOut.setPowerMin(getPowerMin().reduce(elements.getPowerMin()));
  }
  if (getPowerMaxIsSet() && elements.getPowerMaxIsSet()) {
    dataOut.setPowerMax(getPowerMax().reduce(elements.getPowerMax()));
  }
  if (getEnergyMinIsSet() && elements.getEnergyMinIsSet()) {
    dataOut.setEnergyMin(getEnergyMin().reduce(elements.getEnergyMin()));
  }
  if (getEnergyMaxIsSet() && elements.getEnergyMaxIsSet()) {
    dataOut.setEnergyMax(getEnergyMax().reduce(elements.getEnergyMax()));
  }
  return dataOut;
}

bool OperatingConstraintsPowerRangeData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"sequenceId", "powerMin", "powerMax", "energyMin", "energyMax"})) {
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

std::string OperatingConstraintsPowerRangeData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
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