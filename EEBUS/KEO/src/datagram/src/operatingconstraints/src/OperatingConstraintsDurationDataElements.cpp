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

#include <keo_datagram/operatingconstraints/OperatingConstraintsDurationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsDurationDataElements::
    OperatingConstraintsDurationDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_activeDurationMinIsSet(false),
      m_activeDurationMaxIsSet(false), m_pauseDurationMinIsSet(false),
      m_pauseDurationMaxIsSet(false), m_activeDurationSumMinIsSet(false),
      m_activeDurationSumMaxIsSet(false)

{}

bool OperatingConstraintsDurationDataElements::operator==(
    const OperatingConstraintsDurationDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_activeDurationMinIsSet != c_classObject.m_activeDurationMinIsSet) {
    return false;
  }
  if (m_activeDurationMaxIsSet != c_classObject.m_activeDurationMaxIsSet) {
    return false;
  }
  if (m_pauseDurationMinIsSet != c_classObject.m_pauseDurationMinIsSet) {
    return false;
  }
  if (m_pauseDurationMaxIsSet != c_classObject.m_pauseDurationMaxIsSet) {
    return false;
  }
  if (m_activeDurationSumMinIsSet !=
      c_classObject.m_activeDurationSumMinIsSet) {
    return false;
  }
  if (m_activeDurationSumMaxIsSet !=
      c_classObject.m_activeDurationSumMaxIsSet) {
    return false;
  }

  return true;
}

bool OperatingConstraintsDurationDataElements::operator!=(
    const OperatingConstraintsDurationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsDurationDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_activeDurationMinIsSet &&
         !m_activeDurationMaxIsSet && !m_pauseDurationMinIsSet &&
         !m_pauseDurationMaxIsSet && !m_activeDurationSumMinIsSet &&
         !m_activeDurationSumMaxIsSet;
}

DataElements::Type
OperatingConstraintsDurationDataElements::getDataType() const {
  return DataElements::Type::OPERATING_CONSTRAINTS_DURATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr OperatingConstraintsDurationDataElements::clone() const {
  return std::make_shared<OperatingConstraintsDurationDataElements>(*this);
}

void OperatingConstraintsDurationDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void OperatingConstraintsDurationDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsDurationDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsDurationDataElements::setActiveDurationMin() {
  m_activeDurationMinIsSet = true;
}

void OperatingConstraintsDurationDataElements::cleanActiveDurationMin() {
  m_activeDurationMinIsSet = false;
}

bool OperatingConstraintsDurationDataElements::getActiveDurationMinIsSet()
    const {
  return m_activeDurationMinIsSet;
}

void OperatingConstraintsDurationDataElements::setActiveDurationMax() {
  m_activeDurationMaxIsSet = true;
}

void OperatingConstraintsDurationDataElements::cleanActiveDurationMax() {
  m_activeDurationMaxIsSet = false;
}

bool OperatingConstraintsDurationDataElements::getActiveDurationMaxIsSet()
    const {
  return m_activeDurationMaxIsSet;
}

void OperatingConstraintsDurationDataElements::setPauseDurationMin() {
  m_pauseDurationMinIsSet = true;
}

void OperatingConstraintsDurationDataElements::cleanPauseDurationMin() {
  m_pauseDurationMinIsSet = false;
}

bool OperatingConstraintsDurationDataElements::getPauseDurationMinIsSet()
    const {
  return m_pauseDurationMinIsSet;
}

void OperatingConstraintsDurationDataElements::setPauseDurationMax() {
  m_pauseDurationMaxIsSet = true;
}

void OperatingConstraintsDurationDataElements::cleanPauseDurationMax() {
  m_pauseDurationMaxIsSet = false;
}

bool OperatingConstraintsDurationDataElements::getPauseDurationMaxIsSet()
    const {
  return m_pauseDurationMaxIsSet;
}

void OperatingConstraintsDurationDataElements::setActiveDurationSumMin() {
  m_activeDurationSumMinIsSet = true;
}

void OperatingConstraintsDurationDataElements::cleanActiveDurationSumMin() {
  m_activeDurationSumMinIsSet = false;
}

bool OperatingConstraintsDurationDataElements::getActiveDurationSumMinIsSet()
    const {
  return m_activeDurationSumMinIsSet;
}

void OperatingConstraintsDurationDataElements::setActiveDurationSumMax() {
  m_activeDurationSumMaxIsSet = true;
}

void OperatingConstraintsDurationDataElements::cleanActiveDurationSumMax() {
  m_activeDurationSumMaxIsSet = false;
}

bool OperatingConstraintsDurationDataElements::getActiveDurationSumMaxIsSet()
    const {
  return m_activeDurationSumMaxIsSet;
}

bool OperatingConstraintsDurationDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "activeDurationMin", "activeDurationMax",
                   "pauseDurationMin", "pauseDurationMax",
                   "activeDurationSumMin", "activeDurationSumMax"})) {
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
                                     "activeDurationMin")) {
      m_activeDurationMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "activeDurationMax")) {
      m_activeDurationMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "pauseDurationMin")) {
      m_pauseDurationMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "pauseDurationMax")) {
      m_pauseDurationMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "activeDurationSumMin")) {
      m_activeDurationSumMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "activeDurationSumMax")) {
      m_activeDurationSumMaxIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsDurationDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_activeDurationMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("activeDurationMin");
  }
  if (m_activeDurationMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("activeDurationMax");
  }
  if (m_pauseDurationMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("pauseDurationMin");
  }
  if (m_pauseDurationMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("pauseDurationMax");
  }
  if (m_activeDurationSumMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("activeDurationSumMin");
  }
  if (m_activeDurationSumMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("activeDurationSumMax");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram