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

#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationData.h>

#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionThresholdRelationData::SupplyConditionThresholdRelationData()
    : m_conditionIdIsSet(false), m_conditionId(0), m_thresholdIdIsSet(false),
      m_thresholdId(std::vector<xs_unsignedInt>())

{}

SupplyConditionThresholdRelationData::SupplyConditionThresholdRelationData(
    const xs_unsignedInt &c_conditionId,
    const std::vector<xs_unsignedInt> &c_thresholdId)
    : m_conditionIdIsSet(true), m_conditionId(c_conditionId),
      m_thresholdIdIsSet(true), m_thresholdId(c_thresholdId)

{}

bool SupplyConditionThresholdRelationData::
operator==(const SupplyConditionThresholdRelationData &c_classObject) const {
  if (m_conditionIdIsSet != c_classObject.m_conditionIdIsSet ||
      (m_conditionIdIsSet && (m_conditionId != c_classObject.m_conditionId))) {
    return false;
  }
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet ||
      (m_thresholdIdIsSet && (m_thresholdId != c_classObject.m_thresholdId))) {
    return false;
  }

  return true;
}

bool SupplyConditionThresholdRelationData::
operator!=(const SupplyConditionThresholdRelationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SupplyConditionThresholdRelationData::isEmpty() const {
  return !m_conditionIdIsSet && !m_thresholdIdIsSet;
}

void SupplyConditionThresholdRelationData::setConditionId(
    const xs_unsignedInt &conditionId) {
  m_conditionId = conditionId;
  m_conditionIdIsSet = true;
}

const xs_unsignedInt &
SupplyConditionThresholdRelationData::getConditionId() const {
  return m_conditionId;
}

void SupplyConditionThresholdRelationData::cleanConditionId() {
  m_conditionId = 0;
  m_conditionIdIsSet = false;
}

bool SupplyConditionThresholdRelationData::getConditionIdIsSet() const {
  return m_conditionIdIsSet;
}

void SupplyConditionThresholdRelationData::setThresholdId(
    const std::vector<xs_unsignedInt> &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const std::vector<xs_unsignedInt> &
SupplyConditionThresholdRelationData::getThresholdId() const {
  return m_thresholdId;
}

void SupplyConditionThresholdRelationData::cleanThresholdId() {
  m_thresholdId.clear();
  m_thresholdIdIsSet = false;
}

bool SupplyConditionThresholdRelationData::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

SupplyConditionThresholdRelationData
SupplyConditionThresholdRelationData::reduce(
    const SupplyConditionThresholdRelationDataElements &elements) const {
  SupplyConditionThresholdRelationData dataOut;
  if (getConditionIdIsSet() && elements.getConditionIdIsSet()) {
    dataOut.setConditionId(getConditionId());
  }
  if (getThresholdIdIsSet() && elements.getThresholdIdIsSet()) {
    dataOut.setThresholdId(getThresholdId());
  }
  return dataOut;
}

bool SupplyConditionThresholdRelationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"conditionId", "thresholdId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "conditionId", &m_conditionId)) {
      m_conditionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() && KeoJsonTransformation::getList<xs_unsignedInt>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdId", &m_thresholdId)) {
      m_thresholdIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SupplyConditionThresholdRelationData::toJson() const {
  std::string result = "[";
  if (m_conditionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("conditionId", m_conditionId);
  }
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_unsignedInt>("thresholdId",
                                                               m_thresholdId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram