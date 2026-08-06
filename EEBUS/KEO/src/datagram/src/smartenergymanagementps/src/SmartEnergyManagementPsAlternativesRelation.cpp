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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternativesRelation.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsAlternativesRelation::
    SmartEnergyManagementPsAlternativesRelation()
    : m_alternativesIdIsSet(false), m_alternativesId(0),
      m_sequenceIdIsSet(false), m_sequenceId(std::vector<xs_unsignedInt>())

{}

SmartEnergyManagementPsAlternativesRelation::
    SmartEnergyManagementPsAlternativesRelation(
        const xs_unsignedInt &c_alternativesId,
        const std::vector<xs_unsignedInt> &c_sequenceId)
    : m_alternativesIdIsSet(true), m_alternativesId(c_alternativesId),
      m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId)

{}

bool SmartEnergyManagementPsAlternativesRelation::operator==(
    const SmartEnergyManagementPsAlternativesRelation &c_classObject) const {
  if (m_alternativesIdIsSet != c_classObject.m_alternativesIdIsSet ||
      (m_alternativesIdIsSet &&
       (m_alternativesId != c_classObject.m_alternativesId))) {
    return false;
  }
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsAlternativesRelation::operator!=(
    const SmartEnergyManagementPsAlternativesRelation &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsAlternativesRelation::isEmpty() const {
  return !m_alternativesIdIsSet && !m_sequenceIdIsSet;
}

void SmartEnergyManagementPsAlternativesRelation::setAlternativesId(
    const xs_unsignedInt &alternativesId) {
  m_alternativesId = alternativesId;
  m_alternativesIdIsSet = true;
}

const xs_unsignedInt &
SmartEnergyManagementPsAlternativesRelation::getAlternativesId() const {
  return m_alternativesId;
}

void SmartEnergyManagementPsAlternativesRelation::cleanAlternativesId() {
  m_alternativesId = 0;
  m_alternativesIdIsSet = false;
}

bool SmartEnergyManagementPsAlternativesRelation::getAlternativesIdIsSet()
    const {
  return m_alternativesIdIsSet;
}

void SmartEnergyManagementPsAlternativesRelation::setSequenceId(
    const std::vector<xs_unsignedInt> &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const std::vector<xs_unsignedInt> &
SmartEnergyManagementPsAlternativesRelation::getSequenceId() const {
  return m_sequenceId;
}

void SmartEnergyManagementPsAlternativesRelation::cleanSequenceId() {
  m_sequenceId.clear();
  m_sequenceIdIsSet = false;
}

bool SmartEnergyManagementPsAlternativesRelation::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

bool SmartEnergyManagementPsAlternativesRelation::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"alternativesId", "sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "alternativesId", &m_alternativesId)) {
      m_alternativesIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() && KeoJsonTransformation::getList<xs_unsignedInt>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsAlternativesRelation::toJson() const {
  std::string result = "[";
  if (m_alternativesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("alternativesId", m_alternativesId);
  }
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_unsignedInt>("sequenceId",
                                                               m_sequenceId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram