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

#include <keo_datagram/operatingconstraints/OperatingConstraintsDurationData.h>

#include <keo_datagram/operatingconstraints/OperatingConstraintsDurationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsDurationData::OperatingConstraintsDurationData()
    : m_sequenceIdIsSet(false), m_sequenceId(0),
      m_activeDurationMinIsSet(false), m_activeDurationMin(xs_duration()),
      m_activeDurationMaxIsSet(false), m_activeDurationMax(xs_duration()),
      m_pauseDurationMinIsSet(false), m_pauseDurationMin(xs_duration()),
      m_pauseDurationMaxIsSet(false), m_pauseDurationMax(xs_duration()),
      m_activeDurationSumMinIsSet(false), m_activeDurationSumMin(xs_duration()),
      m_activeDurationSumMaxIsSet(false), m_activeDurationSumMax(xs_duration())

{}

bool OperatingConstraintsDurationData::
operator==(const OperatingConstraintsDurationData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_activeDurationMinIsSet != c_classObject.m_activeDurationMinIsSet ||
      (m_activeDurationMinIsSet &&
       (m_activeDurationMin != c_classObject.m_activeDurationMin))) {
    return false;
  }
  if (m_activeDurationMaxIsSet != c_classObject.m_activeDurationMaxIsSet ||
      (m_activeDurationMaxIsSet &&
       (m_activeDurationMax != c_classObject.m_activeDurationMax))) {
    return false;
  }
  if (m_pauseDurationMinIsSet != c_classObject.m_pauseDurationMinIsSet ||
      (m_pauseDurationMinIsSet &&
       (m_pauseDurationMin != c_classObject.m_pauseDurationMin))) {
    return false;
  }
  if (m_pauseDurationMaxIsSet != c_classObject.m_pauseDurationMaxIsSet ||
      (m_pauseDurationMaxIsSet &&
       (m_pauseDurationMax != c_classObject.m_pauseDurationMax))) {
    return false;
  }
  if (m_activeDurationSumMinIsSet !=
          c_classObject.m_activeDurationSumMinIsSet ||
      (m_activeDurationSumMinIsSet &&
       (m_activeDurationSumMin != c_classObject.m_activeDurationSumMin))) {
    return false;
  }
  if (m_activeDurationSumMaxIsSet !=
          c_classObject.m_activeDurationSumMaxIsSet ||
      (m_activeDurationSumMaxIsSet &&
       (m_activeDurationSumMax != c_classObject.m_activeDurationSumMax))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsDurationData::
operator!=(const OperatingConstraintsDurationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsDurationData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_activeDurationMinIsSet &&
         !m_activeDurationMaxIsSet && !m_pauseDurationMinIsSet &&
         !m_pauseDurationMaxIsSet && !m_activeDurationSumMinIsSet &&
         !m_activeDurationSumMaxIsSet;
}

void OperatingConstraintsDurationData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &OperatingConstraintsDurationData::getSequenceId() const {
  return m_sequenceId;
}

void OperatingConstraintsDurationData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsDurationData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsDurationData::setActiveDurationMin(
    const xs_duration &activeDurationMin) {
  m_activeDurationMin = activeDurationMin;
  m_activeDurationMinIsSet = true;
}

const xs_duration &
OperatingConstraintsDurationData::getActiveDurationMin() const {
  return m_activeDurationMin;
}

void OperatingConstraintsDurationData::cleanActiveDurationMin() {
  m_activeDurationMin = xs_duration();
  m_activeDurationMinIsSet = false;
}

bool OperatingConstraintsDurationData::getActiveDurationMinIsSet() const {
  return m_activeDurationMinIsSet;
}

void OperatingConstraintsDurationData::setActiveDurationMax(
    const xs_duration &activeDurationMax) {
  m_activeDurationMax = activeDurationMax;
  m_activeDurationMaxIsSet = true;
}

const xs_duration &
OperatingConstraintsDurationData::getActiveDurationMax() const {
  return m_activeDurationMax;
}

void OperatingConstraintsDurationData::cleanActiveDurationMax() {
  m_activeDurationMax = xs_duration();
  m_activeDurationMaxIsSet = false;
}

bool OperatingConstraintsDurationData::getActiveDurationMaxIsSet() const {
  return m_activeDurationMaxIsSet;
}

void OperatingConstraintsDurationData::setPauseDurationMin(
    const xs_duration &pauseDurationMin) {
  m_pauseDurationMin = pauseDurationMin;
  m_pauseDurationMinIsSet = true;
}

const xs_duration &
OperatingConstraintsDurationData::getPauseDurationMin() const {
  return m_pauseDurationMin;
}

void OperatingConstraintsDurationData::cleanPauseDurationMin() {
  m_pauseDurationMin = xs_duration();
  m_pauseDurationMinIsSet = false;
}

bool OperatingConstraintsDurationData::getPauseDurationMinIsSet() const {
  return m_pauseDurationMinIsSet;
}

void OperatingConstraintsDurationData::setPauseDurationMax(
    const xs_duration &pauseDurationMax) {
  m_pauseDurationMax = pauseDurationMax;
  m_pauseDurationMaxIsSet = true;
}

const xs_duration &
OperatingConstraintsDurationData::getPauseDurationMax() const {
  return m_pauseDurationMax;
}

void OperatingConstraintsDurationData::cleanPauseDurationMax() {
  m_pauseDurationMax = xs_duration();
  m_pauseDurationMaxIsSet = false;
}

bool OperatingConstraintsDurationData::getPauseDurationMaxIsSet() const {
  return m_pauseDurationMaxIsSet;
}

void OperatingConstraintsDurationData::setActiveDurationSumMin(
    const xs_duration &activeDurationSumMin) {
  m_activeDurationSumMin = activeDurationSumMin;
  m_activeDurationSumMinIsSet = true;
}

const xs_duration &
OperatingConstraintsDurationData::getActiveDurationSumMin() const {
  return m_activeDurationSumMin;
}

void OperatingConstraintsDurationData::cleanActiveDurationSumMin() {
  m_activeDurationSumMin = xs_duration();
  m_activeDurationSumMinIsSet = false;
}

bool OperatingConstraintsDurationData::getActiveDurationSumMinIsSet() const {
  return m_activeDurationSumMinIsSet;
}

void OperatingConstraintsDurationData::setActiveDurationSumMax(
    const xs_duration &activeDurationSumMax) {
  m_activeDurationSumMax = activeDurationSumMax;
  m_activeDurationSumMaxIsSet = true;
}

const xs_duration &
OperatingConstraintsDurationData::getActiveDurationSumMax() const {
  return m_activeDurationSumMax;
}

void OperatingConstraintsDurationData::cleanActiveDurationSumMax() {
  m_activeDurationSumMax = xs_duration();
  m_activeDurationSumMaxIsSet = false;
}

bool OperatingConstraintsDurationData::getActiveDurationSumMaxIsSet() const {
  return m_activeDurationSumMaxIsSet;
}

OperatingConstraintsDurationData OperatingConstraintsDurationData::reduce(
    const OperatingConstraintsDurationDataElements &elements) const {
  OperatingConstraintsDurationData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getActiveDurationMinIsSet() && elements.getActiveDurationMinIsSet()) {
    dataOut.setActiveDurationMin(getActiveDurationMin());
  }
  if (getActiveDurationMaxIsSet() && elements.getActiveDurationMaxIsSet()) {
    dataOut.setActiveDurationMax(getActiveDurationMax());
  }
  if (getPauseDurationMinIsSet() && elements.getPauseDurationMinIsSet()) {
    dataOut.setPauseDurationMin(getPauseDurationMin());
  }
  if (getPauseDurationMaxIsSet() && elements.getPauseDurationMaxIsSet()) {
    dataOut.setPauseDurationMax(getPauseDurationMax());
  }
  if (getActiveDurationSumMinIsSet() &&
      elements.getActiveDurationSumMinIsSet()) {
    dataOut.setActiveDurationSumMin(getActiveDurationSumMin());
  }
  if (getActiveDurationSumMaxIsSet() &&
      elements.getActiveDurationSumMaxIsSet()) {
    dataOut.setActiveDurationSumMax(getActiveDurationSumMax());
  }
  return dataOut;
}

bool OperatingConstraintsDurationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "activeDurationMin", "activeDurationMax",
                   "pauseDurationMin", "pauseDurationMax",
                   "activeDurationSumMin", "activeDurationSumMax"})) {
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
                                   "activeDurationMin", &m_activeDurationMin)) {
      m_activeDurationMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "activeDurationMax", &m_activeDurationMax)) {
      m_activeDurationMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "pauseDurationMin", &m_pauseDurationMin)) {
      m_pauseDurationMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "pauseDurationMax", &m_pauseDurationMax)) {
      m_pauseDurationMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "activeDurationSumMin",
                                   &m_activeDurationSumMin)) {
      m_activeDurationSumMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "activeDurationSumMax",
                                   &m_activeDurationSumMax)) {
      m_activeDurationSumMaxIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsDurationData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_activeDurationMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("activeDurationMin", m_activeDurationMin);
  }
  if (m_activeDurationMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("activeDurationMax", m_activeDurationMax);
  }
  if (m_pauseDurationMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("pauseDurationMin", m_pauseDurationMin);
  }
  if (m_pauseDurationMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("pauseDurationMax", m_pauseDurationMax);
  }
  if (m_activeDurationSumMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("activeDurationSumMin",
                                           m_activeDurationSumMin);
  }
  if (m_activeDurationSumMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("activeDurationSumMax",
                                           m_activeDurationSumMax);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram