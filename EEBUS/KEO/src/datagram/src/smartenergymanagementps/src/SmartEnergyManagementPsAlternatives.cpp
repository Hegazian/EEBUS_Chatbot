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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternatives.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsAlternatives::SmartEnergyManagementPsAlternatives()
    : m_relationIsSet(false),
      m_relation(SmartEnergyManagementPsAlternativesRelation()),
      m_powerSequenceIsSet(false),
      m_powerSequence(std::vector<SmartEnergyManagementPsPowerSequence>())

{}

SmartEnergyManagementPsAlternatives::SmartEnergyManagementPsAlternatives(
    const SmartEnergyManagementPsAlternativesRelation &c_relation,
    const std::vector<SmartEnergyManagementPsPowerSequence> &c_powerSequence)
    : m_relationIsSet(true), m_relation(c_relation), m_powerSequenceIsSet(true),
      m_powerSequence(c_powerSequence)

{}

bool SmartEnergyManagementPsAlternatives::
operator==(const SmartEnergyManagementPsAlternatives &c_classObject) const {
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

bool SmartEnergyManagementPsAlternatives::
operator!=(const SmartEnergyManagementPsAlternatives &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsAlternatives::isEmpty() const {
  return !m_relationIsSet && !m_powerSequenceIsSet;
}

void SmartEnergyManagementPsAlternatives::setRelation(
    const SmartEnergyManagementPsAlternativesRelation &relation) {
  m_relation = relation;
  m_relationIsSet = true;
}

const SmartEnergyManagementPsAlternativesRelation &
SmartEnergyManagementPsAlternatives::getRelation() const {
  return m_relation;
}

void SmartEnergyManagementPsAlternatives::cleanRelation() {
  m_relation = SmartEnergyManagementPsAlternativesRelation();
  m_relationIsSet = false;
}

bool SmartEnergyManagementPsAlternatives::getRelationIsSet() const {
  return m_relationIsSet;
}

void SmartEnergyManagementPsAlternatives::setPowerSequence(
    const std::vector<SmartEnergyManagementPsPowerSequence> &powerSequence) {
  m_powerSequence = powerSequence;
  m_powerSequenceIsSet = true;
}

const std::vector<SmartEnergyManagementPsPowerSequence> &
SmartEnergyManagementPsAlternatives::getPowerSequence() const {
  return m_powerSequence;
}

void SmartEnergyManagementPsAlternatives::cleanPowerSequence() {
  m_powerSequence.clear();
  m_powerSequenceIsSet = false;
}

bool SmartEnergyManagementPsAlternatives::getPowerSequenceIsSet() const {
  return m_powerSequenceIsSet;
}

bool SmartEnergyManagementPsAlternatives::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::getList<SmartEnergyManagementPsPowerSequence>(
            static_cast<KeoJsonValue *>(&(*iter)), "powerSequence",
            &m_powerSequence)) {
      m_powerSequenceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsAlternatives::toJson() const {
  std::string result = "[";
  if (m_relationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("relation", m_relation);
  }
  if (m_powerSequenceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<SmartEnergyManagementPsPowerSequence>(
            "powerSequence", m_powerSequence);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram