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

#include <keo_datagram/operatingconstraints/OperatingConstraintsInterruptDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsInterruptDataElements::
    OperatingConstraintsInterruptDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_isPausableIsSet(false),
      m_isStoppableIsSet(false), m_notInterruptibleAtHighPowerIsSet(false),
      m_maxCyclesPerDayIsSet(false)

{}

bool OperatingConstraintsInterruptDataElements::operator==(
    const OperatingConstraintsInterruptDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_isPausableIsSet != c_classObject.m_isPausableIsSet) {
    return false;
  }
  if (m_isStoppableIsSet != c_classObject.m_isStoppableIsSet) {
    return false;
  }
  if (m_notInterruptibleAtHighPowerIsSet !=
      c_classObject.m_notInterruptibleAtHighPowerIsSet) {
    return false;
  }
  if (m_maxCyclesPerDayIsSet != c_classObject.m_maxCyclesPerDayIsSet) {
    return false;
  }

  return true;
}

bool OperatingConstraintsInterruptDataElements::operator!=(
    const OperatingConstraintsInterruptDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsInterruptDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_isPausableIsSet && !m_isStoppableIsSet &&
         !m_notInterruptibleAtHighPowerIsSet && !m_maxCyclesPerDayIsSet;
}

DataElements::Type
OperatingConstraintsInterruptDataElements::getDataType() const {
  return DataElements::Type::OPERATING_CONSTRAINTS_INTERRUPT_DATA_ELEMENTS_TYPE;
}

DataElementsPtr OperatingConstraintsInterruptDataElements::clone() const {
  return std::make_shared<OperatingConstraintsInterruptDataElements>(*this);
}

void OperatingConstraintsInterruptDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void OperatingConstraintsInterruptDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsInterruptDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsInterruptDataElements::setIsPausable() {
  m_isPausableIsSet = true;
}

void OperatingConstraintsInterruptDataElements::cleanIsPausable() {
  m_isPausableIsSet = false;
}

bool OperatingConstraintsInterruptDataElements::getIsPausableIsSet() const {
  return m_isPausableIsSet;
}

void OperatingConstraintsInterruptDataElements::setIsStoppable() {
  m_isStoppableIsSet = true;
}

void OperatingConstraintsInterruptDataElements::cleanIsStoppable() {
  m_isStoppableIsSet = false;
}

bool OperatingConstraintsInterruptDataElements::getIsStoppableIsSet() const {
  return m_isStoppableIsSet;
}

void OperatingConstraintsInterruptDataElements::
    setNotInterruptibleAtHighPower() {
  m_notInterruptibleAtHighPowerIsSet = true;
}

void OperatingConstraintsInterruptDataElements::
    cleanNotInterruptibleAtHighPower() {
  m_notInterruptibleAtHighPowerIsSet = false;
}

bool OperatingConstraintsInterruptDataElements::
    getNotInterruptibleAtHighPowerIsSet() const {
  return m_notInterruptibleAtHighPowerIsSet;
}

void OperatingConstraintsInterruptDataElements::setMaxCyclesPerDay() {
  m_maxCyclesPerDayIsSet = true;
}

void OperatingConstraintsInterruptDataElements::cleanMaxCyclesPerDay() {
  m_maxCyclesPerDayIsSet = false;
}

bool OperatingConstraintsInterruptDataElements::getMaxCyclesPerDayIsSet()
    const {
  return m_maxCyclesPerDayIsSet;
}

bool OperatingConstraintsInterruptDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "isPausable", "isStoppable",
                   "notInterruptibleAtHighPower", "maxCyclesPerDay"})) {
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
                                     "isPausable")) {
      m_isPausableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isStoppable")) {
      m_isStoppableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "notInterruptibleAtHighPower")) {
      m_notInterruptibleAtHighPowerIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxCyclesPerDay")) {
      m_maxCyclesPerDayIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsInterruptDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_isPausableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isPausable");
  }
  if (m_isStoppableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isStoppable");
  }
  if (m_notInterruptibleAtHighPowerIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("notInterruptibleAtHighPower");
  }
  if (m_maxCyclesPerDayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxCyclesPerDay");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram