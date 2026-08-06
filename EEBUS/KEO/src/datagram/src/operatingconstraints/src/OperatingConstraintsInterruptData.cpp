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

#include <keo_datagram/operatingconstraints/OperatingConstraintsInterruptData.h>

#include <keo_datagram/operatingconstraints/OperatingConstraintsInterruptDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsInterruptData::OperatingConstraintsInterruptData()
    : m_sequenceIdIsSet(false), m_sequenceId(0), m_isPausableIsSet(false),
      m_isPausable(false), m_isStoppableIsSet(false), m_isStoppable(false),
      m_notInterruptibleAtHighPowerIsSet(false),
      m_notInterruptibleAtHighPower(false), m_maxCyclesPerDayIsSet(false),
      m_maxCyclesPerDay(0)

{}

bool OperatingConstraintsInterruptData::
operator==(const OperatingConstraintsInterruptData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_isPausableIsSet != c_classObject.m_isPausableIsSet ||
      (m_isPausableIsSet && (m_isPausable != c_classObject.m_isPausable))) {
    return false;
  }
  if (m_isStoppableIsSet != c_classObject.m_isStoppableIsSet ||
      (m_isStoppableIsSet && (m_isStoppable != c_classObject.m_isStoppable))) {
    return false;
  }
  if (m_notInterruptibleAtHighPowerIsSet !=
          c_classObject.m_notInterruptibleAtHighPowerIsSet ||
      (m_notInterruptibleAtHighPowerIsSet &&
       (m_notInterruptibleAtHighPower !=
        c_classObject.m_notInterruptibleAtHighPower))) {
    return false;
  }
  if (m_maxCyclesPerDayIsSet != c_classObject.m_maxCyclesPerDayIsSet ||
      (m_maxCyclesPerDayIsSet &&
       (m_maxCyclesPerDay != c_classObject.m_maxCyclesPerDay))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsInterruptData::
operator!=(const OperatingConstraintsInterruptData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsInterruptData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_isPausableIsSet && !m_isStoppableIsSet &&
         !m_notInterruptibleAtHighPowerIsSet && !m_maxCyclesPerDayIsSet;
}

void OperatingConstraintsInterruptData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &OperatingConstraintsInterruptData::getSequenceId() const {
  return m_sequenceId;
}

void OperatingConstraintsInterruptData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsInterruptData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsInterruptData::setIsPausable(
    const xs_boolean &isPausable) {
  m_isPausable = isPausable;
  m_isPausableIsSet = true;
}

const xs_boolean &OperatingConstraintsInterruptData::getIsPausable() const {
  return m_isPausable;
}

void OperatingConstraintsInterruptData::cleanIsPausable() {
  m_isPausable = false;
  m_isPausableIsSet = false;
}

bool OperatingConstraintsInterruptData::getIsPausableIsSet() const {
  return m_isPausableIsSet;
}

void OperatingConstraintsInterruptData::setIsStoppable(
    const xs_boolean &isStoppable) {
  m_isStoppable = isStoppable;
  m_isStoppableIsSet = true;
}

const xs_boolean &OperatingConstraintsInterruptData::getIsStoppable() const {
  return m_isStoppable;
}

void OperatingConstraintsInterruptData::cleanIsStoppable() {
  m_isStoppable = false;
  m_isStoppableIsSet = false;
}

bool OperatingConstraintsInterruptData::getIsStoppableIsSet() const {
  return m_isStoppableIsSet;
}

void OperatingConstraintsInterruptData::setNotInterruptibleAtHighPower(
    const xs_boolean &notInterruptibleAtHighPower) {
  m_notInterruptibleAtHighPower = notInterruptibleAtHighPower;
  m_notInterruptibleAtHighPowerIsSet = true;
}

const xs_boolean &
OperatingConstraintsInterruptData::getNotInterruptibleAtHighPower() const {
  return m_notInterruptibleAtHighPower;
}

void OperatingConstraintsInterruptData::cleanNotInterruptibleAtHighPower() {
  m_notInterruptibleAtHighPower = false;
  m_notInterruptibleAtHighPowerIsSet = false;
}

bool OperatingConstraintsInterruptData::getNotInterruptibleAtHighPowerIsSet()
    const {
  return m_notInterruptibleAtHighPowerIsSet;
}

void OperatingConstraintsInterruptData::setMaxCyclesPerDay(
    const xs_unsignedInt &maxCyclesPerDay) {
  m_maxCyclesPerDay = maxCyclesPerDay;
  m_maxCyclesPerDayIsSet = true;
}

const xs_unsignedInt &
OperatingConstraintsInterruptData::getMaxCyclesPerDay() const {
  return m_maxCyclesPerDay;
}

void OperatingConstraintsInterruptData::cleanMaxCyclesPerDay() {
  m_maxCyclesPerDay = 0;
  m_maxCyclesPerDayIsSet = false;
}

bool OperatingConstraintsInterruptData::getMaxCyclesPerDayIsSet() const {
  return m_maxCyclesPerDayIsSet;
}

OperatingConstraintsInterruptData OperatingConstraintsInterruptData::reduce(
    const OperatingConstraintsInterruptDataElements &elements) const {
  OperatingConstraintsInterruptData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getIsPausableIsSet() && elements.getIsPausableIsSet()) {
    dataOut.setIsPausable(getIsPausable());
  }
  if (getIsStoppableIsSet() && elements.getIsStoppableIsSet()) {
    dataOut.setIsStoppable(getIsStoppable());
  }
  if (getNotInterruptibleAtHighPowerIsSet() &&
      elements.getNotInterruptibleAtHighPowerIsSet()) {
    dataOut.setNotInterruptibleAtHighPower(getNotInterruptibleAtHighPower());
  }
  if (getMaxCyclesPerDayIsSet() && elements.getMaxCyclesPerDayIsSet()) {
    dataOut.setMaxCyclesPerDay(getMaxCyclesPerDay());
  }
  return dataOut;
}

bool OperatingConstraintsInterruptData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "isPausable", "isStoppable",
                   "notInterruptibleAtHighPower", "maxCyclesPerDay"})) {
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
                                   "isPausable", &m_isPausable)) {
      m_isPausableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isStoppable", &m_isStoppable)) {
      m_isStoppableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "notInterruptibleAtHighPower",
                                   &m_notInterruptibleAtHighPower)) {
      m_notInterruptibleAtHighPowerIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxCyclesPerDay", &m_maxCyclesPerDay)) {
      m_maxCyclesPerDayIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsInterruptData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_isPausableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isPausable", m_isPausable);
  }
  if (m_isStoppableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isStoppable", m_isStoppable);
  }
  if (m_notInterruptibleAtHighPowerIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("notInterruptibleAtHighPower",
                                           m_notInterruptibleAtHighPower);
  }
  if (m_maxCyclesPerDayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("maxCyclesPerDay", m_maxCyclesPerDay);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram