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

#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelData.h>

#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsPowerLevelData::OperatingConstraintsPowerLevelData()
    : m_sequenceIdIsSet(false), m_sequenceId(0), m_powerIsSet(false),
      m_power(std::vector<ScaledNumber>())

{}

OperatingConstraintsPowerLevelData::OperatingConstraintsPowerLevelData(
    const xs_unsignedInt &c_sequenceId,
    const std::vector<ScaledNumber> &c_power)
    : m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId), m_powerIsSet(true),
      m_power(c_power)

{}

bool OperatingConstraintsPowerLevelData::
operator==(const OperatingConstraintsPowerLevelData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_powerIsSet != c_classObject.m_powerIsSet ||
      (m_powerIsSet && (m_power != c_classObject.m_power))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsPowerLevelData::
operator!=(const OperatingConstraintsPowerLevelData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsPowerLevelData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_powerIsSet;
}

void OperatingConstraintsPowerLevelData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
OperatingConstraintsPowerLevelData::getSequenceId() const {
  return m_sequenceId;
}

void OperatingConstraintsPowerLevelData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsPowerLevelData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsPowerLevelData::setPower(
    const std::vector<ScaledNumber> &power) {
  m_power = power;
  m_powerIsSet = true;
}

const std::vector<ScaledNumber> &
OperatingConstraintsPowerLevelData::getPower() const {
  return m_power;
}

void OperatingConstraintsPowerLevelData::cleanPower() {
  m_power.clear();
  m_powerIsSet = false;
}

bool OperatingConstraintsPowerLevelData::getPowerIsSet() const {
  return m_powerIsSet;
}

OperatingConstraintsPowerLevelData OperatingConstraintsPowerLevelData::reduce(
    const OperatingConstraintsPowerLevelDataElements &elements) const {
  OperatingConstraintsPowerLevelData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getPowerIsSet() && elements.getPowerIsSet()) {
    std::vector<ScaledNumber> values;
    for (const auto &value : getPower()) {
      values.push_back(value.reduce(elements.getPower()));
    }
    dataOut.setPower(values);
  }
  return dataOut;
}

bool OperatingConstraintsPowerLevelData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"sequenceId", "power"})) {
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
        KeoJsonTransformation::getList<ScaledNumber>(
            static_cast<KeoJsonValue *>(&(*iter)), "power", &m_power)) {
      m_powerIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsPowerLevelData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_powerIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<ScaledNumber>("power", m_power);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram