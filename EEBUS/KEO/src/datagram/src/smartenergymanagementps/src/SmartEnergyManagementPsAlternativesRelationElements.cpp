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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternativesRelationElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsAlternativesRelationElements::
    SmartEnergyManagementPsAlternativesRelationElements()
    : m_alternativesIdIsSet(false), m_sequenceIdIsSet(false)

{}

SmartEnergyManagementPsAlternativesRelationElements::
    SmartEnergyManagementPsAlternativesRelationElements(
        xs_boolean c_alternativesIdIsSet, xs_boolean c_sequenceIdIsSet)
    : m_alternativesIdIsSet(c_alternativesIdIsSet),
      m_sequenceIdIsSet(c_sequenceIdIsSet)

{}

bool SmartEnergyManagementPsAlternativesRelationElements::operator==(
    const SmartEnergyManagementPsAlternativesRelationElements &c_classObject)
    const {
  if (m_alternativesIdIsSet != c_classObject.m_alternativesIdIsSet) {
    return false;
  }
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsAlternativesRelationElements::operator!=(
    const SmartEnergyManagementPsAlternativesRelationElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsAlternativesRelationElements::isEmpty() const {
  return !m_alternativesIdIsSet && !m_sequenceIdIsSet;
}

void SmartEnergyManagementPsAlternativesRelationElements::setAlternativesId() {
  m_alternativesIdIsSet = true;
}

void SmartEnergyManagementPsAlternativesRelationElements::
    cleanAlternativesId() {
  m_alternativesIdIsSet = false;
}

bool SmartEnergyManagementPsAlternativesRelationElements::
    getAlternativesIdIsSet() const {
  return m_alternativesIdIsSet;
}

void SmartEnergyManagementPsAlternativesRelationElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void SmartEnergyManagementPsAlternativesRelationElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool SmartEnergyManagementPsAlternativesRelationElements::getSequenceIdIsSet()
    const {
  return m_sequenceIdIsSet;
}

bool SmartEnergyManagementPsAlternativesRelationElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"alternativesId", "sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "alternativesId")) {
      m_alternativesIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string
SmartEnergyManagementPsAlternativesRelationElements::toJson() const {
  std::string result = "[";
  if (m_alternativesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("alternativesId");
  }
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram