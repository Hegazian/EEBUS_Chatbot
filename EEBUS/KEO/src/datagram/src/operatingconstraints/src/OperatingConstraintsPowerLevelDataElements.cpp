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

#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsPowerLevelDataElements::
    OperatingConstraintsPowerLevelDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_powerIsSet(false),
      m_power(ScaledNumberElements())

{}

OperatingConstraintsPowerLevelDataElements::
    OperatingConstraintsPowerLevelDataElements(
        xs_boolean c_sequenceIdIsSet, const ScaledNumberElements &c_power)
    : DataElements(), m_sequenceIdIsSet(c_sequenceIdIsSet), m_powerIsSet(true),
      m_power(c_power)

{}

bool OperatingConstraintsPowerLevelDataElements::operator==(
    const OperatingConstraintsPowerLevelDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_powerIsSet != c_classObject.m_powerIsSet ||
      (m_powerIsSet && (m_power != c_classObject.m_power))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsPowerLevelDataElements::operator!=(
    const OperatingConstraintsPowerLevelDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsPowerLevelDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_powerIsSet;
}

DataElements::Type
OperatingConstraintsPowerLevelDataElements::getDataType() const {
  return DataElements::Type::
      OPERATING_CONSTRAINTS_POWER_LEVEL_DATA_ELEMENTS_TYPE;
}

DataElementsPtr OperatingConstraintsPowerLevelDataElements::clone() const {
  return std::make_shared<OperatingConstraintsPowerLevelDataElements>(*this);
}

void OperatingConstraintsPowerLevelDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void OperatingConstraintsPowerLevelDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsPowerLevelDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsPowerLevelDataElements::setPower(
    const ScaledNumberElements &power) {
  m_power = power;
  m_powerIsSet = true;
}

const ScaledNumberElements &
OperatingConstraintsPowerLevelDataElements::getPower() const {
  return m_power;
}

void OperatingConstraintsPowerLevelDataElements::cleanPower() {
  m_power = ScaledNumberElements();
  m_powerIsSet = false;
}

bool OperatingConstraintsPowerLevelDataElements::getPowerIsSet() const {
  return m_powerIsSet;
}

bool OperatingConstraintsPowerLevelDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"sequenceId", "power"})) {
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
                                   "power", &m_power)) {
      m_powerIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsPowerLevelDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_powerIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("power", m_power);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram