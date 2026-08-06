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

#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionThresholdRelationListDataSelectors::
    SupplyConditionThresholdRelationListDataSelectors()
    : DataSelectors(), m_conditionIdIsSet(false), m_conditionId(0),
      m_thresholdIdIsSet(false), m_thresholdId(0)

{}

SupplyConditionThresholdRelationListDataSelectors::
    SupplyConditionThresholdRelationListDataSelectors(
        const xs_unsignedInt &c_conditionId,
        const xs_unsignedInt &c_thresholdId)
    : DataSelectors(), m_conditionIdIsSet(true), m_conditionId(c_conditionId),
      m_thresholdIdIsSet(true), m_thresholdId(c_thresholdId)

{}

bool SupplyConditionThresholdRelationListDataSelectors::operator==(
    const SupplyConditionThresholdRelationListDataSelectors &c_classObject)
    const {
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

bool SupplyConditionThresholdRelationListDataSelectors::operator!=(
    const SupplyConditionThresholdRelationListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool SupplyConditionThresholdRelationListDataSelectors::isEmpty() const {
  return !m_conditionIdIsSet && !m_thresholdIdIsSet;
}

DataSelectors::Type
SupplyConditionThresholdRelationListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
SupplyConditionThresholdRelationListDataSelectors::clone() const {
  return std::make_shared<SupplyConditionThresholdRelationListDataSelectors>(
      *this);
}

void SupplyConditionThresholdRelationListDataSelectors::setConditionId(
    const xs_unsignedInt &conditionId) {
  m_conditionId = conditionId;
  m_conditionIdIsSet = true;
}

const xs_unsignedInt &
SupplyConditionThresholdRelationListDataSelectors::getConditionId() const {
  return m_conditionId;
}

void SupplyConditionThresholdRelationListDataSelectors::cleanConditionId() {
  m_conditionId = 0;
  m_conditionIdIsSet = false;
}

bool SupplyConditionThresholdRelationListDataSelectors::getConditionIdIsSet()
    const {
  return m_conditionIdIsSet;
}

void SupplyConditionThresholdRelationListDataSelectors::setThresholdId(
    const xs_unsignedInt &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const xs_unsignedInt &
SupplyConditionThresholdRelationListDataSelectors::getThresholdId() const {
  return m_thresholdId;
}

void SupplyConditionThresholdRelationListDataSelectors::cleanThresholdId() {
  m_thresholdId = 0;
  m_thresholdIdIsSet = false;
}

bool SupplyConditionThresholdRelationListDataSelectors::getThresholdIdIsSet()
    const {
  return m_thresholdIdIsSet;
}

bool SupplyConditionThresholdRelationListDataSelectors::selects(
    const SupplyConditionThresholdRelationData &data) const {
  if (getConditionIdIsSet() && (!data.getConditionIdIsSet() ||
                                getConditionId() != data.getConditionId())) {
    return false;
  }
  if (getThresholdIdIsSet() &&
      (!data.getThresholdIdIsSet() ||
       std::find(std::begin(data.getThresholdId()),
                 std::end(data.getThresholdId()),
                 getThresholdId()) == std::end(data.getThresholdId()))) {
    return false;
  }
  return true;
}

bool SupplyConditionThresholdRelationListDataSelectors::fromJson(
    KeoJsonValue *json) {
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
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdId", &m_thresholdId)) {
      m_thresholdIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SupplyConditionThresholdRelationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_conditionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("conditionId", m_conditionId);
  }
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdId", m_thresholdId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram