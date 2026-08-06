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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternativesElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsAlternativesElements::
    SmartEnergyManagementPsAlternativesElements()
    : m_relationIsSet(false),
      m_relation(SmartEnergyManagementPsAlternativesRelationElements()),
      m_powerSequenceIsSet(false),
      m_powerSequence(SmartEnergyManagementPsPowerSequenceElements())

{}

SmartEnergyManagementPsAlternativesElements::
    SmartEnergyManagementPsAlternativesElements(
        const SmartEnergyManagementPsAlternativesRelationElements &c_relation,
        const SmartEnergyManagementPsPowerSequenceElements &c_powerSequence)
    : m_relationIsSet(true), m_relation(c_relation), m_powerSequenceIsSet(true),
      m_powerSequence(c_powerSequence)

{}

bool SmartEnergyManagementPsAlternativesElements::operator==(
    const SmartEnergyManagementPsAlternativesElements &c_classObject) const {
  if (m_relationIsSet != c_classObject.m_relationIsSet ||
      (m_relationIsSet && (m_relation != c_classObject.m_relation))) {
    return false;
  }
  if (m_powerSequenceIsSet != c_classObject.m_powerSequenceIsSet ||
      (m_powerSequenceIsSet &&
       (m_powerSequence != c_classObject.m_powerSequence))) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsAlternativesElements::operator!=(
    const SmartEnergyManagementPsAlternativesElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsAlternativesElements::isEmpty() const {
  return !m_relationIsSet && !m_powerSequenceIsSet;
}

void SmartEnergyManagementPsAlternativesElements::setRelation(
    const SmartEnergyManagementPsAlternativesRelationElements &relation) {
  m_relation = relation;
  m_relationIsSet = true;
}

const SmartEnergyManagementPsAlternativesRelationElements &
SmartEnergyManagementPsAlternativesElements::getRelation() const {
  return m_relation;
}

void SmartEnergyManagementPsAlternativesElements::cleanRelation() {
  m_relation = SmartEnergyManagementPsAlternativesRelationElements();
  m_relationIsSet = false;
}

bool SmartEnergyManagementPsAlternativesElements::getRelationIsSet() const {
  return m_relationIsSet;
}

void SmartEnergyManagementPsAlternativesElements::setPowerSequence(
    const SmartEnergyManagementPsPowerSequenceElements &powerSequence) {
  m_powerSequence = powerSequence;
  m_powerSequenceIsSet = true;
}

const SmartEnergyManagementPsPowerSequenceElements &
SmartEnergyManagementPsAlternativesElements::getPowerSequence() const {
  return m_powerSequence;
}

void SmartEnergyManagementPsAlternativesElements::cleanPowerSequence() {
  m_powerSequence = SmartEnergyManagementPsPowerSequenceElements();
  m_powerSequenceIsSet = false;
}

bool SmartEnergyManagementPsAlternativesElements::getPowerSequenceIsSet()
    const {
  return m_powerSequenceIsSet;
}

bool SmartEnergyManagementPsAlternativesElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"relation", "powerSequence"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "relation", &m_relation)) {
      m_relationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerSequence", &m_powerSequence)) {
      m_powerSequenceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsAlternativesElements::toJson() const {
  std::string result = "[";
  if (m_relationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("relation", m_relation);
  }
  if (m_powerSequenceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerSequence", m_powerSequence);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram